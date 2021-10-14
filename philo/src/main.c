/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: heveline <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/30 20:57:51 by heveline          #+#    #+#             */
/*   Updated: 2021/08/31 18:48:09 by heveline         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

void	*thread_create(void *smth)
{
	t_philo	*philo;

	philo = (t_philo *)smth;
	if (philo->philo_id % 2 == 0)
		usleep(100);
	while (philo->input->death_flag != 1 && philo->need_to_eat != 0)
	{
		philo_eating(philo);
		philo_sleep_think(philo);
	}
	return (NULL);
}

void	death_check(t_data *data)
{
	static int	i;

	while (data->input->death_flag == 0
		&& data->input->finish_eating < data->ph_count)
	{
		if (get_time() - data->philo[i].start_to_eat > data->input->time_to_die
			&& data->philo[i].need_to_eat != 0)
		{
			pthread_mutex_lock(data->philo[i].print_lock);
			if (data->input->death_flag == 0)
				printf("%d ms %d died\n", get_time() - data->start_time,
					data->philo[i].philo_id + 1);
			pthread_mutex_unlock(data->philo[i].print_lock);
			data->input->death_flag = 1;
			break ;
		}
		i = (i + 1) % data->ph_count;
	}
}

void	free_fun(t_data *data)
{
	int	i;

	i = 0;
	while (i <= data->ph_count)
	{
		free(data->forks[i]);
		i++;
	}
	free(data->forks);
	free(data->input);
	free(data->philo);
	free(data->thread);
	free(data);
}

int	main(int argc, char **argv)
{
	t_data	*data;
	int		i;

	i = 0;
	if (argc != 5 && argc != 6)
		return (printf("Wrong number of arguments!\n"));
	data = (t_data *)malloc(sizeof(t_data));
	if (!data)
		return (printf("Error in memory allocation!\n"));
	if (input_init(data, argc, argv) != 0)
		return (0);
	if (data->input->must_to_eat == 0)
	{
		free_fun(data);
		return (0);
	}
	data->start_time = get_time();
	data->input->death_flag = 0;
	while (i < data->ph_count)
	{
		pthread_create(&data->thread[i], NULL, thread_create, &data->philo[i]);
		i++;
	}
	death_check(data);
	free_fun(data);
}
