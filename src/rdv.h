#ifndef __RDV_H__
#define __RDV_H__

#include <string>
#include <iostream>
#include <array>
#include "LPersonne.h"
#include "date.h"
#include "heure.h"


class rdv
{
    public:
        // CONSTRUCTEURS + DESTRUCTEUR
        rdv();
        rdv(std::string nom, date d, heure h_debut
        , heure h_fin);
        rdv(std::string nom, date d, heure h_debut
        , heure h_fin
        , LPersonne* participants);
        rdv(const rdv& r);
        virtual ~rdv();

        // ACCESSEURS & MUTATEURS
        std::string nom() const;
        void setNom(std::string nom);
        date day() const;
        void setDate(date day);
        heure h_debut() const;
        void setHDebut(heure debut);
        heure h_fin() const;
        void setHFin(heure fin);
        LPersonne* participants() const;
        void setParticipants(LPersonne *participants);

        //METHODES
        void ajouterParticipant(personne*& pers);
        void save(std::ostream& ost) const;
        // void load(std::istream& ist);
        bool estAvant(const rdv& r) const;
        bool overlap(const rdv& r) const;


        bool operator>(const rdv& r);
        bool operator==(const rdv& r);
        // friend std::ostream& operator <<(std::ostream& ost, const rdv& r);
        // friend std::istream& operator >>(std::istream& ist, rdv& r);


    protected:

    private:
        std::string d_nom;
        date d_date;
        std::array<heure, 2> d_horaires;
        LPersonne *d_participants;
        rdv *d_suiv;
        //rdv* d_prec;
        //unsigned int d_status;
};

#endif // __RDV_H__
