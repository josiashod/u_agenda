#include "rdvform.h"

#include <QMessageBox>
#include <QLineEdit>
#include <QTextEdit>
#include <QLabel>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QPushButton>
#include <QFrame>
#include <QDateTimeEdit>
#include <QGridLayout>

RdvForm::RdvForm(QDate date, LRdv *lrdv, LPersonne *lpersonne, rdv* r, QWidget *parent)
    : QDialog(parent)
    , d_rdv{r}
    , d_lrdv{lrdv}
    , d_lpersonne{lpersonne}
    , d_date{date}
{
    createForm();
}


RdvForm::~RdvForm()
{

}


void RdvForm::createForm()
{
    setWindowTitle("Nouveau Rendez-vous");
    auto mainLayout{new QVBoxLayout(this)};
    setMinimumSize(450,382);

    auto GrilleLayout = new QGridLayout{};
    //auto LayoutGroupe = new QHBoxLayout{};

    //auto LayoutChamp = new QVBoxLayout{};

    d_nom_input = new QLineEdit();
    d_nom_input->setPlaceholderText("JuryS4");
    GrilleLayout->addWidget(d_nom_input,0,1);
    d_nom_erreur = new QLabel{""};
    d_nom_erreur->setStyleSheet("QLabel{ color: #e11d48 }");
    GrilleLayout->addWidget(d_nom_erreur,1,1);

    d_description_input = new QTextEdit();
    d_description_input->setPlaceholderText("Jury L2 MI S4");
    GrilleLayout->addWidget(d_description_input,2,1);
    d_description_erreur = new QLabel{""};
    d_description_erreur->setStyleSheet("QLabel{ color: #e11d48 }");
    GrilleLayout->addWidget(d_description_erreur,3,1);

    d_localisation_input = new QLineEdit();
    GrilleLayout->addWidget(d_localisation_input,4,1);
    d_localisation_input->setPlaceholderText("Salle C0.13");
    d_localisation_erreur = new QLabel{""};
    d_localisation_erreur->setStyleSheet("QLabel{ color: #e11d48 }");
    GrilleLayout->addWidget(d_localisation_erreur,5,1);

    d_date_input = new QDateTimeEdit();
    d_date_input->setCalendarPopup(true);
    d_date_input->setDisplayFormat("dd/MM/yyyy");
    d_date_input->setDate(d_date);
    GrilleLayout->addWidget(d_date_input,6,1);
    d_date_erreur = new QLabel{""};
    d_date_erreur->setStyleSheet("QLabel{ color: #e11d48 }");
    GrilleLayout->addWidget(d_date_erreur,7,1);

    d_hd_input = new QDateTimeEdit();
    d_hd_input->setDisplayFormat("HH:mm");
    d_hd_input->setTime(QTime::currentTime());
    GrilleLayout->addWidget(d_hd_input,8,1);
    d_hd_erreur = new QLabel{""};
    d_hd_erreur->setStyleSheet("QLabel{ color: #e11d48 }");
    GrilleLayout->addWidget(d_hd_erreur,9,1);

    d_hf_input = new QDateTimeEdit();
    d_hf_input->setDisplayFormat("HH:mm");
    d_hf_input->setTime(QTime::currentTime().addSecs(3600));
    GrilleLayout->addWidget(d_hf_input,10,1);
    d_hf_erreur = new QLabel{""};
    d_hf_erreur->setStyleSheet("QLabel{ color: #e11d48 }");
    GrilleLayout->addWidget(d_hf_erreur,11,1);

    d_participants_input = new CheckBoxList();
    d_participants_input->addItem("Josias");
    GrilleLayout->addWidget(d_participants_input,12,1);
    d_participants_erreur = new QLabel{""};
    d_participants_erreur->setStyleSheet("QLabel{ color: #e11d48 }");
    GrilleLayout->addWidget(d_participants_erreur,13,1);



    //auto LayoutIntitule = new QVBoxLayout{};
    GrilleLayout->addWidget(new QLabel{tr("Nom")},0,0);
    GrilleLayout->addWidget(new QLabel{tr("Description")},2,0);
    GrilleLayout->addWidget(new QLabel{tr("Localisation")},4,0);
    GrilleLayout->addWidget(new QLabel{tr("Date")},6,0);
    GrilleLayout->addWidget(new QLabel{tr("Heure de début")},8,0);
    GrilleLayout->addWidget(new QLabel{tr("Heure de fin")},10,0);
    GrilleLayout->addWidget(new QLabel{tr("Participants")},12,0);


    //LayoutGroupe->addLayout(LayoutIntitule);
    //LayoutGroupe->addLayout(LayoutChamp);
    mainLayout->addLayout(GrilleLayout);


    auto ligne = new QFrame{};
    ligne->setFrameStyle(QFrame::HLine|QFrame::Sunken);
    mainLayout->addWidget(ligne);

    auto boiteBoutons = new QHBoxLayout{};
    auto ajout = new QPushButton{"Ajouter"};
    boiteBoutons->addWidget(ajout);
    auto reset = new QPushButton{"Reinitialiser"};
    boiteBoutons->addWidget(reset);
    mainLayout->addLayout(boiteBoutons);

    setLayout(mainLayout);

    connect(reset,&QPushButton::clicked,this,&RdvForm::onReinitialise);
}


bool RdvForm::verifieForm()
{
    return true;
//    return (d_nom_input->text().length() >= 2 && d_description_input->text().length() >= 3 && d_localisation_input->text().length() >= 2);
}

void RdvForm::afficheErreur()
{
    if(!d_nom_input->text().length())
        d_nom_erreur->setText("Veuillez entrer un nom");
    else if(d_nom_input->text().length() <= 1)
        d_nom_erreur->setText("Le nom doit comporter au moins 2 caractères");
    else
        d_nom_erreur->setText("");

//    if(!d_description_input->text().length())
//        d_description_erreur->setText("Veuillez entrer une description");
//    else if(d_description_input->text().length() <= 2)
//        d_description_erreur->setText("La description doit comporter au moins 3 caractères");
//    else
//        d_description_erreur->setText("");

    if(!d_localisation_input->text().length())
        d_localisation_erreur->setText("Veuillez entrer une localisation");
    else if(d_localisation_input->text().length() <= 1)
        d_localisation_erreur->setText("La localisation doit comporter au moins 2 caractères");
    else
        d_localisation_erreur->setText("");

}

void RdvForm::onReinitialise()
{
    d_nom_input->setText("");
    d_description_input->setText("");
    d_localisation_input->setText("");
    d_date_input->setDate(d_date);
    d_hd_input->setTime(QTime::currentTime());
    d_hf_input->setTime(QTime::currentTime().addSecs(3600));
    d_participants_input->ResetSelection();


}

