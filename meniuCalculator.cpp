#include "meniuCalculator.h"

vector <Buton> butoane;
Vector2f pozitieButonCalculeaza(850, 100);
string etichetaButonCalculeaza = "Calculeaza";
Buton calculeaza(pozitieButonCalculeaza, etichetaButonCalculeaza);

void initializare_butoane(){
    int cols = 4;
    float spacing = 10.0f;

    vector<string> taste = {
            "7", "8", "9", "/",
            "4", "5", "6", "*",
            "1", "2", "3", ".",
            "+", "0", "-", "+",
            "SIN", "COS", "TAN", "C"
    };

    float startX = (windowWidth - (cols * marimeButon.x) - (spacing * (cols - 1))) / 2.0f;
    float startY = 180.0f;

    for (int i = 0; i < taste.size(); i++) {
        int row = i / cols;
        int col = i % cols;
        float x = startX + col * (marimeButon.x + spacing);
        float y = startY + row * (marimeButon.y + spacing);

        Vector2f pozitie(x, y);
        butoane.emplace_back(pozitie, taste[i]);
    }

    // Buton calculeaza

    calculeaza.text.setFillColor(negru);
    calculeaza.shape.setSize(Vector2f(2.0f * marimeButon.x + spacing, 0.6f * marimeButon.y));
    calculeaza.text.setCharacterSize(38);
    calculeaza.text.setStyle(Text::Bold);
    FloatRect textBounds = calculeaza.text.getLocalBounds();
    calculeaza.text.setOrigin(textBounds.left + textBounds.width / 2.0f, textBounds.top + textBounds.height / 2.0f);
    calculeaza.text.setPosition(calculeaza.shape.getPosition() + Vector2f(2 * marimeButon.x + spacing, 0.6f * marimeButon.y) * 0.5f);
    butoane.push_back(calculeaza);

}

void procesare_evenimente(RenderWindow &window, string &userInput, Text &inputText, Vector2f &mousePos) {

    Event event;
    while (window.pollEvent(event)) {
        if (event.type == Event::Closed)
            window.close();

    if(!calculare){
        if (event.type == Event::MouseButtonPressed)
            if (event.mouseButton.button == Mouse::Left) {
                for (auto buton: butoane) {
                    if (buton.shape.getGlobalBounds().contains(mousePos)) {
                        string eticheta_buton = buton.text.getString();

                        if (eticheta_buton == "C")
                            userInput.clear();

                        else if (eticheta_buton == "SIN" || eticheta_buton == "COS" || eticheta_buton == "TAN")
                            userInput += (eticheta_buton + "(");

                        else if (eticheta_buton == "Calculeaza")
                            calculare = true;

                        else
                            userInput += eticheta_buton;

                        inputText.setString(userInput);
                        break;
                    }
                }
            }

        if (event.type == Event::TextEntered) {
            if (event.text.unicode == '\b' && !userInput.empty())
                userInput.pop_back();

            else if (event.text.unicode < 255 && event.text.unicode != '\b')
                userInput += char(event.text.unicode);


            else if (event.key.code == Keyboard::Return) {
                userInput.clear();
            } else if (event.key.code == Keyboard::Escape)
                window.close();

            inputText.setString(userInput);
        }

        FloatRect textRect = inputText.getLocalBounds();
        inputText.setOrigin(textRect.left + textRect.width / 2.0f, 0);
        inputText.setPosition(Vector2f(window.getSize().x / 2.0f, 110.0f));

    }

    else{
        sf::Vector2f mousePos = static_cast<sf::Vector2f>(sf::Mouse::getPosition(window));

        if (!sf::Mouse::isButtonPressed(sf::Mouse::Left))
            nodul_selectat = nullptr;


        if (nodul_selectat != nullptr)
            nodul_selectat->x = mousePos.x - 20,
                    nodul_selectat->y = mousePos.y - 20;
    }

    }
}

void desenare(RenderWindow &window, Text &title, RectangleShape &inputBox, Text &inputText){

        window.clear(gri);
        window.draw(title);
        window.draw(inputBox);
        window.draw(inputText);

        // Draw buttons
        for (auto buton : butoane) {
            window.draw(buton.shape);
            window.draw(buton.text);
        }

        window.display();

}