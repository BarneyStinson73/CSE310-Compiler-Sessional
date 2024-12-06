#!/bin/bash

bison --header="y.tab.h" --output="y.tab.c" parser.y
echo 'Generated the parser C file as well the header file'
g++ -w -c -o y.o y.tab.c
echo 'Generated the parser object file'
flex scanner.l
echo 'Generated the scanner C file'
g++ -w -c -o l.o lex.yy.c
# if the above command doesn't work try g++ -fpermissive -w -c -o l.o lex.yy.c
echo 'Generated the scanner object file'
g++ -g y.o l.o -o a.out
echo 'All ready, running'
./a.out $1
# yacc -d parser.y -v 
#  echo 'Generated the parser C file' 
#  flex scanner.l 
#  echo 'Generated the scanner C file' 
#  g++ lex.yy.c y.tab.c -fsanitize=address -g -o out 
#  echo 'All ready, running' 
#  ./out $1 
#  rm lex.yy.c y.tab.c y.tab.h