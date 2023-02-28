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

        void affiche(std::ostream& ost) const;
        friend std::ostream& operator<<(std::ostream& ost, const heure& h);
        void lire(std::istream& ist);
        friend std::istream& operator>>(std::istream& ist, heure& h);

        bool estAvant(const heure& h) const;
        bool estMemeHeureQue(const heure& h) const;
        bool estEntre(const heure& debut, const heure& fin) const;
        bool operator==(const heure& h) const;
        bool operator>(const heure& h) const;

    protected:

    private:
        unsigned int d_h;
        unsigned int d_mn;
};

#endif // HEURE_H
