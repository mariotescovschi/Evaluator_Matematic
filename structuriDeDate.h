#ifndef UNTITLED8_STRUCTURIDEDATE_H
#define UNTITLED8_STRUCTURIDEDATE_H
#include <string>
#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>
#include <queue>
#include <string>
#define alb sf::Color::White
#define negru sf::Color::Black
#define gri sf::Color(200, 200, 200)
#define griDeschis sf::Color(230, 230, 230)
#define griInchis sf::Color(150, 150, 150)
#define rosu sf::Color::Red
#define verde sf::Color::Green
#define albastru sf::Color::Blue
#define galben sf::Color::Yellow
#define violet sf::Color(148, 0, 211)
#define marimeButon sf::Vector2f(100, 100)
#define windowWidth 1200
#define windowHeight 900
#define horizontal_spacing 50
#define vertical_spacing 70

using namespace sf;
using namespace std;
extern bool calculare;
extern bool desenat;
struct Variabile{
    string nume;
    double valoare;
    bool citit;
};

extern Variabile var[100];


extern Font font;

extern int putere[256];
extern char alte_functii[10][12];
extern char semne[10];


struct Buton{
    RectangleShape shape;
    Text text;

    Buton(Vector2f& position, string& buttonText) {
        shape.setSize(marimeButon);
        shape.setFillColor(alb);
        shape.setOutlineColor(negru);
        shape.setOutlineThickness(3.f);
        shape.setPosition(position);

        text.setFont(font);
        text.setString(buttonText);
        text.setCharacterSize(38);
        text.setFillColor(negru);
        text.setStyle(Text::Bold);

        FloatRect textBounds = text.getLocalBounds();
        text.setOrigin(textBounds.left + textBounds.width / 2.0f, textBounds.top + textBounds.height / 2.0f);

        text.setPosition(shape.getPosition() + marimeButon * 0.5f);
    }
};

extern vector<Buton> butoane;
extern float minX, maxX;
struct Node{
    string functie;
    double var;
    float x, y;
    Node *left, *right, *middle;
};
extern Node *tree;
extern Node *nodul_selectat;
extern sf::Vector2f pozitie_mouse;
extern string input_expresie;
extern string input_variabila;
extern int lista_erori[4];
extern vector <string> lista_mesaje;
extern RenderWindow window;
extern bool corect;
extern bool valoare_variabila_afisare;
extern bool avem_variabile;
#endif
