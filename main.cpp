/*
 * TP4 - Comparaison de performances
 * Sans vector - Utilisation de tableaux statiques pour le jeu de données
 */

#include <iostream>
#include <ctime>      // Pour utiliser clock() et mesurer le temps
#include "utilitaire_generation.h"
#include "type_def.h"
#include "utilitaires.h"
#include "repertoire.h"

using namespace std;

// On définit combien de personnes on va créer (1000)
const int NB_PERSONNES = 1000;
// On définit combien de recherches/suppressions on va tester (100)
const int NB_TESTS = 100;

int main() {
    // Etape 0 : Préparation des données
    cout << "Generation des " << NB_PERSONNES << " personnes..." << endl;
    
    // On crée un tableau temporaire pour stocker les gens générés.
    // C'est important pour ajouter exactement les mêmes personnes dans la liste et le tableau après.
    personne jeuDeTest[NB_PERSONNES];
    
    for(int i = 0; i < NB_PERSONNES; i++) {
        jeuDeTest[i] = genererPersonne(); // Crée un nom/prénom aléatoire
    }

    clock_t start, end;
    double cpu_time_used;

    // Partie 1 : Liste Chaînée
    cout << "\nTESTS LISTE CHAINEE" << endl;

    // On initialise la liste à vide (pointeur null)
    elementListe* maListe = nullptr;

    // Test 1 : ajout
    start = clock(); // Démarre le chrono
    for(int i = 0; i < NB_PERSONNES; i++) {
        // Ajoute chaque personne dans la liste (crée un nouveau maillon)
        maListe = ajouter(jeuDeTest[i], maListe);
    }
    end = clock(); // Arrête le chrono
    cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;
    cout << "Temps AJOUT (" << NB_PERSONNES << ") : " << cpu_time_used << " s" << endl;

    // Test 2 : affichage
    start = clock();
    // afficher(maListe); // On le laisse en commentaire car écrire dans la console est très lent
    end = clock();
    cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;
    cout << "Temps AFFICHAGE : " << cpu_time_used << " s (desactive)" << endl;

    // Test 3 : recherche
    start = clock();
    for(int i = 0; i < NB_TESTS; i++) {
        // Parcourt la liste un par un pour trouver la personne
        rechercher(jeuDeTest[i], maListe);
    }
    end = clock();
    cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;
    cout << "Temps RECHERCHE (" << NB_TESTS << ") : " << cpu_time_used << " s" << endl;

    // Test 4 : suppression
    start = clock();
    for(int i = 0; i < NB_TESTS; i++) {
        // Trouve la personne, change les pointeurs et supprime le maillon
        maListe = supprimer(jeuDeTest[i], maListe);
    }
    end = clock();
    cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;
    cout << "Temps SUPPRESSION (" << NB_TESTS << ") : " << cpu_time_used << " s" << endl;

    // Nettoyage mémoire Liste
    // Indispensable en C++ : on boucle pour delete chaque maillon restant
    while (maListe != nullptr) {
        elementListe* tmp = maListe->suivant;
        delete maListe;
        maListe = tmp;
    }

    // Partie 2 : Tableau Trié
    cout << "\nTESTS TABLEAU TRIE" << endl;

    // Allocation dynamique de la structure qui contient notre tableau
    tableauTrie* monTableau = new tableauTrie;
    monTableau->nbElements = 0;

    // Test 1 : ajout
    start = clock();
    for(int i = 0; i < NB_PERSONNES; i++) {
        // Insère la personne au bon endroit pour garder le tableau trié (décale les autres)
        ajouterTab(jeuDeTest[i], monTableau);
    }
    end = clock();
    cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;
    cout << "Temps AJOUT (" << NB_PERSONNES << ") : " << cpu_time_used << " s" << endl;

    // Test 2 : affichage
    start = clock();
    // afficherTab(monTableau); 
    end = clock();
    cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;
    cout << "Temps AFFICHAGE : " << cpu_time_used << " s (desactive)" << endl;

    // Test 3 : recherche
    start = clock();
    for(int i = 0; i < NB_TESTS; i++) {
        // Recherche dans le tableau (souvent plus rapide car accès direct ou dichotomie)
        rechercherTab(jeuDeTest[i], monTableau);
    }
    end = clock();
    cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;
    cout << "Temps RECHERCHE (" << NB_TESTS << ") : " << cpu_time_used << " s" << endl;

    // Test 4 : suppression
    start = clock();
    for(int i = 0; i < NB_TESTS; i++) {
        // Supprime l'élément et décale tous les suivants vers la gauche pour boucher le trou
        monTableau = supprimerTab(jeuDeTest[i], monTableau);
    }
    end = clock();
    cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;
    cout << "Temps SUPPRESSION (" << NB_TESTS << ") : " << cpu_time_used << " s" << endl;

    // Nettoyage mémoire Tableau
    delete monTableau;
    
    return 0;
}