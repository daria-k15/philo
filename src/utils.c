#include "../philo.h"

int	get_time(void)
{
	struct timeval	curr_time;
	int				res;

	gettimeofday(&curr_time, NULL);
	res = curr_time.tv_sec * 1000 + curr_time.tv_usec / 1000;
	return (res);  
}