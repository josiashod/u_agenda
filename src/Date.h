#ifndef DATE_H
#define DATE_H
#include <iostream>


class Date
{
    public:
        Date();
        Date(unsigned int jour, unsigned int mois, unsigned int annee);
        virtual ~Date();

        unsigned int jour() const;
        unsigned int mois() const;
        unsigned int annee() const;
        void setAnnee(unsigned int annee);
        void setMois(unsigned int mois);
        void setJour(unsigned int jour);

        void lireDate(istream& ist);
        friend istream& operator>>(istream& ist, Date& d);
        void afficheDate(ostream& ost) const;
        friend ostream& operator<<(ostream& ost, const Date& d);

        bool estAvant(const Date& date) const;
        bool estMemeJourQue(const Date& date) const;

        bool operator==(const Date& date) const;
        bool operator>(const Date& date) const;


    private:
        unsigned int d_jour;
        unsigned int d_mois;
        unsigned int d_annee;
};

#endif // DATE_H
