#include "Date.h"

using namespace std;

Date::Date(){}
Date::Date(int jour, int mois, int annee){
    d_date[0] = jour;
    d_date[1] = mois;
    d_date[2] = annee;
}
Date::~Date()
{}

int Date::jour() const{
    return d_date[0];
}
int Date::mois() const{
    return d_date[1];
}
int Date::annee() const{
    return d_date[2];
}

void Date::setJour(int jour){
    d_date[0] = jour;
}
void Date::setMois(int mois){
    d_date[1] = mois;
}
void Date::setAnnee(int annee){
    d_date[2] = annee;
}


void lireDate(istream& ist){
    char c;
    ist >> d_dat[0] >> c >> d_date[1] >> c >> d_date[2];
}
istream& operator>>(istream& ist, Date& d){
    d.lireDate(ist);
    return ist;
}
void Date::afficheDate(ostream& ost) const{
    ost << jour() << "/" << mois() << "/" << annee();
}
ostream& operator<<(ostream& ost,const Date& d){
    d.afficheDate(ost);
    return ost;
}


bool Date::estAvant(const Date& d2)const {
    if(annee()>d2.annee()){
        return false;
    }else if(annee()==d2.annee() && mois()>d2.mois()){
        return false;
    }else if(annee()==d2.annee() && mois()==d2.mois() && jour()>=d2.jour()){
        return false;
    }
    return true;
}

bool Date::estMemeJourQue(const Date& d2)const{
    return (annee()==d2.annee() && mois()==d2.mois() && jour()==d2.jour());
}
