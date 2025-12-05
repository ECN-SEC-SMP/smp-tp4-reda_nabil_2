#include "type_def.h"
#include "utilitaires.h"
#include <iostream>
#include "utilitaire_generation.h"

using namespace std;

elementListe *ajouter(personne hello, elementListe *debut)
{
    elementListe *nouveau = new elementListe;
    nouveau->one = hello;

    // insertion en tête ou liste vide
    if (debut == nullptr || comparerPersonne(hello, debut->one))
    {
        nouveau->suivant = debut;
        return nouveau;
    }

    elementListe *prec = debut;
    elementListe *l = debut->suivant;

    // insertion au milieu ou en fin
    while (l != nullptr && !comparerPersonne(hello, l->one))
    {
        prec = l;
        l = l->suivant;
    }

    prec->suivant = nouveau;
    nouveau->suivant = l;
    return debut;
}

tableauTrie *ajouterTab(personne someone, tableauTrie *tabl)
{
    tableauTrie* new_tab = tabl; // Juste un alias pour simplifier

    // 1. Cas Tableau Plein
    if (new_tab->nbElements == MAX_TAILLE) {
        std::cout << "Erreur : Tableau plein !" << std::endl;
        return new_tab;
    }

    // 2. Trouver la position d'insertion (i)
    int i = 0;
    // On cherche tant que 'someone' est "plus grand" que la personne dans le tableau
    // Note : On utilise 'nbElements' actuel (avant incrémentation) pour ne pas lire n'importe quoi
    while (i < new_tab->nbElements && !comparerPersonne(someone, new_tab->tab[i])) {
        i++;
    }

    // 3. Décalage des éléments vers la DROITE
    // On part de la fin (la nouvelle case vide) et on descend jusqu'à i + 1
    // Exemple : si on insère en 1, on déplace la case 2 vers 3, puis 1 vers 2.
    for (int j = new_tab->nbElements; j > i; j--) {
        new_tab->tab[j] = new_tab->tab[j-1];
    }

    // 4. Insertion et Mise à jour
    new_tab->tab[i] = someone; // On insère à la place libérée
    new_tab->nbElements++;     // On augmente le compteur APRES avoir tout fini

    return new_tab;
}

void afficher(elementListe *debut)
{
    elementListe *l = debut;
    while (l->suivant != nullptr)
    {
        affichagePersonne(l->one);
        l = l->suivant;
    }
    affichagePersonne(l->one);
}

void afficherTab(tableauTrie *tabl){
    std::cout << "DEBUG: Nombre d'elements trouves : " << tabl->nbElements << std::endl;
    for(int i=0; i<tabl->nbElements;i++){
        std::cout << "Nom: "<<tabl->tab[i].nom << " Prenom: " << tabl->tab[i].prenom << " tel: "<< tabl->tab[i].numero<< std::endl;
    }
}

int rechercherTab(personne persona, tableauTrie *tab){
    int i=0;
    while(!egalitePersonne(persona, tab->tab[i])){
        i++;
    }
    if(egalitePersonne(persona,tab->tab [i])){
        return i;
    }else {
        return -1;
    }
    
}

int rechercher(personne persona, elementListe *debut)
{
    int i = 0;
    elementListe *l = debut;

    while (l != nullptr)
    {
        if (egalitePersonne(persona, l->one))
        {
            return i; // trouvé
        }
        l = l->suivant;
        i++;
    }

    return -1; // non trouvé ou liste vide
}

elementListe *supprimer(personne persona, elementListe *debut)
{
    elementListe *l = debut;
    elementListe *prec = nullptr;
    int x = 0;
    int i = 0;
    x = rechercher(persona, debut);
    while (i != x)
    {
        prec = l;
        l = l->suivant;
        i++;
    }
    prec->suivant = l->suivant;
    delete l;
    return debut;
}

tableauTrie* supprimerTab(personne persona, tableauTrie* tab){
    int index= 0;
    index = rechercherTab(persona, tab);

    if(index == -1){
        cout << "l'élement n'existe pas." << endl;
        return tab;
    }
    for(int j=index; j<tab->nbElements; j++){
        tab->tab[j] = tab->tab[j+1];
        
    }
    tab->nbElements--;
    return tab;
}
