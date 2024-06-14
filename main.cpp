#include <SFML/Graphics.hpp>
#include "Setup/structuriDeDate.h"
#include "Graphics/meniuCalculator.h"
#include "Setup/preprocesare.h"
#include "Graphics/graficaArbore.h"

int main() {
    preprocesare();

    while (window.isOpen()) {
        pozitie_mouse = Vector2f(Mouse::getPosition(window));

        //If the Calculate button is pressed
        if (calculeaza_apasat) {
            //If we haven't drawn the tree, process the expression and the coordinates of the nodes
            if (!arbore_desenat)
                create_tree();

            //If expression is correct and we don't have unknowns, draw the tree
            if (corect && !avem_necunoscute) {
                window.clear(gri);
                desenare_arbore(tree);
                window.display();
            }
        } else {
            desenare_calculator();
            window.display();
        }

        procesare_evenimente();
    }

    return 0;
}