#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include "labyrinth.h"
#include "pacman.h"
#include "ghosts.h"


int main(){

    labyrinth l;
    pacman p;
    ghost *g = malloc(3*sizeof(ghost));

    int i, superPacman = 0;
    bool pacalive = true;
    bool end = false;
    bool move = false;


    printf("Utilisez les touches O, K, L et M pour vous deplacer\n");
    printf("La touche Q permet de quitter le jeu\n");
    printf("Bonne chance!\n");

    getch();

    printf("Selectionnez un niveau de difficulte compris entre 1 et 3\n");

    scanf("c", i);

    initLabFile("lab", &l);
    printLab(&l);
    initPacman(&p, 1, 1, &l);

    for(i = 0; i < 3; i++){

        initGhostRand(&g[i], &l);
    }


    collide(&l, &p, &g);

    printLab(&l);
//    copyLab(l, &(g.memoire.lab));

    while(l.nbGomme > p.points && end != true){

            if(superPacman == 0){

            switch(getch()){

                case 'q' :
                    end = 0;
                    break;

                case 'o' :
                    move = movePacmanTop(&p, &l);
                    break;

                case 'k' :
                    move = movePacmanLeft(&p, &l);
                    break;

                case 'l' :
                    move = movePacmanBottom(&p, &l);
                    break;

                case 'm' :
                    move = movePacmanRight(&p, &l);
                    break;
            }

            for(i = 0; i < 3; i++){

               //refreshGhostMemory(&g[i], l);
               //moveGhostRand(&g[i], &l);
               //moveGhostMemory(&g[i], &l);
               moveGhostInt(l, &g[i]);
            }

            printLab(&l);

            printf("Points: %d/%d", p.points, l.nbGomme);

            }else{

            switch(getch()){

                case 'q' :
                    end = 0;
                    break;

                case 'o' :
                    move = moveSuperPacmanTop(&p, &l);
                    break;

                case 'k' :
                    move = moveSuperPacmanLeft(&p, &l);
                    break;

                case 'l' :
                    move = moveSuperPacmanBottom(&p, &l);
                    break;

                case 'm' :
                    move = moveSuperPacmanRight(&p, &l);
                    break;
            }
        }

       }

    if(p.points == l.nbGomme){

            printf("Victoire\n");
    }
    else{

            if(pacalive == false || end == true){

            printf("Game Over!\n");
            }
        }

    return 0;
}
