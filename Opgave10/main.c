#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define ROLL 1
#define STOP 2
#define AGAIN 1

void printBoard();
void loose();
int rollDie();
int canStop();
void resetChoosenColumns();
int tryInsertColumn(int column);
int roll();
int chooseRollOrStop();
int chooseAgainOrStop();
int chooseCombination(int* dice);
void startRound();
void checkWin();

struct column {
    int max;
    int permanent;
    int current;
};
typedef struct column column_t;

column_t board[11] = {
    { 3, 0, 0 },
    { 5, 0, 0 },
    { 7, 0, 0 },
    { 9, 0, 0 },
    { 11, 0, 0 },
    { 13, 12, 0 },
    { 11, 0, 0 },
    { 9, 0, 0 },
    { 7, 0, 0 },
    { 5, 0, 0 },
    { 3, 0, 0 }
};
int chosenColumns[3] = {-1,-1,-1};

void printBoard() {
    int y = 13;

    for (int y = 13; y >= 0; y--) {
        for (int x = 0; x < 11; x++) {
            column_t c = board[x];

            if (y == c.max-1) {
                if (c.current+c.permanent == c.max) {
                    printf("x  ");
                } else {
                    printf("%d  ", x+2);
                }
            }
            else if (y < c.max-1) {
                char ch;
                if (y+1 <= c.permanent) {
                    ch = '*';
                } else if (y+1 <= c.permanent+c.current) {
                    ch = 'x';
                } else {
                    ch = 'o';
                }

                printf("%c  ", ch);
            } else {
                printf("   ");
            }
        }
        printf("\n");
    }

    for (int x = 0; x < 11; x++) {
        printf("%d ", x+2);
        if (x < 10-2) printf(" ");
    }

    printf("\n");
}

void loose() {
    for (int i = 0; i < 11; i++) {
        board[i].current = 0;
    }
}
int rollDie() {
    return rand() % 6+1;
}
int canStop() {
    int c = 0;
    for (int i = 0; i < 3; i++) {
        if (chosenColumns[i] != -1) c++;
    }
    return c < 3;
}
void resetChoosenColumns() {
    for (int i = 0; i < 3; i++) {
        chosenColumns[i] = -1;
    }
}
int tryInsertColumn(int column) {
    for (int i = 0; i < 3; i++) {
        if (chosenColumns[i] == -1 || chosenColumns[i] == column) {
            chosenColumns[i] = column;
            if (board[column-2].permanent+board[column-2].current == board[column-2].max) {
                printf("you have exceded the limit of the column, and you lost the round");
                return 0;
            }

            board[column-2].current++;

            checkWin();

            return 1;
        }
    }

    printf("you have already chosen three columns, and you lost the round\n");
    return 0;
}
void checkWin() {
    for (int i = 0; i < 11; i++) {
        if (board[i].current+board[i].permanent == board[i].max) {
            printf("congratulations you have won!!!!\n");
            exit(1);
        }
    }
}
int roll() {
    int dice[4] = {rollDie(),rollDie(),rollDie(),rollDie()};
    int pairsChosen = 0;

    while (pairsChosen < 2) {
        if (pairsChosen == 1 && chooseAgainOrStop() == STOP) {
            return 1;
        }

        int column = chooseCombination(dice);
        printf("you chose %d\n", column);
        
        if (tryInsertColumn(column)) {
            pairsChosen++;
            printBoard();
        } else {
            return 0;
        }
    }

    return 1;
}

int chooseRollOrStop() {
    int choise = -1;

    while (choise == -1) {
        printf("1) roll\n");

        if (canStop()) { 
            printf("2) stop\n");
        }

        int s_result = scanf("%d", &choise);
        if (s_result != 1 || (!canStop() && choise != 1) || (canStop() && (choise < 1 || choise > 2))) {
            printf("invalid choise, try again\n");
            choise = -1;   
        }
    }

    return choise;
}
int chooseAgainOrStop() {
    int choise = -1;

    while (choise == -1) {
        printf("1) choose again\n2) stop choosing\n");

        if (scanf("%d", &choise) != 1 || choise < 0 || choise > 2) {
            choise = -1;
        }
    }

    return choise;
}
int chooseCombination(int* dice) {
    printf("%d %d %d %d\nchoose combination (0-3): ", dice[0], dice[1], dice[2], dice[3]);

    int choise1, choise2, s_result;
    int chosen = 0;

    while (!chosen) {
        int s_result = scanf("%d %d", &choise1, &choise2);

        if (s_result != 2 || choise1 < 0 || choise1 > 3 || choise2 < 0 || choise2 > 3 || dice[choise1] == -1 || dice[choise2] == -1) {
            printf("invalid choise, try again\n");
            chosen = 0;
        } else {
            chosen = 1;
        }
    }

    int column = dice[choise1]+dice[choise2];
    dice[choise1] = -1;
    dice[choise2] = -1;
    return column;
}

void startRound() {
    int playAgain = 1;

    resetChoosenColumns();

    while (playAgain) {
        printBoard();
        switch (chooseRollOrStop()) {
            case ROLL: {
                playAgain = roll();
                if (!playAgain) {
                    loose();
                }
                break;
            }
            case STOP: {
                for (int i = 0; i < 11; i++) {
                    board[i].permanent += board[i].current;
                    board[i].current = 0;
                }
                playAgain = 0;
                break;
            }
        }
    }

    startRound();
}

int main() {
    // setup rand with random seed
    srand(time(NULL));

    startRound();
    return 0;
}