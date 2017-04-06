# https://www.codingame.com/ide/puzzle/the-descent
# Xavier Morel - 2016-03-12

while true; do
    mountains=""
    for (( i=0; i<8; i++ )); do
        # mountainH: represents the height of one mountain, from 9 to 0.
        if ((i>0)); then
            mountains+=";"
        fi
        read mountainH
        mountains+=$mountainH":"$i
    done

    echo $mountains | tr ";" "\n" | sort -n | tail -n 1 | cut -d ":" -f 2
done
