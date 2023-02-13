#include "date.h"

date::date(){}

date::date(unsigned int jour, unsigned int mois, unsigned int annee):
    d_jour{jour}
    , d_mois{mois}
    , d_annee{annee}
{}

date::~date()
{}

unsigned int date::jour() const
{
    return d_jour;
}

unsigned int date::mois() const
{
    return d_mois;
}

unsigned int date::annee() const
{
    return d_annee;
}

void date::setJour(unsigned int jour)
{
    d_jour = jour;
}

void date::setMois(unsigned int mois)
{
    d_mois = mois;
}

void date::setAnnee(unsigned int annee)
{
    d_annee = annee;
}

void date::lireDate(std::istream& ist)
{
    char c;
    ist >> d_jour >> c >> d_mois >> c >> d_annee;
}

std::istream& operator>>(std::istream& ist, date& d)
{
    d.lireDate(ist);
    return ist;
}

void date::afficheDate(std::ostream& ost) const
{
    ost << d_jour << "/" << d_mois << "/" << d_annee;
}

std::ostream& operator<<(std::ostream& ost, const date& d)
{
    d.afficheDate(ost);
    return ost;
}


bool date::estAvant(const date& date) const
{
    if(d_annee > date.d_annee)
    {
        return false;
    }
    else if(d_annee == date.d_annee && d_mois > date.d_mois)
    {
        return false;
    }
    else if(d_annee == date.d_annee && d_mois == date.d_mois && d_jour >= date.d_jour)
    {
        return false;
    }
    return true;
}

bool date::estMemeJourQue(const date& date) const
{
    return (d_annee == date.d_annee && d_mois == date.d_mois && d_jour == date.d_jour);
}

bool date::operator==(const date& date) const
{
    return estMemeJourQue(date);
}

bool date::operator>(const date& date) const
{
    return estAvant(date);
}
