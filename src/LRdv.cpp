#include "LRDv.h"

LRdv::LRdv(): d_tete{nullptr}, d_queue{nullptr}, d_suivant{nullptr} {}

LRdv::~LRdv()
{
    rdv* rdv1 = d_tete;
    while(rdv1){
        rdv* rdvsuivant = rdv1->d_suivant;
        delete rdv1;
        rdv1 = rdvsuivant;
    }
}

rdv* LRdv::tete() const { return d_tete; }

rdv* LRdv::queue() const { return d_queue; }

void LRdv::supprimer(std::string nom)
{
    rdv* r1 = d_tete, *precr1= nullptr;
    while(r1 !== nullptr && nom != r1->nom){
			precr1 = r1;
			r1 = r1->d_suiv;
	}
	if(r1 == d_tete){
		d_tete = r1->d_suiv;
		delete r1;
		r1 = nullptr;		
	}
	if (r1->d_suiv = nullptr){
		delete r1->d_suiv;
		r1->d_suiv=nullptr;
	}
		r1 = precr1->d_suiv;
		precr1->d_suiv; = r1->d_suiv;
		delete r1;
		
	
}

rdv* recherche(std::string nom) const
{
	rdv *rv = d_tete;
	while(rv != nullptr && nom != rv->nom){
		rv=rv->d_suiv;
	}
	if(!rv){
		return;
	}
	return rv;
}