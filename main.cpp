/*
 * TP4 - Comparaison de performances
 * Sans vector - Utilisation de tableaux statiques pour le jeu de données
 */

#include <iostream>
#include <ctime>      // Pour clock()
#include "utilitaire_generation.h"
#include "type_def.h"
#include "utilitaires.h"
#include "repertoire.h"

using namespace std;

// Nombre total de personnes pour le test
const int NB_PERSONNES = 1000;
// Nombre d'opérations pour la recherche et suppression
const int NB_TESTS = 100;

int main() {
    // ---------------------------------------------------------
    // ETAPE 0 : PRÉPARATION DU JEU DE DONNÉES
    // ---------------------------------------------------------
    cout << "Generation des " << NB_PERSONNES << " personnes..." << endl;
    
    // On crée un tableau simple pour stocker les données temporairement
    // Cela permet d'ajouter exactement les mêmes personnes dans la liste et le tableau
    personne jeuDeTest[NB_PERSONNES];
    
    for(int i = 0; i < NB_PERSONNES; i++) {
        jeuDeTest[i] = genererPersonne();
    }

    clock_t start, end;
    double cpu_time_used;

    // =========================================================
    // PARTIE 1 : LISTE CHAÎNÉE
    // =========================================================
    cout << "\n-----------------------------------------" << endl;
    cout << "       TESTS LISTE CHAINEE" << endl;
    cout << "-----------------------------------------" << endl;

    elementListe* maListe = nullptr;

    // --- TEST 1 : AJOUT ---
    start = clock();
    for(int i = 0; i < NB_PERSONNES; i++) {
        maListe = ajouter(jeuDeTest[i], maListe);
    }
    end = clock();
    cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;
    cout << "Temps AJOUT (" << NB_PERSONNES << ") : " << cpu_time_used << " s" << endl;

    // --- TEST 2 : AFFICHAGE ---
    // (L'affichage console est très lent, ne t'étonne pas si ça prend du temps)
    start = clock();
    // afficher(maListe); // DECOMMENTER SI BESOIN (pollue la console)
    end = clock();
    cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;
    cout << "Temps AFFICHAGE : " << cpu_time_used << " s (desactive)" << endl;

    // --- TEST 3 : RECHERCHE ---
    // On cherche les 100 premières personnes du jeu de test
    start = clock();
    for(int i = 0; i < NB_TESTS; i++) {
        rechercher(jeuDeTest[i], maListe);
    }
    end = clock();
    cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;
    cout << "Temps RECHERCHE (" << NB_TESTS << ") : " << cpu_time_used << " s" << endl;

    // --- TEST 4 : SUPPRESSION ---
    start = clock();
    for(int i = 0; i < NB_TESTS; i++) {
        maListe = supprimer(jeuDeTest[i], maListe);
    }
    end = clock();
    cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;
    cout << "Temps SUPPRESSION (" << NB_TESTS << ") : " << cpu_time_used << " s" << endl;

    // Nettoyage mémoire Liste (Important en C++)
    while (maListe != nullptr) {
        elementListe* tmp = maListe->suivant;
        delete maListe;
        maListe = tmp;
    }

    // =========================================================
    // PARTIE 2 : TABLEAU TRIÉ
    // =========================================================
    cout << "\n-----------------------------------------" << endl;
    cout << "       TESTS TABLEAU TRIE" << endl;
    cout << "-----------------------------------------" << endl;

    tableauTrie* monTableau = new tableauTrie;
    monTableau->nbElements = 0;

    // --- TEST 1 : AJOUT ---
    start = clock();
    for(int i = 0; i < NB_PERSONNES; i++) {
        // J'utilise ici la version avec pointeur (*) car c'est la plus performante
        // Si tu as gardé la version sans pointeur, adapte l'appel
        ajouterTab(jeuDeTest[i], monTableau);
    }
    end = clock();
    cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;
    cout << "Temps AJOUT (" << NB_PERSONNES << ") : " << cpu_time_used << " s" << endl;

    // --- TEST 2 : AFFICHAGE ---
    start = clock();
    // afficherTab(monTableau); // DECOMMENTER SI BESOIN
    end = clock();
    cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;
    cout << "Temps AFFICHAGE : " << cpu_time_used << " s (desactive)" << endl;

    // --- TEST 3 : RECHERCHE ---
    start = clock();
    for(int i = 0; i < NB_TESTS; i++) {
        rechercherTab(jeuDeTest[i], monTableau);
    }
    end = clock();
    cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;
    cout << "Temps RECHERCHE (" << NB_TESTS << ") : " << cpu_time_used << " s" << endl;

    // --- TEST 4 : SUPPRESSION ---
    // Note : pour que la suppression marche, il faut que ta fonction accepte
    // de supprimer quelqu'un qui existe vraiment. On utilise le jeuDeTest.
    start = clock();
    for(int i = 0; i < NB_TESTS; i++) {
        monTableau = supprimerTab(jeuDeTest[i], monTableau);
    }
    end = clock();
    cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;
    cout << "Temps SUPPRESSION (" << NB_TESTS << ") : " << cpu_time_used << " s" << endl;

    // Nettoyage mémoire Tableau
    delete monTableau;
    return 0;
}