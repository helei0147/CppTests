#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

#define NUMBER_OF_THREAD 10

void* print_hello_world(void *tid)
{
    printf("Hello World.Greetings from thread %d\n",tid);
    pthread_exit(NULL);
}
int main(int argc,char * argv[])
{
    pthread_t threads(NUMBER_OF_THREAD);
    int status,i;
    for(int i=0;i<NUMBER_OF_THREAD;i++)
    {
        printf("Main here, Creating thread %d \n",i);
        status=pthread_create(&threads[i],NULL,print_hello_world,(void *)i);
        if(status!=0)
        {
            printf("Ooops,pthread_create returned error code %d\n", status);
            exit(-1);
        }
    }
    exit(NULL);
}
