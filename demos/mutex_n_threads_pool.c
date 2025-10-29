#include "../philo.h"

#define THREADS 8
#define ITERATIONS 7500 // 8 * 7500 = 60000

int count = 0;
pthread_mutex_t lock;

void *increment(void *n)
{
    for (int i = 0; i < ITERATIONS; i++)
    {
        // critical section
        pthread_mutex_lock(&lock);
        count++;
        pthread_mutex_unlock(&lock);
    }
    return NULL;
}

int main(int argc, char const *argv[])
{
	pthread_t threads[THREADS];
	pthread_mutex_init(&lock, NULL);

	for (int i = 0; i < THREADS; i++)
	{
		if(pthread_create(&threads[i], NULL, increment, NULL))
		{
			printf("error creating thread %d\n", i);
			exit(1);
		}
	}
	
	for (int i = 0; i < THREADS; i++)
	{
		pthread_join(threads[i], NULL);
	}

	printf("count: %d\n", count);
	return 0;
}
