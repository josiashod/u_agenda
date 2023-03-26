#include "uagenda.h"
#include "rdvdialog.h"
#include "contactsdialog.h"
#include "contactform.h"

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
#include <QFontDatabase>
#include <QApplication>
#include <QFileDialog>
#include <QMessageBox>
#include <QStandardPaths>

UAgenda::UAgenda(QWidget *parent)
    : QWidget(parent)
    , d_currentDate{QDate::currentDate()}
    , d_contacts{nullptr}
{
    loadData();
    creerInterface();
    afficheDate();
    afficheCalendrier();
}

UAgenda::~UAgenda()
{
    delete d_grille;
    delete d_etiquetteDate;
    delete d_calendrierWidget;
    delete d_contacts;
}

void UAgenda::loadData()
{
    d_contacts = new LPersonne();
    d_contacts->ajouter("KAGEYAMA", "Tobio", "0609090909", "kageyama.tobio@uha.fr");
    d_contacts->ajouter("SHOYO", "Hinata", "0609090909", "hinata.shoyo@uha.fr");
    d_contacts->ajouter("ADAM", "Sandler", "0609090909", "sandler.adam@uha.fr");
}

void UAgenda::setPolice()
{

    // Mise en place de la police
    int id = QFontDatabase::addApplicationFont(":/fonts/BarlowCondensed-Regular.ttf");
    QString family = QFontDatabase::applicationFontFamilies(id).at(0);
    auto barlowCondensed{QFont(family)};
//    barlowCondensed.setPixelSize(15);

    QApplication::setFont(barlowCondensed);
}

void UAgenda::creerInterface()
{
    setWindowTitle("UAGENDA");
    setWindowIcon(QIcon(":/logo/"+ QString::number(d_currentDate.day()) +".png"));
    setMinimumSize(1650, 830);
    setPolice();

    auto main{new QVBoxLayout(this)};

    // HEADER CONFIGURATON
    auto header{new QHBoxLayout()};
    auto searchbar{new QHBoxLayout()};
    auto search_in{new QLineEdit()};
    auto search_button{new QPushButton(QIcon(":/icons/search.svg"), "")};
    auto today_button{new QPushButton(tr("Aujourd'hui"))};
    auto prev_button{new QPushButton(QIcon(":/icons/caret-left.svg"), "")};
    auto next_button{new QPushButton(QIcon(":/icons/caret-right.svg"), "")};
    auto export_button{new QPushButton(QIcon(":/icons/export.svg"), tr("Exporter"))};
    export_button->setToolTip(tr("Exporter l'agenda"));

    search_button->setStyleSheet("QPushButton { padding: 4.5px 3px; }");
    search_in->setStyleSheet("QLineEdit { padding: 2px 3px; }");
    search_in->setPlaceholderText("Chercher un évènement");
    searchbar->addWidget(search_in, 1);
    searchbar->addWidget(search_button, 0, Qt::AlignCenter);
    searchbar->setSpacing(0);

    connect(export_button, &QPushButton::clicked, this, &UAgenda::onExportRdv);
    connect(search_button, &QPushButton::clicked, this, &UAgenda::onRechercheRdv);

    d_etiquetteDate = new QLabel{""};
    header->addWidget(d_etiquetteDate, 1);
    header->addSpacing(100);
    header->addWidget(today_button, 0, Qt::AlignRight);
    header->addWidget(prev_button, 0, Qt::AlignRight);
    header->addWidget(next_button, 0, Qt::AlignRight);
    header->addLayout(searchbar, 1);
    header->addWidget(export_button, 0, Qt::AlignRight);

    connect(today_button, &QPushButton::clicked, this, &UAgenda::onReinitDate);
    connect(prev_button, &QPushButton::clicked, this, &UAgenda::onPrevMonth);
    connect(next_button, &QPushButton::clicked, this, &UAgenda::onNextMonth);


    auto content{new QHBoxLayout()};
    auto sidebar{new QVBoxLayout()};


    // SIDEBAR
    auto create_button{new QPushButton(QIcon(":/icons/plus.svg"), tr("Ajouter"))};
    auto menu{ new QMenu()};
    menu->addAction("Ajouter un rendez-vous");
    menu->addAction("Ajouter un contact");
    //menu->setMinimumSize( create_button->width(), menu->height() );
    create_button->setMenu(menu);

    connect(menu, &QMenu::triggered, this, &UAgenda::onAjouter);

    d_calendrierWidget = new QCalendarWidget();
    d_calendrierWidget->setGridVisible(true);
    auto contact_button{new QPushButton(QIcon(":/icons/people.svg"), tr("Mes contacts"))};

    connect(contact_button, &QPushButton::clicked, this, &UAgenda::onAfficheContact);

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

    content->addLayout(sidebar, 1);
    content->addSpacing(10);
    content->addWidget(vligne, 0, Qt::AlignRight);
    content->addLayout(calendrier, 3);

    main->addSpacing(13);
    main->addLayout(header, 0);
    auto hligne {new QFrame{}};
    hligne->setFrameStyle(QFrame::HLine|QFrame::Sunken);

    main->addSpacing(13);
    main->addWidget(hligne, 0);
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

        connect(button, &QPushButton::clicked, this, &UAgenda::onAfficheRdvsJour);

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
    auto contacts{new ContactsDialog(d_contacts, this)};

    contacts->setModal(true);
    contacts->show();
}

void UAgenda::onRechercheRdv()
{
    auto rdvDialog{new RdvDialog(this, "Resultat de \"Test\"")};

    rdvDialog->setModal(true);
    rdvDialog->show();
}

void UAgenda::onAfficheRdvsJour()
{
    auto button{(QPushButton*)sender()};
    QString titre = "Rendez-vous du ";
    int jour = (button->text()).toInt();
    int mois = d_currentDate.month();
    int annee = d_currentDate.year();

    titre += ((jour < 10) ? "0" : "") + QString::number(jour) + "/";
    titre += ((mois < 10) ? "0" : "") + QString::number(mois) + "/";
    titre += QString::number(annee);

    auto rdvDialog{new RdvDialog(this, titre)};

    rdvDialog->setModal(true);
    rdvDialog->show();
}

void UAgenda::onExportRdv()
{
    QString directory = QDir::homePath();
    QLocale locale = QLocale();

    directory += "/" + QStandardPaths::displayName(QStandardPaths::DocumentsLocation) + "/";

    QString fileName = QFileDialog::getSaveFileName(this,
            tr("Sauvegarde de l'agenda"),
            directory + "UAGENDA_" + locale.toString(QDate::currentDate(), "dd-MM-yyyy") + ".ics",
            tr("iCalendar files(*.ics *ifb *.iCal *.icalendar)"));

    if (fileName.isEmpty())
            return;
    else
    {
        QFile file(fileName);
        if (!file.open(QIODevice::WriteOnly)) {
            QMessageBox::information(this, tr("Impossible d'ouvrir le fichier"),
                file.errorString());
            return;
        }
//        QDataStream out(&file);
//            out.setVersion(QDataStream::Qt_4_5);
//            out << contacts;
    }
}

void UAgenda::onAjouter(QAction *action)
{
    if(action->text() == "Ajouter un rendez-vous")
    {}
    else
    {
        auto form{new ContactForm()};
        form->setModal(true);
        connect(form, &ContactForm::addPersonne, this, &UAgenda::onAjouterContact);
        form->exec();
    }
}

void UAgenda::onAjouterContact(personne p)
{
    d_contacts->ajouter(p);
    QMessageBox{QMessageBox::Information, tr("Information"), tr("Le contact a été ajouté avec succès")}.exec();
}
