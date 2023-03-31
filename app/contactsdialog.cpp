#include "contactsdialog.h"
#include "contactitem.h"
#include "contact.h"


#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QLabel>
#include <QLineEdit>
#include <QPushButton>
#include <QFrame>
#include <QListWidget>
#include <QMessageBox>
#include <QFileDialog>
#include <QStandardPaths>

ContactsDialog::ContactsDialog(LPersonne *contacts, QWidget *parent) :
    QDialog(parent),
    d_order{"ASC"},
    d_contacts_default{contacts},
    d_contacts{contacts}
{
    creerInterface();
    afficherContacts();
    afficherOrderButton();
}

ContactsDialog::~ContactsDialog()
{
}

void ContactsDialog::creerInterface()
{
    setWindowTitle("Mes contacts");
    setMinimumSize(450, 652);

    auto main{new QVBoxLayout(this)};
    auto header{new QHBoxLayout()};
    d_list_contacts = new QListWidget();


    auto titre{new QLabel(tr("Liste des contacts"))};
    auto btnImporter{new QPushButton(QIcon(":/icons/import.svg"), tr("Importer"))};
    auto btnExporter{new QPushButton(QIcon(":/icons/export.svg"), tr("Exporter"))};

    btnImporter->setAutoDefault(false);
    btnExporter->setAutoDefault(false);

    connect(btnExporter, &QPushButton::clicked, this, &ContactsDialog::onExporter);
    connect(btnImporter, &QPushButton::clicked, this, &ContactsDialog::onImporter);

    header->addWidget(titre, 1, Qt::AlignLeft);
    header->addWidget(btnImporter, 0, Qt::AlignRight);
    header->addWidget(btnExporter, 0, Qt::AlignRight);

    main->setSpacing(10);
    //main->insertStretch(-1, 1);
    main->addLayout(header, 0);
    titre->setStyleSheet("QLabel { font-weight: bold; }");

    auto ligne{new QHBoxLayout()};

    d_recherche = new QLineEdit();
    d_recherche->setPlaceholderText("Rechercher un contact");
    ligne->addWidget(d_recherche, 1);

    d_order_btn = new QPushButton("");
    d_order_btn->setAutoDefault(false);
    ligne->addWidget(d_order_btn, 0, Qt::AlignRight);

    main->addLayout(ligne, 0);
    main->addWidget(d_list_contacts, 55);

    connect(d_recherche, &QLineEdit::textEdited, this, &ContactsDialog::onRecherche);
    connect(d_order_btn, &QPushButton::clicked, this, &ContactsDialog::onOrder);
}

void ContactsDialog::afficherContacts()
{
    d_list_contacts->clear();

    if(d_contacts && d_contacts->tete())
    {
        personne *crt;

        if(d_order == "ASC")
            crt = d_contacts->tete();
        else
            crt = d_contacts->queue();

        while(crt)
        {
            auto item{new QListWidgetItem()};
            item->setSizeHint(QSize(0, 60));
            item->setFlags(item->flags() & ~Qt::ItemIsEnabled);

            auto contact{new ContactItem(crt)};

            connect(contact, &ContactItem::updated, this, &ContactsDialog::onModifier);
            connect(contact, &ContactItem::deleted, this, &ContactsDialog::onSupprimer);

            d_list_contacts->addItem(item);
            d_list_contacts->setItemWidget(item, contact);

            if(d_order == "ASC")
                crt = crt->suivant();
            else
                crt = crt->precedent();
        }
    }
    else
    {
        auto item{new QListWidgetItem("Aucun contacts")};
        item->setSizeHint(QSize(0, 60));
        item->setFlags(item->flags() & ~Qt::ItemIsEnabled);
        item->setTextAlignment(Qt::AlignCenter);
        d_list_contacts->addItem(item);
    }
}

void ContactsDialog::afficherOrderButton()
{
    if(d_order == "ASC")
    {
        d_order_btn->setToolTip("DESC");
        d_order_btn->setIcon(QIcon(":/icons/sort-alpha-up.svg"));
    }
    else
    {
        d_order_btn->setToolTip("ASC");
        d_order_btn->setIcon(QIcon(":/icons/sort-alpha-down.svg"));
    }
}

void ContactsDialog::onModifier(personne oldPersonne, personne newPersonne)
{
    personne *pers = d_contacts_default->rechercher(oldPersonne.nomComplet());

    pers->setNom(newPersonne.nom());
    pers->setPrenom(newPersonne.prenom());
    pers->setNumero(newPersonne.numero());
    pers->setEmail(newPersonne.email());

    QMessageBox{QMessageBox::Information, tr("Information"), tr("Le contact a été modifié avec succès")}.exec();

    if(d_recherche->text().length() > 0)
        clear();
    else
        afficherContacts();
}

void ContactsDialog::onSupprimer(std::string nomComplet)
{
    d_contacts_default->supprimer(nomComplet);

//    QMessageBox{QMessageBox::Information, tr("Information"), tr("Le contact a été supprimé avec succès")}.exec();

    if(d_recherche->text().length() > 0)
        clear();
    else
        afficherContacts();
}

void ContactsDialog::clear()
{
    delete d_contacts;
    d_contacts = d_contacts_default;
    d_recherche->setText("");
    afficherContacts();
}

void ContactsDialog::onRecherche(const QString &text)
{
    if(text.length() > 0)
    {
        d_contacts = d_contacts->rechercherPlusieurs(text.toStdString());
        afficherContacts();
    }
    else
    {
        clear();
    }
}

void ContactsDialog::onImporter()
{
    QString directory = QDir::homePath();

    directory += "/" + QStandardPaths::displayName(QStandardPaths::DocumentsLocation) + "/";

    QString fileName = QFileDialog::getOpenFileName(this,
            tr("Importer des contacts"),
            directory,
            tr("VCard files(*.vcf *vcard)"), nullptr, QFileDialog::ReadOnly);

    QFile file(fileName);
    if (!file.open(QIODevice::ReadOnly)) {
        QMessageBox::information(this, tr("Impossible d'ouvrir le fichier"),
            file.errorString());
        return;
    }

    int taille = d_contacts_default->taille();

    d_contacts_default->importerDepuis(fileName.toStdString());

    if(d_recherche->text().length() > 0)
        clear();
    else
    {
        d_contacts = d_contacts_default;
        afficherContacts();
    }

    QString message = QString::number(d_contacts_default->taille() - taille) + " contacts importé avec succès";
    QMessageBox{QMessageBox::Information, tr("Information"), message}.exec();
}

void ContactsDialog::onExporter()
{
    QString directory = QDir::homePath();
    QLocale locale = QLocale();

    directory += "/" + QStandardPaths::displayName(QStandardPaths::DocumentsLocation) + "/";

    QString fileName = QFileDialog::getSaveFileName(this,
            tr("Sauvegarde des contacts"),
            directory + "UAGENDA_CONTACTS_" + locale.toString(QDate::currentDate(), "dd-MM-yyyy") + ".vcf",
            tr("VCard files(*.vcf *vcard)"));

    if (fileName.isEmpty())
        return;
    else
    {
        QFile file(fileName);
        if (!file.open(QIODevice::WriteOnly)) {
            QMessageBox::information(this, tr("Impossible d'ouvrir le fichier"),
                file.errorString());
            return;
        }
        d_contacts->exporterDans(fileName.toStdString());
        QString message = QString::number(d_contacts->taille()) + " contacts exporté avec succès";
        QMessageBox{QMessageBox::Information, tr("Information"), message}.exec();
    }
}

void ContactsDialog::onOrder()
{
    if(d_order == "ASC")
        d_order = "DESC";
    else
        d_order = "ASC";

    afficherOrderButton();
    afficherContacts();
}
