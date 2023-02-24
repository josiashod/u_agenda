#include "uagenda.h"
#include "contactdialog.h"

#include <QGridLayout>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QPushButton>
#include <QLabel>
#include <QLineEdit>
#include <QCalendarWidget>
#include <QTextCursor>
#include <QFrame>
#include <QMenu>

UAgenda::UAgenda(QWidget *parent)
    : QWidget(parent)
    , d_currentDate{QDate::currentDate()}
{
    creerInterface();
    afficheDate();
    afficheCalendrier();
}

UAgenda::~UAgenda()
{
    delete d_grille;
    delete d_etiquetteDate;
    delete d_calendrierWidget;
}

void UAgenda::creerInterface()
{
    setWindowTitle("UAGENDA");
    setWindowIcon(QIcon(":/logo/"+ QString::number(d_currentDate.day()) +".png"));
    setMinimumSize(1650, 830);

    auto main{new QVBoxLayout(this)};

    // HEADER CONFIGURATON
    auto header{new QHBoxLayout()};
    //header->addWidget(new QLabel("UAGENDA"), 0);

    // NAVBAR
    //auto navbar{new QHBoxLayout()};
    auto searchbar{new QHBoxLayout()};
    auto search_in{new QLineEdit()};
    auto search_button{new QPushButton(QIcon(":/icons/search.svg"), "")};
    auto today_button{new QPushButton(tr("Aujourd'hui"))};
    auto prev_button{new QPushButton(QIcon(":/icons/caret-left.svg"), "")};
    auto next_button{new QPushButton(QIcon(":/icons/caret-right.svg"), "")};

    //header->addLayout(navbar, 2);

    search_in->setStyleSheet("QLineEdit { padding: 2px 3px; }");
    search_in->setPlaceholderText("Chercher un évènement");
    searchbar->addWidget(search_in, 1);
    searchbar->addWidget(search_button, 0);
    searchbar->setSpacing(0);

    d_etiquetteDate = new QLabel{""};
    header->addWidget(d_etiquetteDate, 1);
    header->addSpacing(100);
    header->addWidget(today_button, 0, Qt::AlignRight);
    header->addWidget(prev_button, 0, Qt::AlignRight);
    header->addWidget(next_button, 0, Qt::AlignRight);
    header->addLayout(searchbar, 1);

    connect(today_button, &QPushButton::clicked, this, &UAgenda::onReinitDate);
    connect(prev_button, &QPushButton::clicked, this, &UAgenda::onPrevMonth);
    connect(next_button, &QPushButton::clicked, this, &UAgenda::onNextMonth);

    //navbar->setSpacing(12);
    //navbar->insertStretch( 0, -1 );

    auto content{new QHBoxLayout()};
    auto sidebar{new QVBoxLayout()};


    // SIDEBAR
    auto create_button{new QPushButton(QIcon(":/icons/plus.svg"), tr("Ajouter"))};
    auto menu{ new QMenu()};
    menu->addAction("Ajouter un rendez-vous");
    menu->addAction("Ajouter un contact");
    //menu->setMinimumSize( create_button->width(), menu->height() );
    create_button->setMenu(menu);

    d_calendrierWidget = new QCalendarWidget();
    d_calendrierWidget->setGridVisible(true);
//    auto search_contact{new QHBoxLayout()};
//    auto search_contact_in{new QLineEdit()};
    auto contact_button{new QPushButton(QIcon(":/icons/people.svg"), tr("Mes contacts"))};

    connect(contact_button, &QPushButton::clicked, this, &UAgenda::onAfficheContact);

//    search_contact_in->setStyleSheet("QLineEdit { padding: 2px 3px; }");
//    search_contact_in->setPlaceholderText("Rechercher un contact");
//    search_contact->addWidget(search_contact_in, 1);
//    search_contact->addWidget(contact_button, 0);
//    search_contact->setSpacing(0);

    sidebar->addWidget(create_button, 0, Qt::AlignTop);
    sidebar->addWidget(d_calendrierWidget, 1);
    sidebar->addWidget(contact_button, 1);
    sidebar->setSpacing(20);
    sidebar->insertStretch(-1, 1);

    connect(d_calendrierWidget, &QCalendarWidget::currentPageChanged, this, &UAgenda::onCalendrierChange);

    auto calendrier{new QVBoxLayout()};
    d_grille = new QGridLayout();

    auto vligne {new QFrame{}};
    vligne->setFrameStyle(QFrame::VLine|QFrame::Sunken);

    calendrier->addLayout(d_grille, 1);

    content->addLayout(sidebar, 0);
    content->addSpacing(10);
    content->addWidget(vligne, 0, Qt::AlignRight);
    content->addLayout(calendrier, 1);

    main->addSpacing(13);
    main->addLayout(header, 0);
    auto hligne {new QFrame{}};
    hligne->setFrameStyle(QFrame::HLine|QFrame::Sunken);

    main->addSpacing(13);
    main->addWidget(hligne, 0);
    //main->addSpacing(30);
    main->addLayout(content, 1);
}

void UAgenda::afficheDate()
{
    QLocale locale = QLocale();
    d_etiquetteDate->setText(locale.toString(d_currentDate, "MMMM yyyy").toUpper());
}


void UAgenda::rafraichirGrille()
{
    QLayoutItem *child;
    while ((child = d_grille->takeAt(0)) != nullptr)
    {
        delete child->widget(); // delete the widget
        delete child;   // delete the layout item
    }
}

void UAgenda::afficheCalendrier()
{
    rafraichirGrille();

    int actual_day = 1;
    QDate date{d_currentDate.year(), d_currentDate.month(), actual_day};
    int row = 1;
    d_grille->setRowStretch(row, 1);


    for (int day = 1; day <= 7; ++day)
    {
        d_grille->setColumnStretch(day - 1, 1);
        auto label {new QLabel(QLocale::system().dayName(day).toUpper())};
        label->setStyleSheet("QLabel { font-weight: bold; margin-bottom: 10px }");
        auto hligne {new QFrame{}};
        hligne->setFrameStyle(QFrame::HLine|QFrame::Sunken);

        d_grille->addWidget(label, 0, day - 1, Qt::AlignTop|Qt::AlignHCenter);
        d_grille->addWidget(hligne, 0, day - 1, Qt::AlignBottom);
    }

    d_grille->setVerticalSpacing(10);

    while(date.isValid())
    {
//        #308CC6
        int col = date.dayOfWeek();
        auto button{new QPushButton(QString::number(date.day()))};
        button->setStyleSheet("QPushButton { font-weight: bold; margin-right: 8px;"
            "width: 100%;}");

        auto vligne {new QFrame{}};
        vligne->setFrameStyle(QFrame::VLine|QFrame::Sunken);
        auto hligne {new QFrame{}};
        hligne->setFrameStyle(QFrame::HLine|QFrame::Sunken);

        d_grille->addWidget(vligne, row, col - 1, Qt::AlignRight);
        d_grille->addWidget(button, row, col - 1, Qt::AlignTop);
        d_grille->addWidget(hligne, row, col - 1, Qt::AlignBottom);
        if (col == 7)
        {
            ++row;
            d_grille->setRowStretch(row, 1);
        }
        ++actual_day;
        date.setDate(d_currentDate.year(), d_currentDate.month(), actual_day);
    }
}

void UAgenda::onReinitDate()
{
    d_currentDate = QDate::currentDate();
    d_calendrierWidget->setSelectedDate(d_currentDate);
    afficheDate();
    afficheCalendrier();
}

void UAgenda::onNextMonth()
{
    if (d_currentDate.month() == 12)
        d_currentDate.setDate(d_currentDate.year() + 1, 1, 1);
    else
        d_currentDate.setDate(d_currentDate.year(), d_currentDate.month() + 1, 1);

    d_calendrierWidget->setCurrentPage(d_currentDate.year(), d_currentDate.month());
    afficheDate();
    afficheCalendrier();
}

void UAgenda::onPrevMonth()
{
    if (d_currentDate.month() == 1)
        d_currentDate.setDate(d_currentDate.year() - 1, 12, 31);
    else
        d_currentDate.setDate(d_currentDate.year(), d_currentDate.month() - 1, 1);

    d_calendrierWidget->setCurrentPage(d_currentDate.year(), d_currentDate.month());
    afficheDate();
    afficheCalendrier();
}

void UAgenda::onCalendrierChange(int year, int month)
{
    d_currentDate = QDate{year, month, 1};
    afficheDate();
    afficheCalendrier();
}

void UAgenda::onAfficheContact()
{
    auto contactDialog{new ContactDialog(this)};

    contactDialog->setModal(true);
    contactDialog->show();
}
