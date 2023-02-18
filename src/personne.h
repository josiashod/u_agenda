#ifndef __PERSONNE_H__
#define __PERSONNE_H__

#include <iostream>
#include <string>
#include <regex>

class LPersonne;

class personne
{
    public:
        // CONSTRUCTEURS
        personne();
        personne(std::string nom, std::string prenom
        , std::string numero
        , std::string email
        );
        personne(const personne& p);

        // ACCESSEURS & MUTATEURS
        std::string nom() const;
        void setNom(std::string nom);
        std::string prenom() const;
        void setPrenom(std::string prenom);
        std::string numero() const;
        void setNumero(std::string numero);
        std::string email() const;
        void setEmail(std::string email);
        personne* suivant() const;
        personne* precedent() const;
        unsigned int status() const;

        // METHODES
        static bool testEmail(const std::string email);
        static bool testNumero(const std::string numero);

        std::string nomComplet() const;
        bool contient(std::string& str) const;
        bool vientAvant(const personne& p) const;
        void affiche(std::ostream& ost = std::cout) const;
        void lire(std::istream& ist = std::cin);
        void exporter(std::ostream& ost) const;
        void importer(std::istream& ist);

        bool operator==(const personne& p) const;
        bool operator>(const personne& p) const;
        friend std::istream& operator>>(std::istream& ist, personne& p);
        friend std::ostream& operator<<(std::ostream& ost, const personne& p);

        friend class LPersonne;
    private:
        std::string d_nom;
        std::string d_prenom;
        std::string d_numero;
        std::string d_email;
        personne* d_suiv;
        personne* d_prec;
        unsigned int d_status;
};

#endif
