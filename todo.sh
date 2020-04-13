g++ --std=c++11 lexer.cpp -o lexer

FILE=Resultados
if [ -d "$FILE" ]
then
    :
else
    mkdir Resultados
fi

for caso in L0.txt L1.txt L2.txt L3.txt L4.txt
do
    ./lexer $caso
done