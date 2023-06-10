# Makefile to for the brainfuck interpreter

CC=gcc
#FORTIFY_SOURCE : protection 1-2
FLAGS=-Wall -Wextra -Wunused -Wpedantic -pedantic -std=c99 -D_FORTIFY_SOURCE=2
#Program name brainfuck
BRF=brfk 

$(BRF) : main.c brain.h
	$(CC) -o $@ $^ $(FLAGS)

run : $(BRF)
	@./$< $(ARGS)
#./BRF ARGS=file.bf

clear clean rm :
	@rm $(BRF)