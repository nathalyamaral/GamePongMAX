#ifndef _BibliotecaPong_H 
#define _BibliotecaPong_H 

#include <conio.h>

#include <windows.h>

#include <stdio.h>

#include <time.h>

#include <stdlib.h>


// -------------------------------------------------------------------------

void gotoxy(int, int);

// -------------------------------------------------------------------------

void textcolor ();

// -------------------------------------------------------------------------

void textbackground ();

// -------------------------------------------------------------------------

void wait( double);

// -------------------------------------------------------------------------

void printxy(int, int, char []);

void Placar();

void Play(int);

void jogo( int *, double *);

void gameover();

#define largura 80

#define altura 15

void desenha_coluna(int, int, int, int, int);

void desenha_linha(int, int, int, int, int);

void dificuldade(int *);

void rodada();

void menu_Principal( );

#endif
