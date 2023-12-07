#include <iostream>
#include <queue>
#include <SFML/Graphics.hpp>
#include "structuriDeDate.h"
#include "parsareExpresie.h"
#include "preprocesare.h"
using namespace std;
using namespace sf;

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
    citire_functie();
    parsare_expresie(tree);


    ///De modificat
    v[1].x = 5, v[1].y = 500;
    v[1].functie = tree -> functie;
    nr = 1;
    creare_vector_afisare(tree, 200, 1);


    RenderWindow window(VideoMode(1000, 1000), "Grafic functie", Style::Default);
    window.setFramerateLimit(60);

    int i = 1;

    Font font;
    if (!font.loadFromFile("./arial.ttf"))
        cout << "NU MERGE FONTU VARU";

    while (window.isOpen()){
        Event event;
        while (window.pollEvent(event))
            if (event.type == Event::Closed)
                window.close();

        if(i <= nr)
            window.clear(Color::Black);

        int ok = 0;

        if(i <= nr)
            for(int j = 1; j <= i; j++)
                if(v[j].functie[0] != '\0'){
                    ok = 1;
               // cout << v[j].functie << " " << i << ' ' << nr << '\n';
                    Text text;
                    text.setFont(font);
                    text.setString(v[j].functie);
                    text.setCharacterSize(20);
                    text.setFillColor(Color::White);
                    text.setPosition(v[j].y, v[j].x);
                    window.draw(text);

                    if(v[j].st)
                    {
                        Vertex line[] =
                                {
                                        Vertex(Vector2f(v[j].y, v[j].x + 20), Color::White),
                                        Vertex(Vector2f(v[j*2].y, v[j*2].x), Color::White)
                                };
                        window.draw(line, 2, Lines);
                    }
                    if(v[j].dr)
                    {
                        Vertex line[] =
                                {
                                        Vertex(Vector2f(v[j].y, v[j].x + 20), Color::White),
                                        Vertex(Vector2f(v[j*2+1].y, v[j*2+1].x), Color::White)
                                };
                        window.draw(line, 2, Lines);
                    }
                    if(v[j].mid) {
                        Vertex line[] =
                                {
                                        Vertex(Vector2f(v[j].y, v[j].x + 20), Color::White),
                                        Vertex(Vector2f(v[j * 2].y, v[j * 2].x), Color::White)
                                };
                        window.draw(line, 2, Lines);
                    }}
        i++;
        if(i <= nr+1) {


            if(i == (nr + 1)){
                Text text;
                text.setFont(font);
                text.setString("Raspunsul este: ");
                text.setCharacterSize(20);
                text.setFillColor(Color::White);
                text.setPosition(360, 500);
                window.draw(text);


                text.setString(to_string(tree -> var));
                text.setCharacterSize(20);
                text.setFillColor(Color::White);
                text.setPosition(520, 500);
                window.draw(text);
            }
            window.display();
        }
        if(i > nr) {

            continue;
        }
          //sleep(seconds(100));
        else if(ok)
            sleep(seconds(1));
    }

    cout << "Raspunsul este: ";
    cout << tree -> var << endl;
    return 0;
}

/*
 (x>0)*(x^2)+(x<0)*(x-sin(x*2))
 */