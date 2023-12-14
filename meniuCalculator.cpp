#include "meniuCalculator.h"


vector <Buton> butoane;

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
    cout << taste.size();

    for (int i = 0; i < taste.size(); i++) {
        int row = i / cols;
        int col = i % cols;
        float x = startX + col * (marimeButon.x + spacing);
        float y = startY + row * (marimeButon.y + spacing);

        Vector2f pozitie(x, y);
        butoane.emplace_back(pozitie, taste[i]);
        //cout << labels[i] << endl;
    }
};


void procesare_evenimente(RenderWindow &window, string &userInput, Text &inputText){

    Event event;
    while (window.pollEvent(event)) {

        if (event.type == Event::Closed)
            window.close();


        if (event.type == Event::MouseButtonPressed)
            if (event.mouseButton.button == Mouse::Left) {
                Vector2f mousePos = Vector2f(Mouse::getPosition(window));

                for (auto buton : butoane) {
                    if (buton.shape.getGlobalBounds().contains(mousePos)) {
                        string eticheta_buton = buton.text.getString();

                        if (eticheta_buton == "C")
                            userInput.clear();

                        else if (eticheta_buton == "SIN" || eticheta_buton == "COS" || eticheta_buton == "TAN")
                            userInput += (eticheta_buton + "(");

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
            }

            else if (event.key.code == Keyboard::Escape)
                window.close();

            inputText.setString(userInput);
        }

        FloatRect textRect = inputText.getLocalBounds();
        inputText.setOrigin(textRect.left + textRect.width/2.0f, 0);
        inputText.setPosition(Vector2f(window.getSize().x/2.0f, 110.0f)); // 10.0f for a small offset from the top

    }
}

void desenare(RenderWindow &window, Text &title, RectangleShape &inputBox, Text &inputText){
    {
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
}