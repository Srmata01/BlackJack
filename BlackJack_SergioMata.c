#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define TOTAL_CARTAS 52
#define VALORES_CARTA 13
#define MAXIMA_MANO 10

// Representación de las cartas per jugar
char *valores[] = {"2", "3", "4", "5", "6", "7", "8", "9", "10", "J", "Q", "K", "A"};
char *palos[] = {"Corazones", "Diamantes", "Picas", "Tréboles"};

// Estructura para una carta
struct carta {
    char *valor;
    char *palo;
    int valor_numerico;
};

struct carta mazo[TOTAL_CARTAS];
struct carta manoJugador[MAXIMA_MANO];
int numCartasJugador = 0;
int sumaJugador = 0;
char eleccion;

void inicializarMazo() {
    for (int i = 0; i < TOTAL_CARTAS; i++) {
        mazo[i].valor = valores[i % VALORES_CARTA];
        mazo[i].palo = palos[i / VALORES_CARTA];
        mazo[i].valor_numerico = (i % VALORES_CARTA) + 2;
        if (mazo[i].valor_numerico > 10) mazo[i].valor_numerico = 10;
        if (i % VALORES_CARTA == VALORES_CARTA - 1) mazo[i].valor_numerico = 11;
    }
}

void mezclarMazo() {
    srand(time(NULL));
    for (int i = 0; i < TOTAL_CARTAS; i++) {
        int j = rand() % TOTAL_CARTAS;
        struct carta temp = mazo[i];
        mazo[i] = mazo[j];
        mazo[j] = temp;
    }
}

void mostrarCarta(struct carta c) {
    printf("  %s de %s\n", c.valor, c.palo);
}

int sumarMano(struct carta mano[], int numCards) {
    int sum = 0;
    for (int i = 0; i < numCards; i++) {
        sum += mano[i].valor_numerico;
    }
    return sum;
}

int main() {
    inicializarMazo();
    mezclarMazo();

    printf("Bienvenido al Blackjack!\n");

    manoJugador[numCartasJugador++] = mazo[0];
    manoJugador[numCartasJugador++] = mazo[1];
    sumaJugador = sumarMano(manoJugador, numCartasJugador);

    printf("Tus cartas:\n");
    mostrarCarta(manoJugador[0]);
    mostrarCarta(manoJugador[1]);
    printf("Suma total: %d\n", sumaJugador);

    while (sumaJugador < 21) {
        printf("¿Quieres otra carta? (s/n): ");
        scanf(" %c", &eleccion);

        if (eleccion == 's' || eleccion == 'S') {
           manoJugador[numCartasJugador] = mazo[numCartasJugador];
            sumaJugador = sumarMano(manoJugador, ++numCartasJugador);

            printf("Nueva carta:\n");
            mostrarCarta(manoJugador[numCartasJugador - 1]);
            printf("Suma total: %d\n", sumaJugador);
        } else {
            break;
        }
    }

    if (sumaJugador == 21) {
        printf("¡Blackjack! Has ganado.\n");
    } else if (sumaJugador > 21) {
        printf("Te has pasado. Fin del juego.\n");
    } else {
        printf("Te has plantado con %d. Fin del juego.\n", sumaJugador);
    }

    return 0;
}
