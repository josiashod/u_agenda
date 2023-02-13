#include "heure.h"

heure::heure(){}

heure::heure(unsigned int heure, unsigned int minute): d_h{heure}, d_mn{minute}
{}

heure::~heure()
{}

unsigned int heure::d_h const
{
    return d_h;
}

unsigned int heure::d_mn const
{
    return d_mn;
}

void seth(unsigned int h)
{
    d_h = h;
}

void setmn(unsigned int mn)
{
    d_mn = mn;
}

void heure::afficheheure(ostream& ost) const
{
    ost << d_h << "h" << d_mn;

}

ostream& operator<<(ostream& ost, const heure& h)
{
    h.afficheheure(ost);;
    return ost;
}

void heure::lireheure(istream& ist)
{
    char c;
    ist >> d_h >> c >> d_mn;
}

istream& operator>>(istream& ist, heure& h)
{
    h.lireheure(ist);
    return ist;
}

bool heure::estAvant(const heure& heure) const
{
    if(d_h > heure.d_h)
        return false;

    else if(d_h == heure.d_h && d_mn >= heure.d_mn)
        return false;

    return true;
}

bool heure::estMemeheureQue(const heure& heure) const
{
    return (d_h == heure.d_h && d_mn == heure.d_mn);
}

bool heure::estEntre(const heure& debut, const heure& fin) const
{
    if(!estAvant(debut) && estAvant(fin))
        return true;

    return false;
}

bool overlapHorraires(const heure& debut1, const heure& fin1, const heure& debut2, const heure& fin2)
{
    if(debut1.estEntre(debut2, fin2) || fin1.estEntre(debut2, fin2))
        return true;

    if(debut1.estAvant(debut2) && !fin1.estAvant(fin2))
        return true;

    return false;
}
