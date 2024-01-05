#include "graficaArbore.h"
#include "verificareSintaxaExpresiei.h"

float minX = 1e6, maxX = -1e6;
Node* nodul_selectat = nullptr;

void creare_arbore(){
    tree->functie = input_expresie;
    corect = verificare_sintaxa_expresiei();
    parsare_expresie(tree);

    if(!corect) {
        calculare = false;
        return;
    }

    float nextX = 0;
    procesare_pozitii(tree, 0, nextX);
    centrare_arbore(tree);

    desenat = true;
}

void desenare_raspuns(sf::RenderWindow& window){

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
}

void desenare_arbore(sf::RenderWindow& window, Node* node){
    if (node == nullptr)
        return;

    desenare_nod(window, node);
    desenare_raspuns(window);
}

void desenare_nod(sf::RenderWindow& window, Node* node){
    if (node == nullptr)
        return;

    float baseRadius = 20.0f;
    int textLength = node->functie.length();
    float radius = std::max(baseRadius, textLength * 5.0f);

    sf::CircleShape circle(radius);
    circle.setPosition(node->x, node->y);
    circle.setFillColor(sf::Color::White);
    circle.setOutlineColor(sf::Color::Black);
    circle.setOutlineThickness(2);

    if (circle.getGlobalBounds().contains(pozitie_mouse))
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

    if (node->left != nullptr) {
        sf::Vertex line[] = {
                sf::Vertex(sf::Vector2f(node->x, node->y + radius * 1.5f)),
                sf::Vertex(sf::Vector2f(node->left->x + radius, node->left->y + radius))
        };
        window.draw(line, 2, sf::Lines);
        desenare_arbore(window, node->left);
    }

    if (node->right != nullptr) {
        sf::Vertex line[] = {
                sf::Vertex(sf::Vector2f(node->x + radius * 2.0f, node->y + radius * 1.5f)),
                sf::Vertex(sf::Vector2f(node->right->x + radius, node->right->y + radius))
        };
        window.draw(line, 2, sf::Lines);
        desenare_arbore(window, node->right);
    }

    if (node->middle != nullptr) {
        sf::Vertex line[] = {
                sf::Vertex(sf::Vector2f(node->x + radius, node->y + radius * 2)),
                sf::Vertex(sf::Vector2f(node->middle->x + radius, node->middle->y + radius))
        };
        window.draw(line, 2, sf::Lines);
        desenare_arbore(window, node->middle);
    }
}

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

    if(node -> left != nullptr)
    procesare_pozitii(node->left, nivel + 1, nextX);

    node->x = nextX * 1 * horizontal_spacing,
            node->y = 30 + nivel * vertical_spacing;

    minX = min(minX, nextX),
            maxX = max(maxX, nextX);


    if (node->middle != nullptr) {
        if(node -> middle -> left != nullptr)
        nextX -= (subarbore_stang(node->middle->left) + (float)(node->middle->right != nullptr));
        procesare_pozitii(node->middle, nivel + 1, nextX);
    }

    else
        nextX++;

    if(node -> right != nullptr)
    procesare_pozitii(node->right, nivel + 1, nextX);
}


void mutare_arbore(Node* node, float surplus) {
    if (node == nullptr)
        return;

    node->x += surplus;

    if(node -> left != nullptr)
    mutare_arbore(node->left, surplus);
    if(node -> middle != nullptr)
    mutare_arbore(node->middle, surplus);
    if(node -> right != nullptr)
    mutare_arbore(node->right, surplus);
}

void centrare_arbore(Node* root) {

    float surplus;
    if(minX < 0)
        surplus = 600.0f - ((maxX - minX) / 2.0f + 0.5f) * horizontal_spacing + -minX * horizontal_spacing;
    else
        surplus = 600.0f - ((maxX - minX) / 2.0f + 0.5f) * horizontal_spacing;

    cout << minX << " " << maxX << " " << surplus << endl;
    mutare_arbore(root, surplus);
}


