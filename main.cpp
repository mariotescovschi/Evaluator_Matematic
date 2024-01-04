#include <iostream>
#include <queue>
#include <SFML/Graphics.hpp>
#include "structuriDeDate.h"
#include "parsareExpresie.h"
#include "meniuCalculator.h"
#include "preprocesare.h"
#include "graficaArbore.h"
using namespace std;
using namespace sf;

Font font;
Node *tree;
bool desenat = false;
bool calculare = false;
bool corect = true;
bool avem_variabile = false;
Vector2f pozitie_mouse;
string input_expresie;
RenderWindow window(VideoMode(1200, 900), "Grafic functie", Style::Default);

int main() {
    preprocesare();

    window.setFramerateLimit(120);

    font.loadFromFile("arial.ttf");

    Text title("Evaluator Matematic", font, 44);
    title.setFillColor(negru);
    title.setLetterSpacing(1.8f);
    title.setStyle(Text::Bold);

    FloatRect titleBounds = title.getLocalBounds();

    title.setOrigin(titleBounds.width / 2, titleBounds.height / 2);
    title.setPosition(window.getSize().x / 2, 50);

    Text inputText("", font, 24);
    inputText.setFillColor(negru);
    inputText.setPosition(50, 100); // Set as needed

    float input_box_width = 430;
    float window_width_aux = windowWidth;
    RectangleShape inputBox(Vector2f(430, 60));
    inputBox.setPosition((window_width_aux - input_box_width) / 2.0f, 100);
    inputBox.setFillColor(alb);
    inputBox.setOutlineColor(negru);
    inputBox.setOutlineThickness(4.f);

    initializare_butoane();

    while (window.isOpen()) {
        pozitie_mouse = Vector2f(Mouse::getPosition(window));

        if(calculare){
            if(!desenat)
                creare_arbore();

            if(corect && !avem_variabile) {
                window.clear(gri);
                desenare_arbore(window, tree);
                window.display();
            }
        }

        else if(!desenat)
            desenare_calculator(window, title, inputBox, inputText);

        procesare_evenimente(inputText);
    }

    cout << input_expresie << endl;
    cout << "Raspunsul este: ";
    cout << tree -> var << endl;

    return 0;
}

/*
 (x>0)*(x^2)+(x<0)*(x-sin(x*2))
 */