<?php
$maintab = array();
$lines   = (int) fgets(STDIN);
$result  = 0;

$i = 0;
while ($i < $lines) {
    $nbr = fgets(STDIN);
    $nbr = trim($nbr);

    $c = strlen($nbr);
    $tab = &$maintab;
    for ($j = 0; $j < $c; $j++) {
        $number = $nbr[$j];
        if (!isset($tab[$number])) {
            $tab[$number] = array();
            $result++;
            $tab =& $tab[$number];
        } else {
            $tab =& $tab[$number];
        }
    }
    $i++;
}

echo $result;
