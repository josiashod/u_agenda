#ifndef rdv_H
#define rdv_H
#include <string>
#include "Personne.h"
#include "date.h"
#include "heure.h"
#include <iostream>

using namespace std;


class rdv
{
    public:
        // CONSTRUCTEURS + DESTRUCTEUR
        rdv();
        rdv(string nom, date d, heure Debut, heure Fin, LPersonne* participants);
        rdv(string nom, date d, heure debut, heure fin);
        rdv(const rdv& r);
        virtual ~rdv();

        // ACCESSEURS & MUTATEURS
        string nom()const;
        void setNom(string nom);
        date d()const;
        void setDate(date d);
        heure hDebut()const;
        void setDebut(heure debut);
        heure hFin()const;
        void setFin(heure fin);
        LPersonne* participants()const;
        void setParticipants(LPersonne* listP);

        //METHODES
        void ajouterParticipant(personne*& pers);

        void afficherParticipants(ostream& ost)const;
        void affiche(ostream& ost) const;
        void lire(istream& ist);

        bool estAvant(const rdv& r2)const;

        bool operator<(const rdv& r2);
        bool operator==(const rdv& r2);
        friend ostream& operator <<(ostream& ost, const rdv& r);
        friend istream& operator >>(istream& ist, rdv& r);


    protected:

    private:
        string d_nom;
        date d_date;
        heure d_horraire[2];
        LPersonne* d_participants;
        rdv* d_suiv;
        rdv* d_prec;
        //unsigned int d_status;
};

#endif // rdv_H
