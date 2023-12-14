#include <iostream>
#include <queue>
#include <SFML/Graphics.hpp>
#include "structuriDeDate.h"
#include "parsareExpresie.h"
#include "meniuCalculator.h"
#include "preprocesare.h"
using namespace std;
using namespace sf;

Font font;
Node *tree;
int putere[256];
char alte_functii[10][12];
char semne[10];

struct afisare_arbore{
    string functie;
    int x, y;
    bool st, dr, mid;
};
int nr;
afisare_arbore v[1000];
int c[1000], nc;
void citire_functie(){
    string functie;
    cin >> functie;
    tree -> functie = functie;
}


///DE MODIFICAT
//SE CREEAZA UN VECTOR DE AFISARE PENTRU PROCESAREA GRAFICA
void creare_vector_afisare(Node *nod, int cnt, int i){
        if(nod -> left != nullptr){
            nr = max(nr, i*2);
            v[i].st = true;
            v[i*2].x = v[i].x + 50;
            v[i*2].y = v[i].y - cnt;
            v[i*2].functie = nod -> left -> functie;
            creare_vector_afisare(nod -> left, cnt/2, i*2);
        }
        if(nod -> right != nullptr){
            nr = max(nr, i*2+1);
            v[i].dr = true;
            v[i*2+1].x = v[i].x + 50;
            v[i*2+1].y = v[i].y + cnt;
            v[i*2+1].functie = nod -> right -> functie;
            creare_vector_afisare(nod -> right, cnt/2, i*2+1);
        }
        if(nod -> middle != nullptr){
            nr = max(nr, i*2);
            v[i].mid = true;
            v[i*2].x = v[i].x + 50;
            v[i*2].y = v[i].y;
            v[i*2].functie =  nod -> middle -> functie;
            creare_vector_afisare(nod -> middle, cnt/2, i*2);
        }
}

///DEBUG
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
    //citire_functie();
    //parsare_expresie(tree);


    ///De modificat
    v[1].x = 5, v[1].y = 500;
    v[1].functie = tree -> functie;
    nr = 1;
    creare_vector_afisare(tree, 200, 1);

    RenderWindow window(VideoMode(1200, 900), "Grafic functie", Style::Default);
    window.setFramerateLimit(60);

    // Font
    font.loadFromFile("arial.ttf");

    // Title
    Text title("Evaluator Matematic", font, 44);
    title.setFillColor(negru);
    title.setLetterSpacing(1.8f);
    title.setStyle(Text::Bold);

    FloatRect titleBounds = title.getLocalBounds();

    title.setOrigin(titleBounds.width / 2, titleBounds.height / 2);
    title.setPosition(window.getSize().x / 2, 50);

    // Input field
    Text inputText("", font, 24);
    inputText.setFillColor(negru);
    inputText.setPosition(50, 100); // Set as needed

    int input_box_width = 750;
    int window_width_aux = windowWidth;
    RectangleShape inputBox(Vector2f(750, 50)); // Set as needed
    inputBox.setPosition((window_width_aux - input_box_width)*1.0f / 2.0f, 100); // Match inputText position
    inputBox.setFillColor(alb);
    inputBox.setOutlineColor(negru);
    inputBox.setOutlineThickness(4.f);

    string userInput;

    // Buttons
    initializare_butoane();

    while (window.isOpen()) {
        //window.clear(gri);
        //procesare_taste(window, userInput, buttons, inputText);
        procesare_evenimente(window, userInput, inputText);
        desenare(window, title, inputBox, inputText);
    }

    cout << "Raspunsul este: ";
    cout << tree -> var << endl;
    return 0;
}

/*
 (x>0)*(x^2)+(x<0)*(x-sin(x*2))
 */