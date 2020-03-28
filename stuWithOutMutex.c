#include <stdio.h>
#include <pthread.h>
#include <math.h>
#include <unistd.h>


void *student(void *stu);

pthread_mutex_t mutex;

int money = 4000;

int stuMoney[3] = {0, 0, 0};

int main()
{
        int i;
        pthread_t tid;
        int tnum[3];
        for (i = 0; i < 3; i++){
                tnum[i] = i;
                pthread_create(&tid, NULL, (void *(*)(void *))student, &tnum[i]);
        }

        pthread_exit(0);

}

void *student(void *stu)
{
        int *thread_num = stu;
        char stuName = (char)(*thread_num + 65);

        while(money != 0){
                int temp = ceil((double)money/4);
                stuMoney[*thread_num] += temp;
                money -= temp;
                printf("\nstudent %c took: %i\nthere is %i money left\n", stuName, temp, money);
	        sleep(1);
        }
        if(*thread_num == 0){
                printf("\nstudent A has: %i\nstudent C has %i\n student C has %i\n all together they have %i\n", stuMoney[0], stuMoney[1], stuMoney[2], stuMoney[0]+stuM
oney[1]+stuMoney[2]);
        }
}