/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: heveline <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/30 21:06:51 by heveline          #+#    #+#             */
/*   Updated: 2021/08/30 21:07:39 by heveline         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdlib.h>
# include <pthread.h>
# include <sys/time.h>
# include <unistd.h>
# include <stdio.h>

typedef struct s_input
{
	int				num_of_philo;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				must_to_eat;
	int				death_flag;
	int				finish_eating;
}					t_input;

typedef struct s_philo
{
	int				philo_id;
	int				start_to_eat;
	int				need_to_eat;
	t_input			*input;
	struct s_data	*data;
	pthread_mutex_t	*right_fork;
	pthread_mutex_t	*left_fork;
	pthread_mutex_t	*print_lock;
}					t_philo;

typedef struct s_data
{
	int				ph_count;
	int				start_time;
	t_philo			*philo;
	t_input			*input;
	pthread_t		*thread;
	pthread_mutex_t	**forks;
}					t_data;		

int		ft_atoi(const char *str);
int		get_time(void);
int		fork_init(t_data *data);
int		philo_init(t_data *data);
int		input_init(t_data *data, int argc, char **argv);
int		not_num(const char *str);
void	philo_sleep(int time_to, t_philo *philo);
void	philo_sleep_think(t_philo *philo);
void	philo_eating(t_philo *philo);
int		input_init(t_data *data, int argc, char **argv);
#endif
