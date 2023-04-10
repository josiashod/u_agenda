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
        void miseAJourParticipant(const personne& old, const personne& newp);
        bool overlap(const personne& p, const date& d
        , const heure& debut, const heure& fin) const;
        void supprimer(std::string nom);
        void exporter(std::ostream& ost) const; // exporte une liste de rendez-vous
        // exporte une liste de rendez-vous entre deux dates
        void exporter(std::ostream& ost, const date& d_debut, const date& d_fin) const;
        void exporterDans(const std::string fichier) const;
        void exporter(std::ostream& ost, const rdv& r) const; // exporte un seul rendez-vous
        void save(std::ostream& ost) const;
        void load(std::istream& ist);
        LRdv* rechercherPlusieurs(std::string str) const;

    private:
        rdv *d_tete;
};


#endif // LRDV_H_INCLUDED
