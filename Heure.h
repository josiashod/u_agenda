#ifndef HEURE_H
#define HEURE_H
#include <iostream>
using namespace std;


class Heure
{
    public:
        Heure();
        Heure(int heure, int minute);
        virtual ~Heure();
        int h() const;
        int mn() const;
        void seth(int h);
        void setmn(int mn);

        void afficheHeure(ostream& ost) const;
        friend ostream& operator<<(ostream& ost, const Heure& h);
        void lireHeure(istream& ist);
        friend istream& operator>>(istream& ist, Heure& h);

        bool estAvant(const Heure& d2) const;
        bool estMemeHeureQue(const Heure& h2)const;
        bool estEntre(const Heure& debut, const Heure& fin) const;
        friend bool overlapHorraires(const Heure& debut1, const Heure& Fin1, const Heure& Debut2, const Heure& Fin2);

    protected:

    private:
        int d_h, d_mn;
};

#endif // HEURE_H
