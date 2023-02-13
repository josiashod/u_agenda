#include "Heure.h"

Heure::Heure(){}
Heure::Heure(int heure, int minute):
    d_h{heure}, d_mn{minute}
{}
Heure::~Heure()
{}
int Heure::h()const{
    return d_h;
}
int Heure::mn()const{
    return d_mn;
}
void seth(int h){
    d_h=h;
}
void setmn(int mn){
    d_mn=mn;
}


void Heure::afficheHeure(ostream& ost) const{
    ost << h() << "h" << mn();

}
ostream& operator<<(ostream& ost, const Heure& h){
    h.afficheHeure(ost);;
    return ost;
}
void Heure::lireHeure(istream& ist){
    char c;
    ist >> d_h >> c >> d_mn;
}
istream& operator>>(istream& ist, Heure& h){
    h.lireHeure(ist);
    return ist;
}


bool Heure::estAvant(const Heure& d2)const{
    if(h()>d2.h()){
        return false;
    }else if(h()==d2.h() && mn()>=d2.mn()){
        return false;
    }
    return true;
}

bool Heure::estMemeHeureQue(const Heure& h2)const{
    return (h()==h2.h()&&mn()==h2.mn());
}

bool Heure::estEntre(const Heure& debut, const Heure& fin)const{
    if(!estAvant(debut) && estAvant(fin)){
        return true;
    }
    return false;
}

bool overlapHorraires(const Heure& Debut1, const Heure& Fin1, const Heure& Debut2, const Heure& Fin2){
    if(Debut1.estEntre(Debut2, Fin2)||Fin1.estEntre(Debut2, Fin2)){
        return true;
    }
    if(Debut1.estAvant(Debut2)&&!Fin1.estAvant(Fin2)){
        return true;
    }
    return false;
}
