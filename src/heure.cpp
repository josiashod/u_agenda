#include "heure.h"

heure::heure(){}

heure::heure(unsigned int heure, unsigned int minute): d_h{heure}, d_mn{minute}
{}

heure::~heure()
{}

unsigned int heure::h() const
{
    return d_h;
}

unsigned int heure::mn() const
{
    return d_mn;
}

void heure::seth(unsigned int h)
{
    d_h = h;
}

void heure::setmn(unsigned int mn)
{
    d_mn = mn;
}

void heure::afficheHeure(std::ostream& ost) const
{
    ost << d_h << "h" << d_mn;

}

std::ostream& operator<<(std::ostream& ost, const heure& h)
{
    h.afficheHeure(ost);;
    return ost;
}

void heure::lireHeure(std::istream& ist)
{
    char c;
    ist >> d_h >> c >> d_mn;
}

std::istream& operator>>(std::istream& ist, heure& h)
{
    h.lireHeure(ist);
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

bool heure::estMemeHeureQue(const heure& heure) const
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
