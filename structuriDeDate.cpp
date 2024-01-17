#include "structuriDeDate.h"

Font font;
Node *tree;

bool arbore_desenat = false;
bool calculeaza_apasat = false;
bool corect = true;
bool avem_necunoscute = false;
bool eroare_input_necunoscuta = false;

Vector2f pozitie_mouse;
string input_expresie;
RenderWindow window(VideoMode(1200, 900), "Grafic functie", Style::Default);

float minX = 1e6, maxX = -1e6;
int putere[256];
char alte_functii[10][12];
char semne[10];
int numar_variabile = 0;

float valoare_necunoscuta = 0;
float vertical_spacing = 70;
float horizontal_spacing = 50;

string input_variabila;
string eticheta_necunoscuta;

vector <Buton> butoane;
RectangleShape buton_ok(Vector2f(40, 30));
RectangleShape buton_inapoi(Vector2f(70, 30));

Variabile var[100];