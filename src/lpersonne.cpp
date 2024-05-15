#include "lpersonne.h"
#include <fstream>

LPersonne::LPersonne(): d_tete{nullptr}
, d_queue{nullptr}
, d_taille{0}
{}

LPersonne::LPersonne(const LPersonne& lp): d_tete{nullptr}
, d_queue{nullptr}
, d_taille{0}
{
    if(lp.d_tete)
    {
        d_tete = new personne(*lp.d_tete);

        personne *crt = d_tete;
        personne *lp_crt = lp.d_tete->d_suiv;

        while(lp_crt)
        {
            crt->d_suiv = new personne(*lp_crt);
            crt->d_suiv->d_prec = crt;
            crt = crt->d_suiv;

            lp_crt = lp_crt->d_suiv;
        }

        d_queue = crt;
    }
}


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

void LPersonne::ajouter(const personne& pers)
{
    if (pers.d_status != OK || pers.nomComplet().empty())
        return;

    auto p{new personne{pers}};

    d_taille++;

    if(!d_tete)
    {
        d_tete = p;
        d_queue = p;
        return;
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
            auto p{personne{*crt}};
            lp->ajouter(p);
        }
        crt = crt->d_suiv;
    }

    return (lp);
}

bool LPersonne::estDansLaListe(const personne& p) const
{
    return (rechercher(p.nomComplet()) != nullptr);
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

    if (!as->d_prec && !as->d_suiv)
        d_tete = nullptr;
    else if(as == d_tete)
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

int LPersonne::supprimer(const personne& p)
{

    if(p.d_status != OK || p.nomComplet().empty())
        return (ERR_NOT_FOUND);

    personne *as;

    if(p.nomComplet() == d_tete->nomComplet())
    {
        as = d_tete;
        d_tete = d_tete->d_suiv;
        d_tete->d_prec = nullptr;
    }
    else if(p.nomComplet() == d_queue->nomComplet())
    {
        as = d_queue;
        d_queue = d_queue->d_prec;
        d_queue->d_suiv = nullptr;
    }
    else
    {
        personne *crt = d_tete;
        while(crt && crt->nomComplet() != p.nomComplet())
            crt = crt->d_suiv;

        if(!crt)
            return (ERR_NOT_FOUND);
        as = crt;
        crt->d_suiv->d_prec = crt->d_prec;
        crt->d_prec->d_suiv = crt->d_suiv;
    }

    d_taille--;
    if(!d_taille)
        d_tete = nullptr;
    delete as;

    return (OK);
}

void LPersonne::save(std::ostream& ost, int profondeur) const
{
    personne *crt = nullptr;
    ost << "[" << std::endl;
    
    if(d_tete)
    {
        d_tete->affiche(ost, profondeur + 1);
        crt = d_tete->d_suiv;
    }

    while(crt != nullptr)
    {
        ost << ',' << std::endl;
        crt->affiche(ost, profondeur + 1);
        crt = crt->d_suiv;
    }
    ost << std::endl << std::string(profondeur - 1, '\t') + "]";
}

void LPersonne::load(std::istream& ist)
{
    const std::regex end_rgx{R"(.*])"};
    std::smatch match;
    std::string ligne{""};

    getline(ist, ligne);

    while(!ist.eof())
    {
        personne p{};
        ist >> p;
        if(p.d_status == OK && !p.nomComplet().empty())
            ajouter(p);
        
        int ist_lastpos = ist.tellg();
        getline(ist, ligne);
        if(std::regex_match(ligne, match, end_rgx))
            break;
        else
            ist.seekg(ist_lastpos);
    }
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
        personne p{};
        p.importer(ist);
        if(!p.nomComplet().empty())
            ajouter(p);
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

bool LPersonne::operator==(const LPersonne& lp) const
{
    if(d_taille != lp.d_taille)
        return false;

    personne *crt = d_tete;
    personne *acmp = lp.d_tete;

    while(crt != nullptr && acmp != nullptr)
    {
        if(!(*crt == *acmp))
            return false;

        crt = crt->d_suiv;
        acmp = acmp->d_suiv;
    }

    return true;
}

LPersonne& LPersonne::operator=(const LPersonne& lp)
{
    if(&lp == this)
        return *this;
    
    personne *crt1 = d_tete;
    personne *crt2 = lp.d_tete;
    personne *prec = nullptr;

    while (crt1 != nullptr && crt2 != nullptr)
	{
		*crt1 = *crt2;
		prec = crt1;
		crt1 = crt1->d_suiv;
		crt2 = crt2->d_suiv;
	}
	if (crt1 != nullptr)
	{
		if (prec != nullptr)
        {
			prec->d_suiv = nullptr;
            d_queue = prec;
        }
		else
			d_tete = nullptr;
		while(crt1)
		{
			prec = crt1;
			crt1 = crt1->d_suiv;
			delete prec;
		}
	}
	else if (crt2 != nullptr)
	{
		while(crt2 != nullptr)
		{
			crt1 = new personne(*crt2);
            d_queue = crt1;
			if (prec == nullptr)
				d_tete = crt1;
			else
			{
				prec->d_suiv = crt1;
				crt1->d_prec = prec;
			}
			prec = crt1;
			crt2 = crt2->d_suiv;
		}
	}

    d_queue = prec;
    this->d_taille = lp.d_taille;

	return *this;
}


std::istream& operator>>(std::istream& ist, LPersonne& lp)
{
    lp.load(ist);
    return ist;
}
std::ostream& operator<<(std::ostream& ost, const LPersonne& lp)
{
    lp.save(ost);
    return ost;
}
