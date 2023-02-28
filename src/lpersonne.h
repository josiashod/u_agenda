#ifndef __L_PERSONNE_H__
#define __L_PERSONNE_H__

#include <string>
#include <iostream>
#include "personne.h"
#include "error.h"

class LPersonne {
    public:
        // CONSTRUCTEURS
        LPersonne();
        ~LPersonne();

        // ACCESSEURS MUTATEURS
        personne* tete() const;
        personne* queue() const;
        unsigned int taille() const;

        // METHODES
        int ajouter(std::string nom, std::string prenom
            , std::string numero
            , std::string email
        );
        void ajouter(personne*& p);
        personne* rechercher(std::string nomComplet) const;
        LPersonne* rechercherPlusieurs(std::string str) const;
        int supprimer(std::string nomComplet);
        int supprimer(personne*& p);

        void save(std::ostream& ost) const;
        void load(std::istream& ist);
        void exporter(std::ostream& ost) const;
        void exporterDans(const std::string fichier) const;
        void importer(std::istream& ist);
        int importerDepuis(const std::string fichier);

        bool operator==(const LPersonne& lp) const;
        // friend std::istream& operator>>(std::istream& ist, LPersonne& lp);
        // friend std::ostream& operator<<(std::ostream& ost, const LPersonne& lp);

    private:
        personne* d_tete;
        personne* d_queue;
        unsigned int d_taille;
};

#endif
