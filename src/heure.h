#ifndef __HEURE_H__
#define __HEURE_H__

#include <iostream>
using namespace std;


class heure
{
    public:
        heure();
        heure(int heure, int minute);
        virtual ~heure();
        int h() const;
        int mn() const;
        void seth(int h);
        void setmn(int mn);

        void afficheHeure(ostream& ost) const;
        friend ostream& operator<<(ostream& ost, const heure& h);
        void lireHeure(istream& ist);
        friend istream& operator>>(istream& ist, heure& h);

        bool estAvant(const heure& heure) const;
        bool estMemeHeureQue(const heure& heure)const;
        bool estEntre(const heure& debut, const heure& fin) const;
        friend bool overlapHorraires(const heure& debut1, const heure& fin1, const heure& debut2, const heure& fin2);

    protected:

    private:
        int d_h, d_mn;
};

#endif // HEURE_H
