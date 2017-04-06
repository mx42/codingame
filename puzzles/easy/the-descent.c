// https://www.codingame.com/ide/puzzle/the-descent
// Xavier Morel - 2016-03-12

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

/**
 * Auto-generated code below aims at helping you parse
 * the standard input according to the problem statement.
 **/
int main()
{

    // game loop
    while (1) {
        int maxRange = 0;
        int maxValue = 0;
        for (int i = 0; i < 8; i++) {
            int mountainH; // represents the height of one mountain, from 9 to 0.
            scanf("%d", &mountainH);
            if (mountainH > maxValue) {
                maxValue = mountainH;
                maxRange = i;
            }
        }

        // Write an action using printf(). DON'T FORGET THE TRAILING \n
        // To debug: fprintf(stderr, "Debug messages...\n");

        printf("%d\n", maxRange); // The number of the mountain to fire on.
    }

    return 0;
}
