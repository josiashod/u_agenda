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

std::string heure::toString() const
{
    std::string str = "";

    str += ((d_h < 10) ? "0" : "") + std::to_string(d_h) + ":";
    str += ((d_mn < 10) ? "0" : "") + std::to_string(d_mn);

    return (str);
}

void heure::affiche(std::ostream& ost) const
{
    ost << d_h << ":" << d_mn << std::endl;

}

std::ostream& operator<<(std::ostream& ost, const heure& h)
{
    h.affiche(ost);
    return ost;
}

void heure::lire(std::istream& ist)
{
    char c;
    ist >> d_h >> c >> d_mn;
}

std::istream& operator>>(std::istream& ist, heure& h)
{
    h.lire(ist);
    return ist;
}

bool heure::estAvant(const heure& h) const
{
    if(d_h > h.d_h)
        return false;

    else if(d_h == h.d_h && d_mn >= h.d_mn)
        return false;

    return true;
}

bool heure::estMemeHeureQue(const heure& h) const
{
    return (d_h == h.d_h && d_mn == h.d_mn);
}

bool heure::estEntre(const heure& debut, const heure& fin) const
{
    return (!estAvant(debut) && estAvant(fin));
}

bool heure::operator==(const heure& h) const
{
    return estMemeHeureQue(h);
}

bool heure::operator!=(const heure& h) const
{
    return !estMemeHeureQue(h);
}

bool heure::operator>(const heure& h) const
{
    return estAvant(h);
}
