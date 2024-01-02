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
bool desenat = false;
Node* nodul_selectat = nullptr;

const int VERTICAL_SPACING = 70;
const int HORIZONTAL_SPACING = 50;

float minX = 1e6, maxX = -1e6;


float subarbore_stang(Node* node){

    if(node == nullptr)
        return 0;

    float cnt = 0;

    if(node -> left != nullptr)
        cnt += 1 + subarbore_stang(node -> left);

    if(node -> right != nullptr)
        cnt += 1 + subarbore_stang(node -> right);

    return cnt;
}

void procesare_pozitii(Node* node, float nivel, float &nextX) {

    if (node == nullptr)
        return;

    procesare_pozitii(node->left, nivel + 1, nextX);

    node->x = nextX * 1 * HORIZONTAL_SPACING,
    node->y = 30 + nivel * VERTICAL_SPACING;

    minX = min(minX, nextX),
    maxX = max(maxX, nextX);


    if (node->middle != nullptr)
        nextX -= (subarbore_stang(node->middle->left) + 1),
        procesare_pozitii(node->middle, nivel + 1, nextX);

    else
        nextX++;

    procesare_pozitii(node->right, nivel + 1, nextX);
}


void mutare_arbore(Node* node, float surplus) {

    if (node == nullptr)
        return;

    node->x += surplus;

    mutare_arbore(node->left, surplus);
    mutare_arbore(node->middle, surplus);
    mutare_arbore(node->right, surplus);
}

void centrare_arbore(Node* root, int minX, int maxX) {

    int surplus = 600 - ((maxX - minX) / 2 + 0.5) * HORIZONTAL_SPACING;

    mutare_arbore(root, surplus);
}

void desenare_arbore(sf::RenderWindow& window, Node* node, const sf::Font& font, const sf::Vector2f mousePos)
{
    if (node == nullptr)
        return;


    float baseRadius = 20.0f;
    int textLength = node->functie.length();
    float radius = std::max(baseRadius, textLength * 5.0f); // Adjust multiplier as needed

    sf::CircleShape circle(radius);
    circle.setPosition(node->x, node->y);
    circle.setFillColor(sf::Color::White);
    circle.setOutlineColor(sf::Color::Black);
    circle.setOutlineThickness(2);

    if (circle.getGlobalBounds().contains(mousePos))
        if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
            nodul_selectat = node;

    sf::Text text;
    text.setFont(font);
    text.setString(node->functie);
    text.setCharacterSize(18);
    text.setFillColor(sf::Color::Black);
    sf::FloatRect textRect = text.getLocalBounds();
    text.setOrigin(textRect.left + textRect.width / 2.0f, textRect.top + textRect.height / 2.0f);
    text.setPosition(node->x + radius, node->y + radius);

    window.draw(circle);
    window.draw(text);

    if (node->left) {
        sf::Vertex line[] = {
                sf::Vertex(sf::Vector2f(node->x, node->y + 30)),
                sf::Vertex(sf::Vector2f(node->left->x + radius, node->left->y + radius))
        };
        window.draw(line, 2, sf::Lines);
        desenare_arbore(window, node->left, font, mousePos);
    }

    if (node->right) {
        sf::Vertex line[] = {
                sf::Vertex(sf::Vector2f(node->x + radius*2, node->y + radius*1.5)),
                sf::Vertex(sf::Vector2f(node->right->x + radius, node->right->y + radius))
        };
        window.draw(line, 2, sf::Lines);
        desenare_arbore(window, node->right, font, mousePos);
    }

    if (node->middle) {
        sf::Vertex line[] = {
                sf::Vertex(sf::Vector2f(node->x + radius, node->y + radius * 2)),
                sf::Vertex(sf::Vector2f(node->middle->x + radius, node->middle->y + radius))
        };
        window.draw(line, 2, sf::Lines);
        desenare_arbore(window, node->middle, font, mousePos);
    }
}

int main() {
    preprocesare();

    RenderWindow window(VideoMode(1200, 900), "Grafic functie", Style::Default);
    window.setFramerateLimit(120);

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

    Text inputText("", font, 24);
    inputText.setFillColor(negru);
    inputText.setPosition(50, 100); // Set as needed

    int input_box_width = 430;
    int window_width_aux = windowWidth;
    RectangleShape inputBox(Vector2f(430, 60));
    inputBox.setPosition((window_width_aux - input_box_width)*1.0f / 2.0f, 100);
    inputBox.setFillColor(alb);
    inputBox.setOutlineColor(negru);
    inputBox.setOutlineThickness(4.f);

    string userInput;

    initializare_butoane();



    while (window.isOpen()) {

        Vector2f mousePos = Vector2f(Mouse::getPosition(window));

        if(calculare){

            if(!desenat) {
                initiere_tree();
                tree->functie = userInput;
                parsare_expresie(tree);

                float nextX = 0;
                procesare_pozitii(tree, 0, nextX);
                centrare_arbore(tree, minX, maxX);

                desenat = true;
            }

            window.clear(gri);
            desenare_arbore(window, tree, font, mousePos);

            sf::Text text;
            text.setFont(font);
            text.setString("Raspunsul este: " + to_string(tree -> var));
            text.setCharacterSize(35);
            text.setFillColor(sf::Color::Black);
            sf::FloatRect textRect = text.getLocalBounds();
            text.setOrigin(textRect.left + textRect.width / 2.0f, textRect.top + textRect.height / 2.0f);
            text.setPosition(600, 750);
            text.setStyle(Text::Bold);

            window.draw(text);
            window.display();
        }
        else if(!desenat)
            desenare(window, title, inputBox, inputText);

        procesare_evenimente(window, userInput, inputText, mousePos);

    }

    cout << userInput;
    cout << "Raspunsul este: ";
    cout << tree -> var << endl;

    return 0;
}

/*
 (x>0)*(x^2)+(x<0)*(x-sin(x*2))
 */