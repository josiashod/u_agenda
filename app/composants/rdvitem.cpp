#include "rdvitem.h"
#include "event.h"

#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QPushButton>
#include <QMessageBox>
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

    connect(btnAffiche, &QPushButton::clicked, this, &RdvItem::onAfficher);
 //   connect(btnModifier, &QPushButton::clicked, this, &RdvItem::onAfficherFormModif);
    connect(btnSupprimer, &QPushButton::clicked, this, &RdvItem::onSupprimer);


    ligne->addWidget(btnAffiche, 0, Qt::AlignRight|Qt::AlignCenter);
    ligne->addWidget(btnModifier, 0, Qt::AlignRight|Qt::AlignCenter);
    ligne->addWidget(btnSupprimer, 0, Qt::AlignRight|Qt::AlignCenter);


    setLayout(ligne);
}

void RdvItem::onAfficher()
{
    auto r{new Event(d_rdv, nullptr, nullptr, this)};
    connect(r, &Event::deleted, this, &RdvItem::onSupprimer);
    r->setModal(true);
    r->show();
}

//void RdvItem::onModifier(rdv ancien, rdv nouveau)
//{
//    emit updated(ancien, nouveau);
//}

void RdvItem::onSupprimer()
{
    auto choice = QMessageBox{QMessageBox::Critical, tr("Suppression"), tr("Voulez-vous vraiment supprimer ce rendez-vous"), QMessageBox::No|QMessageBox::Yes}.exec();

    if (choice == QMessageBox::Yes)
        emit deleted(d_rdv.nom());
}

/* void RdvItem::onAfficherFormModif()
{
    auto form {new RdvForm(d_rdv)};
    form->setModal(true);
    connect(form, &RdvForm::modifiePersonne, this, &RdvForm::onModifier);
    form->exec();
} */
