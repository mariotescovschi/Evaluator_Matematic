#ifndef PROIECTIP_EVALUATORMATEMATIC_GRAFICAARBORE_H
#define PROIECTIP_EVALUATORMATEMATIC_GRAFICAARBORE_H
#include "structuriDeDate.h"
#include "parsareExpresie.h"
#include <string>
#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>
#include <queue>

void desenare_raspuns(sf::RenderWindow& window);

void creare_arbore();

void desenare_nod(sf::RenderWindow& window, Node* node);

void centrare_arbore(Node* root);

void mutare_arbore(Node* node, float surplus);

void procesare_pozitii(Node* node, float nivel, float &nextX);

float subarbore_stang(Node* node);

void desenare_arbore(sf::RenderWindow& window, Node* node);

#endif
