#include "meniuCalculator.h"
void initializare_butoane() {
    float col = 4;
    float spatiu = 10.0f;

    vector<string> taste = {
            "7", "8", "9", "/",
            "4", "5", "6", "*",
            "1", "2", "3", ".",
            "+", "0", "-", "(",
            "sin", "cos", "tan", ")",
            "cot", "atan", "log", "ln"
    };


    float start_x = (windowWidth - (col * marimeButon.x) - (spatiu * (col - 1))) / 2.0f;
    float start_y = 180.0f;

    for (int i = 0; i < taste.size(); i++) {
        int l = i / (int)col;
        int c = i % (int)col;
        float x = start_x + (float)c * (marimeButon.x + spatiu);
        float y = start_y + (float)l * (marimeButon.y + spatiu);

        Vector2f pozitie(x, y);
        butoane.emplace_back(pozitie, taste[i]);
    }

    // Buton calculeaza
    Vector2f pozitie_calculeaza(850, 100);
    string eticheta_calculeaza = "Calculeaza";
    Buton calculeaza(pozitie_calculeaza, eticheta_calculeaza);

    calculeaza.forma.setSize(Vector2f(2.0f * marimeButon.x + spatiu, 0.6f * marimeButon.y));

    FloatRect limita = calculeaza.text.getLocalBounds();
    calculeaza.text.setOrigin(limita.left + limita.width / 2.0f, limita.top + limita.height / 2.0f);
    calculeaza.text.setPosition(calculeaza.forma.getPosition() + Vector2f(2 * marimeButon.x + spatiu, 0.6f * marimeButon.y) * 0.5f);

    //Buton clear
    Vector2f pozitie_clear(290, 100);
    string eticheta_clear = "C";
    Buton clear(pozitie_clear, eticheta_clear);

    clear.forma.setSize(Vector2f(0.6f * marimeButon.x + spatiu, 0.6f * marimeButon.y));

    clear.text.setOrigin(limita.left + limita.width / 1.9f, limita.top + limita.height / 1.1f);
    clear.text.setPosition(clear.forma.getPosition() + Vector2f(2 * marimeButon.x + spatiu, 0.7f * marimeButon.y) * 0.6f);

    butoane.push_back(calculeaza);
    butoane.push_back(clear);
}

//Functia verifica daca inputul este corect si calculeaza valoarea in valoare_necunoscuta
void verifica_input_variabila(){
    bool negativ = false, punct = false;
    int pozitie_punct = 0;
    eroare_input_necunoscuta = false;
    valoare_necunoscuta = 0;
    for (int i = 0; i < input_variabila.size(); i++) {
        if (input_variabila[i] < '0' || input_variabila[i] > '9') {
            if(input_variabila[i] == '.' && !punct) {
                punct = true;
                pozitie_punct = i;
                continue;
            }
            else if(input_variabila[i] == '-' && !negativ && i == 0) {
                negativ = true;
                continue;
            }
            else
                eroare_input_necunoscuta = true;

            valoare_necunoscuta = 0;
            break;
        }

        if(input_variabila[i] == '-') {
            if(negativ)
                eroare_input_necunoscuta = true,
                valoare_necunoscuta = 0;

            negativ = true;
            continue;
        }

        else if(input_variabila[i] == '.') {
            if(punct)
                eroare_input_necunoscuta = true,
                valoare_necunoscuta = 0;

            punct = true;
            pozitie_punct = i;
            continue;
        }

        if(!punct)
            valoare_necunoscuta = valoare_necunoscuta * 10 + (input_variabila[i] - '0');
        else
            valoare_necunoscuta += (input_variabila[i] - '0') * pow(10, pozitie_punct - i);
    }

    if(negativ)
        valoare_necunoscuta *= -1;

    if (!eroare_input_necunoscuta)
        avem_necunoscute = false,
        input_variabila.clear();
}

void procesare_evenimente() {
    Event event;
    while (window.pollEvent(event)) {

        if (event.type == Event::Closed)
            window.close();

    if(!calculeaza_apasat){
        if (event.type == Event::MouseButtonPressed)
            if (event.mouseButton.button == Mouse::Left) {
                for (auto &buton: butoane) {
                    if (buton.forma.getGlobalBounds().contains(pozitie_mouse)) {
                        string eticheta_buton = buton.text.getString();

                        if (eticheta_buton == "C")
                            input_expresie.clear();

                        else if (eticheta_buton == "sin" || eticheta_buton == "cos" || eticheta_buton == "tan")
                            input_expresie += (eticheta_buton + "(");

                        else if (eticheta_buton == "Calculeaza") {
                            for(int i = 0; i < 6; i++)
                                lista_erori[i] = 0;
                            calculeaza_apasat = true;
                        }

                        else
                            input_expresie += eticheta_buton;

                        break;
                    }
                }
            }

        if(event.type == Event::KeyPressed && event.key.code == Keyboard::Enter)
            calculeaza_apasat = true;

        else if (event.type == Event::TextEntered) {
            if (event.text.unicode == '\b' && !input_expresie.empty())
                input_expresie.pop_back();

            else if (event.text.unicode < 255 && event.text.unicode != '\b')
                input_expresie += char(event.text.unicode);


            else if (event.key.code == Keyboard::Return)
                input_expresie.clear();

            else if (event.key.code == Keyboard::Escape)
                window.close();
        }
    }

    else{

        if(avem_necunoscute) {
            if (event.type == Event::MouseButtonPressed) {
                if (event.mouseButton.button == Mouse::Left) {
                    for (auto &buton: butoane)
                        if (buton.forma.getGlobalBounds().contains(pozitie_mouse)) {
                            string eticheta_buton = buton.text.getString();

                            if(eticheta_buton >= '0' && eticheta_buton <= '9' || eticheta_buton == '.'){
                                input_variabila += eticheta_buton;
                                break;
                        }
                    }

                    if (buton_ok.getGlobalBounds().contains(pozitie_mouse))
                        verifica_input_variabila();
                }
            }

            if(event.type == Event::KeyPressed && event.key.code == Keyboard::Enter)
                        verifica_input_variabila();


            if (event.type == Event::TextEntered) {
                if (event.text.unicode == '\b' && !input_variabila.empty())
                    input_variabila.pop_back();

                else if (event.text.unicode < 255 && event.text.unicode != '\b')
                    input_variabila += char(event.text.unicode);


                else if (event.key.code == Keyboard::Return)
                    input_variabila.clear();

                else if (event.key.code == Keyboard::Escape)
                    window.close();
            }
        }

        //Selecteaza nodul pentru a fi mutat
        else{
            Vector2f mousePos = static_cast<Vector2f>(Mouse::getPosition(window));

            if (!Mouse::isButtonPressed(Mouse::Left))
                nodul_selectat = nullptr;

            if (nodul_selectat != nullptr)
                nodul_selectat->x = mousePos.x - 20,
                nodul_selectat->y = mousePos.y - 20;

            if(Mouse::isButtonPressed(Mouse::Left) && buton_inapoi.getGlobalBounds().contains(pozitie_mouse)){
                    avem_necunoscute = false;
                    calculeaza_apasat = false;
                    arbore_desenat = false;
                    input_variabila.clear();
                    input_expresie.clear();
                    numar_variabile = 0;
                }
        }
    }

    }
}

//Erori de sintaxa si de calcul
void afisare_erori() {
    float y = 200;
    int cnt = 0;
    for (int i = 0; i < 6; i++)
        if(lista_erori[i]){
            cnt ++;
            y += 50;
            Text text;
            text.setFont(font);
            text.setString(to_string(cnt) + ". " + lista_mesaje[i]);
            text.setCharacterSize(25);
            text.setFillColor(albastru);
            text.setPosition(1000 - text.getLocalBounds().width / 2, y);
            window.draw(text);
    }
}

//Functie apelata in timpul parsarii expresiei, care cere valoarea unei variabile necunoscute
void desenare_input_valoare_variabila() {
    desenare_calculator();

    pozitie_mouse = Vector2f(Mouse::getPosition(window));

    Text prompt;
    prompt.setFont(font);
    prompt.setString("Introduceti " + eticheta_necunoscuta + ": ");
    prompt.setCharacterSize(24);
    prompt.setFillColor(negru);

    FloatRect limita_text = prompt.getLocalBounds();

    prompt.setPosition(Vector2f (5.0f, 200.0f));
    window.draw(prompt);

    RectangleShape forma(Vector2f(80.0f, limita_text.height + 10.0f));
    forma.setPosition(prompt.getPosition().x + limita_text.width + 5.0f, 200.0f + (limita_text.height - 10.0f) / 2.0f);
    forma.setFillColor(alb);
    forma.setOutlineColor(negru);
    forma.setOutlineThickness(2.0f);
    window.draw(forma);

    Text text("", font, 24);
    text.setFillColor(negru);
    text.setPosition(forma.getPosition().x, forma.getPosition().y);
    text.setString(input_variabila);
    window.draw(text);

    buton_ok.setPosition(180, forma.getPosition().y + 40);
    buton_ok.setFillColor(alb);
    buton_ok.setOutlineColor(negru);
    buton_ok.setOutlineThickness(2.0f);
    window.draw(buton_ok);

    Text text_ok("OK", font, 24);

    text_ok.setFillColor(negru);
    text_ok.setPosition(buton_ok.getPosition().x + 2, buton_ok.getPosition().y);
    window.draw(text_ok);

    procesare_evenimente();

    //Afisare eroare daca inputul nu este un numar
    if(eroare_input_necunoscuta){
        Text eroare("Valoarea nu este corecta!", font, 24);
        eroare.setFillColor(rosu);
        eroare.setPosition(40, buton_ok.getPosition().y + buton_ok.getGlobalBounds().height + 10);
        window.draw(eroare);
    }

    window.display();
}

void desenare_titlu(){
    Text titlu("Evaluator de expresii", font, 48);
    titlu.setFillColor(negru);
    titlu.setLetterSpacing(1.8f);
    titlu.setStyle(Text::Bold);

    titlu.setOrigin(titlu.getLocalBounds().width / 2, titlu.getLocalBounds().height / 2);
    titlu.setPosition((float)window.getSize().x / 2, 50);

    window.draw(titlu);
}

void desenare_input (){
    RectangleShape forma(Vector2f(430, 60));
    forma.setPosition(((float)window.getSize().x - 430.0f) / 2.0f, 100);
    forma.setFillColor(alb);
    forma.setOutlineColor(negru);
    forma.setOutlineThickness(4.0f);

    Text text("", font, 24);
    text.setFillColor(negru);
    text.setString(input_expresie);


    text.setOrigin(text.getLocalBounds().width / 2.0f, 0);
    text.setPosition(forma.getPosition().x + forma.getLocalBounds().width / 2.0f, forma.getPosition().y + 10);


    window.draw(forma);
    window.draw(text);
}

void desenare_calculator() {

        window.clear(gri);
        desenare_titlu();
        desenare_input();

        for (auto buton : butoane)
            window.draw(buton.forma),
            window.draw(buton.text);


    if(!corect) {
        string etichetaErori = "Erori";
        Text text;
        text.setFont(font);
        text.setString(etichetaErori);
        text.setCharacterSize(38);
        text.setFillColor(rosu);

        Vector2f pozitieErori(1000 - text.getLocalBounds().width / 2, 200);
        text.setPosition(pozitieErori);
        window.draw(text);

        afisare_erori();
    }

}