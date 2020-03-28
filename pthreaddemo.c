#include <stdio.h>
#include <pthread.h>


void *student(void *stu);

pthread_mutex_t mutex;


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
        printf("%i\n",*thread_num);
        char stuName = (char)(*thread_num + 65);
        printf("hello from student %c\n", stuName);
        //pthread_mutex_lock(&mutex);
        //pthread_mutex_unlock(&mutex);

}