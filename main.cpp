#include <iostream>
#include <iomanip>
#include <queue>
#include "structuriDeDate.h"
#include "parsareExpresie.h"
#include "preprocesare.h"
#include <SFML/Graphics.hpp>
using namespace std;
using namespace sf;

Node *tree;
int putere[256];
char alte_functii[10][12];
char semne[10];
struct afisare_arbore{
    char functie[150];
    int x, y;
    bool st, dr, mid;
};
int nr;
afisare_arbore v[1000];
void citire_functie(){
    char functie[150];
    cin.getline(functie, 150);
    strcpy(tree -> functie, functie);
}

queue<pair<pair<Node, int>, pair<int,int>>> q;
char afisaj[100][100][10];

///DE MODIFICAT
//SE CREEAZA UN VECTOR DE AFISARE PENTRU PROCESAREA GRAFICA
void creare_vector_afisare(Node *tree, int cnt, int i){
        if(tree -> left != NULL){
            nr = max(nr, i*2);
            v[i].st = true;
            v[i*2].x = v[i].x + 50;
            v[i*2].y = v[i].y - cnt;
            strcpy(v[i*2].functie, tree -> left -> functie);
            creare_vector_afisare(tree -> left, cnt/2, i*2);
        }
        if(tree -> right != NULL){
            nr = max(nr, i*2+1);
            v[i].dr = true;
            v[i*2+1].x = v[i].x + 50;
            v[i*2+1].y = v[i].y + cnt;
            strcpy(v[i*2+1].functie, tree -> right -> functie);
            creare_vector_afisare(tree -> right, cnt/2, i*2+1);
        }
        if(tree -> middle != NULL){
            nr = max(nr, i*2);
            v[i].mid = true;
            v[i*2].x = v[i].x + 50;
            v[i*2].y = v[i].y;
            strcpy(v[i*2].functie, tree -> middle -> functie);
            creare_vector_afisare(tree -> middle, cnt/2, i*2);
        }
}

///DOAR PENTRU DEBBUGING, DE STERS DUPA
//AFISEAZA ARBORELE IN CONSOLA
void afisare_in_consola(Node *tree, int niv){

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


    for(int i = 0; i < 20; i++, cout << '\n')
        for(int j = 0; j < 100; j++)
            cout << afisaj[i][j];
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
    afisare_in_consola(tree, 0);


    ///De modificat
    v[1].x = 5, v[1].y = 500;
    strcpy(v[1].functie, tree -> functie);
    nr = 1;
    creare_vector_afisare(tree, 200, 1);


    RenderWindow window(VideoMode(1000, 1000), "Grafic functie", Style::Default);
    window.setFramerateLimit(60);

    Font font;
    if (!font.loadFromFile("./arial.ttf"))
        cout << "NU MERGE FONTU VARU";

    else
    while (window.isOpen()){
        Event event;
        while (window.pollEvent(event))
            if (event.type == Event::Closed)
                window.close();

        window.clear(Color::Black);
        for(int i = 1; i <= nr; i++)
            {
                    Text text;
                    text.setFont(font);
                    text.setString(v[i].functie);
                    text.setCharacterSize(20);
                    text.setFillColor(Color::White);
                    text.setPosition(v[i].y, v[i].x);
                    window.draw(text);

                    if(v[i].st)
                    {
                        Vertex line[] =
                                {
                                        Vertex(Vector2f(v[i].y, v[i].x + 20), Color::White),
                                        Vertex(Vector2f(v[i*2].y, v[i*2].x), Color::White)
                                };
                        window.draw(line, 2, Lines);
                    }
                    if(v[i].dr)
                    {
                        Vertex line[] =
                                {
                                        Vertex(Vector2f(v[i].y, v[i].x + 20), Color::White),
                                        Vertex(Vector2f(v[i*2+1].y, v[i*2+1].x), Color::White)
                                };
                        window.draw(line, 2, Lines);
                    }
                    if(v[i].mid)
                    {
                        Vertex line[] =
                                {
                                        Vertex(Vector2f(v[i].y, v[i].x + 20), Color::White),
                                        Vertex(Vector2f(v[i*2].y, v[i*2].x), Color::White)
                                };
                        window.draw(line, 2, Lines);
                    }
                }

        window.display();
    }



    cout << "Raspunsul este: ";
    cout << tree -> var << endl;
    return 0;
}
