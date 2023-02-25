#include "rdvdialog.h"

#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QLabel>
#include <QLineEdit>
#include <QPushButton>
#include <QFrame>
#include <QListWidget>


Rdv::Rdv(QWidget *parent, QString nomComplet) :
    QWidget(parent)
  , d_nomComplet{nomComplet}
{
    creerInterface();
}

Rdv::~Rdv()
{
}

void Rdv::creerInterface()
{
    auto ligne{new QHBoxLayout()};

    auto info{new QVBoxLayout()};
    info->setSpacing(5);

    auto details{new QLabel("27 Férvier 2023 de 18h30 à 20h00")};
    details->setStyleSheet("QLabel {font-weight: 4; font-size: 13px}");

    info->addWidget(new QLabel(d_nomComplet), 0);
    info->addWidget(details, 0);

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


RdvDialog::RdvDialog(QWidget *parent, QString titre) :
    QDialog(parent)
  , d_titre{titre}
{
    creerInterface();
}

RdvDialog::~RdvDialog()
{
}

void RdvDialog::creerInterface()
{
    setWindowTitle(d_titre);
    setMinimumSize(450, 652);

    auto main{new QVBoxLayout(this)};
    auto rdvs{new QListWidget()};

    auto btnExporter{new QPushButton(QIcon(":/icons/export.svg"), tr("Exporter"))};
    btnExporter->setAutoDefault(false);

    main->addWidget(btnExporter, 0, Qt::AlignRight);

    main->addWidget(rdvs, 1);

    for(int i = 0; i < 10; i++)
    {
        auto item{new QListWidgetItem()};
        item->setSizeHint(QSize(0, 60));
        item->setFlags(item->flags() & ~Qt::ItemIsEnabled);

        auto rdv{new Rdv{nullptr, "Rdv N°" + QString::number(i)}};

        rdvs->addItem(item);
        rdvs->setItemWidget(item, rdv);
    }
}
