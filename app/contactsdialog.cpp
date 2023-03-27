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
    d_contacts_default{contacts},
    d_contacts{contacts}
{
    creerInterface();
    afficherContacts();
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

    d_recherche = new QLineEdit();
    d_recherche->setPlaceholderText("Rechercher un contact");
    main->addWidget(d_recherche, 0, Qt::AlignTop);
    main->addWidget(d_list_contacts, 55);

    connect(d_recherche, &QLineEdit::textEdited, this, &ContactsDialog::onRecherche);
}

void ContactsDialog::afficherContacts()
{
    d_list_contacts->clear();

    if(d_contacts && d_contacts->tete())
    {
        personne *crt = d_contacts->tete();

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
            crt = crt->suivant();
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
