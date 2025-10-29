#include "../philo.h"

int i = 0;

void *increment(void *n)
{
	i++;
	sleep(1);
	
	return NULL;
}

int main(int argc, char const *argv[])
{
	pthread_t thread1;
	pthread_t thread2;

	pthread_create(&thread1, NULL, increment, NULL);
	pthread_create(&thread2, NULL, increment, NULL);

	pthread_join(thread1, NULL);
	pthread_join(thread2, NULL);

	printf("i: %d\n", i);
	return 0;
}
