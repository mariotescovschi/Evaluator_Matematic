#include "verificareSintaxaExpresiei.h"
#include <cstring>

vector <string> lista_mesaje = {
    "Impartire la 0.",
    "Operatori nu sunt corecti.",
    "Paranteze goale.",
    "Paranteze gresite.",
    "Nu poate fi negativ.",
    "Nu poate fi 0/negativ."
};

bool verificare_sintaxa_expresiei(){
    stergere_spatii_goale();

    if(!impartire_la_zero())
        lista_erori[0] = 1;

    if(!operatori_corecti())
        lista_erori[1] = 1;

    if(!paranteze_goale())
        lista_erori[2] = 1;

    if(!verificare_paranteze())
        lista_erori[3] = 1;

    return lista_erori[0] == 0 && lista_erori[1] == 0 && lista_erori[2] == 0 && lista_erori[3] == 0;
}

bool este_operator(char ch) {
    return strchr(semne, ch) != nullptr;
}

bool operatori_corecti() {
    for (int i = 0; i < input_expresie.length() - 1; i++)
        if (este_operator(input_expresie[i]) && (i == 0 || i == input_expresie.length() - 1 || este_operator(input_expresie[i + 1])))
            return false;

    return true;
}

bool verificare_paranteze() {
    char stiva[266];
    int top = 0;

    for (int i = 0; i < input_expresie.length(); i++) {
        char ch = input_expresie[i];
        switch (ch) {
            case '(':
            case '[':
            case '{':
                stiva[++top] = ch;
                break;
            case ')':
                if (!top || stiva[top] != '(')
                    return false;
                top--;
                break;
            case ']':
                if (!top || stiva[top] != '[')
                    return false;
                top--;
                break;
            case '}':
                if (!top || stiva[top] != '{')
                    return false;
                top--;
                break;
        }
    }

    return !top;
}

bool paranteze_goale() {
    for (int i = 0; i < input_expresie.length() - 1; i++)
        if ((input_expresie[i] == '(' && input_expresie[i + 1] == ')') ||
            (input_expresie[i] == '[' && input_expresie[i + 1] == ']') ||
            (input_expresie[i] == '{' && input_expresie[i + 1] == '}'))
                return false;

    return true;
}

void stergere_spatii_goale() {
    string string_aux;
    for (char ch : input_expresie)
        if (ch != ' ')
            string_aux += ch;

    input_expresie = string_aux;
}

bool impartire_la_zero() {
    for (int i = 0; i < input_expresie.length() - 1; i++)
        if (input_expresie[i] == '/' && input_expresie[i + 1] == '0')
            return false;

    return true;
}
