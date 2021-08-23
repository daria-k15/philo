#include "../philo.h"

void *smth()
{
	int i = 0;
	while (i < 10)
	{
		printf("thread ID = %d   smth\n", getpid());
		i++;
		usleep(1000);
	}
	return (NULL);
}

int main()
{
	int i = 0;
	pthread_t t1;

	pthread_create(&t1, NULL, smth, NULL);
	while (i < 10)
	{
		printf("thread ID = %d  main\n", getpid());
		usleep(1000);
		i++;
	}
	// pthread_join(t1, NULL);
}