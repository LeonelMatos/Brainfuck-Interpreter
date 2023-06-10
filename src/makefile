# Makefile to for the brainfuck interpreter

CC=gcc
#FORTIFY_SOURCE : protection 1-2
FLAGS=-Wall -Wextra -Wunused -Wpedantic -pedantic -std=c99 -D_FORTIFY_SOURCE=2
EXE=brainfuck

$(EXE) : main.c brain.h
	@$(CC) -o $@ $^ $(FLAGS)

clear clean rm :
	@rm $(EXE)