#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define refSize 20

int optimal(int, int*);
int LRU(int, int*);
void FIFO(int, int, int*, int*);

int main(int argc, char *argv[]){
        if(argc != 2){printf("usage: include number of frames in command line");exit(-1);}
        int numFrame = atoi(argv[1]);
        if(numFrame < 1){printf("number of frames must be atleast 1"); exit(-1);}

        int ref[refSize], pagefault[2];

        srand(time(0));

        printf("\nrefrence strint: ");
        for(int i = 0; i < refSize; i++){
                ref[i] =  (rand() % 5) + 1;
                printf("%i ", ref[i]);
        }
        printf("\n");

        printf("the num faults for optimal: %i\n", optimal(numFrame, ref));
        printf("the num faults for LRU: %i\n", LRU(numFrame, ref));

}

int optimal(int numFrame, int *ref){

        int *frame = malloc(numFrame * sizeof(int));
        int numFaults = 0;

        printf("\nOptimal solution\n\n");

        for(int i = 0; i < refSize; i++){

                int hit = 0;

                for(int j = 0; j < numFrame; j++){

                        if(*(frame + j) == *(ref + i)){
                                printf("hit ");
                                hit = 1;
                                break;
                        }
                }

                if(!hit){
                        numFaults++;
                        printf("page fault ");
                        //check for empty frame
                        for(int j = 0; j < numFrame; j++){
                                if(*(frame + j) == 0){
                                        printf("filling empty frame ");
                                        *(frame + j) = *(ref + i);
                                        hit = 1;
                                        break;
                                }
                        }
                }

                if(!hit){
                        //optimal
                        int count = 0;
                        int dist[numFrame];
                        for(int j = 0; j < numFrame; j++){
                                dist[j] = -1;
                        }
                        for(int j = i; j < refSize; j++){
                                for(int k = 0; k < numFrame; k++){
                                        if(*(frame + k) == *(ref + j) && dist[k] == -1){
                                                dist[k] = j;
                                        }
                                }
                        }
                        int great = 0;
                        int index = -1;
                        for(int j = 0; j < numFrame; j++){
                                if(dist[j] == -1){
                                        index = j;
                                        hit = 1;
                                        break;
                                }
                                if(dist[j] > great){
                                        great = dist[j];
                                        index = j;
                                        hit = 1;
                                }

                        }
                        if(hit){
                                printf("replaced using optimal ");
                                *(frame + index) = *(ref + i);
                        }
                }

                if(!hit){
                        printf("replaced using FIFO");
                        FIFO(i, numFrame, frame, ref);
                }
                //print frames
                for(int j = 0; j < numFrame; j++){
                        printf("%i ", *(frame + j));
                }
                printf("\n");
        }
        return numFaults;

}

int LRU(int numFrame, int *ref){

        int *frame = malloc(numFrame * sizeof(int));
        int numFaults = 0;

        printf("\nLRU solution\n\n");

        for(int i = 0; i < refSize; i++){

                int hit = 0;
                for(int j = 0; j < numFrame; j++){
                        if(*(frame + j) == *(ref + i)){
                                printf("hit ");
                                hit = 1;
                                break;
                        }
                }
                if(!hit){
                        numFaults++;
                        printf("page fault ");
                        //check for empty frame
                        for(int j = 0; j < numFrame; j++){
                                if(*(frame + j) == 0){
                                        printf("filling empty frame ");
                                        *(frame + j) = *(ref + i);
                                        hit = 1;
                                        break;
                                }
                        }
                }
                if(!hit){
                        //LRU
                        int count = 0;
                        int dist[numFrame];
                        for(int j = 0; j < numFrame; j++){
                                dist[j] = -1;
                        }
                        for(int j = i; j >= 0; j--){
                                for(int k = 0; k < numFrame; k++){
                                        if(*(frame + k) == *(ref + j) && dist[k] == -1){
                                                dist[k] = i - j;
                                        }
                                }
                        }

                        int great = 0;
                        int index = -1;

                        for(int j = 0; j < numFrame; j++){
                                if(dist[j] > great){
                                        great = dist[j];
                                        index = j;
                                        hit = 1;
                                }
                        }
                        if(hit){
                                printf("replaced using LRU ");
                                *(frame + index) = *(ref + i);
                        }
                }
                if(!hit){
                        printf("replaced using FIFO");
                        FIFO(i, numFrame, frame, ref);
                }
                //print frames
                for(int j = 0; j < numFrame; j++){
                printf("%i ", *(frame + j));
                }
                printf("\n");

        }
        return numFaults;
}

void FIFO(int i, int numFrame, int *frame, int *ref){
        int count = 0;
        int j = 0;
        int index = i;
        int yo = 0;

        while(count != 3){
                index--;
                for(j = 0; j < numFrame; j++){
                        if(*(frame + j) == *(ref + index)){
                                count++;
                                yo = j;
                        }
                }
        }
        *(frame + yo) = *(ref + i);
}
