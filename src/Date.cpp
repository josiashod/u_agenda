#include "Date.h"

Date::Date(){}

Date::Date(unsigned int jour, unsigned int mois, unsigned int annee):
    d_jour{jour}
    , d_mois{mois}
    , d_annee{annee}
{}

Date::~Date()
{}

unsigned int Date::d_jour const
{
    return d_jour;
}

unsigned int Date::d_mois const
{
    return d_mois;
}

unsigned int Date::d_annee const
{
    return d_annee;
}

void Date::setJour(unsigned int jour)
{
    d_jour = jour;
}

void Date::setMois(unsigned int mois)
{
    d_mois = mois;
}

void Date::setAnnee(unsigned int annee)
{
    d_annee = annee;
}

void lireDate(std::istream& ist)
{
    char c;
    ist >> d_jour >> c >> d_mois >> c >> d_annee;
}

std::istream& operator>>(std::istream& ist, Date& d)
{
    d.lireDate(ist);
    return ist;
}

void Date::afficheDate(std::ostream& ost) const
{
    ost << d_jour << "/" << d_mois << "/" << d_annee;
}

std::ostream& operator<<(std::ostream& ost, const Date& d)
{
    d.afficheDate(ost);
    return ost;
}


bool Date::estAvant(const Date& date) const
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

bool Date::estMemeJourQue(const Date& date) const
{
    return (d_annee == date.d_annee && d_mois == date.d_mois && d_jour == date.d_jour);
}

bool operator==(const Date& date) const
{
    return estMemeJourQue(date);
}

bool operator>(const Date& date) const
{
    return estAvant(date);
}
