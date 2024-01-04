#include "meniuCalculator.h"
bool valoare_variabila_afisare = false;
string input_variabila;
vector <Buton> butoane;
void initializare_butoane() {
    float cols = 4;
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
        int row = i / (int)cols;
        int col = i % (int)cols;
        float x = startX + (float)col * (marimeButon.x + spacing);
        float y = startY + (float)row * (marimeButon.y + spacing);

        Vector2f pozitie(x, y);
        butoane.emplace_back(pozitie, taste[i]);
    }

    // Buton calculeaza
    Vector2f pozitieButonCalculeaza(850, 100);
    string etichetaButonCalculeaza = "Calculeaza";
    Buton calculeaza(pozitieButonCalculeaza, etichetaButonCalculeaza);

    calculeaza.text.setFillColor(negru);
    calculeaza.shape.setSize(Vector2f(2.0f * marimeButon.x + spacing, 0.6f * marimeButon.y));
    calculeaza.text.setCharacterSize(38);
    calculeaza.text.setStyle(Text::Bold);
    FloatRect textBounds = calculeaza.text.getLocalBounds();
    calculeaza.text.setOrigin(textBounds.left + textBounds.width / 2.0f, textBounds.top + textBounds.height / 2.0f);
    calculeaza.text.setPosition(calculeaza.shape.getPosition() + Vector2f(2 * marimeButon.x + spacing, 0.6f * marimeButon.y) * 0.5f);
    butoane.push_back(calculeaza);


}

void procesare_evenimente(Text &inputText) {
    Event event;
    while (window.pollEvent(event)) {

        if (event.type == Event::Closed)
            window.close();

    if(!calculare){
        if (event.type == Event::MouseButtonPressed)
            if (event.mouseButton.button == Mouse::Left) {
                for (auto &buton: butoane) {
                    if (buton.shape.getGlobalBounds().contains(pozitie_mouse)) {
                        string eticheta_buton = buton.text.getString();

                        if (eticheta_buton == "C")
                            input_expresie.clear();

                        else if (eticheta_buton == "SIN" || eticheta_buton == "COS" || eticheta_buton == "TAN")
                            input_expresie += (eticheta_buton + "(");

                        else if (eticheta_buton == "Calculeaza") {
                            for(int i = 0; i < 4; i++)
                                lista_erori[i] = 0;
                            calculare = true;
                        }

                        else
                            input_expresie += eticheta_buton;

                        inputText.setString(input_expresie);
                        break;
                    }
                }
            }

        if (event.type == Event::TextEntered) {
            if (event.text.unicode == '\b' && !input_expresie.empty())
                input_expresie.pop_back();

            else if (event.text.unicode < 255 && event.text.unicode != '\b')
                input_expresie += char(event.text.unicode);


            else if (event.key.code == Keyboard::Return)
                input_expresie.clear();

            else if (event.key.code == Keyboard::Escape)
                window.close();

            inputText.setString(input_expresie);
        }

        FloatRect textRect = inputText.getLocalBounds();
        inputText.setOrigin(textRect.left + textRect.width / 2.0f, 0);
        inputText.setPosition(Vector2f(window.getSize().x / 2.0f, 110.0f));
    }

    else{

        if(avem_variabile) {
            if (event.type == Event::MouseButtonPressed)
                if (event.mouseButton.button == Mouse::Left) {
                    for (auto &buton: butoane) {
                        if (buton.shape.getGlobalBounds().contains(pozitie_mouse)) {
                            string eticheta_buton = buton.text.getString();

                            if (eticheta_buton == "0" || eticheta_buton == "1" || eticheta_buton == "2" ||
                                eticheta_buton == "3" || eticheta_buton == "4" || eticheta_buton == "5" ||
                                eticheta_buton == "6" || eticheta_buton == "7" || eticheta_buton == "8" ||
                                eticheta_buton == "9" || eticheta_buton == ".")

                                input_variabila += eticheta_buton;

                            inputText.setString(input_variabila);
                            break;
                        }
                    }
                }

            if (event.type == Event::TextEntered) {
                if (event.text.unicode == '\b' && !input_variabila.empty())
                    input_variabila.pop_back();

                else if (event.text.unicode < 255 && event.text.unicode != '\b')
                    input_variabila += char(event.text.unicode);


                else if (event.key.code == Keyboard::Return)
                    input_variabila.clear();

                else if (event.key.code == Keyboard::Escape)
                    window.close();

                inputText.setString(input_variabila);
            }

            FloatRect textRect = inputText.getLocalBounds();
            inputText.setOrigin(textRect.left + textRect.width / 2.0f, 0);
            inputText.setPosition(Vector2f(window.getSize().x / 2.0f, 110.0f));
        }
        else{
        }
    }

    }
}

void afisare_erori() {
    float y = 200;
    int cnt = 0;
    for (int i = 0; i < 4; i++)
        if(lista_erori[i]){
        cnt ++;
        y += 50;
        string etichetaErori = to_string(cnt) + ". " + lista_mesaje[i];
        Text text;
        text.setFont(font);
        text.setString(etichetaErori);
        text.setCharacterSize(25);
        text.setFillColor(albastru);

        FloatRect textBounds = text.getLocalBounds();
        Vector2f pozitieErori(1000 - textBounds.width / 2, y);
        text.setPosition(pozitieErori);
        window.draw(text);
    }
}

void desenare_input_valoare_variabila(string nume_variabila) {
    Text prompt;
    prompt.setFont(font);
    prompt.setString("Introduceti valoarea variabilei " + nume_variabila + ": ");
    prompt.setCharacterSize(30);
    prompt.setFillColor(negru);

    FloatRect textBounds = prompt.getLocalBounds();
    Vector2f pozitiePrompt(1000 - textBounds.width / 2, 200);
    prompt.setPosition(pozitiePrompt);
    window.draw(prompt);

    RectangleShape inputBox(Vector2f(pozitiePrompt.x + textBounds.width + 10, 200));
    inputBox.setPosition(pozitiePrompt.x + textBounds.width + 10, 200);
    inputBox.setFillColor(alb);
    inputBox.setOutlineColor(negru);
    inputBox.setOutlineThickness(4.f);
    window.draw(inputBox);


    Text inputText("", font, 24);

    RectangleShape butonOK(Vector2f(100, 50));
    butonOK.setPosition(50, 50);
    butonOK.setFillColor(rosu);
    butonOK.setOutlineColor(negru);
    butonOK.setOutlineThickness(4.f);
    window.draw(butonOK);

    Text textOK("OK", font, 24);
    textOK.setFillColor(negru);
    textOK.setPosition(50, 50);
    window.draw(textOK);


    //while(avem_variabile)
      //s  procesare_evenimente(inputText);
}

void desenare_calculator(RenderWindow &window, Text &title, RectangleShape &inputBox, Text &inputText) {

        window.clear(gri);
        window.draw(title);
        window.draw(inputBox);
        window.draw(inputText);

        for (auto buton : butoane)
            window.draw(buton.shape),
            window.draw(buton.text);


    if(!corect) {
        // Erori
        string etichetaErori = "Erori";
        Text text;
        text.setFont(font);
        text.setString(etichetaErori);
        text.setCharacterSize(38);
        text.setFillColor(rosu);

        FloatRect textBounds = text.getLocalBounds();
        Vector2f pozitieErori(1000 - textBounds.width / 2, 200);
        text.setPosition(pozitieErori);
        window.draw(text);
        afisare_erori();
    }

    else if(valoare_variabila_afisare)
        desenare_input_valoare_variabila("caca");

    window.display();
}