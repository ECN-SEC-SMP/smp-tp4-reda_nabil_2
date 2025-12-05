/*
 * TP4 - Programme Complet
 * Phase 1 : Tests unitaires (fonctionnement)
 * Phase 2 : Tests de performances (temps d'exécution)
 */

#include <iostream>
#include <ctime>      // Pour clock()
#include "utilitaire_generation.h"
#include "type_def.h"
#include "utilitaires.h"
#include "repertoire.h"

using namespace std;

// Constantes pour la Phase 2 (Performance)
const int NB_PERSONNES = 1000;
const int NB_TESTS = 100;

int main() {
    // =========================================================
    // PHASE 1 : VERIFICATION DU FONCTIONNEMENT (Petit Test)
    // =========================================================
    cout << "##################################################" << endl;
    cout << "#    PHASE 1 : VERIFICATION DU FONCTIONNEMENT    #" << endl;
    cout << "##################################################" << endl;

    int idx = 0;
    // Génération de 4 personnes aléatoires
    personne firstone = genererPersonne();
    personne secondone = genererPersonne();
    personne thirdone = genererPersonne();
    personne fourthone = genererPersonne();

    // --- TEST LISTE CHAINEE (FONCTIONNEL) ---
    elementListe* myList = nullptr; 

    cout << "\n--- Données de test (4 pers) ----" << endl;
    affichagePersonne(firstone);
    affichagePersonne(secondone);
    affichagePersonne(thirdone);
    affichagePersonne(fourthone);
    
    // Ajout
    myList = ajouter(firstone, myList);
    myList = ajouter(secondone, myList);
    myList = ajouter(thirdone, myList);

    // Recherche
    cout << "\n--- Recherche du 2eme element dans la liste ---" << endl;
    idx = rechercher(secondone, myList);
    cout << "Index trouve : " << idx << endl;

    cout << "--- Contenu liste avant suppression ---" << endl;
    afficher(myList);

    // Suppression
    cout << "--- Suppression du 2eme element ---" << endl;
    myList = supprimer(secondone, myList);
    afficher(myList); 

    // Nettoyage Liste Phase 1
    while (myList != nullptr) {
        elementListe* tmp = myList->suivant;
        delete myList;
        myList = tmp;
    }

    // --- TEST TABLEAU TRIE (FONCTIONNEL) ---
    cout << "\n---- Test Tableau Trie (Fonctionnel) ----" << endl;

    tableauTrie *tabl = new tableauTrie;
    tabl->nbElements = 0; 

    // Ajout
    tabl = ajouterTab(firstone, tabl);
    tabl = ajouterTab(secondone, tabl);
    tabl = ajouterTab(thirdone, tabl);
    tabl = ajouterTab(fourthone, tabl);

    afficherTab(tabl); 

    // Recherche
    cout << "--- Recherche de la 4eme personne ---" << endl;
    idx = rechercherTab(fourthone, tabl);
    cout << "Index trouve : " << idx << endl;

    // Suppression
    cout << "--- Suppression de la 4eme personne ---" << endl;
    tabl = supprimerTab(fourthone, tabl);
    afficherTab(tabl);

    // Nettoyage Tableau Phase 1
    delete tabl;


    // =========================================================
    // PHASE 2 : TESTS DE PERFORMANCES (Grand Test)
    // =========================================================
    cout << "\n\n";
    cout << "##################################################" << endl;
    cout << "#      PHASE 2 : TESTS DE PERFORMANCES           #" << endl;
    cout << "##################################################" << endl;

    cout << "Generation des " << NB_PERSONNES << " personnes..." << endl;
    
    // Tableau temporaire pour le jeu de données
    personne jeuDeTest[NB_PERSONNES];
    for(int i = 0; i < NB_PERSONNES; i++) {
        jeuDeTest[i] = genererPersonne();
    }

    clock_t start, end;
    double cpu_time_used;

    // --- LISTE CHAINEE (PERF) ---
    cout << "\n>>> TESTS LISTE CHAINEE (" << NB_PERSONNES << " elements)" << endl;

    elementListe* maListe = nullptr;

    // Test 1 : Ajout
    start = clock();
    for(int i = 0; i < NB_PERSONNES; i++) {
        maListe = ajouter(jeuDeTest[i], maListe);
    }
    end = clock();
    cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;
    cout << "Temps AJOUT : " << cpu_time_used << " s" << endl;

    // Test 2 : Affichage (désactivé pour perf)
    cout << "Temps AFFICHAGE : (desactive pour ne pas polluer)" << endl;

    // Test 3 : Recherche
    start = clock();
    for(int i = 0; i < NB_TESTS; i++) {
        rechercher(jeuDeTest[i], maListe);
    }
    end = clock();
    cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;
    cout << "Temps RECHERCHE (" << NB_TESTS << " op) : " << cpu_time_used << " s" << endl;

    // Test 4 : Suppression
    start = clock();
    for(int i = 0; i < NB_TESTS; i++) {
        maListe = supprimer(jeuDeTest[i], maListe);
    }
    end = clock();
    cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;
    cout << "Temps SUPPRESSION (" << NB_TESTS << " op) : " << cpu_time_used << " s" << endl;

    // Nettoyage Liste Phase 2
    while (maListe != nullptr) {
        elementListe* tmp = maListe->suivant;
        delete maListe;
        maListe = tmp;
    }

    // --- TABLEAU TRIE (PERF) ---
    cout << "\n>>> TESTS TABLEAU TRIE (" << NB_PERSONNES << " elements)" << endl;

    tableauTrie* monTableau = new tableauTrie;
    monTableau->nbElements = 0;

    // Test 1 : Ajout
    start = clock();
    for(int i = 0; i < NB_PERSONNES; i++) {
        ajouterTab(jeuDeTest[i], monTableau);
    }
    end = clock();
    cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;
    cout << "Temps AJOUT : " << cpu_time_used << " s" << endl;

    // Test 2 : Affichage
    cout << "Temps AFFICHAGE : (desactive pour ne pas polluer)" << endl;

    // Test 3 : Recherche
    start = clock();
    for(int i = 0; i < NB_TESTS; i++) {
        rechercherTab(jeuDeTest[i], monTableau);
    }
    end = clock();
    cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;
    cout << "Temps RECHERCHE (" << NB_TESTS << " op) : " << cpu_time_used << " s" << endl;

    // Test 4 : Suppression
    start = clock();
    for(int i = 0; i < NB_TESTS; i++) {
        monTableau = supprimerTab(jeuDeTest[i], monTableau);
    }
    end = clock();
    cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;
    cout << "Temps SUPPRESSION (" << NB_TESTS << " op) : " << cpu_time_used << " s" << endl;

    // Nettoyage Tableau Phase 2
    delete monTableau;
    
    return 0;
}