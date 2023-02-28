#include "lrdv.h"
#include "date.h"
#include "heure.h"

LRdv::LRdv(): d_tete{nullptr}
{}

LRdv::~LRdv()
{
    rdv* as = d_tete;

    while(as){
        d_tete = as->d_suivant;
        delete as;
        as = d_tete;
    }
}

rdv* LRdv::tete() const { return d_tete; }

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

rdv* recherche(std::string nom) const
{
	rdv *crt = d_tete;
	while(crt != nullptr && nom != crt->nom){
		crt=crt->d_suiv;
	}
	if(!crt)
		return;

	return crt;
}