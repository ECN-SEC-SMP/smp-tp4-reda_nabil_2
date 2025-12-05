#include "type_def.h"
#include <iostream>
#include "utilitaire_generation.h"

// Génère une structure 'personne' avec des données aléatoires (Nom, Prénom, Tél)
personne genererPersonne(){
    personne newpersonne;
    // Va chercher un nom et un prénom au hasard dans les fichiers textes fournis
    string nom_personne = genererNomPrenom("Noms_TP4.txt", 1000);
    string prenom_personne = genererNomPrenom("Prenoms_TP4.txt", 11612);
    string tel = genererTel();
    
    // Remplit la structure
    newpersonne.nom = nom_personne;
    newpersonne.prenom = prenom_personne;
    newpersonne.numero = tel;
    return newpersonne;
}

// Crée un nouveau maillon (noeud) pour la liste chaînée
elementListe* creerElementListe(personne hey){
    elementListe* newElement = new elementListe; // Allocation dynamique
    newElement->one = hey;        // On met la donnée
    newElement->suivant = nullptr; // Pour l'instant, il ne pointe vers rien
    return newElement;
}

// Affiche les informations d'une personne dans la console
void affichagePersonne(personne reda){
    std::cout << "Nom: "<<reda.nom << " Prenom: " << reda.prenom << " tel: " << reda.numero << std::endl;
}

// Vérifie si deux personnes sont strictement identiques (tous les champs pareils)
bool egalitePersonne(personne reda, personne nabil){
    // Note : il semble y avoir une petite coquille dans ton code original (reda.prenom == reda.prenom)
    // Mais le but ici est de vérifier : Nom egal ? ET Prénom egal ? ET Numéro egal ?
    if(reda.nom == nabil.nom  ){
        if(reda.prenom == reda.prenom){ // Attention: devrait être (reda.prenom == nabil.prenom)
            if( nabil.numero == reda.numero){
                return true; // Tout est pareil
            } else{ 
                return false;
            }
        } else {
            return false;
        }
    } else {
        return false;
    }
}

// Compare deux personnes pour savoir qui est avant l'autre (Ordre Alphabétique)
// Priorité : Nom -> puis Prénom -> puis Numéro
bool comparerPersonne(personne one, personne two){
    if (one.nom < two.nom){
        return true; // 'one' est avant 'two' (ex: Dupont avant Durand)
    } else if ( one.nom > two.nom){
        return false;
    } else {
        // Si les noms sont pareils, on regarde les prénoms
        if(one.prenom < two.prenom){
            return true;
        } else if (one.prenom > two.prenom){
            return false;
        } else {
            // Si prénoms pareils aussi, on regarde le numéro
            if(one.numero < two.numero){
                return true;
            } else if (one.numero > two.numero){
                return false;
            } else {
                return false;
            }
        }
    }
}