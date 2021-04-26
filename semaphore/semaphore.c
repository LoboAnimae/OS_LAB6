/**
 * Generates several PThreads. Parameters in semaphore.h.
 * Allows for resources to be consumed. Best results when
 * resources are less than pthreads.
 * */

#include "semaphore.h"
sem_t *sem;
int pthreads_done;


void mark_done(int pthread_number) {
    printf("Terminando thread %d\n", pthread_number + 1);
    pthreads_done++;
}

int assign_resource(int pthread_number) {
    sem_wait(sem);
    if (available_resources == 0) {
//        printf("%d - No hay recursos!\n", pthread_number + 1);
        return 0;
    }
    available_resources--;
    printf("%d - Semaforo abierto con exito.\n", pthread_number + 1);
    sleep(1);
    printf("%d - Recurso devuelto :)\n", pthread_number + 1);
    available_resources++;
    sem_post(sem);
    return 1;
}

void *worker(void *i) {
    int pthread_number;
    pthread_number = *((int *) (&i));
    printf("Iniciando thread %d\n", pthread_number + 1);
    for (int i = 0; i < PTHREAD_ITERATIONS; ++i) {
        printf("%d - Iniciando iteracion %d\n", pthread_number + 1, i + 1);
        assign_resource(pthread_number);
        while (!assign_resource(pthread_number)) {};
    }
    mark_done(pthread_number);
    return NULL;
}

int main() {

    unsigned int value;
    printf("Iniciando programa\n");

    // Variable init
    sem = sem_open("pSem", O_CREAT, 0777, &value);
    if (sem == SEM_FAILED) {
        printf("============================\nERROR: SEMAPHORE ERROR\n============================\n");
        exit(-1);
    }

    // Variable assign
    pthreads_done = 0;

    // Try to grab the memory needed for the threads
    pthread_t threads[PTHREAD_NUMBER];
    printf("Creando threads\n");
    // Generate the P-Threads
    for (int i = 0; i < PTHREAD_NUMBER; ++i) {
        pthread_create(&threads[i], NULL, worker, (void *) i);
    }
    do {

    } while (pthreads_done != PTHREAD_NUMBER - 1);
    printf("Fertig!\n");
    return 0;
}