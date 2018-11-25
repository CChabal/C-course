/*
 * Programmeringsteknik med C och Matlab
 * Fall 18
 * Assignment 2

 * File:         ou2.c
 * Description:  A program that reads in the amount of judges and their scores,
 *               then return their max/min and average value. The average value
 *               calculation does not take in to account the min/max values.
 * CS username:  *******
 * Input:        Choice of initial amount of judges and their scores.
 * Output:       The judges min/max and average scores.
 */

#include <stdio.h>

// Declaration of all functions
void startingInfo(void);
int numberJudges(void);
void readScores(int nrjudge, double scores[]);
void printScores(int nrjudge, double scores[]);
void findMinMaxAverage(int nrjudge, double scores[], double *min, double *max,
                       double *average);
void printResult(double min, double max, double average);

int main(void) {

    // Created variables to be used as argument for future functions
    int nrjudge;
    double min, max, average;

    startingInfo();
    nrjudge = numberJudges();

    // The creation of an array with the help of the users choice.
    double scores[nrjudge];

    readScores(nrjudge, scores);
    printScores(nrjudge, scores);
    findMinMaxAverage(nrjudge, scores, &min, &max, &average);
    printResult(min, max, average);

    return 0;
}

// Prints out the information
void startingInfo(void) {
    printf("Program information\n");
    printf("The program reads in the number of judges and the score from ");
    printf("each judge.\nThen it calculates the average score without regard ");
    printf("to the lowest and\nhighest judge score. Finally it prints the ");
    printf("results (the highest, the\nlowest and the final average score).\n");
    printf("\n");
}

/*  The user chooses the amount of judges and saves the amount in a variable
    which returns */
int numberJudges(void) {
    int nrjudge;
    do {
        printf("Number of judges (min 3 and max 10 judges)? ");
        scanf("%d", &nrjudge);
    } while (nrjudge < 3 || nrjudge > 10);
    printf("\n");
    return nrjudge;
}

/*  Takes in the array and its size. Reads the scores and saves
    these in an array */
void readScores(int nrjudge, double scores[]) {
    for (int i = 0; i < nrjudge; i++) {
        printf("Score from judge %d? ", i+1);
        scanf("%lf", &scores[i]);
    }
}

/*  Takes in the array and its size. Prints out the score which was
    saved in the array */
void printScores(int nrjudge, double scores[]) {
    printf("\nLoaded scores:\n");
    for (int i = 0; i < nrjudge; i++) {
        printf("Judge %d: %.1f\n", i+1, scores[i]);
    }
}

/*  Takes in the array and its size plus the memoryadresses for min, max and
    average. Then calculates the values for min, max and average */
void findMinMaxAverage(int nrjudge, double scores[], double *min, double *max,
                       double *average) {
    *min = scores[0];
    *max = scores[0];
    *average = 0;
    for (int i = 0; i < nrjudge; i++) {
        if (scores[i] < *min) {
            *min = scores[i];
        }
        if (scores[i] > *max) {
            *max = scores[i];
        }
        *average += scores[i];
    }

    *average = *average - (*min + *max);
    *average = *average / (nrjudge - 2);
}

//  Prints out the result
void printResult(double min, double max, double average) {
    printf("\nFinal result:\n");
    printf("Highest judge score: %.1f\n", max);
    printf("Lowest judge score: %.1f\n", min);
    printf("Final average score: %.1f\n\n", average);
}
