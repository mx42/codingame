<?php
// https://www.codingame.com/ide/puzzle/the-descent
// Xavier Morel - 2016-03-12

/**
 * Auto-generated code below aims at helping you parse
 * the standard input according to the problem statement.
 **/

// game loop
while (TRUE) {
    $maxVal = 0;
    $maxRange = 0;

    for ($i = 0; $i < 8; $i++) {
        fscanf(
            STDIN,
            "%d",
            $mountainH // represents the height of one mountain, from 9 to 0.
        );

        if ($mountainH > $maxVal) {
            $maxVal = $mountainH;
            $maxRange = $i;
        }
    }

    // Write an action using echo(). DON'T FORGET THE TRAILING \n
    // To debug (equivalent to var_dump): error_log(var_export($var, true));

    echo "$maxRange\n"; // The number of the mountain to fire on.
}
