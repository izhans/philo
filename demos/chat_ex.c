// philos_demo.c
// Compile: gcc -Wall -Wextra -pthread -o philos_demo philos_demo.c
// Usage: ./philos_demo 0   # mode 0 = comer con lock (correcto)
//        ./philos_demo 1   # mode 1 = liberar antes de comer (incorrecto)

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
#include <sys/time.h>

#define N 5
#define ROUNDS 3

pthread_mutex_t forks[N];
int mode = 0; // 0 = comer con lock; 1 = liberar antes de comer

static long now_ms(void) {
    struct timeval tv;
    gettimeofday(&tv, NULL);
    return tv.tv_sec * 1000L + tv.tv_usec / 1000L;
}

void log_msg(const char *s, int id) {
    printf("[%6ld ms] Philosopher %d %s\n", now_ms(), id, s);
    fflush(stdout);
}

void *philosopher(void *arg) {
    int id = (int)(intptr_t)arg;
    int left = id;
    int right = (id + 1) % N;

    for (int r = 0; r < ROUNDS; r++) {
        // Think (no locks)
        log_msg("is thinking", id);
        usleep(100 * 1000); // 100ms

        // Try to take forks: simple ordering to reduce deadlock (lower id first)
        if (left < right) {
            pthread_mutex_lock(&forks[left]);
            log_msg("picked up left fork", id);
            pthread_mutex_lock(&forks[right]);
            log_msg("picked up right fork", id);
        } else {
            pthread_mutex_lock(&forks[right]);
            log_msg("picked up right fork", id);
            pthread_mutex_lock(&forks[left]);
            log_msg("picked up left fork", id);
        }

        if (mode == 0) {
            // MODE 0: Eat while holding forks -> correct modelling
            log_msg("starts eating (holding forks)", id);
            usleep(200 * 1000); // 200ms simulate eating
            log_msg("stops eating, will release forks", id);

            pthread_mutex_unlock(&forks[left]);
            pthread_mutex_unlock(&forks[right]);
            log_msg("released both forks", id);
        } else {
            // MODE 1: release forks BEFORE eating -> incorrect
            pthread_mutex_unlock(&forks[left]);
            pthread_mutex_unlock(&forks[right]);
            log_msg("released forks (BAD) and now starts eating WITHOUT holding them", id);
            usleep(200 * 1000); // eating while not holding forks
            log_msg("stops eating (didn't hold forks)", id);
        }
    }

    log_msg("is done", id);
    return NULL;
}

int main(int argc, char **argv) {
    if (argc >= 2) mode = atoi(argv[1]);
    printf("Running demo with mode=%d (%s)\n", mode,
        mode == 0 ? "COMER_CON_LOCK (eat while holding forks)"
                   : "COMER_SIN_LOCK (release then eat)");

    for (int i = 0; i < N; i++) pthread_mutex_init(&forks[i], NULL);

    pthread_t th[N];
    for (int i = 0; i < N; i++) {
        if (pthread_create(&th[i], NULL, philosopher, (void*)(intptr_t)i)) {
            perror("pthread_create");
            exit(1);
        }
    }
    for (int i = 0; i < N; i++) pthread_join(th[i], NULL);

    for (int i = 0; i < N; i++) pthread_mutex_destroy(&forks[i]);
    printf("Demo finished.\n");
    return 0;
}
