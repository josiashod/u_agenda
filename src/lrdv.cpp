#include "lrdv.h"
#include "lpersonne.h"
#include "date.h"
#include "heure.h"
#include <fstream>

LRdv::LRdv(): d_tete{nullptr}
{}

LRdv::~LRdv()
{
    rdv* as = d_tete;

    while(as)
	{
        d_tete = as->d_suiv;
        delete as;
        as = d_tete;
    }
}

rdv* LRdv::tete() const { return d_tete; }

int LRdv::ajouter(const rdv& r)
{
	auto nr{new rdv{r}};

	if (!d_tete)
	{
		d_tete = nr;
		return (OK);
	}

	rdv *crt = d_tete;

	if ((*nr) > (*crt))
	{
		nr->d_suiv = d_tete;
		d_tete = nr;
		return (OK);
	}

	while(crt->d_suiv && *crt->d_suiv > *nr)
		crt = crt->d_suiv;

	nr->d_suiv = crt->d_suiv;
	crt->d_suiv = nr;

	return (OK);
}

rdv* LRdv::trouverUn(std::string nom) const
{
	rdv *crt = d_tete;
	while(crt != nullptr && nom != crt->d_nom){
		crt=crt->d_suiv;
	}
	if(!crt)
		return nullptr;

	return crt;
}

LRdv* LRdv::trouverParDate(const date& d) const
{
	rdv *crt = d_tete;
	auto lr{new LRdv{}};

	while(crt)
	{
		if (crt->d_date == d)
			lr->ajouter(*crt);
		crt = crt->d_suiv;
	}

	return (lr);
}

LRdv* LRdv::trouverParPersonne(const personne& p) const
{
	rdv *crt = d_tete;
	auto lr{new LRdv{}};

	while(crt)
	{
		if (crt->d_participants->estDansLaListe(p))
			lr->ajouter(*crt);
		crt = crt->d_suiv;
	}

	return (lr);
}

LRdv* LRdv::rechercherPlusieurs(std::string str) const
{
    LRdv *lr = new LRdv{};

    rdv *crt = d_tete;

    while(crt)
    {
        if (crt->contient(str))
        {
            auto r{rdv{*crt}};
            lr->ajouter(r);
        }
        crt = crt->d_suiv;
    }

    return (lr);
}

void LRdv::miseAJourParticipant(const personne& old, const personne& newp)
{
	rdv *crt = d_tete;

	while(crt)
	{
        personne* p = crt->d_participants->rechercher(old.nomComplet());

		if(p)
			*p = newp;

		crt = crt->d_suiv;
	}
}

bool LRdv::overlap(const personne& p, const date& d
	, const heure& debut, const heure& fin) const
{
	rdv* crt = d_tete;

	while(crt)
	{
		if(crt->overlap(d, debut, fin) && (crt->d_participants && crt->d_participants->estDansLaListe(p)))
			break;

		crt = crt->d_suiv;
	}

	return (crt != nullptr);
}

void LRdv::supprimer(std::string nom)
{
    rdv *crt = d_tete;

	if(crt->d_nom == nom){
		d_tete = crt->d_suiv;
		delete crt;
		return;
	}

    while(crt->d_suiv && nom != crt->d_suiv->d_nom)
		crt = crt->d_suiv;

	if (crt)
	{
		rdv *as = crt->d_suiv;
		crt->d_suiv = as->d_suiv;
		delete as;
	}
}

void LRdv::exporter(std::ostream& ost) const
{
	ost << "BEGIN:VCALENDAR" << std::endl;
	ost << "VERSION:2.0" << std::endl;
	ost << "PRODID:-//uagenda/event//v1.0//FR" << std::endl;

	rdv *crt = d_tete;
    while(crt != nullptr)
    {
        (*crt).exporter(ost);
        crt = crt->d_suiv;
    }

	ost << "END:VCALENDAR" << std::endl;
}

void LRdv::exporter(std::ostream& ost, const date& d_debut, const date& d_fin) const
{
	ost << "BEGIN:VCALENDAR" << std::endl;
	ost << "VERSION:2.0" << std::endl;
	ost << "PRODID:-//uagenda/event//v1.0//FR" << std::endl;

	rdv *crt = d_tete;
	while(crt && crt->d_date < d_debut)
		crt = crt->d_suiv;

	while(crt && crt->d_date <= d_fin)
	{
        (*crt).exporter(ost);
        crt = crt->d_suiv;
    }

	ost << "END:VCALENDAR" << std::endl;
}

void LRdv::exporter(std::ostream& ost, const rdv& r) const
{
	ost << "BEGIN:VCALENDAR" << std::endl;
	ost << "VERSION:2.0" << std::endl;
	ost << "PRODID:-//uagenda/event//v1.0//FR" << std::endl;

	r.exporter(ost);

	ost << "END:VCALENDAR" << std::endl;
}

void LRdv::exporterDans(const std::string fichier) const
{
    std::ofstream oft{fichier};

    exporter(oft);
    oft.close();
}

void LRdv::save(std::ostream& ost) const
{
	if(!d_tete)
		return;
	
	rdv *crt = nullptr;
    ost << "[" << std::endl;

    if(d_tete)
    {
        d_tete->save(ost, 1);
        crt = d_tete->d_suiv;
    }

    while(crt != nullptr)
    {
        ost << ',' << std::endl;
        crt->save(ost, 1);
        crt = crt->d_suiv;
    }

    ost << std::endl << "]";
}

void LRdv::load(std::istream& ist)
{
    const std::regex end_rgx{R"(.*])"};
    std::smatch match;
    std::string ligne{""};

    getline(ist, ligne);

    while(!ist.eof())
    {
        rdv *r{new rdv{}};
        r->load(ist);

        if(!r->nom().empty())
            ajouter(*r);
        else
            delete r;
    }
}
