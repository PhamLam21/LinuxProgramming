#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<unistd.h>
#include<pthread.h>

pthread_t pthread1 , pthread2;

typedef struct 
{
    char name[30];
    int date;
    char sdt[11];
    char city[20];
} human_t;
void outputData(human_t* data)
{
    printf("%s\n", data->name);
    printf("%d\n", data->date);
    printf("%s\n", data->sdt);
    printf("%s\n", data->city);
}
static void *handle_thread(void* args)
{
    pthread_t tid = pthread_self();
    human_t *hm1 = (human_t *) args;

    if(pthread_equal(tid, pthread1))
    {
        printf("I'm in thread 1\n");
    }
    else
    {
        outputData(hm1);
    }
}


int main()
{
    human_t hm1 = {0};
    int ret = 0;
    strncpy(hm1.name, "Pham Lam", sizeof(hm1.name));
    hm1.date = 2002;
    strncpy(hm1.sdt, "0985450902", sizeof(hm1.sdt));
    strncpy(hm1.city, "Son La", sizeof(hm1.city));

    if(ret = pthread_create(&pthread1, NULL, handle_thread, NULL)) 
    {
        printf("pthread_create() error number = %d\n", ret);
        return -1;
    }
    sleep(4);
    if(ret = pthread_create(&pthread2, NULL, handle_thread, &hm1)) 
    {
        printf("pthread_create() error number = %d\n", ret);
        return -1;
    }
    sleep(5);

    pthread_join(pthread1, NULL);
    pthread_join(pthread2, NULL);

    return 0;
}