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
#define rosu sf::Color::Red
#define albastru sf::Color::Blue
#define marimeButon sf::Vector2f(100, 100)
#define windowWidth 1200
using namespace sf;
using namespace std;

//Structuri de date
struct Variabile{
    string nume;
    double valoare;
    bool citit;
};
extern Variabile var[100];

struct Node{
    string functie;
    double var;
    float x, y;
    Node *left, *right, *middle;
};
extern Node *tree;

struct TextInput{
    Text text;
    RectangleShape forma;
};
extern TextInput input;

//Logica actiuni
extern bool calculeaza_apasat;
extern bool arbore_desenat;
extern bool corect;
extern bool avem_necunoscute;
extern bool eroare_input_necunoscuta;
extern float valoare_necunoscuta;

extern int putere[256];
extern char alte_functii[10][12];
extern char semne[10];
extern int numar_variabile;

//Partea grafica
extern Font font;
extern RenderWindow window;

struct Buton{
    RectangleShape forma;
    Text text;

    Buton(Vector2f& pozitie, string& eticheta) {
        forma.setSize(marimeButon);
        forma.setFillColor(alb);
        forma.setOutlineColor(negru);
        forma.setOutlineThickness(3.f);
        forma.setPosition(pozitie);

        text.setFont(font);
        text.setString(eticheta);
        text.setCharacterSize(38);
        text.setFillColor(negru);
        text.setStyle(Text::Bold);

        FloatRect limita_text = text.getLocalBounds();
        text.setOrigin(limita_text.left + limita_text.width / 2.0f, limita_text.top + limita_text.height / 2.0f);

        text.setPosition(forma.getPosition() + marimeButon * 0.5f);
    }
};
extern vector<Buton> butoane;

extern float minX, maxX;
extern Vector2f pozitie_mouse;
extern string input_expresie;
extern string input_variabila;
extern int lista_erori[6];
extern vector <string> lista_mesaje;
extern Node *nodul_selectat;

extern string eticheta_necunoscuta;
extern RectangleShape buton_ok;
extern RectangleShape buton_inapoi;

extern float horizontal_spacing;
extern float vertical_spacing;
#endif
