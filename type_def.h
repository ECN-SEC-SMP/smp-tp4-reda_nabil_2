#ifndef TYPE_DEF_H
#define TYPE_DEF_H





#include <string>
#include <iostream>
using namespace std;

typedef struct personne {
    string nom;
    string prenom;
    string numero;
} personne;

typedef struct elementListe {
    personne one;
    elementListe* suivant;
} elementListe;

const int MAX_TAILLE = 100; // Taille fixe pour l'exemple

typedef struct tableauTrie {
    personne tab[MAX_TAILLE]; // Le tableau de données
    int nbElements;           // Combien de cases sont utilisées
} repertoire;

#endif