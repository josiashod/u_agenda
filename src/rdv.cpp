#include "rdv.h"

// CONSTRUCTEURS + DESTRUCTEUR
rdv::rdv()
{}

rdv::rdv(std::string nom, date d, heure h_debut
, heure h_fin, std::string description
, std::string localisation): d_nom{nom}, d_date{d}
    , d_horaires{h_debut, h_fin}
    , d_description{description}
    , d_localisation{localisation}
    , d_participants{nullptr}
    , d_suiv{nullptr}
    // , d_prec{nullptr}
{}

rdv::rdv(std::string nom, date d, heure h_debut
, heure h_fin, std::string description
, std::string localisation
, LPersonne* participants): d_nom{nom}, d_date{d}
    , d_horaires{h_debut, h_fin}
    , d_description{description}
    , d_localisation{localisation}
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

std::string rdv::description() const
{
    return d_description;
}

void rdv::setDescription(std::string description)
{
    d_description = description;
}

std::string rdv::localisation() const
{
    return d_localisation;
}

void rdv::setLocalisation(std::string localisation)
{
    d_localisation = localisation;
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

void rdv::save(std::ostream& ost) const
{
    ost << "BEGIN:RDV" << std::endl;
    ost << '{' + d_nom + ", " + d_description + ", "
    + d_localisation + '}' << std::endl;
    ost << d_date;
    ost << d_horaires[0];
    ost << d_horaires[1];
    ost << *d_participants;
    ost << "END:RDV" << std::endl;
}

void rdv::load(std::istream& ist)
{
    std::string ligne{""};
    int ist_pos;

    ist >> ligne;

    if (ligne != "BEGIN:RDV")
        return;

    char c;
    ist >> c >> d_nom >> d_description >> d_localisation;

    d_nom = d_nom.substr(0, d_nom.length() - 1);
    d_description = d_description.substr(0, d_description.length() - 1);
    d_localisation = d_localisation.substr(0, d_localisation.length() - 1);

    ist >> d_date;
    ist >> d_horaires[0];
    ist >> d_horaires[1];

    d_participants = new LPersonne();
    ist >> (*d_participants);

    ist >> ligne;
}

std::string timestamp(date d, heure h)
{
    std::string tz{""};

    tz += std::to_string(d.annee());
    tz += ((d.mois() < 10) ? "0" : "") + std::to_string(d.mois());
    tz += ((d.jour() < 10) ? "0" : "") + std::to_string(d.jour()) + "T";
    tz += ((h.h() < 10) ? "0" : "") + std::to_string(h.h());
    tz += ((h.mn() < 10) ? "0" : "") + std::to_string(h.mn()) + "00Z";

    return tz;
}

void rdv::exporter(std::ostream& ost) const
{
    ost << "BEGIN:VEVENT" << std::endl;
    ost << "DTSTART:" << timestamp(d_date, d_horaires[0]) << std::endl;
    ost << "DTEND:" << timestamp(d_date, d_horaires[1]) << std::endl;
    ost << "SUMMARY:" << d_nom << std::endl;
    ost << "DESCRIPTION:\\n\\n" << d_description;

    personne *crt = (d_participants) ? d_participants->tete() : nullptr;
    if (crt)
        ost << "\\n";
    while(crt)
    {
        ost << crt->nomComplet() << "\\n";
        crt = crt->suivant();
    }
    ost << std::endl;
    ost << "LOCATION:" << d_localisation << std::endl;
    ost << "END:VEVENT" << std::endl;
}

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

std::ostream& operator<<(std::ostream& ost, const rdv& r){
    r.save(ost);
    return ost;
}

std::istream& operator>>(std::istream& ist, rdv& r){
    r.load(ist);
    return ist;
}
