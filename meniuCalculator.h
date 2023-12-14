#ifndef PROIECTIP_EVALUATORMATEMATIC_MENIUCALCULATOR_H
#define PROIECTIP_EVALUATORMATEMATIC_MENIUCALCULATOR_H
#include "structuriDeDate.h"
using namespace std;
using namespace sf;

void initializare_butoane();
void procesare_evenimente(RenderWindow &window, string& userInput, Text &inputText);
void desenare(RenderWindow &window, Text &title, RectangleShape &inputBox, Text &inputText);



#endif //PROIECTIP_EVALUATORMATEMATIC_MENIUCALCULATOR_H
