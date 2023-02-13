#ifndef DATE_H
#define DATE_H
#include <iostream>
using namespace std;


class Date
{
    public:
        Date();
        Date(int jour, int mois, int annee);
        virtual ~Date();
        int jour() const;
        int mois() const;
        int annee() const;
        void setAnnee(int annee);
        void setMois(int mois);
        void setJour(int jour);

        void lireDate(istream& ist);
        friend istream& operator>>(istream& ist, Date& d);
        void afficheDate(ostream& ost) const;
        friend ostream& operator<<(ostream& ost,const Date& d);

        bool estAvant(const Date& d2)const;
        bool estMemeJourQue(const Date& d2)const;

    private:
        // d_annee, d_heure, d_minutes;
        int d_date[3];
};

#endif // DATE_H
