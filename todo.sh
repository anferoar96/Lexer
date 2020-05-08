g++ --std=c++11 lexer.cpp parser.cpp -o lexer

FILE=Res_lexer
FILE2=Res_parser

if [ $1 = "1" ]
then
    if [ -d "$FILE" ]
    then
        :
    else
        mkdir $FILE
    fi
else
    if [ -d "$FILE2" ]
    then
        :
    else
        mkdir $FILE2
    fi  
fi

for caso in 0.txt 1.txt 2.txt 3.txt 4.txt
do
    ./lexer $1 $caso
done