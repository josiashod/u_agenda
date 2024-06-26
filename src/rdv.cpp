#include "rdv.h"
#include "lpersonne.h"
#include "parser.h"
#include <sstream>

// CONSTRUCTEURS + DESTRUCTEUR
rdv::rdv(): d_nom{""}
, d_description{""}
, d_localisation{""}
{}

rdv::rdv(std::string nom, date d, heure h_debut
, heure h_fin, std::string description
, std::string localisation): d_nom{nom}, d_date{d}
    , d_horaires{h_debut, h_fin}
    , d_description{description}
    , d_localisation{localisation}
    , d_participants{new LPersonne()}
    , d_suiv{nullptr}
    // , d_prec{nullptr}
{}

rdv::rdv(std::string nom, date d, heure h_debut
, heure h_fin, std::string description
, std::string localisation
, const LPersonne& participants): d_nom{nom}, d_date{d}
    , d_horaires{h_debut, h_fin}
    , d_description{description}
    , d_localisation{localisation}
    , d_participants{nullptr}
    , d_suiv{nullptr}
    // , d_prec{nullptr}
{
    d_participants = new LPersonne(participants);
}

rdv::rdv(const rdv& r):
    d_nom{r.d_nom}
    , d_date{r.d_date}
    , d_horaires{r.d_horaires[0], r.d_horaires[1]}
    , d_description{r.d_description}
    , d_localisation{r.d_localisation}
    , d_participants{}
    , d_suiv{nullptr}
    // , d_prec{nullptr}
{

    d_participants = new LPersonne(*r.d_participants);
}

rdv::~rdv()
{
    if(d_participants)
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

void rdv::setDate(const date& day) {
    d_date = day;
}

heure rdv::h_debut()const{
    return d_horaires[0];
}
void rdv::setHDebut(const heure& debut){
    d_horaires[0] = debut;
}

heure rdv::h_fin() const
{
    return d_horaires[1];
}

void rdv::setHFin(const heure& fin)
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
void rdv::ajouterParticipant(const personne& participant)
{
    if(!d_participants)
        d_participants = new LPersonne();

    d_participants->ajouter(participant);
}

void rdv::supprimerParticipant(const personne& participant)
{
    if(!d_participants)
        return;
    d_participants->supprimer(participant.nomComplet());
}

rdv* rdv::suivant() const
{
    return d_suiv;
}

void rdv::save(std::ostream& ost, int profondeur) const
{
    ost << std::string(profondeur - 1, '\t') + "{" << std::endl;
    ost << std::string(profondeur, '\t') + "\"nom\":" << " \"" + d_nom + "\"," << std::endl;
    ost << std::string(profondeur, '\t') + "\"description\":" << " \"" + d_description + "\"," << std::endl;
    ost << std::string(profondeur, '\t') + "\"localisation\":" << " \"" + d_localisation + "\"," << std::endl;
    ost << std::string(profondeur, '\t') + "\"date\":" << " \"" + d_date.toString() + "\"," << std::endl;
    ost << std::string(profondeur, '\t') + "\"heure de debut\":" << " \"" + d_horaires[0].toString() + "\"," << std::endl;
    ost << std::string(profondeur, '\t') + "\"heure de fin\":" << " \"" + d_horaires[1].toString() + "\"," << std::endl;
    ost << std::string(profondeur, '\t') + "\"participants\":";
    d_participants->save(ost, profondeur + 1);
    ost << std::endl;
    ost << std::string(profondeur - 1, '\t') + "}";
}

void rdv::load(std::istream& ist)
{
    std::string ligne{""};

    // on recupere la premiere parenthèse
    getline(ist, ligne);

    // on recupere le nom
    getline(ist, ligne);
    d_nom = attribute_extrator(ligne).value;

    // on recupere la description
    getline(ist, ligne);
    d_description = attribute_extrator(ligne).value;

    // on recupere la localisation
    getline(ist, ligne);
    d_localisation = attribute_extrator(ligne).value;

    // on recupere la date
    getline(ist, ligne);
    std::istringstream date_in(attribute_extrator(ligne).value);
    date_in >> d_date;

    // on recupere l'heure de debut
    getline(ist, ligne);
    std::istringstream debut_in(attribute_extrator(ligne).value);
    debut_in >> d_horaires[0];

    // on recupere l'heure de fin
    getline(ist, ligne);
    std::istringstream fin_in(attribute_extrator(ligne).value);
    fin_in >> d_horaires[1];

    d_participants = new LPersonne();
    ist >> *d_participants;
    getline(ist, ligne);
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
    if(d_date < r.d_date)
       return true;

    else if(d_date != r.d_date)
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

bool rdv::overlap(const date& d, const heure& debut, const heure& fin) const
{
    if (!(d_date == d))
        return false;

    if(debut.estEntre(h_debut(), h_fin()) || fin.estEntre(h_debut(), h_fin()))
        return true;

    return false;
}

bool rdv::contient(std::string& str) const
{
    std::size_t trouvee;

    std::string nom = d_nom;

    std::transform(nom.begin(), nom.end(), nom.begin(), ::tolower);
    std::transform(str.begin(), str.end(), str.begin(), ::tolower);

    trouvee = nom.find(str);
    return (trouvee != std::string::npos);
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

rdv& rdv::operator=(const rdv &r)
{
    d_nom = r.d_nom;
    d_date = r.d_date;
    d_horaires = r.d_horaires;
    d_description = r.d_description;
    d_localisation = r.d_localisation;
    *d_participants = *r.d_participants;

    return *this;
}

std::ostream& operator<<(std::ostream& ost, const rdv& r){
    r.save(ost);
    return ost;
}

std::istream& operator>>(std::istream& ist, rdv& r){
    r.load(ist);
    return ist;
}
