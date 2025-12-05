#include "type_def.h"
#include <iostream>
#include "utilitaire_generation.h"

personne genererPersonne(){
    personne newpersonne;
    string nom_personne = genererNomPrenom("Noms_TP4.txt", 1000);
    string prenom_personne = genererNomPrenom("Prenoms_TP4.txt", 11612);
    string tel = genererTel();
    newpersonne.nom = nom_personne;
    newpersonne.prenom = prenom_personne;
    newpersonne.numero = tel;
    return newpersonne;
}

elementListe* creerElementListe(personne hey){
    elementListe* newElement = new elementListe;
    newElement->one = hey;
    newElement->suivant = nullptr;
    return newElement;
}

void affichagePersonne(personne reda){
    std::cout << "Nom: "<<reda.nom << " Prenom: " << reda.prenom << " tel: " << reda.numero << std::endl;
}

bool egalitePersonne(personne reda, personne nabil){
    if(reda.nom == nabil.nom  ){
        if(reda.prenom == reda.prenom){
            if( nabil.numero == reda.numero){
                return true;
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

bool comparerPersonne(personne one, personne two){
    if (one.nom < two.nom){
        return true;
    } else if ( one.nom > two.nom){
        return false;
    } else {
        if(one.prenom < two.prenom){
            return true;
        } else if (one.prenom > two.prenom){
            return false;
        } else {
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