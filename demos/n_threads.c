#include "../philo.h"
#define N 20000

int i = 0;

void *increment(void *n)
{
	i++;
	sleep(2);
	
	return NULL;
}

int main(int argc, char const *argv[])
{
	pthread_t threads[N];

	for (int i = 0; i < N; i++)
	{
		pthread_create(&threads[i], NULL, increment, NULL);
	}
	
	for (int i = 0; i < N; i++)
	{
		pthread_join(threads[i], NULL);
	}

	printf("i: %d\n", i);
	return 0;
}
