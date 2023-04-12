#include "rdvform.h"

#include <QMessageBox>
#include <QLineEdit>
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
{
    createForm();
    afficheDate(date);
    chargementCheckBoxList();
    remplirFormulaire();
}


RdvForm::~RdvForm()
{}


void RdvForm::createForm()
{
    if (!d_rdv)
        setWindowTitle("Nouveau Rendez-vous");
    else
        setWindowTitle("Modifier "+ QString::fromStdString(d_rdv->nom()));

    auto mainLayout{new QVBoxLayout(this)};
    setMinimumSize(450,382);

    auto GrilleLayout = new QGridLayout{};

    d_nom_input = new QLineEdit();
    d_nom_input->setPlaceholderText("Nom du rendez-vous");
    GrilleLayout->addWidget(d_nom_input, 0, 1);
    d_nom_erreur = new QLabel{""};
    d_nom_erreur->setStyleSheet("QLabel{ color: #e11d48 }");
    GrilleLayout->addWidget(d_nom_erreur, 1, 1);

    d_description_input = new QLineEdit();
    d_description_input->setPlaceholderText("Description du rendez-vous");
    GrilleLayout->addWidget(d_description_input, 2, 1);
    d_description_erreur = new QLabel{""};
    d_description_erreur->setStyleSheet("QLabel{ color: #e11d48 }");
    GrilleLayout->addWidget(d_description_erreur, 3, 1);

    d_localisation_input = new QLineEdit();
    GrilleLayout->addWidget(d_localisation_input, 4, 1);
    d_localisation_input->setPlaceholderText("Salle C0.13");
    d_localisation_erreur = new QLabel{""};
    d_localisation_erreur->setStyleSheet("QLabel{ color: #e11d48 }");
    GrilleLayout->addWidget(d_localisation_erreur, 5, 1);

    d_date_input = new QDateTimeEdit();
    d_date_input->setCalendarPopup(true);
    d_date_input->setDisplayFormat("dd/MM/yyyy");
    GrilleLayout->addWidget(d_date_input, 6, 1);

    d_hd_input = new QDateTimeEdit();
    d_hd_input->setDisplayFormat("HH:mm");
    d_hd_input->setTime(QTime::currentTime());
    GrilleLayout->addWidget(d_hd_input, 7, 1);

    d_hf_input = new QDateTimeEdit();
    d_hf_input->setDisplayFormat("HH:mm");
    d_hf_input->setTime(QTime::currentTime().addSecs(1800));
    GrilleLayout->addWidget(d_hf_input, 8, 1);

    connect(d_date_input, &QDateTimeEdit::dateChanged, this, &RdvForm::onDateChange);
    connect(d_hd_input, &QDateTimeEdit::timeChanged, this, &RdvForm::onHDChange);
    connect(d_hf_input, &QDateTimeEdit::timeChanged, this, &RdvForm::onHFChange);

    d_participants_input = new CheckBoxList();
    GrilleLayout->addWidget(d_participants_input, 9, 1);
    d_participants_erreur = new QLabel{""};
    d_participants_erreur->setStyleSheet("QLabel{ color: #e11d48 }");
    GrilleLayout->addWidget(d_participants_erreur, 10, 1);
    //connect(d_participants_input, &CheckBoxList::selectionChanged, this, &RdvForm::onParticipantChange);


    GrilleLayout->addWidget(new QLabel{tr("Nom")}, 0, 0);
    GrilleLayout->addWidget(new QLabel{tr("Description")}, 2, 0);
    GrilleLayout->addWidget(new QLabel{tr("Localisation")}, 4, 0);
    GrilleLayout->addWidget(new QLabel{tr("Date")}, 6, 0);
    GrilleLayout->addWidget(new QLabel{tr("Heure de début")}, 7, 0);
    GrilleLayout->addWidget(new QLabel{tr("Heure de fin")}, 8, 0);
    GrilleLayout->addWidget(new QLabel{tr("Participants")}, 9, 0);
    GrilleLayout->setVerticalSpacing(5);

    mainLayout->addLayout(GrilleLayout);


    auto ligne = new QFrame{};
    ligne->setFrameStyle(QFrame::HLine|QFrame::Sunken);
    mainLayout->addWidget(ligne);

//    auto boiteBoutons = new QHBoxLayout{};
    auto btn = new QPushButton{"Ajouter"};
    btn->setAutoDefault(false);

    if(!d_rdv)
    {
        btn->setText("Ajouter");
        btn->setStyleSheet("QPushButton{background-color: #0D9488}");
        connect(btn, &QPushButton::clicked, this, &RdvForm::onAjouter);
    }
    else
    {
        btn->setText("Enregistrer");
        btn->setStyleSheet("QPushButton{background-color: #fb923c}");
        connect(btn, &QPushButton::clicked, this, &RdvForm::onModifier);
    }

//    boiteBoutons->addWidget(btn);

//    auto reset = new QPushButton{"Reinitialiser"};
//    reset->setAutoDefault(false);
//    boiteBoutons->addWidget(reset);
    mainLayout->addWidget(btn);

    setLayout(mainLayout);
}

void RdvForm::afficheDate(QDate d)
{
    d_date_input->setDate(d);
}

void RdvForm::afficheHD(QTime time)
{
    d_hd_input->setTime(time);
}

void RdvForm::afficheHF(QTime time)
{
    d_hf_input->setTime(time);
}

void RdvForm::onDateChange(QDate d)
{
    afficheDate(d);
}

void RdvForm::onHDChange(QTime time)
{
    if(d_hf_input->time() <= time)
    {
        QTime nt{time};
        afficheHF(nt.addSecs(1800));
    }
    afficheHD(time);
}

void RdvForm::onHFChange(QTime time)
{
    if(time <= d_hd_input->time())
    {
        QTime nt{time};
        afficheHD(nt.addSecs(-1800));
    }
    afficheHF(time);
}

bool RdvForm::verifieForm()
{
    if (d_nom_input->text().length() <= 2)
        return false;
    if (!d_participants_input->currentText().length())
        return false;
    if (d_description_input->text().length() <= 2)
        return false;
    if (d_localisation_input->text().length() <= 2)
        return false;
    return (true && !overlapRDV());
}

void RdvForm::remplirFormulaire()
{
    if(d_rdv)
    {
        d_nom_input->setText(QString::fromStdString(d_rdv->nom()));
        d_description_input->setText(QString::fromStdString(d_rdv->description()));
        d_localisation_input->setText(QString::fromStdString(d_rdv->localisation()));
        d_date_input->setDate(QDate(d_rdv->day().annee(), d_rdv->day().mois(), d_rdv->day().jour()));
        d_hd_input->setTime(QTime(d_rdv->h_debut().h(), d_rdv->h_debut().mn()));
        d_hf_input->setTime(QTime(d_rdv->h_fin().h(), d_rdv->h_fin().mn()));
        if(d_rdv->participants())
        {
            QStringList participants;
            personne* crt = d_rdv->participants()->tete();
            while(crt)
            {
                participants.append(QString::fromStdString(crt->nomComplet()));
                crt = crt->suivant();
            }

            d_participants_input->setCurrentText(participants);
        }
    }
}

void RdvForm::chargementCheckBoxList()
{
    if(d_lpersonne && d_lpersonne->tete())
    {
        personne *crt = d_lpersonne->tete();
        while(crt)
        {
            d_participants_input->addItem(QString::fromStdString(crt->nomComplet()));
            crt = crt->suivant();
        }
    }
}

void RdvForm::afficheErreur()
{
    if(!d_nom_input->text().length())
        d_nom_erreur->setText("Veuillez entrer un nom");
    else if(d_nom_input->text().length() <= 2)
        d_nom_erreur->setText("Le nom doit comporter au moins 3 caractères");
    else
        d_nom_erreur->setText("");

    if(!d_description_input->text().length())
        d_description_erreur->setText("Veuillez entrer une description");
    else if(d_description_input->text().length() <= 2)
        d_description_erreur->setText("La description doit comporter au moins 3 caractères");
    else
        d_description_erreur->setText("");

    if(!d_localisation_input->text().length())
        d_localisation_erreur->setText("Veuillez entrer un lieu");
    else if(d_nom_input->text().length() <= 2)
        d_localisation_erreur->setText("Le lieu doit comporter au moins 3 caractères");
    else
        d_localisation_erreur->setText("");

    if (!d_participants_input->currentText().length())
        d_participants_erreur->setText("Veuillez ajouter au moins 1 participant");
    else
        d_participants_erreur->setText("");
}

//void RdvForm::onReinitialise()
//{
//    d_nom_input->setText("");
//    d_description_input->setText("");
//    d_localisation_input->setText("");
//    d_date_input->seheure_debutate(d_date);
//    d_hd_input->setTime(QTime::currentTime());
//    d_hf_input->setTime(QTime::currentTime().addSecs(3600));
//    d_participants_input->ResetSelection();
//}

bool RdvForm::overlapRDV()
{
    bool overlap = false;
    int i = 0;

    QStringList participant = d_participants_input->currentText();
    QString texte = "";
    auto qdate = d_date_input->date();
    auto hd = d_hd_input->time();
    auto hf = d_hf_input->time();
    date d{static_cast<unsigned int>(qdate.day()),
    static_cast<unsigned int>(qdate.month()), static_cast<unsigned int>(qdate.year())};

    auto heure_debut{heure{static_cast<unsigned int>(hd.hour()), static_cast<unsigned int>(hd.minute())}};
    auto heure_fin{heure{static_cast<unsigned int>(hf.hour()), static_cast<unsigned int>(hf.minute())}};

    if(d_rdv && d_rdv->participants())
    {
        personne *crt = d_rdv->participants()->tete();
        while(crt)
        {
            int i = participant.indexOf(QString::fromStdString(crt->nomComplet()));
            if(i > -1)
                participant.removeAt(i);
            crt = crt->suivant();
        }
    }

    if(participant.length() || (d_rdv && (heure_debut != d_rdv->h_debut() || heure_fin != d_rdv->h_fin() || d != d_rdv->day())))
    {
        participant = (participant.length() == 0) ? d_participants_input->currentText() : participant;
        for(auto personne: participant)
        {
            auto p = d_lpersonne->rechercher(personne.toStdString());

            if(p)
            {
                if(d_lrdv->overlap(*p, d, heure_debut, heure_fin))
                {
                    overlap = true;
                    texte += (i ? ", " : "") + personne;
                    i++;
                }
            }
        }
    }

    if(overlap && i)
    {
        texte += ((i == 1) ? " a" : " ont");
        texte += " déjà un autre rendez-vous à cette heure";
        QMessageBox{QMessageBox::Critical, tr("Erreur"), texte , QMessageBox::Ok, this}.exec();
    }

    return overlap;
}

void RdvForm::onAjouter()
{
    afficheErreur();
    if(verifieForm())
    {
        auto qdate = d_date_input->date();
        auto hd = d_hd_input->time();
        auto hf = d_hf_input->time();

        //convertion en date et heure;
        date d{static_cast<unsigned int>(qdate.day()),
        static_cast<unsigned int>(qdate.month()), static_cast<unsigned int>(qdate.year())};
        auto heure_debut{heure{static_cast<unsigned int>(hd.hour()), static_cast<unsigned int>(hd.minute())}};
        auto heure_fin{heure{static_cast<unsigned int>(hf.hour()), static_cast<unsigned int>(hf.minute())}};

        std::string nom = d_nom_input->text().toStdString();
        std::string description = d_description_input->text().toStdString();
        std::string localisation = d_localisation_input->text().toStdString();

        rdv r{nom, d, heure_debut, heure_fin, description, localisation};

        for(auto personne: d_participants_input->currentText())
        {
            auto p = d_lpersonne->rechercher(personne.toStdString());
            r.ajouterParticipant(*p);
        }

        emit ajoutRdv(r);
        close();
    }
}

void RdvForm::onModifier()
{
    afficheErreur();

    if(verifieForm())
    {
        auto qdate = d_date_input->date();
        auto hd = d_hd_input->time();
        auto hf = d_hf_input->time();

        //convertion en date et heure;
        date d{static_cast<unsigned int>(qdate.day()),
        static_cast<unsigned int>(qdate.month()), static_cast<unsigned int>(qdate.year())};
        auto heure_debut{heure{static_cast<unsigned int>(hd.hour()), static_cast<unsigned int>(hd.minute())}};
        auto heure_fin{heure{static_cast<unsigned int>(hf.hour()), static_cast<unsigned int>(hf.minute())}};

        std::string nom = d_nom_input->text().toStdString();
        std::string description = d_description_input->text().toStdString();
        std::string localisation = d_localisation_input->text().toStdString();

        rdv r{nom, d, heure_debut, heure_fin, description, localisation};

        for(auto personne: d_participants_input->currentText())
        {
            auto p = d_lpersonne->rechercher(personne.toStdString());
            r.ajouterParticipant(*p);
        }

        emit modifieRdv(d_rdv->nom(), r);
        close();
    }
}
