#include "verificareParanteze.h"
#include "structuriDeDate.h"
#include <string>
using namespace std;

bool paranteze_exterioare(string functie){

    int nr_paranteze = 0;
    for(int i = 0; i < functie.size() - 1; i++) {
        if (functie[i] == '(')
            nr_paranteze++;

        else if (functie[i] == ')')
            nr_paranteze--;

        if(nr_paranteze == 0)
            return false;
    }
    return true;
}


bool are_paranteze_exterioare(string functie){
    return functie[0] == '(' && functie[functie.size() - 1] == ')';
}

void stergere_paranteze_exterioare(Node *nod){

    if(are_paranteze_exterioare(nod -> functie) && nod -> functie.size() == 2)
        lista_erori[2] = 1,
        corect = false;

    else if(paranteze_exterioare(nod -> functie)) {
        for (int i = 0; i < nod->functie.size() - 1; i++)
            nod->functie[i] = nod->functie[i + 1];

        nod->functie.resize(nod->functie.size() - 2);
    }

}

void verificare_paranteze(Node *nod){
    if(are_paranteze_exterioare(nod -> functie))
        stergere_paranteze_exterioare(nod);
}

