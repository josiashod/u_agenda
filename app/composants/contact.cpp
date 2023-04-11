#include "contact.h"
#include "rdvdialog.h"

#include <QVBoxLayout>
#include <QLabel>
#include <QPushButton>

Contact::Contact(personne* p, LRdv *lrdv, QWidget *parent) :
    QDialog(parent),
    d_personne{p},
    d_lrdv{lrdv}
{
    creerVue();
}

Contact::~Contact()
{
    if(d_lrdv);
        delete d_lrdv;
}

void Contact::creerVue()
{
    setWindowTitle(QString::fromStdString(d_personne->nomComplet()));
    setMinimumSize(300, 202);

    auto main{new QVBoxLayout(this)};

    main->addWidget(new QLabel{"Nom:"});
    main->addWidget(new QLabel{QString::fromStdString(d_personne->nom())});
    main->addSpacing(15);

    main->addWidget(new QLabel{"Prénom:"});
    main->addWidget(new QLabel{QString::fromStdString(d_personne->prenom())});
    main->addSpacing(15);

    main->addWidget(new QLabel{"Numéro:"});
    auto numero{new QLabel{QString::fromStdString(d_personne->numero())}};
    numero->setTextInteractionFlags(Qt::TextSelectableByMouse);
    main->addWidget(numero);
    main->addSpacing(15);

    main->addWidget(new QLabel{"Email:"});
    auto email{new QLabel{QString::fromStdString(d_personne->email())}};
    email->setTextInteractionFlags(Qt::TextSelectableByMouse);
    main->addWidget(email);
    main->addSpacing(15);

    auto btn{new QPushButton{"Voir les rendez-vous"}};
    connect(btn, &QPushButton::clicked, this, &Contact::onAfficheRdv);
    main->addWidget(btn, 1, Qt::AlignBottom);
}

void Contact::onAfficheRdv()
{
    auto texte = "Rendez-vous de " + QString::fromStdString(d_personne->nomComplet());
    auto rdvDialog{new RdvDialog(texte, d_lrdv, nullptr, nullptr, this)};

    rdvDialog->setModal(true);
    rdvDialog->show();
}
