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
    main->addWidget(new QLabel{QString::fromStdString(d_personne->numero())});
    main->addSpacing(15);

    main->addWidget(new QLabel{"Email:"});
    main->addWidget(new QLabel{QString::fromStdString(d_personne->email())});
    main->addSpacing(15);
}
