#include "event.h"
#include "rdvform.h"

#include <QVBoxLayout>
#include <QLabel>
#include <QDate>
#include <QPushButton>

Event::Event(const rdv& r, LRdv *lrdv, LPersonne *lpersonne, QWidget *parent) :
    QDialog(parent)
  , d_rdv{r}
  , d_lrdv{lrdv}
  , d_lpersonne{lpersonne}
{
    creerVue();
    afficherRdv();
}

void Event::creerVue()
{
    setWindowTitle(QString::fromStdString(d_rdv.nom()));
    setMinimumSize(300, 202);

    auto main{new QVBoxLayout(this)};

    d_nom_label = new QLabel{""};
    d_nom_label->setStyleSheet("QLabel {font-weight: 4; font-size: 24px}");
    main->addWidget(d_nom_label);
    main->addSpacing(2);

    d_horaires_label = new QLabel{""};
    main->addWidget(d_horaires_label);
    main->addSpacing(5);

    d_localisation_label = new QLabel{""};
    main->addWidget(d_localisation_label);
    main->addSpacing(5);

    main->addWidget(new QLabel{"Description:"});
    d_description_label  = new QLabel{""};
    main->addWidget(d_description_label);
    main->addSpacing(15);

    d_participants_label  = new QLabel{""};
    main->addWidget(d_participants_label);
    main->addSpacing(15);
    main->addStretch(1);

    auto btnModifier{new QPushButton{QIcon(":/icons/pencil-square.svg"), "Modifier"}};
    btnModifier->setAutoDefault(false);
    auto btnSup{new QPushButton{QIcon(":/icons/trash.svg"), "Supprimer"}};
    btnSup->setAutoDefault(false);

    connect(btnModifier, &QPushButton::clicked, this, &Event::onModifier);
    connect(btnSup, &QPushButton::clicked, this, &Event::onSupprimer);

    main->addWidget(btnModifier, 0, Qt::AlignBottom);
    main->addWidget(btnSup, 0, Qt::AlignBottom);
}

void Event::afficherRdv()
{

    QDate date{static_cast<int>(d_rdv.day().annee()),
        static_cast<int>(d_rdv.day().mois()), static_cast<int>(d_rdv.day().jour())};
    QLocale locale = QLocale();


    d_nom_label->setText(QString::fromStdString(d_rdv.nom()));

    QString details = locale.toString(date, "ddd dd MMM yyyy");
    details += " de " + QString::fromStdString(d_rdv.h_debut().toString());
    details += " à " + QString::fromStdString(d_rdv.h_fin().toString());

    d_horaires_label->setText(details);

    d_description_label->setText(QString::fromStdString(d_rdv.description()));

    d_localisation_label->setText("Lieu: " + QString::fromStdString(d_rdv.localisation()));

    if(d_rdv.participants() && d_rdv.participants()->tete()){
        details = "Participants:\n";
        personne *crt = d_rdv.participants()->tete();
        while(crt){
            details += QString::fromStdString(crt->nomComplet()) + "\n";
            crt = crt->suivant();
        }

        d_participants_label->setText(details);
    }
}

void Event::onSupprimer()
{
    emit deleted(d_rdv.nom());
    hide();
}

void Event::onModifier()
{
    auto form{new RdvForm(QDate::currentDate(), d_lrdv, d_lpersonne, &d_rdv, this)};
    form->setModal(true);

    connect(form, &RdvForm::modifieRdv, this, &Event::onModificationRdv);
    form->exec();
}

void Event::onModificationRdv(std::string nom, const rdv& r)
{
    d_rdv = r;
    afficherRdv();
    emit updated(nom, d_rdv);
}
