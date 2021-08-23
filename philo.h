#ifndef PHILO_H
# define PHILO_H

#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <sys/time.h>
#include <pthread.h>

typedef struct s_philo
{
	int	position;
	int lfork;
	int rfork;
}		t_philo;

typedef struct s_invalue
{
	int	philo_number;
	int	time_to_die;
	int	time_to_eat;
	int	time_to_sleep;
	int	eating_sum;
}		t_invalue;

#endif