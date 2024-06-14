#include "graficaArbore.h"
#include "../Parsing/verificareSintaxaExpresiei.h"

Node *selected_node = nullptr;

void desenare_buton_inapoi();

void create_tree() {
    corect = verificare_sintaxa_expresiei();
    tree->functie = input_expresie;

    parsare_expresie(tree);

    if (!corect) {
        calculeaza_apasat = false;
        return;
    }

    float nextX = 0;
    process_positions(tree, 0, nextX);
    center_tree(tree);

    arbore_desenat = true;
}

void draw_answer() {
    Text text;
    text.setFont(font);
    text.setString("Raspunsul este: " + to_string(tree->var));
    text.setCharacterSize(35);
    text.setFillColor(Color::Black);

    FloatRect textRect = text.getLocalBounds();
    text.setOrigin(textRect.left + textRect.width / 2.0f, textRect.top + textRect.height / 2.0f);
    text.setPosition(600, 750);
    text.setStyle(Text::Bold);
    window.draw(text);
}

void desenare_arbore(Node *node) {

    draw_node(node);
    draw_answer();
    desenare_buton_inapoi();
}

//Deseneaza recursiv fiecare nod si muchiile dintre ele
void draw_node(Node *node) {
    if (node == nullptr)
        return;

    float baseRadius = 20.0f;
    int textLength = node->functie.length();
    float radius = max(baseRadius, textLength * 5.0f);

    CircleShape circle(radius);
    circle.setPosition(node->x, node->y);
    circle.setFillColor(Color::White);
    circle.setOutlineColor(Color::Black);
    circle.setOutlineThickness(2);

    if (circle.getGlobalBounds().contains(pozitie_mouse))
        if (Mouse::isButtonPressed(Mouse::Left))
            selected_node = node;

    Text text;
    text.setFont(font);
    text.setString(node->functie);
    text.setCharacterSize(18);
    text.setFillColor(Color::Black);

    FloatRect textRect = text.getLocalBounds();
    text.setOrigin(textRect.left + textRect.width / 2.0f, textRect.top + textRect.height / 2.0f);
    text.setPosition(node->x + radius, node->y + radius);

    window.draw(circle);
    window.draw(text);

    if (node->left != nullptr) {
        Vertex line[] = {
                Vertex(Vector2f(node->x, node->y + radius * 1.5f)),
                Vertex(Vector2f(node->left->x + radius, node->left->y + radius))
        };
        window.draw(line, 2, Lines);
        desenare_arbore(node->left);
    }

    if (node->right != nullptr) {
        Vertex line[] = {
                Vertex(Vector2f(node->x + radius * 2.0f, node->y + radius * 1.5f)),
                Vertex(Vector2f(node->right->x + radius, node->right->y + radius))
        };
        window.draw(line, 2, Lines);
        desenare_arbore(node->right);
    }

    if (node->middle != nullptr) {
        Vertex line[] = {
                Vertex(Vector2f(node->x + radius, node->y + radius * 2)),
                Vertex(Vector2f(node->middle->x + radius, node->middle->y + radius))
        };
        window.draw(line, 2, Lines);
        desenare_arbore(node->middle);
    }
}

float subarbore_stang(Node *node) {

    if (node == nullptr)
        return 0;

    float cnt = 0;

    if (node->left != nullptr)
        cnt += 1 + subarbore_stang(node->left);

    if (node->right != nullptr)
        cnt += 1 + subarbore_stang(node->right);

    return cnt;
}

void process_positions(Node *node, float nivel, float &nextX) {

    if (node == nullptr)
        return;

    if (node->left != nullptr)
        process_positions(node->left, nivel + 1, nextX);

    node->x = nextX * 1.0f * horizontal_spacing,
            node->y = 30 + nivel * vertical_spacing;

    minX = min(minX, nextX),
            maxX = max(maxX, nextX);


    if (node->middle != nullptr) {
        if (node->middle->left != nullptr)
            nextX -= (subarbore_stang(node->middle->left) + (float) (node->middle->right != nullptr));
        process_positions(node->middle, nivel + 1, nextX);
    } else
        nextX++;

    if (node->right != nullptr)
        process_positions(node->right, nivel + 1, nextX);
}


void move_tree(Node *node, float surplus) {
    if (node == nullptr)
        return;

    node->x += surplus;

    if (node->left != nullptr)
        move_tree(node->left, surplus);
    if (node->middle != nullptr)
        move_tree(node->middle, surplus);
    if (node->right != nullptr)
        move_tree(node->right, surplus);
}

void center_tree(Node *root) {

    float surplus;
    if (minX < 0)
        surplus = 600.0f - ((maxX - minX) / 2.0f + 0.5f) * horizontal_spacing + -minX * horizontal_spacing;
    else
        surplus = 600.0f - ((maxX - minX) / 2.0f + 0.5f) * horizontal_spacing;

    move_tree(root, surplus);
}

void desenare_buton_inapoi() {

    buton_inapoi.setPosition(20, 20);
    buton_inapoi.setFillColor(alb);
    buton_inapoi.setOutlineColor(negru);
    buton_inapoi.setOutlineThickness(3.0f);
    window.draw(buton_inapoi);

    Text text_inapoi("Inapoi", font, 23);
    text_inapoi.setStyle(Text::Bold);
    text_inapoi.setFillColor(negru);
    text_inapoi.setPosition(buton_inapoi.getPosition().x + 2, buton_inapoi.getPosition().y);
    window.draw(text_inapoi);
}