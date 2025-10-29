#include "../philo.h"
#define N 60000

int count = 0;
pthread_mutex_t lock;

void *increment(void *n)
{
	// critical section -> lock
	pthread_mutex_lock(&lock);
	count++;
	usleep(200);
	// end critical section -> unlock
	pthread_mutex_unlock(&lock);

	
	return NULL;
}

int main(int argc, char const *argv[])
{
	pthread_t threads[N];
	pthread_mutex_init(&lock, NULL);

	for (int i = 0; i < N; i++)
	{
		if(pthread_create(&threads[i], NULL, increment, NULL))
		{
			printf("error creating thread %d\n", i);
			exit(1);
		}
	}
	
	for (int i = 0; i < N; i++)
	{
		pthread_join(threads[i], NULL);
	}

	printf("count: %d\n", count);
	return 0;
}
