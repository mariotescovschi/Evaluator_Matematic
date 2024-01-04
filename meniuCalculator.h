#ifndef PROIECTIP_EVALUATORMATEMATIC_MENIUCALCULATOR_H
#define PROIECTIP_EVALUATORMATEMATIC_MENIUCALCULATOR_H
#include "structuriDeDate.h"
using namespace std;
using namespace sf;

void initializare_butoane();

void procesare_evenimente(Text &inputText);

void desenare_input_valoare_variabila(string nume_variabila);

void desenare_calculator(RenderWindow &window, Text &title, RectangleShape &inputBox, Text &inputText);



#endif //PROIECTIP_EVALUATORMATEMATIC_MENIUCALCULATOR_H
