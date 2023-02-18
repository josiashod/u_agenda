#include "LPersonne.h"
#include <fstream>

LPersonne::LPersonne(): d_tete{nullptr}
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

personne* LPersonne::tete() const
{
    return d_tete;
}

personne* LPersonne::queue() const
{
    return d_queue;
}

unsigned int LPersonne::taille() const
{
    return d_taille;
}

int LPersonne::ajouter(std::string nom, std::string prenom
    , std::string numero
    , std::string email
)
{
    personne *p = new personne{nom, prenom, numero, email};
    int status = p->d_status;


    if(status != OK)
    {
        delete p;
        return (status);
    }

    d_taille++;

    if(!d_tete)
    {
        d_tete = p;
        d_queue = p;
        return (OK);
    }

    personne *crt = d_tete;


    while(crt && (*crt > *p))
        crt = crt->d_suiv;

    if(!crt)
    {
        d_queue->d_suiv = p;
        p->d_prec = d_queue;
        d_queue = p;
    }
    else
    {
        if (crt == d_tete)
            d_tete = p;
        else
            crt->d_prec->d_suiv = p;

        p->d_prec = crt->d_prec;
        p->d_suiv = crt;
        crt->d_prec = p;
    }

    return (OK);
}

void LPersonne::ajouter(personne*& p)
{
    if (!p)
        return;

    personne *crt = d_tete;

    d_taille++;

    if(!d_tete)
    {
        d_tete = p;
        d_queue = p;
        return;
    }


    while(crt && (*crt > *p))
        crt = crt->d_suiv;

    if(!crt)
    {
        d_queue->d_suiv = p;
        p->d_prec = d_queue;
        d_queue = p;
    }
    else
    {
        if (crt == d_tete)
            d_tete = p;
        else
            crt->d_prec->d_suiv = p;
        p->d_prec = crt->d_prec;
        p->d_suiv = crt;
        crt->d_prec = p;
    }
}

personne* LPersonne::rechercher(std::string nomComplet) const
{
    if (nomComplet.length() <= 0)
        return (nullptr);
    
    personne *crt = d_tete;

    while(crt && (nomComplet != crt->nomComplet()))
        crt = crt->d_suiv;
    
    if(!crt)
        return (nullptr);

    return (crt);
}

LPersonne* LPersonne::rechercherPlusieurs(std::string str) const
{
    LPersonne *lp = new LPersonne{};

    personne *crt = d_tete;

    while(crt)
    {
        if (crt->contient(str))
        {
            auto p{new personne{*crt}};
            lp->ajouter(p);
        }
        crt = crt->d_suiv;
    }

    return (lp);
}

int LPersonne::supprimer(std::string nomComplet)
{
    if (nomComplet.length() <= 0)
        return (ERR_WITH_VALUE);

    personne *as = d_tete;

    while(as && (nomComplet != as->nomComplet()))
        as = as->d_suiv;

    if(!as)
        return (ERR_NOT_FOUND);

    if(as == d_tete)
    {
        d_tete = as->d_suiv;
        d_tete->d_prec = nullptr;
    }
    else if(as == d_queue)
    {
        d_queue = as->d_prec;
        as->d_prec->d_suiv = nullptr;
    }
    else
    {
        as->d_suiv->d_prec = as->d_prec;
        as->d_prec->d_suiv = as->d_suiv;
    }

    d_taille--;
    delete as;

    return (OK);
}

int LPersonne::supprimer(personne*& p)
{

    if(!p)
        return (ERR_NOT_FOUND);

    if(p == d_tete)
    {
        d_tete = p->d_suiv;
        d_tete->d_prec = nullptr;
    }
    else if(p == d_queue)
    {
        d_queue = p->d_prec;
        p->d_prec->d_suiv = nullptr;
    }
    else
    {
        p->d_suiv->d_prec = p->d_prec;
        p->d_prec->d_suiv = p->d_suiv;
    }

    d_taille--;
    delete p;

    return (OK);
}

void LPersonne::exporter(std::ostream& ost) const
{
    personne *crt = d_tete;

    while(crt)
    {
        crt->exporter(ost);
        crt = crt->d_suiv;
    }
}

void LPersonne::exporterDans(const std::string fichier) const
{
    std::ofstream oft{fichier};

    exporter(oft);
    oft.close();
}

void LPersonne::importer(std::istream& ist)
{
    while(!ist.eof())
    {
        personne *p{new personne{}};
        p->importer(ist);
        if(p->nomComplet().length() > 0)
            ajouter(p);
        else
            delete p;
    }
}

int LPersonne::importerDepuis(const std::string fichier)
{
    std::ifstream ift{fichier};

    if (!ift)
        return ERR_WITH_VALUE;

    importer(ift);
    ift.close();

    return (OK);
}