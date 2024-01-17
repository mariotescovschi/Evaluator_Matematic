#include <SFML/Graphics.hpp>
#include "structuriDeDate.h"
#include "meniuCalculator.h"
#include "preprocesare.h"
#include "graficaArbore.h"

int main() {
    preprocesare();

    while (window.isOpen()) {
        pozitie_mouse = Vector2f(Mouse::getPosition(window));

        //Daca este apasat butonul Calculeaza
        if(calculeaza_apasat){
            //Daca nu am desenat arborele, procesam expresia si coordonatele nodurilor
            if(!arbore_desenat)
                creare_arbore();

            //Daca expresia este corecta si nu mai avem necunoscute, desenam arborele
            if(corect && !avem_necunoscute) {
                window.clear(gri);
                desenare_arbore(tree);
                window.display();
            }
        }

        else{
            desenare_calculator();
            window.display();
        }

        procesare_evenimente();
    }

    return 0;
}