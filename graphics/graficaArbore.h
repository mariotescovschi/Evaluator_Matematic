#ifndef PROIECTIP_EVALUATORMATEMATIC_GRAFICAARBORE_H
#define PROIECTIP_EVALUATORMATEMATIC_GRAFICAARBORE_H

#include "../Setup/structuriDeDate.h"
#include "../Parsing/parsareExpresie.h"
#include <string>
#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>
#include <queue>

void draw_answer();

void create_tree();

void draw_node(Node *node);

void center_tree(Node *root);

void move_tree(Node *node, float surplus);

void process_positions(Node *node, float nivel, float &nextX);

float subarbore_stang(Node *node);

void desenare_arbore(Node *node);

#endif
