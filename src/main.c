#include "../philo.h"

void *test(void *arg)
{
	usleep(100000);
	printf("Just testing thread\n");
	usleep(100000);
	return (NULL);
}

int main()
{
	pthread_t thread_id;

	// char *str1 = "1_1_1_1_1_1";
	// char *str2 = "2_2_2_2_2_2";

	pthread_create(&thread_id, NULL, test, NULL);
	pthread_join(thread_id, NULL);
}