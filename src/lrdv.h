#ifndef __LRDV_H__
#define __LRDV_H__

#include <string>
#include <iostream>

class rdv;
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
        int ajouter(rdv*& nr);
        rdv* trouverUn(std::string nom) const;
        LRdv* trouverParDate(const date& d);
        LRdv* trouverParPersone(const personne& p);
        bool overlap(const personne& p, const date& d
        , const heure* h);
        void supprimer(std::string nom);
        void exporter(std::ostream& ost) const;
        void importer(std::istream& ist);
        // static bool personneOverlapRdv(const LRdv* lr, const personne* p
        // , const rdv* r);

    private:
        rdv *d_tete;
};


#endif // LRDV_H_INCLUDED
