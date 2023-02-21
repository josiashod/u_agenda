#include "uagenda.h"

#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QPushButton>
#include <QLabel>
#include <QLineEdit>
#include <QCalendarWidget>

UAgenda::UAgenda(QWidget *parent)
    : QWidget(parent)
{
    creerInterface();
}

UAgenda::~UAgenda()
{
}

void UAgenda::creerInterface()
{
    setWindowTitle("UAGENDA");
    auto main{new QVBoxLayout(this)};

    // HEADER CONFIGURATON
    auto header{new QHBoxLayout()};
    header->addWidget(new QLabel("UAGENDA"), 0);

    // NAVBAR
    auto navbar{new QHBoxLayout()};
    auto searchbar{new QHBoxLayout()};
    auto search_in{new QLineEdit()};
    auto search_button{new QPushButton(tr("chercher"))};
    auto today_button{new QPushButton(tr("Aujourd'hui"))};
    auto prev_button{new QPushButton(tr("<"))};
    auto mode_button{new QPushButton(tr("Mois"))};
    auto next_button{new QPushButton(tr(">"))};

    header->addLayout(navbar, 2);

    search_in->setStyleSheet("QLineEdit { padding: 2px 3px; }");
    search_in->setPlaceholderText("Chercher un évènement");
    searchbar->addWidget(search_in, 1);
    searchbar->addWidget(search_button, 0);
    searchbar->setSpacing(0);

    navbar->addWidget(today_button, 0, Qt::AlignRight);
    navbar->addWidget(prev_button, 0, Qt::AlignRight);
    navbar->addWidget(mode_button, 0, Qt::AlignRight);
    navbar->addWidget(next_button, 0, Qt::AlignRight);
    navbar->addLayout(searchbar, 0);
    navbar->addWidget(new QLabel("17 Février 2023"), 0, Qt::AlignRight);
    navbar->setSpacing(12);
    navbar->insertStretch( 0, -1 );

    auto content{new QHBoxLayout()};
    auto sidebar{new QVBoxLayout()};


    // SIDEBAR
    auto create_button{new QPushButton(tr("+ Créer"))};
    auto calendrier{new QCalendarWidget()};
    auto search_contact{new QHBoxLayout()};
    auto search_contact_in{new QLineEdit()};
    auto search_contact_button{new QPushButton(tr("chercher"))};

    search_contact_in->setStyleSheet("QLineEdit { padding: 2px 3px; }");
    search_contact_in->setPlaceholderText("Rechercher un contact");
    search_contact->addWidget(search_contact_in, 1);
    search_contact->addWidget(search_contact_button, 0);
    search_contact->setSpacing(0);

    sidebar->addSpacing(30);
    sidebar->addWidget(create_button, 0, Qt::AlignTop);
    sidebar->addWidget(calendrier, 0, Qt::AlignTop);
    //sidebar->addWidget(new QLabel("UAGENDA"), 1);
    sidebar->addLayout(search_contact, 1);
//    sidebar->setContentsMargins(10, 20 , 0, 10);
    sidebar->setSpacing(20);
    sidebar->insertStretch(-1, 1 );
    //
    //sidebar->addStretch(1);


    auto body{new QVBoxLayout()};
    content->addLayout(sidebar, 0);
    content->addLayout(body, 2);

    main->addLayout(header, 0);
    main->addLayout(content, 1);
}
