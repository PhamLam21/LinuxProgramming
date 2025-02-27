#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<unistd.h>
#include<pthread.h>
#include<fcntl.h>

typedef struct 
{
    char name[30];
    int date;
    char city[20];
} human_t;

human_t hm1;
pthread_mutex_t lock = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t writeData = PTHREAD_COND_INITIALIZER;
pthread_cond_t readData = PTHREAD_COND_INITIALIZER;

char buffer[1024];

void static *inputData(void *args)
{
    while(1)
    {
        pthread_mutex_lock(&lock);

        printf("Moi nhap ten: ");
        scanf("%[^\n]%*c", hm1.name);
        printf("Moi nhap nam sinh: ");
        scanf("%d%*c", &hm1.date);
        printf("Moi nhap que quan: ");
        scanf("%[^\n]%*c", hm1.city);

        pthread_cond_signal(&writeData);
        pthread_cond_wait(&readData, &lock);
        pthread_mutex_unlock(&lock);
    }
}

void static *writeToFile(void *args)
{
    while(1){
        pthread_cond_wait(&writeData, &lock);
        // pthread_mutex_lock(&lock);
        int fd = open("thongtinsinhvien.txt", O_RDWR | O_CREAT , 0766);
        sprintf(buffer, "%s %d %s", hm1.name, hm1.date, hm1.city);
        write(fd, buffer, strlen(buffer));
        memset(buffer, '\0', sizeof(buffer));
        close(fd);

        pthread_cond_signal(&readData);
        pthread_mutex_unlock(&lock);
    }
}

int main()
{
    pthread_t thread_id1, thread_id2;

    if (pthread_create(&thread_id1, NULL, inputData, NULL)) {
        printf("pthread_create() error\n");
        return -1;
    }
    if (pthread_create(&thread_id2, NULL, writeToFile, NULL)) {
        printf("pthread_create() error\n");
        return -1;
    }
    while(1)
    {   
        pthread_cond_wait(&readData, &lock);
        // pthread_mutex_lock(&lock);
        int fd = open("thongtinsinhvien.txt", O_RDWR | O_CREAT , 0766);

        ssize_t number;
        while(number = read(fd, buffer, sizeof(buffer)))
        {
            buffer[number] = 0;
            puts(buffer);
        }
        close(fd);
        pthread_cond_signal(&readData);
        pthread_mutex_unlock(&lock);
    }

    pthread_join(thread_id1, NULL);
    pthread_join(thread_id2, NULL);

    pthread_mutex_destroy(&lock);
    pthread_cond_destroy(&readData);
    pthread_cond_destroy(&writeData);
    return 0;
}
