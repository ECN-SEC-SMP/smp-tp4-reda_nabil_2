#include "type_def.h"

elementListe* ajouter(personne hello, elementListe* debut);
void afficher(elementListe* debut);
int rechercher(personne persona,elementListe* debut);
elementListe* supprimer(personne persona, elementListe* debut);


tableauTrie* ajouterTab(personne someone, tableauTrie *tabl);
void afficherTab(tableauTrie *tabl);
int rechercherTab(personne persona, tableauTrie *tab);
tableauTrie* supprimerTab(personne persona, tableauTrie* tab);