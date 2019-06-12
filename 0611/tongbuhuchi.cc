#include <stdio.h>
#include <unistd.h>
#include <vector>
#include <pthread.h>

std::vector<int> data;

void* Product(void* arg){
    (void)arg;

    return NULL;
}

void* Consume(void* arg){
    (void)arg;

    return NULL;
}

int main(){
    pthread_t tid1,tid2;
    pthread_create(&tid1,NULL,Product,NULL);
    pthread_create(&tid2,NULL,Consume,NULL);

    pthread_join(tid1,NULL);
    pthread_join(tid2,NULL);

    return 0;
}

