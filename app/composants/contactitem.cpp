#include "contactitem.h"
#include "contact.h"
#include "contactform.h"

#include <QLabel>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QPushButton>
#include <QMessageBox>

ContactItem::ContactItem(personne *p, QWidget *parent) :
    QWidget(parent),
    d_personne{p}
{
    creerItem();
}

ContactItem::~ContactItem()
{
}

void ContactItem::creerItem()
{
    auto ligne{new QHBoxLayout()};

    auto info{new QVBoxLayout()};
    info->setSpacing(5);

//    auto email{new QLabel(QString::fromStdString(d_personne->email()))};
//    email->setStyleSheet("QLabel {font-weight: 12; font-size: 14px}");

    auto numero{new QLabel(QString::fromStdString(d_personne->numero()))};
    numero->setStyleSheet("QLabel {font-weight: 4; font-size: 14px}");

    info->addWidget(new QLabel(QString::fromStdString(d_personne->nomComplet())), 0);
    info->addWidget(numero, 0);
//    info->addWidget(email, 0);

    ligne->addLayout(info, 1);

    auto btnAffiche{new QPushButton(QIcon(":/icons/eye.svg"), "")};
    btnAffiche->setAutoDefault(false);

    auto btnModifier{new QPushButton(QIcon(":/icons/pencil-square.svg"), "")};
    btnModifier->setAutoDefault(false);

    auto btnSupprimer{new QPushButton(QIcon(":/icons/trash.svg"), "")};
    btnSupprimer->setAutoDefault(false);

    connect(btnAffiche, &QPushButton::clicked, this, &ContactItem::onAfficher);
    connect(btnModifier, &QPushButton::clicked, this, &ContactItem::onAfficherFormModification);
    connect(btnSupprimer, &QPushButton::clicked, this, &ContactItem::onSupprimer);

    ligne->addWidget(btnAffiche, 0, Qt::AlignRight|Qt::AlignVCenter);
    ligne->addWidget(btnModifier, 0, Qt::AlignRight|Qt::AlignVCenter);
    ligne->addWidget(btnSupprimer, 0, Qt::AlignRight|Qt::AlignVCenter);

    setLayout(ligne);
}

void ContactItem::onAfficher()
{
    auto contact{new Contact(d_personne, this)};
    contact->setModal(true);
    contact->show();
}

void ContactItem::onModifier(personne oldPersonne, personne newPersonne)
{
    emit updated(oldPersonne, newPersonne);
}

void ContactItem::onSupprimer()
{
    auto choice = QMessageBox{QMessageBox::Critical, tr("Suppression"),
        tr("Voulez-vous vraiment supprimer ce contact"), QMessageBox::No|QMessageBox::Yes, this}.exec();

    if (choice == QMessageBox::Yes)
        emit deleted(d_personne->nomComplet());
}

void ContactItem::onAfficherFormModification()
{
    auto form {new ContactForm(d_personne)};
    form->setModal(true);
    connect(form, &ContactForm::updatePersonne, this, &ContactItem::onModifier);
    form->exec();
}
