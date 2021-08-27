#ifndef PHILO_H
# define PHILO_H

#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <sys/time.h>
#include <pthread.h>
#include <stdlib.h>

# define EAT	0
# define SLEEP	1
# define THINK	3
# define DIE	4

typedef struct s_forks
{
	pthread_mutex_t	*fork_mutex;
	int				last_touch;
}					t_forks;


typedef struct s_philo
{
	int				philo_index;
	int				philo_count;
	int				start_to_eat;
	int				need_to_eat;
	int				death_flag;
	int				end_to_eat;
	int				max_eat;
	t_forks			*left_fork;
	t_forks			*right_fork;
	pthread_t		*thread;
}					t_philo;

typedef struct s_all
{
	int				num_of_philo;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				eat_sum;
	int				start_time;
	int				philo_count;
	t_philo			*philo;
	t_forks			*forks;
	pthread_mutex_t	*print_lock;
	pthread_mutex_t	*die_lock;
}					t_all;


int	ft_atoi(const char *str);
int	get_time(void);
int	get_work_time(int time);

#endif