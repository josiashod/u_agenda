#include "contact.h"

#include <QVBoxLayout>
#include <QLabel>

Contact::Contact(personne* p, QWidget *parent) :
    QDialog(parent),
    d_personne{p}
{
    creerVue();
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
}
