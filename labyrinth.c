#include "labyrinth.h"


///Initialise le labyrinth

int initLab(labyrinth *l, int lin, int col){

    int i,j;

    if(lin > 0 && col > 0){

        (*l).col = col;
        (*l).lin = lin;
        (*l).lab = malloc(lin*sizeof(char*));

        for(i = 0; i < lin; i++){
            (*l).lab[i] = malloc(col * sizeof(char));

            for(j = 0; j < col; j++){
                (*l).lab[i][j] = ' ';
            }
        }

        return 1;
    }
    else{

        return 0;
    }
}


///Initialise le labyrinth grâce au fichier filename

int initLabFile(char * filename, labyrinth * l){

    int i=0;
    int j, lin, col;
    char chaine[256] = "";

    (*l).nbGomme = 0;
    FILE * fichier = NULL;

    sprintf(chaine,"labyrinth.txt", filename);

    fichier = fopen(chaine, "r");

    if(fichier == NULL){

        return -1;
    }

    else{

        fscanf(fichier, "%d %d", &lin, &col);

        initLab(l, lin, col);

        fgets(chaine, 256, fichier);

        while(fgets(chaine, 256, fichier) != NULL && i < (*l).lin){

                for(j = 0; j < (*l).col; j++){

                    switch(chaine[j]){

                        case '#' :
                            (*l).lab[i][j] = chaine[j];
                            break;

                        case ' ' :
                            (*l).lab[i][j] = '.';
                            (*l).nbGomme++;
                            break;

                        case 'O' :
                            (*l).lab[i][j] = chaine[j];
                            break;

                        case 'o' :
                            (*l).lab[i][j] = chaine[j];
                            break;
                    }
                }

                i++;
            }

        (*l).nbGomme--;
        }

    return 0;

    fclose(fichier);
}


///Renseigne sur l'état de la case

char getCase(labyrinth * l, int lin, int col){

    return((*l).lab[lin][col]);
}


///Change l'état de la case

void setCase(labyrinth * l, int lin, int col, char state){

    (*l).lab[lin][col] = state;
}


///Affiche le labyrinth case par case

void printLab(labyrinth * l){

    if (system("CLS")) system("clear");

    int i,j;

    for(i = 0; i < (*l).lin; i++){

        for(j = 0; j < (*l).col; j++){

            printf("%c",(*l).lab[i][j]);
        }

        printf("\n");
    }

    printf("\n");
}


///Libère l'espace aloué pour le labyrinth

void freeLab(labyrinth *l){

    int i;

    for(i = 0; i < (*l).lin; i++){

        free((*l).lab[i]);
        free((*l).lab);
    }
}


///Créé une copie du labyrinth

void copyLab(labyrinth l1,labyrinth *l2){

    int i, j;

    initLab(l2, l1.lin, l1.col);

    for(i = 0; i < l1.lin; i++){

        for(j = 0; j < l1.col; j++){

                (*l2).lab[i][j] = l1.lab[i][j];
        }
    }
}


///Depile la file

list_labyrinth *defile(list_labyrinth *l){

    list_labyrinth **p;
    p = malloc(sizeof(list_labyrinth *));
    (*p) = l;

    if((*p) != NULL){

        while((*(*p)).next != NULL)
                (*p) = (*(*p)).next;
    }

    (*p) = NULL;

    return(l);
}


///Empile la file

list_labyrinth *enfile_copie(list_labyrinth *l, labyrinth lab){

    list_labyrinth *p;
    p = malloc(sizeof(list_labyrinth));
    (*p).l = malloc(sizeof(labyrinth));

    if(l == NULL){

            l = p;
            copyLab(lab, (*l).l);
            (*l).next = NULL;

            return(l);

    }else{

        copyLab(lab, (*p).l);
        (*p).next = l;

         return(p);
    }
}

