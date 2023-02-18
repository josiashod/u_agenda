#include "LPersonne.h"


LPersonne::LPersonne(): d_tete{nullptr}
, d_queue{nullptr}
, d_taille{0}
{}

LPersonne::~LPersonne()
{
    personne* as = d_tete;

    while(as != nullptr)
    {
        d_tete = as->d_suiv;
        delete as;
        as = d_tete;
    }
}

void LPersonne::ajout_personne(std::string nom, std::string prenom, std::string numero, std::string email){
    personne* nouvellePersonne = new personne(nom, prenom, numero, email);
    nouvellePersonne->setSuivant(d_tete);
    d_tete = nouvellePersonne;
    d_taille++;
}

void LPersonne::ajout_personne(personne P){
    personne* nouvellePersonne = new personne(P.nom(), P.prenom(), P.numero(), P.email());
    nouvellePersonne->setSuivant(d_tete);
    d_tete = nouvellePersonne;
    d_taille++;
}

void LPersonne::supprimer(std::string nom) {
    if (d_tete == nullptr) {
       return;
    }

    if (d_tete->nom() == nom) {
        personne* ancienDebut = d_tete;
        d_tete = d_tete->suivant();
        delete ancienDebut;
        d_taille--;
        return;
    }

    personne* courant = d_tete;
    while (courant->suivant() != nullptr) {
        if (courant->suivant()->nom() == nom) {
            personne* ancienSuivant = courant->suivant();
            courant->setSuivant(courant->suivant()->suivant());
            delete ancienSuivant;
            d_taille--;
            return;
        }
        courant = courant->suivant();
    }
}

void LPersonne::rechercher(std::string nom) {
    personne* courant = d_tete;
    while (courant != nullptr) {
        if (courant->nom() == nom) {
            std::cout << courant->nom() << " " << courant->prenom() << ", " << courant->numero() << ", " << courant->email() << std::endl;
        }
        courant = courant->suivant();
    }
}
