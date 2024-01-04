#include <cstring>
#include <cmath>
#include <iostream>
#include <string>
#include "parsareExpresie.h"
#include "structuriDeDate.h"
#include "verificareParanteze.h"
#include "meniuCalculator.h"
using namespace std;
int numar_variabile = 0;
Variabile var[100];

int lista_erori[4];
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

//SE CAUTA O OPERATIE PRIORITARA IN EXPRESIA CURENTA SI SE IMPARTE EXPRESIA IN DOUA
bool operand_prioritar(Node *nod){
    int poz_aux = 0, putere_aux = 0, nr_paranteze = 0;
    char operandul;
    bool cond = false;
    for(int i = nod -> functie.size() - 1; i >= 0; i--) {

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

void citirea_valorii_variabilei(string variabila){
    Text prompt;
    prompt.setFont(font);
    prompt.setString("Introduceti valoarea lui " + variabila + ": ");
    prompt.setCharacterSize(24);
    prompt.setFillColor(negru);

    FloatRect textBounds = prompt.getLocalBounds();
    Vector2f pozitiePrompt(5, 200);
    prompt.setPosition(pozitiePrompt);
    window.draw(prompt);

    RectangleShape inputBox(Vector2f(50, textBounds.height + 10));
    inputBox.setPosition(pozitiePrompt.x + textBounds.width + 10, 200 + (textBounds.height - 10) / 2.);
    inputBox.setFillColor(alb);
    inputBox.setOutlineColor(negru);
    inputBox.setOutlineThickness(4.f);
    window.draw(inputBox);

    Text inputText("", font, 24);
    inputText.setFillColor(negru);
    inputText.setPosition(50, 50);
    window.draw(inputText);

    RectangleShape butonOK(Vector2f(100, 50));
    butonOK.setPosition(inputBox.getPosition().x + 10, inputBox.getPosition().y + 10);
    butonOK.setFillColor(rosu);
    butonOK.setOutlineColor(negru);
    butonOK.setOutlineThickness(4.f);
    window.draw(butonOK);

    Text textOK("OK", font, 24);
    textOK.setFillColor(negru);
    textOK.setPosition(50, 50);
    window.draw(textOK);

    procesare_evenimente(inputText);

    window.display();
}

double valoare_variabila(string variabila){
    if(variabila == "pi")
        return 3.14159265358979323846;
    if(variabila == "e")
        return 2.71828182845904523536;

    if(variabila[0] >= '0' && variabila[0] <= '9')
        return stod(variabila);

    for(int i = 1; i <= numar_variabile; i++)
        if(variabila == var[i].nume)
            return var[i].valoare;

    var[++numar_variabile].nume = variabila;

    avem_variabile = true;
    //citirea variabilei
    while(avem_variabile) {
        citirea_valorii_variabilei(variabila);
    }

    var[numar_variabile].citit = true;

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

}