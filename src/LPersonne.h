#ifndef __L_PERSONNE_H__
#define __L_PERSONNE_H__
#include <iostream>
#include "personne.h"


class LPersonne {
    // CONSTRUCTEURS
    LPersonne();
    ~LPersonne();

    // METHODES
    void ajout_personne(std::string nom, std::string prenom, std::string numero, std::string email);
    void ajout_personne(personne P);
    void rechercher(std::string nom);
    void supprimer(std::string nom);


    private:
        personne* d_tete;
        personne* d_queue;
        unsigned int d_taille;
};

#endif
