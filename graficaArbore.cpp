#include "graficaArbore.h"
#include "verificareSintaxaExpresiei.h"

Node* nodul_selectat = nullptr;

void desenare_buton_inapoi();

void creare_arbore(){
    corect = verificare_sintaxa_expresiei();
    tree->functie = input_expresie;

    parsare_expresie(tree);

    if(!corect) {
        calculeaza_apasat = false;
        return;
    }

    float nextX = 0;
    procesare_pozitii(tree, 0, nextX);
    centrare_arbore(tree);

    arbore_desenat = true;
}

void desenare_raspuns(){
    Text text;
    text.setFont(font);
    text.setString("Raspunsul este: " + to_string(tree -> var));
    text.setCharacterSize(35);
    text.setFillColor(Color::Black);

    FloatRect textRect = text.getLocalBounds();
    text.setOrigin(textRect.left + textRect.width / 2.0f, textRect.top + textRect.height / 2.0f);
    text.setPosition(600, 850);
    text.setStyle(Text::Bold);
    window.draw(text);
}

void desenare_arbore(Node* node){

    desenare_nod(node);
    desenare_raspuns();
    desenare_buton_inapoi();
}

//Deseneaza recursiv fiecare nod si muchiile dintre ele
void desenare_nod(Node* node){
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
            nodul_selectat = node;

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

    node->x = nextX * 1.0f * horizontal_spacing,
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

    mutare_arbore(root, surplus);
}

void desenare_buton_inapoi(){

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