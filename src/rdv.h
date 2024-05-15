#ifndef __RDV_H__
#define __RDV_H__

#include <string>
#include <array>
#include "lpersonne.h"
#include "date.h"
#include "heure.h"

class LRdv;

class rdv
{
    public:
        // CONSTRUCTEURS + DESTRUCTEUR
        rdv();
        rdv(std::string nom, date d, heure h_debut
        , heure h_fin, std::string description
        , std::string localisation);
        rdv(std::string nom, date d, heure h_debut
        , heure h_fin, std::string description
        , std::string localisation
        , const LPersonne& participants);
        rdv(const rdv& r);
        virtual ~rdv();

        // ACCESSEURS & MUTATEURS
        std::string nom() const;
        void setNom(std::string nom);
        date day() const;
        void setDate(const date& day) ;
        heure h_debut() const;
        void setHDebut(const heure& debut);
        heure h_fin() const;
        void setHFin(const heure& fin);
        std::string description() const;
        void setDescription(std::string description);
        std::string localisation() const;
        void setLocalisation(std::string localisation);
        LPersonne* participants() const;
        void setParticipants(LPersonne *participants);
        void ajouterParticipant(const personne& participant);
        void supprimerParticipant(const personne& participant);
        rdv* suivant() const;

        //METHODES
        void save(std::ostream& ost, int profondeur = 1) const;
        void load(std::istream& ist, LPersonne* lpersonne = nullptr);
        void exporter(std::ostream& ost) const;
        bool estAvant(const rdv& r) const;
        bool overlap(const date& d, const heure& debut, const heure& fin) const;
        bool contient(std::string& str) const;


        bool operator>(const rdv& r);
        bool operator==(const rdv& r);
        rdv& operator=(const rdv &r);
        friend std::ostream& operator <<(std::ostream& ost, const rdv& r);
        friend std::istream& operator >>(std::istream& ist, rdv& r);

        friend class LRdv;
    protected:

    private:
        std::string d_nom;
        date d_date;
        std::array<heure, 2> d_horaires;
        std::string d_description;
        std::string d_localisation;
        LPersonne* d_participants;
        rdv* d_suiv;
        //rdv* d_prec;
        //unsigned int d_status;

        // Methodes
};

#endif // __RDV_H__
