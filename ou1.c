/*
 * Programmeringsteknik med C och Matlab
 * Fall 18
 * Assignment 1

 * File:         ou1.c
 * Description:  A program that sets the current exchange rate.
 * CS username:  *******
 * Input:        Exchange rate and amount.
 * Output:       Sum in foreign currency.
 */

#include "stdio.h"

int main(void) {
    // Våra samtliga variabler som behövs.
    int choice;
    double curRate = 1.00, sum = 0, price;

    printf("Your shopping assistant\n");

    do {
        // Dessa val ska återupprepas och detta görs med en do-while sats.
        printf("\n1. Set exchange rate in SEK (current rate: %.2f)\n", curRate);
        printf("2. Read prices in the foreign currency\n");
        printf("3. End\n\n");
        printf("Give your choice (1 - 3): ");
        scanf("%d", &choice);
        // Beroende på användarens val från ovan så hamnar vi i olika cases här nedan.
        switch (choice) {
            case 1:
                // Ber om växelkursen i SEK och sparar denna i variabeln "current rate".
                printf("\nGive exchange rate: ");
                scanf("%lf", &curRate);
                break;

            case 2:
                printf("\n");
                while (price >= 0) {
                    // Efterfrågar pris från användaren.
                    printf("Give price (finish with < 0): ");
                    scanf("%lf", &price);

                    if (price >= 0) {
                        // Summerar upp price in i variabeln "sum".
                        sum += price;
                    } else {
                        printf("\nSum in foreign currency: %.2f\n", sum);
                        printf("Sum in SEK: %.2f\n", sum * curRate);
                        // Avbryter samt nollställer price så användaren kan hoppa in i while satsen igen under case 2, ifall det önskas!
                        price = 0;
                        sum = 0;
                        break;
                    }
                }

            case 3:
                // Case 3 existerar för att inte val 3 ska hamna under default.
                break;

            default:
                // För alla andra val utöver 1-3.
                printf("\nNot a valid choice!\n");
        }
    } while(choice != 3);

    printf("\nEnd of program!\n\n");

    return 0;
}
