#include "event.h"

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
}

void Event::creerVue()
{
    setWindowTitle(QString::fromStdString(d_rdv.nom()));
    setMinimumSize(300, 202);
    std::string texte;
    QDate date{static_cast<int>(d_rdv.day().annee()),
        static_cast<int>(d_rdv.day().mois()), static_cast<int>(d_rdv.day().jour())};

    auto main{new QVBoxLayout(this)};

    auto nom{new QLabel{QString::fromStdString(d_rdv.nom())}};
    nom->setStyleSheet("QLabel {font-weight: 4; font-size: 24px}");
    main->addWidget(nom);
    main->addSpacing(2);

    QLocale locale = QLocale();
    QString details = locale.toString(date, "ddd dd MMM yyyy");
    details += " de " + QString::fromStdString(d_rdv.h_debut().toString());
    details += " à " + QString::fromStdString(d_rdv.h_fin().toString());

    auto horaires{new QLabel{details}};
    horaires->setStyleSheet("QLabel {font-size: 16px}");
    main->addWidget(new QLabel{details});
    main->addSpacing(5);

    main->addWidget(new QLabel{"Lieu: " + QString::fromStdString(d_rdv.localisation())});
    main->addSpacing(5);

    main->addWidget(new QLabel{"Description:"});
    main->addWidget(new QLabel{QString::fromStdString(d_rdv.description())});
    main->addSpacing(15);

    if(d_rdv.participants() && d_rdv.participants()->tete()){
        main->addWidget(new QLabel{"Participants:"});
        personne *crt = d_rdv.participants()->tete();
        while(crt){
            main->addWidget(new QLabel{QString::fromStdString(crt->nomComplet())});
            main->addSpacing(2);
            crt = crt->suivant();
        }
    }
    main->addSpacing(15);
    main->addStretch(1);

    auto btnModifier{new QPushButton{QIcon(":/icons/pencil-square.svg"), "Modifier"}};
    btnModifier->setAutoDefault(false);
    auto btnSup{new QPushButton{QIcon(":/icons/trash.svg"), "Supprimer"}};
    btnSup->setAutoDefault(false);

    connect(btnModifier, &QPushButton::clicked, this, &Event::onSupprimer);
    connect(btnSup, &QPushButton::clicked, this, &Event::onSupprimer);

    main->addWidget(btnModifier, 0, Qt::AlignBottom);
    main->addWidget(btnSup, 0, Qt::AlignBottom);
}

void Event::onSupprimer()
{
    emit deleted(d_rdv.nom());
    hide();
}
