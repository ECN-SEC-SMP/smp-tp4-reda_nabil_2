/*
 * Nom1 Nom2
 * TP4 
 * 
 * .......
 * 
 */


#include <iostream>
#include "utilitaire_generation.h"
#include "type_def.h"
#include "utilitaires.h"
#include "repertoire.h"
using namespace std;


int main(){
    int idx=0;
    personne firstone = genererPersonne();
    personne secondone = genererPersonne();
    personne thirdone = genererPersonne();
    personne fourthone = genererPersonne();
    elementListe* myList = nullptr; // liste vide au départ
    cout << "---- Affichage personne ----" << endl;
    affichagePersonne( firstone);
    affichagePersonne( secondone);
    affichagePersonne( thirdone);
    affichagePersonne(fourthone);
    

    myList = ajouter(firstone, myList);
    myList = ajouter(secondone, myList);
    myList = ajouter(thirdone, myList);

    idx = rechercher(secondone, myList);
    cout << "---- indice du prenom 2 ----" << endl;
    cout << idx << endl;
    cout << "---- Affiche la liste non supp ----" << endl;
    afficher(myList);
    cout << "---- affiche la liste supprimer el 2 ---" << endl;
    myList = supprimer(secondone, myList);
    afficher(myList);
    // libérer toute la liste
    elementListe* tmp;
    while (myList != nullptr) {
        tmp = myList->suivant;
        delete myList;
        myList = tmp;
    }
    cout << "---- Partie tableau ----" << endl;

    tableauTrie *tabl = new tableauTrie; // on reserve un emplacement mémoire au tableau
    
    tabl->nbElements = 0;

    tabl = ajouterTab(firstone, tabl);
    tabl = ajouterTab(secondone, tabl);
    tabl = ajouterTab(thirdone, tabl);
    tabl = ajouterTab(fourthone, tabl);

    afficherTab(tabl);

    idx = rechercherTab(fourthone, tabl);

    cout << idx << endl;
    cout << "---- Tableau supprimé ----" << endl;
    tabl = supprimerTab(fourthone, tabl);
    afficherTab(tabl);
    delete tabl;
    return 0;
}
 