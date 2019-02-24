#include "pacman.h"


///Initialise Pacman aux coordonnées pré-définies

void initPacman(pacman *p, int x, int y, labyrinth *l){

    int i,j;

    if(x > 0 && y > 0){
        (*p).x = x;
        (*p).y = y;
        (*p).pakku = malloc((*l).lin * sizeof(char*));

        for(i = 0; i < (*l).lin; i++){
            (*p).pakku[i] = malloc((*l).col * sizeof(char));

            for(j = 0; j < (*l).col; j++){
                (*p).pakku[i][j] = ' ';
            }
        }
    }

    (*l).lab[x][y] = 'c';
    (*p).points = 0;
    (*p).superPacman = 0;

}


///Déplace Pacman vers le haut

bool movePacmanTop(pacman *p, labyrinth *l){

    int i = (*p).x;
    int j = (*p).y;
    int superPacman;
    bool pacalive, end;

    switch((*l).lab[i-1][j]){

        case '#' :
            (*l).lab[i][j] = 'c';
            break;

        case '.' :
            (*p).x--;
            (*p).points++;
            (*l).lab[i][j] = ' ';
            (*l).lab[i-1][j] = 'c';
            break;

        case ' ' :
            (*p).x--;
            (*l).lab[i][j] = ' ';
            (*l).lab[i-1][j] = 'c';
            break;

        case 'o' :
            (*p).x--;
            (*l).lab[i][j] = ' ';
            (*l).lab[i-1][j] = 'c';
            return superPacman++;
            break;

        case '&' :
            (*l).lab[i][j] = ' ';
            //initPacman(p, 1, 1, l);
            (*p).nb_vie--;
            pacalive = false;
            end = true;
            break;

    }
}


///Déplace Pacman vers le bas

bool movePacmanBottom(pacman *p, labyrinth *l){

    int i = (*p).x;
    int j = (*p).y;
    int superPacman;
    bool pacalive, end;

    switch((*l).lab[i+1][j]){

        case '#' :
            (*l).lab[i][j] = 'c';
            break;

        case '.' :
            (*p).x++;
            (*p).points++;
            (*l).lab[i][j] = ' ';
            (*l).lab[i+1][j] = 'c';
            break;

        case ' ' :
            (*p).x++;
            (*l).lab[i][j] = ' ';
            (*l).lab[i+1][j] = 'c';
            break;

        case 'o' :
            (*p).x++;
            (*l).lab[i][j] = ' ';
            (*l).lab[i+1][j] = 'c';
            return superPacman++;
            break;

        case '&' :
            (*l).lab[i][j] = ' ';
            //initPacman(p, 1, 1, l);
            (*p).nb_vie--;
            pacalive = false;
            end = true;
            break;

    }
}


///Déplace Pacman vers la gauche

bool movePacmanLeft(pacman *p,labyrinth *l){

    int i = (*p).x;
    int j = (*p).y;
    int superPacman;
    bool pacalive, end;

    switch((*l).lab[i][j-1]){

        case '#' :
            (*l).lab[i][j] = 'c';
            break;

        case '.' :
            (*p).y--;
            (*p).points++;
            (*l).lab[i][j] = ' ';
            (*l).lab[i][j-1] = 'c';
            break;

        case ' ' :
            (*p).y--;
            (*l).lab[i][j] = ' ';
            (*l).lab[i][j-1] = 'c';
            break;

        case 'o' :
            (*p).y--;
            (*l).lab[i][j] = ' ';
            (*l).lab[i][j-1] = 'C';
            return superPacman++;
            break;

        case '&' :
            (*l).lab[i][j] = ' ';
            //initPacman(p, 1, 1, l);
            (*p).nb_vie--;
            pacalive = false;
            end = true;
            break;

    }
}


///Déplace Pacman vers la droite

bool movePacmanRight(pacman *p, labyrinth *l){

    int i = (*p).x;
    int j = (*p).y;
    int superPacman;
    bool pacalive, end;

    switch((*l).lab[i][j+1]){

        case '#' :
            (*l).lab[i][j] = 'c';
            break;

        case '.' :
            (*p).y++;
            (*p).points++;
            (*l).lab[i][j] = ' ';
            (*l).lab[i][j+1] = 'c';
            break;

        case ' ' :
            (*p).y++;
            (*l).lab[i][j] = ' ';
            (*l).lab[i][j+1] = 'c';
            break;


        case 'o' :
            (*p).y++;
            (*l).lab[i][j] = ' ';
            (*l).lab[i][j+1] = 'c';
            return true;
            break;

        case '&' :
            (*l).lab[i][j] = ' ';
            //initPacman(p, 1, 1, l);
            (*p).nb_vie--;
            pacalive = false;
            end = true;
            break;

    }
}

void collide(labyrinth *l, pacman *p, ghost *g)
{
    bool end = 0;
    if(((*g).galive)){

        if(((*p).x == (*g).lin) && ((*p).y == (*g).col)){

            if((*p).superPacman > 0){

                setCase(l,(*p).x,(*p).y,'C');
                (*g).galive = false;

            }else{

                //setCase(l,(*p).x,(*p).y, 'X');
                (*p).pacalive = false;
                end = true;
            }
        }
    }
}

// SUPER PACMAN

bool moveSuperPacmanTop(pacman *p, labyrinth *l, ghost *g){

    int i = (*p).x;
    int j = (*p).y;
    int superPacman;

    switch((*l).lab[i-1][j]){

        case '#' :
            (*l).lab[i][j] = 'C';
            break;

        case '.' :
            (*p).x--;
            (*p).points++;
            (*l).lab[i][j] = ' ';
            (*l).lab[i-1][j] = 'C';
            break;

        case ' ' :
            (*p).x--;
            (*l).lab[i][j] = ' ';
            (*l).lab[i-1][j] = 'C';
            break;

        case 'o' :
            (*p).x--;
            (*l).lab[i][j] = 'o';
            (*l).lab[i-1][j] = 'C';
            return superPacman++;
            break;

        case '&' :
            (*l).lab[i][j] = ' ';
            //initGhostRand(&g, l);
            break;

    }
}

bool moveSuperPacmanBottom(pacman *p, labyrinth *l){

    int i = (*p).x;
    int j = (*p).y;
    int superPacman;

    switch((*l).lab[i+1][j]){

        case '#' :
            (*l).lab[i][j] = 'C';
            break;

        case '.' :
            (*p).x++;
            (*p).points++;
            (*l).lab[i][j] = ' ';
            (*l).lab[i+1][j] = 'C';
            break;

        case ' ' :
            (*p).x++;
            (*l).lab[i][j] = ' ';
            (*l).lab[i+1][j] = 'C';
            break;

        case 'o' :
            (*p).x++;
            (*l).lab[i][j] = ' ';
            (*l).lab[i+1][j] = 'C';

            break;

        case '&' :
            (*l).lab[i][j] = ' ';
            //initGhostRand(&g, l);
            break;
    }
}

bool moveSuperPacmanLeft(pacman *p,labyrinth *l){

    int i = (*p).x;
    int j = (*p).y;
    int superPacman;

    switch((*l).lab[i][j-1]){

        case '#' :
            (*l).lab[i][j] = 'C';
            break;

        case '.' :
            (*p).y--;
            (*p).points++;
            (*l).lab[i][j] = ' ';
            (*l).lab[i][j-1] = 'C';
            break;

        case ' ' :
            (*p).y--;
            (*l).lab[i][j] = ' ';
            (*l).lab[i][j-1] = 'C';
            break;

        case 'o' :
            (*p).y--;
            (*l).lab[i][j] = ' ';
            (*l).lab[i][j-1] = 'C';

            break;

        case '&' :
            (*l).lab[i][j] = ' ';
            //initGhostRand(&g, l);
            break;

    }
}

bool moveSuperPacmanRight(pacman *p, labyrinth *l){

    int i = (*p).x;
    int j = (*p).y;
    int superPacman;

    switch((*l).lab[i][j+1]){

        case '#' :
            (*l).lab[i][j] = 'C';
            break;

        case '.' :
            (*p).y++;
            (*p).points++;
            (*l).lab[i][j] = ' ';
            (*l).lab[i][j+1] = 'C';
            break;

        case ' ' :
            (*p).y++;
            (*l).lab[i][j] = ' ';
            (*l).lab[i][j+1] = 'C';
            break;

        case 'o' :
            (*p).y++;
            (*l).lab[i][j] = ' ';
            (*l).lab[i][j+1] = 'C';
            return superPacman = true;
            break;

        case '&' :
            (*l).lab[i][j] = ' ';
            //initGhostRand(&g, l);
            break;
    }
}

