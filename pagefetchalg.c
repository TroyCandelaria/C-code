#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define refSize 20

int optimal(int, int*);
int LRU(int, int*);

/* this code compares a "least recently used" page fetching scheme to an optimal solution*/
int main(int argc, char *argv[]){
        if(argc != 2){printf("usage: include number of frames in command line");exit(-1);}
        int numFrame = atoi(argv[1]);
        if(numFrame < 1){printf("number of frames must be atleast 1"); exit(-1);}

        int ref[refSize], pagefault[2];

        srand(time(0));

        printf("\nrefrence strint: ");
        for(int i = 0; i < refSize; i++){
                //fills a refrence string with values 1-5
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
                        //compare ref to all val in frame to see if theres a page match
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
                        //initalises a distance array
                        int dist[numFrame];
                        for(int j = 0; j < numFrame; j++){
                                dist[j] = -1;
                        }
                        //find the page that will be refrence the latest
                        for(int j = i; j < refSize; j++){
                                for(int k = 0; k < numFrame; k++){
                                        if(*(frame + k) == *(ref + j) && dist[k] == -1){
                                                dist[k] = j;
                                        }
                                }
                        }
                        int great = 0;
                        int index = -1;
                        //replace latest refrences page with current page
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
                        //compare ref to all val in frame to see if theres a page match
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
                        //finds page that was refrenced the longest time ago
                        for(int j = i; j >= 0; j--){
                                for(int k = 0; k < numFrame; k++){
                                        if(*(frame + k) == *(ref + j) && dist[k] == -1){
                                                dist[k] = i - j;
                                        }
                                }
                        }

                        int great = 0;
                        int index = -1;
                        
                        //replace LRU page with curent page
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
                //print frames
                for(int j = 0; j < numFrame; j++){
                printf("%i ", *(frame + j));
                }
                printf("\n");

        }
        return numFaults;
}
