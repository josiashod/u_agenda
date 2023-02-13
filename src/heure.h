#ifndef __HEURE_H__
#define __HEURE_H__

#include <iostream>

class heure
{
    public:
        heure();
        heure(unsigned int heure, unsigned int minute);
        virtual ~heure();
        unsigned int h() const;
        unsigned int mn() const;
        void seth(unsigned int h);
        void setmn(unsigned int mn);

        void afficheHeure(std::ostream& ost) const;
        friend std::ostream& operator<<(std::ostream& ost, const heure& h);
        void lireHeure(std::istream& ist);
        friend std::istream& operator>>(std::istream& ist, heure& h);

        bool estAvant(const heure& heure) const;
        bool estMemeHeureQue(const heure& heure) const;
        bool estEntre(const heure& debut, const heure& fin) const;
        friend bool overlapHorraires(const heure& debut1, const heure& fin1, const heure& debut2, const heure& fin2);

    protected:

    private:
        unsigned int d_h;
        unsigned int d_mn;
};

#endif // HEURE_H
