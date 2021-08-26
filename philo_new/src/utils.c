#include "../philo.h"

int	get_time(void)
{
	struct timeval	curr_time;
	// long		res;

	gettimeofday(&curr_time, NULL);
	// curr_time.tv_sec * 1000LL + curr_time.tv_usec / 1000;
	return (curr_time.tv_sec * 1000 + curr_time.tv_usec / 1000);  
}

int	get_work_time(int time)
{
	struct timeval	output_time;
	// long		res;

	gettimeofday(&output_time, NULL);
	// res = output_time.tv_sec * 1000LL + output_time.tv_usec / 1000;
	return ((output_time.tv_sec * 1000 + output_time.tv_usec / 1000) - time);
}