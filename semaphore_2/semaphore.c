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


void decrease_count(int count) {
    available_resources -= count;
}

void increase_count(int count) {
    available_resources += count;
}

int assign_resource(int pthread_number, int needed_resources) {
    sem_wait(sem);
    if (available_resources == 0 || available_resources - needed_resources < 0) {
//        printf("%d - No hay recursos suficientes!\n", pthread_number + 1);
        return 0;
    }
    printf("Will try to take %d from %d\n", needed_resources, available_resources);
    decrease_count(needed_resources);
    if (needed_resources < 0) {
        printf("============================\nERROR: RESOURCE OVERFLOW\n============================\n");
        exit(-1);
    }
    printf("%d - Semaforo abierto con exito. (Taking %d resources)\n", pthread_number + 1, needed_resources);
    sleep(1);
    printf("%d - Recurso devuelto (%d) :)\n", pthread_number + 1, needed_resources);
    increase_count(needed_resources);
    sem_post(sem);
    return 1;
}

void *worker(void *i) {
    int pthread_number;
    pthread_number = *((int *) (&i));
    printf("Iniciando thread %d\n", pthread_number + 1);
    for (int i = 0; i < PTHREAD_ITERATIONS; ++i) {
        printf("%d - Iniciando iteracion %d\n", pthread_number + 1, i + 1);
        int needed_resources = rand() % MAX_AVAILABLE_RESOURCES - 1;
        if (needed_resources <= 0) needed_resources = 1;
        while (!assign_resource(pthread_number, needed_resources)) {};
    }
    mark_done(pthread_number);
    return NULL;
}

int main() {
    unsigned int value;
    printf("Iniciando programa\n");

    // Variable init
    sem = sem_open("pSem", O_CREAT, 0600, &value);
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