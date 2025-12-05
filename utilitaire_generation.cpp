/*
*
*  utilitaire génération
*   fichiers utilitaires pour générer, noms, prénoms et n° de tel.
*/

#include <iostream>

#include <fstream>
#include <ctime>
#include <cstdlib>
using namespace std;

string genererNomPrenom(string list, int nb)
{
    string inputString[nb];
    fstream input;

    //initialisation de la graine de srand au temps courant à la nanoseconde
    struct timespec spec;
    clock_gettime(CLOCK_REALTIME, &spec);
    srand(spec.tv_nsec);
    
    input.open(list.c_str(), ios::in);
    for(int i=0; i<nb; i++){
        input>>inputString[i];
    }
    input.close();
    return inputString[rand()%nb];
}

string genererTel(){
    //initialisation de la graine de srand au temps courant à la nanoseconde
    struct timespec spec;
    clock_gettime(CLOCK_REALTIME, &spec);
    srand(spec.tv_nsec);

    string num = "0"+to_string(rand()%7+1);
    for(int i =0;i<8;i++){
        num = num+to_string(rand()%10);
    }
    return num;
}
