#pragma once

#include <stdio.h>
#include <string.h>
#include <malloc.h>
#include <locale.h>

#define clear() printf("\033[H\033[J")

int gallows();
int checkWin();
int compareStrings(unsigned char*, unsigned char*);
int checkWord();
int compareWordAndLetter();
int checkLetter();
char gameStart();

void initGuessedWord();
void changeGuessedWord();
void setGameStatus(int );
void getWord();
void getLetter();
void printGuessedWord();

void setLetter(unsigned char );
void setWord(int, unsigned char *);
