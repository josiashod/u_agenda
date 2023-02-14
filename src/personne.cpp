#include "personne.h"
#include "error.h"

// CONSTRUCTEURS
personne::personne() : d_status{OK}
{}

personne::personne(std::string nom
, std::string prenom
, std::string numero
, std::string email
): d_nom{nom}, d_prenom{prenom}
, d_numero{numero}
, d_email{email}
, d_status{OK}
{
    if (!personne::testEmail(d_email) || !personne::testNumero(d_numero))
        d_status = ERR_WITH_VALUE;
}

personne::~personne()
{}

// ACCESSEURS & MUTATEURS
std::string personne::nom() const
{
    return d_nom;
}

void personne::setNom(std::string nom)
{
    d_nom = nom;
}

std::string personne::prenom() const
{
    return d_prenom;
}

void personne::setPrenom(std::string prenom)
{
    d_prenom = prenom;
}

std::string personne::numero() const
{
    return d_numero;
}

void personne::setNumero(std::string numero)
{
    d_numero = numero;

    if (personne::testNumero(numero))
        d_status = OK;
    else
        d_status = ERR_WITH_VALUE;
}

std::string personne::email() const
{
    return d_email;
}

void personne::setEmail(std::string email)
{
    d_email = email;

    if (personne::testEmail(email))
        d_status = OK;
    else
        d_status = ERR_WITH_VALUE;
}

personne* personne::suiv() const
{
    return d_suiv;
}

unsigned int personne::status() const
{
    return d_status;
}

bool personne::testEmail(const std::string email)
{
    const std::regex email_regex{"^[\\w-\\.]+@([\\w-]+\\.)+[\\w-]{2,4}"};
    std::smatch m;

    return (std::regex_match(email, m, email_regex));
}

bool personne::testNumero(const std::string numero)
{
    const std::regex numero_regex{"(0|\\+33|0033)[1-9][0-9]{8}"};
    std::smatch m;

    return (std::regex_match(numero, m, numero_regex));
}

std::string personne::nomComplet() const
{
    return (((d_prenom.length() > 0) ? d_prenom + " " : "")
    + ((d_nom.length() > 0) ? d_nom : ""));
}

bool personne::contient(std::string& str) const
{
    std::size_t trouvee;

    trouvee = nomComplet().find(str);
    return (trouvee != std::string::npos);
}

bool personne::vientAvant(const personne& p) const
{
    return (nomComplet().compare(p.nomComplet()) < 0);
}

void personne::affiche(std::ostream& ost) const
{
    ost << '{' + d_nom + ", " + d_prenom + ", " + d_numero + ", " + d_email + '}' << std::endl;
}

void personne::lire(std::istream &ist)
{
    char c;
    std::string test;

    ist >> c >> d_nom >> d_prenom >> d_email >> d_numero;

    d_nom = d_nom.substr(0, d_nom.length() - 1);
    d_prenom = d_prenom.substr(0, d_prenom.length() - 1);
    d_email = d_email.substr(0, d_email.length() - 1);
    d_numero = d_numero.substr(0, d_numero.length() - 1);
}

void personne::exporter(std::ostream& ost) const
{
    ost << "BEGIN:VCARD" << std::endl;
    ost << "VERSION:2.1" << std::endl;
    ost << "N:" << d_nom + ";" + d_prenom + ";;;" << std::endl;
    ost << "FN:" << nomComplet() << std::endl;
    ost << "TEL;TYPE=CELL:" << d_numero << std::endl;
    ost << "EMAIL:" << d_email << std::endl;
    ost << "END:VCARD" << std::endl;
}

void personne::importer(std::istream& ist)
{
    std::string ligne;
    std::size_t pos;

    ist >> ligne;
    while(!ist.eof() || ligne != "END:VCARD")
    {
        // On recupere le nom et le prenom
        if (ligne.substr(0, 2) == "N:")
        {
            pos = ligne.find(";");
            d_nom = ligne.substr(2, pos - 2);
            ligne = ligne.substr(pos + 1, ligne.length());
            d_prenom = ligne.substr(0, ligne.find(";"));
        }
        // On recupere le numero de telephone
        else if (ligne.substr(0, 3) == "TEL")
        {
            pos = ligne.find(":");
            d_numero = ligne.substr(pos + 1);
        }

        // On recupere le numero de telephone
        else if (ligne.substr(0, 5) == "EMAIL")
        {
            d_email = ligne.substr(6);
        }

        ist >> ligne;
    }

}


bool personne::operator==(const personne& p) const
{
    return (nomComplet().compare(p.nomComplet()) == 0);
}

bool personne::operator>(const personne& p) const
{
    return vientAvant(p);
}

std::istream& operator>>(std::istream& ist, personne& p)
{
    p.lire(ist);
    return ist;
}

std::ostream& operator<<(std::ostream& ost, const personne& p)
{
    p.affiche(ost);
    return ost;
}