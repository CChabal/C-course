/*
 * Programmeringsteknik med C och Matlab
 * Fall 18
 * Assignment 3

 * File:         ou3.c
 * Description:  A simple implementation of Conway's Game of Life.
 * Author:       *******
 * CS username:  *******
 * Input:        Choice of initial configuration and then instruction to step
 *               or exit.
 * Output:       Prints the game field in each step.
 * Limitations:  No validation of input.
 */

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

/* Constants, representation of states */
#define ALIVE 'X'
#define DEAD '.'

/* Declaration of data structure */
typedef struct{
  char current;
  char next;
} cell;

/* Declaration of functions */
void initField(const int rows, const int cols, cell field[rows][cols]);
void loadGlider(const int rows, const int cols, cell field[rows][cols]);
void loadSemaphore(const int rows, const int cols, cell field[rows][cols]);
void loadRandom(const int rows, const int cols, cell field[rows][cols]);
void loadCustom(const int rows, const int cols, cell field[rows][cols]);
void printField(const int rows, const int cols, cell field[rows][cols]);
void lookingForAlive(const int rows, const int cols, cell field[rows][cols]);
int countAlive(const int rows, const int cols, cell field[rows][cols],
                int testrow, int testcol);
void copyNextToCurrent(const int rows, const int cols, cell field[rows][cols]);
void setNext(const int rows, const int cols, cell field[rows][cols]);
void looping(const int rows, const int cols, cell field[rows][cols]);


/* Function:    main
 * Description: Start and run games, interact with the user.
 * Input:       About what initial structure and whether to step or exit.
 * Output:      Information to the user, and the game field in each step.
 */

int main(void) {

    int const rows = 20;
    int const cols = 20;
    cell field[rows][cols];

    initField(rows, cols, field);
    printField(rows, cols, field);
    setNext(rows, cols, field);
    looping(rows, cols, field);

    return 0;
}


/* Function:    initField
 * Description: Initialize all the cells to dead, then asks the user about
 *              which structure to load, and finally load the structure.
 * Input:       The field array and its size.
 * Output:      The field array is updated.
 */

void initField(const int rows, const int cols, cell field[rows][cols]) {

    for (int r = 0 ; r < rows ; r++) {
        for (int c = 0 ; c < cols ; c++) {
            field[r][c].current = DEAD;
        }
    }

    printf("Select field spec to load ([G]lider, [S]emaphore, [R]andom ");
    printf("or [C]ustom): ");

    int ch = getchar();

	/* Ignore following newline */
    if (ch != '\n') {
        getchar();
    }

    switch (ch) {
        case 'g':
        case 'G':
            loadGlider(rows, cols, field);
            break;
        case 's':
        case 'S':
            loadSemaphore(rows, cols, field);
            break;
        case 'r':
        case 'R':
            loadRandom(rows, cols, field);
            break;
        case 'c':
        case 'C':
        default:
            loadCustom(rows, cols, field);
            break;
    }
}


/* Function:    loadGlider
 * Description: Inserts a glider into the field.
 * Input:       The field array and its size.
 * Output:      The field array is updated.
 */

void loadGlider(const int rows, const int cols, cell field[rows][cols]) {

    field[0][1].current = ALIVE;
    field[1][2].current = ALIVE;
    field[2][0].current = ALIVE;
    field[2][1].current = ALIVE;
    field[2][2].current = ALIVE;
}


/* Function:    loadSemaphore
 * Description: Inserts a semaphore into the field.
 * Input:       The field array and its size.
 * Output:      The field array is updated.
 */

void loadSemaphore(const int rows, const int cols, cell field[rows][cols]) {

    field[8][1].current = ALIVE;
    field[8][2].current = ALIVE;
    field[8][3].current = ALIVE;
}


/* Function:    loadRandom
 * Description: Inserts a random structure into the field.
 * Input:       The field array and its size.
 * Output:      The field array is updated. There is a 50 % chance that a cell
 *              is alive.
 */

void loadRandom(const int rows, const int cols, cell field[rows][cols]) {

    srand(time(NULL));

    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            if (rand() % 2) {
                field[i][j].current = ALIVE;
            }
        }
    }
}


/* Function:    loadCustom
 * Description: Lets the user specify a structure that then is inserted into
 *              the field.
 * Input:       The field array and its size.
 * Output:      The field array is updated.
 */

void loadCustom(const int rows, const int cols, cell field[rows][cols]) {

    printf("Give custom format string: ");
    do {
        int r, c;
        scanf("%d,%d", &r, &c);
        field[r][c].current = ALIVE;
    } while (getchar() != '\n');
}

/* Function:    printField
 * Description: Prints up the field onto the screen.
 * Input:       The field array and its size.
 * Output:      Prints up the current field.
 */

void printField(const int rows, const int cols, cell field[rows][cols]) {

    for (int r = 0; r < rows; r++) {
        for (int c = 0; c < cols; c++) {
            printf("%c ", field[r][c].current);
        }
        printf("\n");
    }
}

/* Function:    lookingForAlive
 * Description: Scans each cell and changes the cells state in the next field.
 * Input:       The field array and its size.
 * Output:      Updates the next field.
 */

void lookingForAlive(const int rows, const int cols, cell field[rows][cols]) {

    int count;

    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {

            count = countAlive(rows, cols, field, i, j);

            if (count < 2 || count > 3) {
                field[i][j].next = DEAD;
            }
            if (count == 3) {
                field[i][j].next = ALIVE;
            }
        }
    }
}

/* Function:    countAlive
 * Description: Scans the adjecent cells for the state "ALIVE" and counts them.
 * Input:       The field array and its size plus the coordinates of a cell
 *              to scan around.
 * Output:      The number of "ALIVE" cells.
 */

int countAlive(const int rows, const int cols, cell field[rows][cols],
                int testrow, int testcol) {

    int count = 0;

    for (int i = testrow-1; i <= testrow+1; i++) {
        for (int j = testcol-1; j <= testcol+1; j++) {

            // Kollar så att punkterna är innanför matrisen.
            if ((i > -1 && i < rows) && (j > -1 && j < cols)) {

                if (field[i][j].current == ALIVE) {
                    if (!(i == testrow && j == testcol)) {
                        count = count + 1;
                    }
                }
            }
        }
    }
    return count;
}

/* Function:    copyNextToCurrent
 * Description: Copies the next field to the current field.
 * Input:       The field array and its size.
 * Output:      Current field array is updated.
 */

void copyNextToCurrent(const int rows, const int cols, cell field[rows][cols]) {

    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            field[i][j].current = field[i][j].next;
        }
    }
}

/* Function:    setNext
 * Description: Copies the current field to the next field.
 * Input:       The field array and its size.
 * Output:      Next field array is updated.
 */

void setNext(const int rows, const int cols, cell field[rows][cols]) {

    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            field[i][j].next = field[i][j].current;
        }
    }
}

/* Function:    looping
 * Description: Repeats a certain process depending on the users choice.
 * Input:       The field array and its size.
 * Output:      Options for the user to choose.
 */

void looping(const int rows, const int cols, cell field[rows][cols]) {

    char userChoice;

    do {

        printf("Select one of the following options:\n");
        printf("       (enter)  Step\n");
        printf("       (any)    Exit\n");

        userChoice = getchar();

        if (userChoice == '\n') {
            lookingForAlive(rows, cols, field);
            copyNextToCurrent(rows, cols, field);
            printField(rows, cols, field);
        }

    } while(userChoice == '\n');

}
