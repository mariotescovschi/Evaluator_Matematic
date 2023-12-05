#include <iostream>
#include <iomanip>
#include <queue>
#include "verificareParanteze.h"
#include "structuriDeDate.h"
#include "preprocesare.h"

using namespace std;

Node *tree;
int putere[256];
char alte_functii[10][12];
char semne[10];


void citire_functie(){
    char functie[150];
    cin.getline(functie, 150);
    strcpy(tree -> functie, functie);
}

queue<pair<pair<Node, int>, pair<int,int>>> q;
char afisaj[100][100][10];


bool cautare_functie_matematica(Node *nod){
    char aux[12];
    for(int i = 0; i < strlen(nod -> functie); i++)
        if(nod -> functie[i] == '('){
            strncpy(aux, nod -> functie, i);
            aux[i] = '\0';
            break;
        }

    for(int i = 0; i < 10; i++)
        if(strcmp(aux, alte_functii[i]) == 0){
            nod -> middle = new Node;
            strcpy(nod -> middle -> functie, nod -> functie + strlen(aux));
            strcpy(nod -> functie, aux);
            return true;
        }
    return false;
}

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
        case '/':{
            if(b == 0)
                cout << "Impartire la 0";
            return a / b;
        }
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

void parsare_functie(Node *nod){

    verificare_paranteze(nod);

    if(operand_prioritar(nod))
        parsare_functie(nod -> left),
                parsare_functie(nod -> right),
                nod -> var = operatie(nod -> functie, nod -> left -> var, nod -> right -> var);

    else if(cautare_functie_matematica(nod))
        parsare_functie(nod -> middle),
                nod -> var = operatie(nod -> functie, nod -> middle -> var, 0);

    else
        nod -> var = atof(nod -> functie);

}

void afisare_functie(Node *tree, int niv){

    for(int i = 0; i < 100; i++)
        for(int j = 0; j < 100; j++)
            afisaj[i][j][0] = ' ';

    q.push({{*tree, niv},{0, 50}});
    while(!q.empty()){
        Node nod = q.front().first.first;
        int niv = q.front().first.second;
        int x = q.front().second.first;
        int y = q.front().second.second;
        cout << x << ' ' << y << ' ' << endl;
        q.pop();
        strcpy(afisaj[x][y], nod.functie);
        if(nod.left != NULL)
            afisaj[x+1][y-(5-niv)][0] = '/';
        if(nod.right != NULL)
            afisaj[x+1][y+(5-niv)][0] = '\\';

        if(nod.middle != NULL)
            afisaj[x+1][y+1][0] = '|';

        if(nod.left != NULL)
            q.push({{*nod.left, niv + 1}, {x+2, y-(5-niv)}});

        if(nod.right != NULL)
            q.push({{*nod.right, niv + 1}, {x+2, y+(5-niv)}});

        if(nod.middle != NULL)
            q.push({{*nod.middle, niv + 1}, {x+2, y+1}});
    }
}

void afisare2(Node *nod){

    cout << nod -> functie << " ";
    if(nod -> left != NULL)
        afisare2(nod -> left);
    if(nod -> right != NULL)
        afisare2(nod -> right);
    if(nod -> middle != NULL)
        afisare2(nod -> middle);
}

int main() {
    preprocesare();
    citire_functie();
    parsare_functie(tree);
    afisare_functie(tree, 0);
    for(int i = 0; i < 20; i++, cout << '\n')
        for(int j = 0; j < 100; j++)
            cout << afisaj[i][j];

    cout << "Raspunsul este: ";
    cout << tree -> var << endl;
    return 0;
}
