# U-AGENDA

## À propos

U-AGENDA est une application de gesion d’un carnet de rendez-
vous basée sur l'utilisation des listes chaînées

## Table des matières

- 🪧 [À propos](#à-propos)
- 📦 [Prérequis](#prérequis)
- 🚀 [Installation](#installation)
- 🏗️ [Construit avec](#construit-avec)
- 📚 [Aides](#aides)

## Prérequis

- Qt
- CodeBlocks
- bats

## Installation

[Étapes avec exemples des commandes à lancer pour installer le projet en local]


## Construit avec
- Qt

### Langages
- C++

## Aides

```bash
# Cloner le dépôt
git clone https://github.com/josiashod/u_agenda.git

# Création d'une branche
git checkout -b <nom-branche>

# Changer de branch
git checkout <nom-branche>

# Poussez une nouvelle branch sur le dépôt
git push --set-upstream origin <nom-branche>

# Faire un commit des modifications
git commit -m "Details des modifications effectué"
# Ex: git commit -m "Implémentation du construteur par défaut"

# Poussez ces modifications sur le dépôt distant
git push

# Annuler un commit
git reset --soft HEAD~1
# ou
git checkout
# NB: annule juste le git commit et non les modifications

# Revenir à un commit en arrière
git reset --hard HEAD~1
```

## Utiliation du fichier makefile
```bash
# Compilation
make

# Exécution des tests
make test

# Suppression des fichiers
make clean
```
