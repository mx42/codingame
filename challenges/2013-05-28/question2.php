<?php

<?php
$lines = (int) fgets(STDIN);
$seqs  = array();

for ($i = 0; $i < $lines; $i++) {
    $seq = fgets(STDIN);
    $seq = trim($seq);
    $seqs[] = $seq;
}

function merge_strings($base, $append, $offset, $length) {
    if ($offset > 0) {

    }

}

function simplifySeq($sequences, $n = 0)
{
    if (1 == count($sequences)) {
        return $sequences[0];
    }

    if ($n == count($sequences)) {
        $base = array_pop($sequences);
        $sequences[0] .= $base;
        return simplifySeq($sequences);
    }

    $base = array_pop($sequences);
    $len  = strlen($base);

    $mergeDone = false;
    for ($l = $len; $l > 0; $l--) {
        $part = substr($base, 0, $l);
        foreach ($sequences as &$seq) {
            $seqPart = substr($seq, -$l);
            if ($seqPart == $part) {
                $seq .= substr($base, $l);
                $mergeDone = true;
                break;
            }
        }
        if ($mergeDone) {
            break;
        }
    }

    if (!$mergeDone) {
        array_unshift($sequences, $base);
        return simplifySeq($sequences, $n+1);
    }

    return simplifySeq($sequences);
}

function cleanShortSeqs($seqs)
{
    $c = count($seqs);
    for ($i = 0; $i < $c; $i++) {
        foreach ($seqs as $j => $seq) {
            if ($i != $j && strstr($seq, $seqs[$i])) {
                unset($seqs[$i]);
                break;
            }
        }
    }
    return array_values($seqs);
}

$seqs   = cleanShortSeqs($seqs);
$result = simplifySeq($seqs);
echo strlen($result);

