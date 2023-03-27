#include "rdvitem.h"

#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QPushButton>
#include <QLabel>
#include <QDate>

RdvItem::RdvItem(const rdv& r, QWidget *parent) :
    QWidget(parent)
  , d_rdv{r}
{
    creerInterface();
}

RdvItem::~RdvItem()
{
}

void RdvItem::creerInterface()
{
    auto ligne{new QHBoxLayout()};

    auto info{new QVBoxLayout()};
    info->setSpacing(5);

    QDate date{static_cast<int>(d_rdv.day().annee()),
        static_cast<int>(d_rdv.day().mois()), static_cast<int>(d_rdv.day().jour())};

    QLocale locale = QLocale();
    QString details = locale.toString(date, "dd MMMM yyyy");
    details += " de " + QString::fromStdString(d_rdv.h_debut().toString());
    details += " à " + QString::fromStdString(d_rdv.h_fin().toString());

    auto detailsLabel{new QLabel(details)};
    detailsLabel->setStyleSheet("QLabel {font-weight: 4; font-size: 13px}");

    info->addWidget(new QLabel(QString::fromStdString(d_rdv.nom())), 0);
    info->addWidget(detailsLabel, 0);

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
