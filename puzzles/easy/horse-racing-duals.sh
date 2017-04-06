# https://www.codingame.com/ide/puzzle/horse-racing-duals
# Xavier Morel - 2016-03-12

read N
for ((i=0; i<N; i++)); do
    read Pi
    if ((i>0)); then
        horses+=":"
    fi
    horses+=$Pi
done
echo $horses | tr ":" "\n" | sort -n | awk 'NR>1{print $1-p} {p=$1}' | sort -n | head -n 1
