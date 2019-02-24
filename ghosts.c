#include "ghosts.h"


///Initialise un fantôme au hasard

void initGhostRand(ghost *g,labyrinth *l){

    srand(time(NULL));

    int i = rand()%(*l).lin;
    int j = rand()%(*l).col;

    while((*l).lab[i][j] != '.'){

        i = rand()%(*l).lin, j = rand()%(*l).col;
    }

    (*g).collide = (*l).lab[i][j];
    (*g).lin = i;
    (*g).col = j;
    (*l).lab[i][j] = '&';
    (*g).memory = NULL;
    (*g).nb_lab = 0;
    (*g).smartMemory = malloc(sizeof(labyrinth));
    (*g).galive = true;

}


///Déplacement du fantôme au hasard

void moveGhostRand(ghost *g, labyrinth *l){

    int direction, movelin, movecol;

    bool test = false;

    while(!test)
        {

        direction = rand() % 4;

        switch(direction){
        case 0 : ///haut
            movelin = (*g).lin-1;
            movecol = (*g).col;
            break;

        case 1 : ///bas
            movelin = (*g).lin+1;
            movecol = (*g).col;
            break;

        case 2 : ///gauche
            movecol = (*g).col-1;
            movelin = (*g).lin;
            break;

        case 3 : ///droite
            movecol = (*g).col+1;
            movelin = (*g).lin;
            break;
        }

        if((*l).lab[movelin][movecol] != '#')
        {
            test = true;
        }
    }

    if((*l).lab[movelin][movecol] != '&'){



        switch((*l).lab[movelin][movecol]){

            case 'c' :
                (*l).lab[(*g).lin][(*g).col] = (*g).collide;
                break;


            case '.':
                if((*g).collide == 'c'){

                        (*l).lab[(*g).lin][(*g).col] = ' ';

                    }else{

                        (*l).lab[(*g).lin][(*g).col] = (*g).collide;
                    }
                    break;

            case 'o':
                if((*g).collide == 'c'){

                        (*l).lab[(*g).lin][(*g).col] = ' ';

                    }else{

                        (*l).lab[(*g).lin][(*g).col] = (*g).collide;
                    }
                    break;


            case ' ':   if((*g).collide == 'c'){

                        (*l).lab[(*g).lin][(*g).col]=' ';

                    }else{

                        (*l).lab[(*g).lin][(*g).col] = (*g).collide;

                    }
                    break;
        }
                    (*g).collide = (*l).lab[movelin][movecol];
                    (*l).lab[movelin][movecol] = '&';
                    (*g).lin = movelin;(*g).col = movecol;

                    /// AJOUT CAS cerise super pacman

    }else{

        (*g).lin = movelin;
        (*g).col = movecol;
        (*l).lab[movelin][movecol] = '&';
    }
}


///Déplace la mémoire fantôme

void moveGhostMemory(ghost *g,labyrinth *l){

    int direction, movelin, movecol;
    srand(time(NULL));
    bool test = false;
    bool beenHere;
    list_labyrinth *p;

    if((*g).galive)
        {

        (*l).lab[(*g).lin][(*g).col] = (*g).collide;

            while(!test)
            {
            direction = rand() % 4;

            switch(direction){
                case 0 : ///Haut
                    movelin = (*g).lin-1;
                    movecol = (*g).col;
                    break;

                case 1 : ///Bas
                    movelin = (*g).lin+1;
                    movecol = (*g).col;
                    break;

                case 2 : ///Gauche
                    movecol = (*g).col-1;
                    movelin = (*g).lin;
                    break;

                case 3 : ///Droite
                    movecol = (*g).col+1;
                    movelin = (*g).lin;
                    break;
                }

                if(getCase(l,movelin, movecol) != '#')
                {
                    p = (*g).memory;
                    beenHere = true;

                    while(p != NULL){

                        if(getCase((*p).l, movelin, movecol) == 'X'){

                            beenHere = false;
                        }

                        p = (*p).next;
                    }

                }else{

                    beenHere = false;
                }

                if(beenHere){

                    test = true;
                }
            }

            (*g).lin = movelin;
            (*g).col = movecol;
            (*l).lab[movelin][movecol] = '&';
    }
}


///Rafraichit la mémoire fantôme

void refreshGhostMemory(ghost *g, labyrinth l){

    if((*g).nb_lab == 10){

        (*g).memory = defile((*g).memory);
        (*g).memory = enfile_copie((*g).memory, l);
        setCase((*(*g).memory).l, (*g).lin, (*g).col,'X');

    }else{

        (*g).memory=enfile_copie((*g).memory, l);
        setCase((*(*g).memory).l, (*g).lin, (*g).col,'X');
        (*g).nb_lab++;
    }

}


///Cherche un chemin (le plus cours) vers Pacman

bool searchPath(labyrinth *l, int lin, int col, int cont){

    if(getCase(l, lin, col) == 'c' || getCase(l, lin, col) == 'C'){

        return(true);
    }

    if((getCase(l, lin, col) == '#') || (getCase(l, lin, col) == 'x')){

        return(false);
    }

    if(cont > 10){

        return(false);
    }

    setCase(l, lin, col, 'x');

    if(searchPath(l, lin+1, col, cont+1)){

        return(true);
    }

    if(searchPath(l, lin-1, col, cont+1)){

        return(true);
    }

    if(searchPath(l, lin, col+1, cont+1)){

        return(true);
    }

    if(searchPath(l, lin, col-1, cont+1)){

        return(true);
    }

    cont = cont-1;
    setCase(l, lin, col, ' ');

    return (false);
}


///Déplace le fantôme vers Pacman de façon intelligente

int moveGhostInt(labyrinth lab, ghost *g){

    if((*g).galive)
    {
        bool trouver;
        copyLab(lab, (*g).smartMemory);
        trouver = searchPath((*g).smartMemory, (*g).lin, (*g).col, 0);

        if(trouver){

            if(getCase((*g).smartMemory,(*g).lin-1,(*g).col)=='x' || getCase((*g).smartMemory,(*g).lin-1,(*g).col)=='c'){ ///Haut

                lab.lab[(*g).lin][(*g).col] = (*g).collide;
                (*g).collide = lab.lab[(*g).lin-1][(*g).col];
                lab.lab[(*g).lin-1][(*g).col] = '&';
                (*g).lin = (*g).lin-1;
                (*g).col = (*g).col;

                return(0);
            }

            if(getCase((*g).smartMemory,(*g).lin+1,(*g).col) == 'x' || getCase((*g).smartMemory,(*g).lin+1,(*g).col)== 'c'){ ///Bas

                lab.lab[(*g).lin][(*g).col] = (*g).collide;
                (*g).collide = lab.lab[(*g).lin+1][(*g).col];
                lab.lab[(*g).lin+1][(*g).col] = '&';
                (*g).lin = (*g).lin+1;
                (*g).col = (*g).col;

                return(0);
            }

            if(getCase((*g).smartMemory,(*g).lin,(*g).col-1) == 'x' || getCase((*g).smartMemory,(*g).lin,(*g).col-1)== 'c'){ ///Gauche

                lab.lab[(*g).lin][(*g).col] = (*g).collide;
                (*g).collide = lab.lab[(*g).lin][(*g).col-1];
                lab.lab[(*g).lin][(*g).col-1] = '&';
                (*g).lin = (*g).lin;
                (*g).col = (*g).col-1;

                return(0);
            }

            if(getCase((*g).smartMemory,(*g).lin,(*g).col+1) == 'x' || getCase((*g).smartMemory,(*g).lin,(*g).col+1)== 'c'){ ///Droite

                lab.lab[(*g).lin][(*g).col] = (*g).collide;
                (*g).collide = lab.lab[(*g).lin][(*g).col+1];
                lab.lab[(*g).lin][(*g).col+1] = '&';
                (*g).lin = (*g).lin;
                (*g).col = (*g).col+1;

                return(0);
            }

        }else{

            moveGhostRand(g, &lab);
        }
    }

    return(0);
}
