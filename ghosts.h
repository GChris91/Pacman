#ifndef GHOSTS_H_INCLUDED
#define GHOSTS_H_INCLUDED

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>

#include "labyrinth.h"
//#include "pacman.h"


typedef struct{
    int lin, col;
    int turnMemory;
    char collide;
    bool galive;
    int nb_lab;
    list_labyrinth * memory;
    labyrinth * smartMemory;

}ghost;


void initGhostRand(ghost *g,labyrinth *l);
void moveGhostRand(ghost *g,labyrinth *l);
void refreshGhostMemory(ghost *g,labyrinth l);
void moveGhostMemory(ghost *g,labyrinth *l);
bool searchPath(labyrinth *l, int lin, int col, int cont);
int moveGhostInt(labyrinth lab, ghost *g);


#endif // GHOSTS_H_INCLUDED
