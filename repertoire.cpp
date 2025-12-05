#include "type_def.h"
#include "utilitaires.h"
#include <iostream>
#include "utilitaire_generation.h"

using namespace std;

// Fonction pour ajouter une personne dans la liste tout en gardant l'ordre alphabétique
elementListe *ajouter(personne hello, elementListe *debut)
{
    elementListe *nouveau = new elementListe; // Crée le nouveau maillon
    nouveau->one = hello;

    // Cas 1 : Insertion au tout début (si liste vide ou si 'hello' est plus petit que le premier)
    if (debut == nullptr || comparerPersonne(hello, debut->one))
    {
        nouveau->suivant = debut;
        return nouveau; // Le nouveau devient la tête de liste
    }

    elementListe *prec = debut;
    elementListe *l = debut->suivant;

    // Cas 2 : On parcourt la liste pour trouver la bonne place (insertion au milieu ou fin)
    while (l != nullptr && !comparerPersonne(hello, l->one))
    {
        prec = l;       // Garde une trace du précédent
        l = l->suivant; // Avance
    }

    // On insère le maillon entre 'prec' et 'l'
    prec->suivant = nouveau;
    nouveau->suivant = l;
    return debut;
}

// Fonction pour ajouter dans le tableau en gardant l'ordre (insertion triée)
tableauTrie *ajouterTab(personne someone, tableauTrie *tabl)
{
    tableauTrie* new_tab = tabl;

    // Sécurité : on vérifie si le tableau est déjà plein
    if (new_tab->nbElements == MAX_TAILLE) {
        std::cout << "Erreur : Tableau plein !" << std::endl;
        return new_tab;
    }

    // Etape 1 : On cherche l'index 'i' où on doit insérer la personne
    int i = 0;
    while (i < new_tab->nbElements && !comparerPersonne(someone, new_tab->tab[i])) {
        i++;
    }

    // Etape 2 : On décale tous les éléments suivants vers la DROITE pour faire de la place
    for (int j = new_tab->nbElements; j > i; j--) {
        new_tab->tab[j] = new_tab->tab[j-1];
    }

    // Etape 3 : On met la personne dans le "trou" créé et on augmente le compteur
    new_tab->tab[i] = someone; 
    new_tab->nbElements++;

    return new_tab;
}

// Affiche le contenu de la liste chaînée
void afficher(elementListe *debut)
{
    elementListe *l = debut;
    // Parcourt jusqu'à l'avant-dernier élément
    while (l->suivant != nullptr)
    {
        affichagePersonne(l->one);
        l = l->suivant;
    }
    // Affiche le dernier élément
    affichagePersonne(l->one);
}

// Affiche le contenu du tableau
void afficherTab(tableauTrie *tabl){
    std::cout << "DEBUG: Nombre d'elements trouves : " << tabl->nbElements << std::endl;
    // Boucle simple sur toutes les cases remplies
    for(int i=0; i<tabl->nbElements;i++){
        std::cout << "Nom: "<<tabl->tab[i].nom << " Prenom: " << tabl->tab[i].prenom << " tel: "<< tabl->tab[i].numero<< std::endl;
    }
}

// Recherche linéaire dans le tableau (case par case)
int rechercherTab(personne persona, tableauTrie *tab){
    int i=0;
    // Tant qu'on n'a pas trouvé la personne, on avance
    while(!egalitePersonne(persona, tab->tab[i])){
        i++;
    }
    // Vérification finale si trouvé
    if(egalitePersonne(persona,tab->tab [i])){
        return i; // Retourne l'index
    }else {
        return -1; // Pas trouvé
    }
}

// Recherche linéaire dans la liste chaînée
int rechercher(personne persona, elementListe *debut)
{
    int i = 0;
    elementListe *l = debut;

    // Parcourt toute la liste
    while (l != nullptr)
    {
        if (egalitePersonne(persona, l->one))
        {
            return i; // Trouvé, retourne la position
        }
        l = l->suivant;
        i++;
    }

    return -1; // Fin de liste atteinte sans trouver
}

// Supprime un élément de la liste chaînée
elementListe *supprimer(personne persona, elementListe *debut)
{
    elementListe *l = debut;
    elementListe *prec = nullptr;
    int x = 0;
    int i = 0;
    
    // Récupère l'index de l'élément à supprimer
    x = rechercher(persona, debut);
    
    // Avance jusqu'à cet élément (Note: c'est peu efficace de re-parcourir)
    while (i != x)
    {
        prec = l;
        l = l->suivant;
        i++;
    }
    
    // "Saute" le maillon à supprimer en reliant le précédent au suivant
    prec->suivant = l->suivant;
    delete l; // Libère la mémoire
    return debut;
}

// Supprime un élément du tableau
tableauTrie* supprimerTab(personne persona, tableauTrie* tab){
    int index= 0;
    // Trouve où est la personne
    index = rechercherTab(persona, tab);

    if(index == -1){
        cout << "l'élement n'existe pas." << endl;
        return tab;
    }
    
    // Décale tous les éléments suivants vers la GAUCHE pour écraser la case à supprimer
    for(int j=index; j<tab->nbElements; j++){
        tab->tab[j] = tab->tab[j+1];
    }
    
    // Réduit le nombre d'éléments du tableau
    tab->nbElements--;
    return tab;
}