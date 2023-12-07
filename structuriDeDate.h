#ifndef UNTITLED8_STRUCTURIDEDATE_H
#define UNTITLED8_STRUCTURIDEDATE_H
#include <string>
struct Variabile{
    std::string nume;
    double valoare;
    bool citit;
};

extern Variabile var[100];

extern int putere[256];
extern char alte_functii[10][12];
extern char semne[10];


struct Node{
    std::string functie;
    double var;
    Node *left, *right, *middle;
};
extern Node *tree;

//DC NU MERE

#endif
