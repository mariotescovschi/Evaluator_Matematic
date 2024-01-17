#include <cstring>
#include <cmath>
#include <iostream>
#include <string>
#include "parsareExpresie.h"
#include "structuriDeDate.h"
#include "verificareParanteze.h"
#include "meniuCalculator.h"
using namespace std;

int lista_erori[6];
//SE CAUTA O FUNCTIE MATEMATICA IN EXPRESIA CURENTA SI SE MEMOREAZA IN FIUL MIDDLE
bool cautare_functie_matematica(Node *nod){
    string aux_functie;
    for(int i = 0; i < nod -> functie.size(); i++)
        if(nod -> functie[i] == '(') {
            aux_functie = nod->functie;
            aux_functie.resize(i);

            for (int i = 0; i < 10; i++)
                if (aux_functie == alte_functii[i]) {
                    nod->middle = new Node;
                    nod->left = nullptr;
                    nod->right = nullptr;

                    for (int j = aux_functie.size(); j < nod->functie.size(); j++)
                        nod->middle->functie.push_back(nod->functie[j]);

                    nod->functie.resize(aux_functie.size());

                    return true;
                }
        }

    return false;
}

bool operand_prioritar(Node *nod){
    int poz_aux = 0, putere_aux = 0, nr_paranteze = 0;
    char operandul;
    bool cond = false;
    for(int i = nod -> functie.size() - 1; i >= 0; i--) {

        if(nod -> functie[i] == '-' && (i == 0 || nod -> functie[i - 1] == '(' || nod -> functie[i - 1] == '[' || nod -> functie[i - 1] == '{' || nod -> functie[i - 1] == '^'))
            continue;

        if(strchr(semne, nod -> functie[i]) != nullptr) {
            char operand_aux = *strchr(semne, nod->functie[i]);
            if (nr_paranteze == 0 && putere[operand_aux] > putere_aux)
                poz_aux = i,
                putere_aux = putere[operand_aux],
                operandul = operand_aux,
                cond = true;
        }

        nr_paranteze += (nod -> functie[i] == ')');
        nr_paranteze -= (nod -> functie[i] == '(');
    }

    if(cond){
        nod -> left = new Node;
        nod -> right = new Node;
        nod -> middle = nullptr;

        nod->left->functie = nod->functie;
        nod->left->functie.resize(poz_aux);

        for(int i = poz_aux + 1; i < nod -> functie.size(); i++)
            nod -> right -> functie.push_back(nod -> functie[i]);

        nod -> functie = operandul;
    }

    return cond;
}

double operatie(string tip_operatie, double a, double b){
    switch(tip_operatie[0]){
        case '+':
            return a + b;
        case '-':
            return a - b;
        case '*':
            return a * b;
        case '/':
            return a / b;
        case '^':
            return pow(a, b);
        case '#':
            return a != b;
        case '<':
            return a < b;
        case '>':
            return a > b;
        case '=':
            return a == b;
    }
    if(tip_operatie ==  "sin")
        return sin(a);
    if(tip_operatie == "cos")
        return cos(a);
    if(tip_operatie == "tan")
        return tan(a);
    if(tip_operatie == "cot")
        return 1/tan(a);
    if(tip_operatie == "log")
        return log10(a);
    if(tip_operatie == "ln")
        return log(a);
    if(tip_operatie == "sqrt")
        return sqrt(a);
    if(tip_operatie == "abs")
        return abs(a);
    if(tip_operatie == "exp")
        return exp(a);
    if(tip_operatie == "arctg")
        return atan(a);

    return 0;
}

double valoare_variabila(string variabila){
    if(variabila == "pi")
        return 3.14159265358979323846;
    if(variabila == "e")
        return 2.71828182845904523536;

    if(variabila[0] >= '0' && variabila[0] <= '9' || (variabila[0] == '-' && variabila[1] >= '0' && variabila[1] <= '9'))
        return stod(variabila);

    for(int i = 1; i <= numar_variabile; i++)
        if(variabila == var[i].nume)
            return var[i].valoare;

    var[++numar_variabile].nume = variabila;

    eticheta_necunoscuta = variabila;
    avem_necunoscute = true;
    //citirea variabilei
    while(avem_necunoscute)
        desenare_input_valoare_variabila();


    var[numar_variabile].citit = true;
    var[numar_variabile].valoare = valoare_necunoscuta;

    return var[numar_variabile].valoare;
}

//SE VERIFICA DACA EXPRESIA CURENTA ARE OPERAND PRIORITAR, IMPARTINDU-SE IN 2, FUNCTIE MATEMATICA, CONTINUAND
//SAU DACA ESTE UN NUMAR/VARIABIL, CALCULANDU-SE REZULTATUL
void parsare_expresie(Node *nod){
    if(!corect)
        return;
    verificare_paranteze(nod);

    if(operand_prioritar(nod))
        parsare_expresie(nod -> left),
        parsare_expresie(nod -> right),
        nod -> var = operatie(nod -> functie, nod -> left -> var, nod -> right -> var);

    else if(cautare_functie_matematica(nod))
        parsare_expresie(nod -> middle),
        nod -> var = operatie(nod -> functie, nod -> middle -> var, 0);

    else {
        nod -> left = nullptr;
        nod -> right = nullptr;
        nod -> middle = nullptr;
        nod->var = valoare_variabila(nod->functie);
    }

    if(nod -> functie[0] == '/' && nod -> right -> var == 0)
        lista_erori[0] = 1,
        corect = false;

    if(nod -> functie == "sqrt" && nod -> middle -> var < 0)
        lista_erori[4] = 1,
        corect = false;

    if((nod -> functie == "log" || nod -> functie == "ln") && nod -> middle -> var <= 0)
        lista_erori[5] = 1,
        corect = false;

}