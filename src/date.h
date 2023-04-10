#ifndef __DATE_H__
#define __DATE_H__

#include <iostream>


class date
{
    public:
        date();
        date(unsigned int jour, unsigned int mois, unsigned int annee);
        virtual ~date();

        unsigned int jour() const;
        unsigned int mois() const;
        unsigned int annee() const;
        void setAnnee(unsigned int annee);
        void setMois(unsigned int mois);
        void setJour(unsigned int jour);

        void lire(std::istream& ist);
        friend std::istream& operator>>(std::istream& ist, date& d);
        void affiche(std::ostream& ost) const;
        friend std::ostream& operator<<(std::ostream& ost, const date& d);

        bool estAvant(const date& date) const;
        bool estMemeJourQue(const date& date) const;

        bool operator==(const date& date) const;
        bool operator!=(const date& date) const;
        bool operator<(const date& date) const;
        bool operator>=(const date& date) const;
        bool operator<=(const date& date) const;


    private:
        unsigned int d_jour;
        unsigned int d_mois;
        unsigned int d_annee;
};

#endif // DATE_H
