#include "verificareParanteze.h"
#include "structuriDeDate.h"
#include <iostream>
using namespace std;

bool paranteze_exterioare(char functie[150]){

    int nr_paranteze = 0;
    for(int i = 0; i < strlen(functie) - 1; i++) {
        if (functie[i] == '(')
            nr_paranteze++;

        else if (functie[i] == ')')
            nr_paranteze--;

        if(nr_paranteze == 0)
            return false;
    }
    return true;
}


bool are_paranteze_exterioare(char functie[150]){
    return functie[0] == '(' && functie[strlen(functie) - 1] == ')';
}

void stergere_paranteze_exterioare(Node *nod){

    if(paranteze_exterioare(nod -> functie))
        nod -> functie[strlen(nod -> functie) - 1] = '\0',
                strcpy(nod -> functie, nod -> functie + 1);
}

void verificare_paranteze(Node *nod){
    if(are_paranteze_exterioare(nod -> functie))
        stergere_paranteze_exterioare(nod);
}

