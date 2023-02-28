#include "rdv.h"

// CONSTRUCTEURS + DESTRUCTEUR

rdv::rdv()
{}

rdv::rdv(std::string nom, date d, heure h_debut
, heure h_fin): d_nom{nom}, d_date{d}
    , d_horaires{h_debut, h_fin}
    , d_participants{nullptr}
    , d_suiv{nullptr}
    // , d_prec{nullptr}
{}

rdv::rdv(std::string nom, date d, heure h_debut
, heure h_fin
, LPersonne* participants): d_nom{nom}, d_date{d}
    , d_horaires{h_debut, h_fin}
    , d_participants{participants}
    , d_suiv{nullptr}
    // , d_prec{nullptr}
{}

rdv::rdv(const rdv& r):
    d_nom{r.d_nom}
    , d_date{r.d_date}
    , d_horaires{r.d_horaires[0], r.d_horaires[1]}
    , d_participants{nullptr}
    , d_suiv{nullptr}
    // , d_prec{nullptr}
{}

rdv::~rdv()
{
    delete d_participants;
}


// ACCESSEURS & MUTATEURS
std::string rdv::nom() const
{
    return d_nom;
}

void rdv::setNom(std::string nom)
{
    d_nom = nom;
}

date rdv::day() const
{
    return d_date;
}

void rdv::setDate(date day){
    d_date = day;
}

heure rdv::h_debut()const{
    return d_horaires[0];
}
void rdv::setHDebut(heure debut){
    d_horaires[0] = debut;
}

heure rdv::h_fin() const
{
    return d_horaires[1];
}

void rdv::setHFin(heure fin)
{
    d_horaires[1] = fin;
}

LPersonne* rdv::participants() const
{
    return d_participants;
}

void rdv::setParticipants(LPersonne* participants){
    d_participants = participants;
}

// METHODES
void rdv::ajouterParticipant(personne*& pers){
    d_participants->ajouter(pers);
}

// void rdv::save(ostream& ost) const{
//     ost << d_date << " : " << d_nom << endl;
//     ost << d_horaires[0] << "-" << d_horaires[1] << endl;
//     afficherParticipants(ost);
// }

// void rdv::load(istream& ist){

// }

bool rdv::estAvant(const rdv& r) const
{
    if(d_date > r.d_date)
       return true;

    else if(!(d_date == r.d_date))
        return false;

    else
    {
        if(h_debut() > r.h_debut())
            return true;

        else if(!(h_debut() == r.h_debut()))
            return false;

        else
        {
            if(h_fin() > r.h_fin())
                return true;

            return false;
        }
    }
}

bool rdv::overlap(const rdv& r) const
{
    if (!(d_date == r.d_date))
        return false;

    if(h_debut().estEntre(r.h_debut(), r.h_fin()) 
    || r.h_fin().estEntre(r.h_debut(), r.h_fin()))
        return true;

    if(h_debut().estAvant(r.h_debut()) && !r.h_fin().estAvant(r.h_fin()))
        return true;

    return false;
}

bool rdv::operator>(const rdv& r){
    return estAvant(r);
}

bool rdv::operator==(const rdv& r){
    return (r.d_nom == d_nom &&
        r.d_date == d_date &&
        r.d_horaires == d_horaires &&
        *r.d_participants == *d_participants);
}

// ostream& operator<<(ostream& ost, const rdv r){
//     r.affiche(ost);
//     return ost;
// }

// istream& operator>>(istream& ist, rdv& r){
//     r.lire(ist);
//     return ist;
// }
