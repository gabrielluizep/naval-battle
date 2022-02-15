#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// Defining constants
#define BATTLEFIELD_SIZE 10
#define MAX_SHOTS 30
#define MAX_NAME 30

#define FREE_SPACE 0
#define AIRCRAFT_CARRIER 1
#define FRIGATE 2
#define SUBMARINE 3
#define BOMBED_SPACE 10

// Global variables
int battleField[BATTLEFIELD_SIZE][BATTLEFIELD_SIZE];
int shotCounter = 0;
int score = 0;
char name[MAX_NAME];
int randomX;
int randomY;

// Helper functions

void zeroMatrix() {
    for (int i = 0; i < BATTLEFIELD_SIZE; i++) {
        for (int j = 0; j < BATTLEFIELD_SIZE; j++) {
            battleField[i][j] = FREE_SPACE;
        }
    }
}

void drawSpace() {
    do {
        randomX = rand() % BATTLEFIELD_SIZE;
        randomY = rand() % BATTLEFIELD_SIZE;
    } while (battleField[randomX][randomY] != FREE_SPACE);
}

void setFrigates() {
    for (int i = 0; i < 4; i++) {
        drawSpace();
        battleField[randomX][randomY] = FRIGATE;
    }
}

void setSubmarines() {
    for (int i = 0; i < 4; i++) {
        drawSpace();
        battleField[randomX][randomY] = SUBMARINE;
    }
}

void setAircraftCarrier() {
    drawSpace();
    battleField[randomX][randomY] = AIRCRAFT_CARRIER;
}

void setShips() {
    srand(time(NULL));

    setFrigates();
    setSubmarines();
    setAircraftCarrier();
}

// UI Drawing

void drawLine(int line) {
    printf("     ");

    for (int i = 0; i < BATTLEFIELD_SIZE; i++) {
        printf("| %2d ", battleField[line][i]);
    }

    printf("|/n");
    printf("     +----+----+----+----+----+----+----+----+----+----+\n");
}

void drawHiddenLine(int line) {
    printf("     ");
    for (int i = 0; i < BATTLEFIELD_SIZE; i++) {
        if (battleField[line][i] >= 0 && battleField[line][i] <= 3)
            printf("| -- ");
        else
            printf("| %2d ", battleField[line][i]);
    }
    printf("|\n");
    printf("     +----+----+----+----+----+----+----+----+----+----+\n");
}

void drawHiddenMatrix() {
    printf("     +----+----+----+----+----+----+----+----+----+----+\n");
    for (int i = 0; i < BATTLEFIELD_SIZE; i++) {
        drawHiddenLine(i);
    }
}

struct coordinates {
    int x;
    int y;
};

int shot() {
    if (shotCounter >= MAX_SHOTS) {
        return 1;
    }

    drawHiddenMatrix();

    struct coordinates shot;

    do {
        printf("Selecione qual coluna você deseja atirar\n");

        scanf(" %d", &shot.x);

    } while (shot.x < 0 || shot.x > 9);

    do {
        printf("Selecione qual linha você deseja atirar\n");

        scanf(" %d", &shot.y);

    } while (shot.y < 0 || shot.y > 9);

    shotCounter++;

    printf("tiro acertou %d\n", battleField[shot.x][shot.y]);

    switch (battleField[shot.x][shot.y]) {
        case FREE_SPACE:
            printf("Você atirou, porém não havia nada naquela posição. :(\n");
            break;
        case AIRCRAFT_CARRIER:
            printf("Parabéns, você acertou um porta-aviões! :D\n");
            score += 20;
            break;
        case FRIGATE:
            printf("Parabéns, você acertou uma fragata! :)\n");
            score += 10;
            break;
        case SUBMARINE:
            printf("Parabéns, você acertou um submarino! XD\n");
            score += 30;
            break;

        default:
            return 0;
            break;
    }

    battleField[shot.x][shot.y] += BOMBED_SPACE;

    return 0;
}

int main() {
    system("clear");

    int state;

    zeroMatrix();
    setShips();

    do {
        state = shot();
        system("clear");
    } while (state == 0);

    printf("Seu placar foi de %d\n", score);

    return 0;
}