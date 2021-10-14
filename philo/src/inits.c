/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   inits.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: heveline <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/30 20:49:11 by heveline          #+#    #+#             */
/*   Updated: 2021/08/30 21:02:13 by heveline         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

int	fork_init(t_data *data)
{
	int	i;

	i = 0;
	data->forks = (pthread_mutex_t **)malloc(sizeof(pthread_mutex_t *) \
			* (data->ph_count + 1));
	if (!data->forks)
		return (printf("Error in memory allocation!\n"));
	while (i <= data->ph_count)
	{
		data->forks[i] = (pthread_mutex_t *)malloc(sizeof(pthread_mutex_t));
		if (!data->forks[i])
			return (printf("Error in memory allocation!\n"));
		i++;
	}
	i = 0;
	while (i <= data->ph_count)
	{
		if ((pthread_mutex_init(data->forks[i], NULL) != 0))
			return (printf("Error in mutex initialisation!\n"));
		i++;
	}
	return (0);
}

int	philo_init(t_data *data)
{
	int	i;

	i = 0;
	data->thread = (pthread_t *)malloc(sizeof(pthread_t) \
			* data->input->num_of_philo);
	data->philo = (t_philo *)malloc(sizeof(t_philo) \
			* data->input->num_of_philo);
	if (!data->philo || !data->thread)
		return (printf("Error in memory allocation!\n"));
	while (i < data->ph_count)
	{
		data->philo[i].philo_id = i;
		data->philo[i].start_to_eat = get_time();
		data->philo[i].need_to_eat = data->input->must_to_eat;
		data->philo[i].input = data->input;
		data->philo[i].left_fork = data->forks[i];
		data->philo[i].data = data;
		if (i == 0)
			data->philo[i].right_fork = data->forks[data->ph_count - 1];
		else
			data->philo[i].right_fork = data->forks[i - 1];
		data->philo[i].print_lock = data->forks[data->ph_count];
		i++;
	}
	return (0);
}

int	check_arg(int argc, char **argv)
{
	if (argc == 6)
	{
		if (not_num(argv[5]) != 0 || ft_atoi(argv[5]) < 0)
			return (1);
	}
	if (not_num(argv[1]) != 0 || not_num(argv[2]) != 0
		|| not_num(argv[3]) != 0 || not_num(argv[4]) != 0)
		return (1);
	if (ft_atoi(argv[1]) < 0 || ft_atoi(argv[2]) < 0
		|| ft_atoi(argv[3]) < 0 || ft_atoi(argv[4]) < 0)
		return (1);
	return (0);
}

int	input_init(t_data *data, int argc, char **argv)
{
	data->input = (t_input *)malloc(sizeof(t_input));
	if (!data->input)
		return (printf("Error in fork initialisation!\n"));
	if (check_arg(argc, argv) == 0)
	{
		data->ph_count = ft_atoi(argv[1]);
		data->input->num_of_philo = data->ph_count;
		data->input->time_to_die = ft_atoi(argv[2]);
		data->input->time_to_eat = ft_atoi(argv[3]);
		data->input->time_to_sleep = ft_atoi(argv[4]);
		if (argc == 6)
			data->input->must_to_eat = ft_atoi(argv[5]);
		else
			data->input->must_to_eat = -1;
		data->input->finish_eating = 0;
	}
	else
	{
		free(data->input);
		free(data);
		return (1);
	}
	if (fork_init(data) != 0 || philo_init(data) != 0)
		return (printf("Error in fork initialisation!\n"));
	return (0);
}
