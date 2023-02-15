#include "LPersonne.h"
#include "personne.h"

LPersonne::LPersonne(): d_tete{nullptr}
, d_queue{nullptr}
, d_queue{nullptr}
, d_taille{0}
{}

LPersonne::~LPersonne()
{
    personne* as = d_tete;

    while(as != nullptr)
    {
        d_tete = as->d_suiv;
        delete as;
        as = d_tete;
    }
}