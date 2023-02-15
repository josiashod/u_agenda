#ifndef __L_PERSONNE_H__
#define __L_PERSONNE_H__

class personne;

class LPersonne {
    // CONSTRUCTEURS
    LPersonne();
    ~LPersonne();

    //

    private:
        personne* d_tete;
        personne* d_queue;
        unsigned int d_taille;
};

#endif