#ifndef PACMAN_H_INCLUDED
#define PACMAN_H_INCLUDED


#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>


#include "labyrinth.h"
#include "ghosts.h"


typedef struct{
    int x, y;
    int points;
    int superPacman;
    int nb_vie;
    bool pacalive;
    char ** pakku;

}pacman;



void initPacman(pacman *p, int x, int y, labyrinth *l);

bool movePacmanTop(pacman *p, labyrinth *l);
bool movePacmanBottom(pacman *p, labyrinth *l);
bool movePacmanLeft(pacman *p, labyrinth *l);
bool movePacmanRight(pacman *p, labyrinth *l);

void collide(labyrinth *l, pacman *p, ghost *g);


/*
void moveSuperPacmanTop(pacman *p, labyrinth *l);
void moveSuperPacmanBottom(pacman *p, labyrinth *l);
void moveSuperPacmanLeft(pacman *p, labyrinth *l);
void moveSuperPacmanRight(pacman *p, labyrinth *l);
*/

#endif // PACMAN_H_INCLUDED
