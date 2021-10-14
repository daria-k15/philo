/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   inits.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: heveline <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/14 14:45:28 by heveline          #+#    #+#             */
/*   Updated: 2021/09/14 14:45:42 by heveline         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo_bonus.h"

int	init_forks(t_data *data)
{
	sem_unlink("/forks");
	data->input->forks = sem_open("/forks", O_CREAT, S_IRWXU, data->ph_count);
	if (data->input->forks == SEM_FAILED)
		return (1);
	sem_unlink("/print_lock");
	data->input->print_lock = sem_open("/print_lock", O_CREAT, S_IRWXU, 1);
	if (data->input->print_lock == SEM_FAILED)
		return (1);
	sem_unlink("/flag");
	data->input->flag = sem_open("/flag", O_CREAT, S_IRWXU, 1);
	if (data->input->flag == SEM_FAILED)
		return (1);
	return (0);
}

int	philo_init(t_data *data)
{
	int	i;

	i = 0;
	data->philo = (t_philo *)malloc(sizeof(t_philo) * data->ph_count);
	if (!data->philo)
		return (printf("Error in memory allocation!\n"));
	data->thread = (pthread_t *)malloc(sizeof(pthread_t));
	if (!data->thread)
		return (printf("Error in memory allocation!\n"));
	while (i < data->ph_count)
	{
		data->philo[i].philo_id = i;
		data->philo[i].start_to_eat = get_time();
		data->philo[i].need_to_eat = data->input->must_to_eat;
		data->philo[i].input = data->input;
		data->philo[i].data = data;
		i++;
	}
	return (0);
}

int	input_init(t_data *data, int argc, char **argv)
{
	data->input = (t_input *)malloc(sizeof(t_input));
	if (!data->input)
		return (printf("Error in memory allocation!\n"));
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
		return (1);
	if (init_forks(data) != 0)
		return (printf("Error in semaphore initialisation!\n"));
	if (philo_init(data) != 0)
		return (printf("Error in philo initialisation!\n"));
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
