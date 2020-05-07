g++ --std=c++11 lexer.cpp -o lexer

FILE=Resultados
if [ -d "$FILE" ]
then
    :
else
    mkdir Resultados
fi

for caso in 0.txt 1.txt 2.txt 3.txt 4.txt
do
    ./lexer $1 $caso
done