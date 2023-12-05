#ifndef UNTITLED8_STRUCTURIDEDATE_H
#define UNTITLED8_STRUCTURIDEDATE_H

struct Variabile{
    char nume[150];
    double valoare;
    bool citit;
};

extern Variabile var[100];
extern int putere[256];
extern char alte_functii[10][12];
extern char semne[10];
struct Node{
    char functie[150];
    double var;
    Node *left, *right, *middle;
};
extern Node *tree;



#endif
