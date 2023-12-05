#include "parsareExpresie.h"
#include "structuriDeDate.h"
#include "verificareParanteze.h"
#include <cstring>
#include <cmath>
#include <iostream>
using namespace std;
int numar_variabile = 0;
Variabile var[100];
//SE CAUTA O FUNCTIE MATEMATICA IN EXPRESIA CURENTA SI SE MEMOREAZA IN FIUL MIDDLE
bool cautare_functie_matematica(Node *nod){

    char aux_functie[12];
    for(int i = 0; i < strlen(nod -> functie); i++)
        if(nod -> functie[i] == '('){
            strncpy(aux_functie, nod -> functie, i);
            aux_functie[i] = '\0';
            break;
        }

    for(int i = 0; i < 10; i++)
        if(strcmp(aux_functie, alte_functii[i]) == 0){
            nod -> middle = new Node;
            strcpy(nod -> middle -> functie, nod -> functie + strlen(aux_functie));
            strcpy(nod -> functie, aux_functie);
            return true;
        }

    return false;
}

//SE CAUTA O OPERATIE PRIORITARA IN EXPRESIA CURENTA SI SE IMPARTE EXPRESIA IN DOUA
bool operand_prioritar(Node *nod){

    int poz_aux = 0, putere_aux = 0, nr_paranteze = 0;
    char operandul;
    bool cond = false;
    for(int i = strlen(nod -> functie) - 1; i >= 0; i--) {

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

        strcpy(nod -> right -> functie, nod -> functie + poz_aux + 1);

        nod -> functie[poz_aux] = '\0';
        strcpy(nod -> left -> functie, nod -> functie);

        nod -> functie[0] = operandul;
        nod -> functie[1] = '\0';
    }

    return cond;
}

float operatie(char tip_operatie[15], float a, float b){
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
    if(strcmp(tip_operatie, "sin") == 0)
        return sin(a);
    if(strcmp(tip_operatie, "cos") == 0)
        return cos(a);
    if(strcmp(tip_operatie, "tan") == 0)
        return tan(a);
    if(strcmp(tip_operatie, "cot") == 0)
        return 1 / tan(a);
    if(strcmp(tip_operatie, "log") == 0)
        return log10(a);
    if(strcmp(tip_operatie, "ln") == 0)
        return log(a);
    if(strcmp(tip_operatie, "sqrt") == 0)
        return sqrt(a);
    if(strcmp(tip_operatie, "abs") == 0)
        return abs(a);
    if(strcmp(tip_operatie, "exp") == 0)
        return exp(a);
    if(strcmp(tip_operatie, "arctg") == 0)
        return atan(a);
}

double valoare_variabila(char variabila[15]){
    if(strcmp(variabila, "pi") == 0)
        return 3.14159265358979323846;
    if(strcmp(variabila, "e") == 0)
        return 2.71828182845904523536;

    if(variabila[0] >= '0' && variabila[0] <= '9')
        return atof(variabila);

    for(int i = 1; i <= numar_variabile; i++)
        if(strcmp(variabila, var[i].nume) == 0)
            return var[i].valoare;

    strcpy(var[++numar_variabile].nume, variabila);

    cout << "Introduceti valoarea lui " << variabila << ": ";
    cin >> var[numar_variabile].valoare;
    var[numar_variabile].citit = true;

    return var[numar_variabile].valoare;
}

//SE VERIFICA DACA EXPRESIA CURENTA ARE OPERAND PRIORITAR, IMPARTINDU-SE IN 2, FUNCTIE MATEMATICA, CONTINUAND
//SAU DACA ESTE UN NUMAR/VARIABIL, CALCULANDU-SE REZULTATUL
void parsare_expresie(Node *nod){

    verificare_paranteze(nod);

    if(operand_prioritar(nod))
        parsare_expresie(nod -> left),
        parsare_expresie(nod -> right),
        nod -> var = operatie(nod -> functie, nod -> left -> var, nod -> right -> var);

    else if(cautare_functie_matematica(nod))
        parsare_expresie(nod -> middle),
        nod -> var = operatie(nod -> functie, nod -> middle -> var, 0);

    else
        nod -> var = valoare_variabila(nod -> functie);
}