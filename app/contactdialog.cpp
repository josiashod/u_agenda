#include "contactdialog.h"

#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QLabel>
#include <QLineEdit>
#include <QPushButton>
#include <QFrame>
#include <QListWidget>


Contact::Contact(QWidget *parent, QString nomComplet, QString numero) :
    QWidget(parent)
  , d_nomComplet{nomComplet}
  , d_numero{numero}
{
    creerInterface();
}

Contact::~Contact()
{
}

void Contact::creerInterface()
{
    auto ligne{new QHBoxLayout()};

    auto info{new QVBoxLayout()};
    info->setSpacing(5);

    /*auto email{new QLabel(d_email)};
    email->setStyleSheet("QLabel {font-weight: 12; font-size: 14px}");*/

    auto numero{new QLabel(d_numero)};
    numero->setStyleSheet("QLabel {font-weight: 4; font-size: 13px}");

    info->addWidget(new QLabel(d_nomComplet), 0);
    info->addWidget(numero, 0);
//    info->addWidget(email, 0);

    ligne->addLayout(info, 1);

    auto btnAffiche{new QPushButton(QIcon(":/icons/eye.svg"), "")};
    btnAffiche->setAutoDefault(false);

    auto btnModifier{new QPushButton(QIcon(":/icons/pencil-square.svg"), "")};
    btnModifier->setAutoDefault(false);

    auto btnSupprimer{new QPushButton(QIcon(":/icons/trash.svg"), "")};
    btnSupprimer->setAutoDefault(false);

    ligne->addWidget(btnAffiche, 0, Qt::AlignRight|Qt::AlignCenter);
    ligne->addWidget(btnModifier, 0, Qt::AlignRight|Qt::AlignCenter);
    ligne->addWidget(btnSupprimer, 0, Qt::AlignRight|Qt::AlignCenter);

    setLayout(ligne);
}


ContactDialog::ContactDialog(QWidget *parent) :
    QDialog(parent)
{
    creerInterface();
}

ContactDialog::~ContactDialog()
{
}

void ContactDialog::creerInterface()
{
    setWindowTitle("Mes contacts");
    setMinimumSize(450, 652);

    auto main{new QVBoxLayout(this)};
    auto header{new QHBoxLayout()};
    auto contacts{new QListWidget()};


    auto titre{new QLabel(tr("Liste des contacts"))};
    auto btnImporter{new QPushButton(QIcon(":/icons/import.svg"), tr("Importer"))};
    auto btnExporter{new QPushButton(QIcon(":/icons/export.svg"), tr("Exporter"))};

    btnImporter->setAutoDefault(false);
    btnExporter->setAutoDefault(false);

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
    main->addWidget(contacts, 55);

    for(int i = 0; i < 10; i++)
    {
        auto item{new QListWidgetItem()};
        item->setSizeHint(QSize(0, 60));
        item->setFlags(item->flags() & ~Qt::ItemIsEnabled);

        auto contact{new Contact{nullptr, "Contact N°" + QString::number(i), "+33 45 45 45 45"}};

        contacts->addItem(item);
        contacts->setItemWidget(item, contact);
    }
}
