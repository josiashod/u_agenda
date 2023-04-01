#include "rendezvous.h"

#include <QVBoxLayout>
#include <QLabel>

Rdv::Rdv(rdv* r, QWidget *parent) :
    QDialog(parent),
    d_rdv{r}
{
    creerVue();
}

void Rdv::creerVue()
{
    setWindowTitle(QString::fromStdString(d_rdv->nom()));
    setMinimumSize(300, 202);
    std::string texte;

    auto main{new QVBoxLayout(this)};

    main->addWidget(new QLabel{"Nom:"});
    main->addWidget(new QLabel{QString::fromStdString(d_rdv->nom())});
    main->addSpacing(15);

    main->addWidget(new QLabel{"Date:"});
    if(d_rdv->day().jour() < 10){
        texte = "0" + std::to_string(d_rdv->day().jour()) + "/";
    }
    else{
        texte = std::to_string(d_rdv->day().jour()) +"/";
    }
    if(d_rdv->day().mois() < 10){
        texte = texte + "0" + std::to_string(d_rdv->day().mois()) + "/" + std::to_string(d_rdv->day().annee());
    }
    else{
        texte = texte + std::to_string(d_rdv->day().mois()) + "/" + std::to_string(d_rdv->day().annee());
    }
    main->addWidget(new QLabel{QString::fromStdString(texte)});
    main->addSpacing(15);

    main->addWidget(new QLabel{"Heure début:"});
    texte = std::to_string(d_rdv->h_debut().h()) + ":" + std::to_string(d_rdv->h_debut().mn());
    main->addWidget(new QLabel{QString::fromStdString(texte)});
    main->addSpacing(15);

    main->addWidget(new QLabel{"Heure fin:"});
    texte = std::to_string(d_rdv->h_fin().h()) + ":" + std::to_string(d_rdv->h_fin().mn());
    main->addWidget(new QLabel{QString::fromStdString(texte)});
    main->addSpacing(15);

    main->addWidget(new QLabel{"Localisation:"});
        main->addWidget(new QLabel{QString::fromStdString(d_rdv->localisation())});
    main->addSpacing(15);

    main->addWidget(new QLabel{"Description:"});
    main->addWidget(new QLabel{QString::fromStdString(d_rdv->description())});
    main->addSpacing(15);

    main->addWidget(new QLabel{"Participants:"});
    personne *crt = d_rdv->participants()->tete();
    if(crt == nullptr){
        main->addWidget(new QLabel{"Aucun participant."});
        main->addSpacing(15);
    }
    else{
        while(crt){
            main->addWidget(new QLabel{QString::fromStdString(crt->nomComplet())});
            main->addSpacing(5);
            crt = crt->suivant();
        }
        main->addSpacing(15);
    }

}
