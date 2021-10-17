height=$1
width=$2
number=0
RANGE=$3
rm -rf start.txt
for ((i = 0; i < height; i++)) do
    for ((j = 0; j < width; j++)) do
        number=$RANDOM
        let "number %= $RANGE"
        if (( number == 1 ))
        then
            echo -n "*" >> start.txt
        else
            echo -n " " >> start.txt
        fi
    done
    echo '' >> start.txt
done
#gcc ngrushet.c
#./a.out 1
