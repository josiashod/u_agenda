#ifndef LRDV_H_INCLUDED
#define LRDV_H_INCLUDED

#include<string>
#include<iostream>

class rdv;

class LRdv{
public:
    LRdv();
    ~LRdv();
    rdv *tete();
    void ajout_rdv(std::string nom, struct tm{date}, struct tm{heure_debut}, struct tm{heure_fin},
                   std::string description, std::string localisation, std::string resume);
    void ajouter_rdv(rdv& *rdv);
    rdv *recherche(std::string nom) const;
    void supprime(std::string nom);
    void exporter(std::ostream& ost) const;
    void importer(std::istream& ist);
private:
    rdv *d_tete;
};


#endif // LRDV_H_INCLUDED
