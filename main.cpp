/*
 * Nom1 Nom2
 * TP4 
 * Programme de test basique pour vérifier que les fonctions (Ajout, Recherche, Suppression)
 * fonctionnent correctement sur la Liste et le Tableau.
 */

#include <iostream>
#include "utilitaire_generation.h"
#include "type_def.h"
#include "utilitaires.h"
#include "repertoire.h"
using namespace std;


int main(){
    int idx=0;
    // Génération de 4 personnes aléatoires pour avoir des données de test
    personne firstone = genererPersonne();
    personne secondone = genererPersonne();
    personne thirdone = genererPersonne();
    personne fourthone = genererPersonne();

    // --- PARTIE LISTE CHAINEE ---
    elementListe* myList = nullptr; // Initialisation obligatoire à null (liste vide)

    cout << "---- Affichage personne ----" << endl;
    // Affiche les données générées pour vérifier visuellement
    affichagePersonne( firstone);
    affichagePersonne( secondone);
    affichagePersonne( thirdone);
    affichagePersonne(fourthone);
    
    // Ajoute 3 personnes dans la liste (l'insertion se fait triée selon ta fonction)
    myList = ajouter(firstone, myList);
    myList = ajouter(secondone, myList);
    myList = ajouter(thirdone, myList);

    // Test de la recherche : doit retourner la position (0, 1, 2...)
    idx = rechercher(secondone, myList);
    cout << "---- indice du prenom 2 ----" << endl;
    cout << idx << endl;

    cout << "---- Affiche la liste non supp ----" << endl;
    afficher(myList);

    // Test de la suppression : retire l'élément et recoud la liste
    cout << "---- affiche la liste supprimer el 2 ---" << endl;
    myList = supprimer(secondone, myList);
    afficher(myList); // Vérifie qu'il a bien disparu

    // Libération de la mémoire (Nettoyage complet de la liste)
    elementListe* tmp;
    while (myList != nullptr) {
        tmp = myList->suivant;
        delete myList;
        myList = tmp;
    }

    // --- PARTIE TABLEAU TRIE ---
    cout << "---- Partie tableau ----" << endl;

    tableauTrie *tabl = new tableauTrie; // Allocation dynamique de la structure
    tabl->nbElements = 0; // Important : initialise le compteur à 0

    // Remplissage du tableau (la fonction gère le tri et le décalage des cases)
    tabl = ajouterTab(firstone, tabl);
    tabl = ajouterTab(secondone, tabl);
    tabl = ajouterTab(thirdone, tabl);
    tabl = ajouterTab(fourthone, tabl);

    afficherTab(tabl); // Vérification du contenu

    // Test recherche dans le tableau
    idx = rechercherTab(fourthone, tabl);
    cout << idx << endl;

    cout << "---- Tableau supprimé ----" << endl;
    // Test suppression : retire l'élément et décale les suivants pour combler le trou
    tabl = supprimerTab(fourthone, tabl);
    afficherTab(tabl);

    // Libération de la mémoire de la structure tableau
    delete tabl;
    
    return 0;
}