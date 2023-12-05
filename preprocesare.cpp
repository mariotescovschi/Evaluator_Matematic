#include "preprocesare.h"
#include "structuriDeDate.h"
#include <iostream>

void initiere_tree(){
    tree = new Node;
    tree -> left = NULL;
    tree -> right = NULL;
    tree -> middle = NULL;
}

void prestabilire_putere(){
    putere['+'] = 5;
    putere['-'] = 5;
    putere['*'] = 4;
    putere['/'] = 4;
    putere['^'] = 3;
    putere['#'] = 2;
    putere['<'] = 2;
    putere['>'] = 2;
    putere['='] = 2;
}

void prestabilire_alte_functii(){
    strcpy(alte_functii[0], "sin");
    strcpy(alte_functii[1], "cos");
    strcpy(alte_functii[2], "tan");
    strcpy(alte_functii[3], "cot");
    strcpy(alte_functii[4], "log");
    strcpy(alte_functii[5], "ln");
    strcpy(alte_functii[6], "sqrt");
    strcpy(alte_functii[7], "abs");
    strcpy(alte_functii[8], "exp");
    strcpy(alte_functii[9], "arctg");
}

void prestabilire_semne(){
    semne[0] = '+';
    semne[1] = '-';
    semne[2] = '*';
    semne[3] = '/';
    semne[4] = '^';
    semne[5] = '#';
    semne[6] = '<';
    semne[7] = '>';
    semne[8] = '=';
}
void preprocesare(){
    initiere_tree();
    prestabilire_putere();
    prestabilire_alte_functii();
    prestabilire_semne();
}