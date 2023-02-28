#include "rdv.h"
#include "heure.h"
#include "date.h"
#include "LPersonne.h"

// CONSTRUCTEURS + DESTRUCTEUR

rdv::rdv()
{}
rdv::rdv(string nomRDV, date d, heure Debut, heure Fin, LPersonne* participants):
    d_nom{nomRDV}, d_date{d}, d_horraire{Debut, Fin}, d_participants{participants}
{}
rdv::rdv(string nom, date d, heure Debut, heure Fin):
    d_nom{nom}, d_date{d}, d_horraire{Debut, Fin}, d_participants{nullptr}, d_suiv{nullptr}, d_prec{nullptr}
{}
rdv::rdv(const rdv& r):
    d_nom{r.d_nom}, d_date{r.d_date}, d_horraire{r.d_horraire[0], r.d_horraire[1]}, d_participants{nullptr}, d_suiv{nullptr}, d_prec{nullptr}
{}
rdv::~rdv()
{
    delete d_participants;
}



// ACCESSEURS & MUTATEURS

string rdv::nom()const{
    return d_nom;
}
void rdv::setNom(string nom){
    d_nom = nom;
}

date rdv::d()const{
    return d_date;
}
void rdv::setDate(date d){
    d_date = d;
}

heure rdv::hDebut()const{
    return d_horraire[0];
}
void rdv::setDebut(heure debut){
    d_horraire[0]=debut;
}

heure rdv::hFin()const{
    return d_horraire[1];
}
void rdv::setFin(heure fin){
    d_horraire[1]=fin;
}

LPersonne* rdv::participants()const{
    return d_participants;
}
void rdv::setParticipants(LPersonne* listP){
    d_participants = listP;
}



// METHODES

void rdv::ajouterParticipant(personne*& pers){
    d_participants->ajouter(pers);
}


void rdv::afficherParticipants(ostream& ost)const{
    //d_participants->affiche(ost);
}

void rdv::affiche(ostream& ost) const{
    ost << d_date << " : " << d_nom << endl;
    ost << d_horraire[0] << "-" << d_horraire[1] << endl;
    afficherParticipants(ost);
}

void rdv::lire(istream& ist){

}



bool rdv::estAvant(const rdv& r2)const{
    if(d().estAvant(r2.d())){
       return true;
    }else if(!d().estAvant(r2.d()) && !d().estMemeJourQue(r2.d())){
        return false;
    }else{
        if(hDebut().estAvant(r2.hDebut())){
            return true;
        }else if(!hDebut().estAvant(r2.hDebut())&&!hDebut().estMemeHeureQue(r2.hDebut())){
            return false;
        }else{
            if(hFin().estAvant(r2.hFin())){
                return true;
            }
            return false;
        }
    }
}


ostream& operator<<(ostream& ost, const rdv r){
    r.affiche(ost);
    return ost;
}

istream& operator >>(istream& ist, rdv& r){
    r.lire(ist);
    return ist;
}

bool rdv::operator<(const rdv& r2){
    return estAvant(r2);
}

bool rdv::operator==(const rdv& r2){
    return (r2.d_nom==d_nom &&
            r2.d_date==d_date &&
            r2.d_horraire==d_horraire &&
            r2.d_participants==d_participants);
}

