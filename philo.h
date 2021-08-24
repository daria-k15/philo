#ifndef PHILO_H
# define PHILO_H

#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <sys/time.h>
#include <pthread.h>
#include <stdlib.h>

typedef struct s_input
{
	int				philo_count;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				eating_sum;
	int				death_flag;
	int				end_eat;
	pthread_mutex_t	*locking;
}					t_input;

typedef struct s_philo
{
	int				philo_id;
	pthread_mutex_t	*left_fork;
	pthread_mutex_t	*right_fork;
	pthread_mutex_t	*print;
	int				start_eat;
	int				need_to_eat;
}					t_philo;

typedef struct s_all
{
	int				philo_count;
	t_philo			*philo;
	t_input			*input;
	pthread_t		*thread;
	pthread_mutex_t	**forks;
}					t_all;


int	ft_atoi(const char *str);

#endif