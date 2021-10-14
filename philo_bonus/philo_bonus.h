/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: heveline <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/14 14:48:31 by heveline          #+#    #+#             */
/*   Updated: 2021/09/14 14:49:28 by heveline         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_BONUS_H
# define PHILO_BONUS_H

# include <stdlib.h>
# include <pthread.h>
# include <sys/time.h>
# include <unistd.h>
# include <stdio.h>
# include <semaphore.h>
# include <fcntl.h>
# include <sys/stat.h>
# include <signal.h>
# include <sys/types.h>
# include <sys/wait.h>

typedef struct s_input
{
	int				num_of_philo;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				must_to_eat;
	int				death_flag;
	int				finish_eating;
	sem_t			*forks;
	sem_t			*print_lock;
	sem_t			*flag;
}					t_input;

typedef struct s_philo
{
	int				philo_id;
	int				start_to_eat;
	int				need_to_eat;
	t_input			*input;
	struct s_data	*data;
	pid_t			pid;
}					t_philo;

typedef struct s_data
{
	int				ph_count;
	int				start_time;
	t_philo			*philo;
	t_input			*input;
	pthread_t		*thread;
}					t_data;	

int		ft_atoi(const char *str);
int		not_num(const char *str);
int		get_time(void);
void	philo_sleep(int time_to, t_philo *philo);
void	philo_eating(t_philo *philo);
void	sleep_think(t_philo *philo);
int		init_forks(t_data *data);
int		philo_init(t_data *data);
int		input_init(t_data *data, int argc, char **argv);
int		check_arg(int argc, char **argv);

#endif
