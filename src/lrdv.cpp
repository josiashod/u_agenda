#include "lrdv.h"
#include "lpersonne.h"
#include "rdv.h"
#include "date.h"
#include "heure.h"

LRdv::LRdv(): d_tete{nullptr}
{}

LRdv::~LRdv()
{
    rdv* as = d_tete;

    while(as){
        d_tete = as->d_suiv;
        delete as;
        as = d_tete;
    }
}

rdv* LRdv::tete() const { return d_tete; }

// bool LRdv::personneOverlapRdv(const LRdv* lr, const personne* p
// , const rdv* r)
// {

// 	rdv *crt = lr->d_tete;

// 	while(crt)
// 	{
// 		if(!crt->participants()->estDansLaListe(crtP))
// 			continue;

// 		if(r->overlap(*crt))
// 			return (true);
		
// 		crt = crt->d_suiv;
// 	}

// 	return (false);
// }

int LRdv::ajouter(rdv*& nr)
{
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

LRdv* LRdv::trouverParDate(const date& d)
{
	rdv *crt = d_tete;
	auto lr{new LRdv{}};

	while(crt)
	{
		if (crt->d_date == d)
			lr->ajouter(crt);
		crt = crt->d_suiv;
	}

	return (lr);
}

LRdv* LRdv::trouverParPersone(const personne& p)
{
	rdv *crt = d_tete;
	auto lr{new LRdv{}};

	while(crt)
	{
		if (crt->d_participants->estDansLaListe(&p))
			lr->ajouter(crt);
		crt = crt->d_suiv;
	}

	return (lr);
}

bool LRdv::overlap(const personne& p, const date& d
	, const heure* h)
{
	auto lr = trouverParDate(d);
	LRdv* tmp = nullptr;

	if (lr == nullptr)
	{
		delete lr;
		return true;
	}

	tmp = lr;
	lr = lr->trouverParPersone(p);
	delete tmp;

	if(!lr)
	{
		delete lr;
		return true;
	}

	rdv* crt = lr->d_tete;
	while(crt && !h->estEntre(crt->h_debut(), crt->h_fin()))
		crt = crt->d_suiv;

	bool res = (crt != nullptr);
	delete lr;

	return res;
}

void LRdv::supprimer(std::string nom)
{
    rdv *crt = d_tete;

	if(crt->d_nom == nom){
		d_tete = crt->d_suiv;
		delete crt;	
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