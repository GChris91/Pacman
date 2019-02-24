#ifndef LABYRINTHE_H_INCLUDED
#define LABYRINTHE_H_INCLUDED

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>

typedef struct {
    char ** lab;
    int lin;
    int col;
    int nbGomme;

} labyrinth;


typedef struct list_labyrinth list_labyrinth;


struct list_labyrinth{

labyrinth *l;
list_labyrinth *next;
};


int initLab(labyrinth *l, int lin, int col);
int initLabFile(char *filename, labyrinth *l);
char getCase(labyrinth *l, int lin, int col);
void setCase(labyrinth *l, int lin, int col, char state);
void printLab(labyrinth *l);
void copyLab(labyrinth l1, labyrinth *l2);
void freeLab(labyrinth *l);
list_labyrinth *defile(list_labyrinth *l);
list_labyrinth *enfile_copie(list_labyrinth *l, labyrinth lab);


#endif // LABYRINTH_H_INCLUDED
