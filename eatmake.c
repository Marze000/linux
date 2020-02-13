#include <stdio.h>
#include <unistd.h>
#include <pthread.h>

#define PTHREADCOUNT 4
pthread_mutex_t g_mutex;
pthread_cond_t g_eatcond;
pthread_cond_t g_makecond;

int g_middle = 0;

void* EatStart(void* arg){
    while(1){
        pthread_mutex_lock(&g_mutex);
        while(g_middle == 0){
            pthread_cond_wait(&g_eatcond,&g_mutex);
        }
        g_middle--;
        printf("i am a pthrad:[%p], eat a [%d] middle\n",
                pthread_self(),g_middle);
        pthread_mutex_unlock(&g_mutex);
        pthread_cond_signal(&g_makecond);
    }

}
void* MakeStart(void* arg){
    while(1){
        pthread_mutex_lock(&g_mutex);
        while(g_middle == 1){
            pthread_cond_wait(&g_makecond,&g_mutex);
        }
        g_middle++;
        printf("i am a pthrad:[%p],make a [%d] middle\n",
                pthread_self(),g_middle);
        pthread_mutex_unlock(&g_mutex);
        pthread_cond_signal(&g_eatcond);
    }
}

int main(){
    pthread_t eatpid[PTHREADCOUNT],makepid[PTHREADCOUNT];
    pthread_mutex_init(&g_mutex,NULL);
    pthread_cond_init(&g_makecond,NULL);
    pthread_cond_init(&g_eatcond,NULL);

    for(int i = 0;i < PTHREADCOUNT; ++i){
        pthread_create(&eatpid[i],NULL,EatStart,NULL);
        pthread_create(&makepid[i],NULL,MakeStart,NULL);
    }
    for(int i = 0;i < PTHREADCOUNT; ++i){
        pthread_join(eatpid[i],NULL);
        pthread_join(makepid[i],NULL);
    }
    pthread_mutex_destroy(&g_mutex);
    pthread_cond_destroy(&g_eatcond);
    pthread_cond_destroy(&g_makecond);
    return 0;
}

