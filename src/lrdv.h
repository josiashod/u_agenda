#ifndef __LRDV_H__
#define __LRDV_H__

#include <string>
#include <iostream>
#include "rdv.h"

class date;
class heure;
class LPersonne;
class personne;

class LRdv
{
    public:
        // CONSTRUCTEURS ET DESTRUCTEURS
        LRdv();
        ~LRdv();

        // ACCESSEURS & MUTATEURS
        rdv *tete() const;

        // METHODES
        int ajouter(const rdv& r);
        rdv* trouverUn(std::string nom) const;
        LRdv* trouverParDate(const date& d) const;
        LRdv* trouverParPersonne(const personne& p) const;
        bool overlap(const personne& p, const date& d
        , const heure& h);
        void supprimer(std::string nom);
        void exporter(std::ostream& ost) const; // exporte une liste de rendez-vous
        void exporter(std::ostream& ost, const rdv& r) const; // exporte un seul rendez-vous
        void save(std::ostream& ost) const;
        void load(std::istream& ist);

    private:
        rdv *d_tete;
};


#endif // LRDV_H_INCLUDED
