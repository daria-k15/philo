/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: heveline <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/14 14:45:47 by heveline          #+#    #+#             */
/*   Updated: 2021/09/14 14:47:00 by heveline         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo_bonus.h"

void	*death_check(void *smth)
{
	t_philo	*philo;

	philo = (t_philo *)smth;
	while (philo->input->death_flag == 0
		&& philo->input->finish_eating < philo->data->ph_count)
	{
		if (philo->need_to_eat == 0)
			exit (1);
		if (get_time() - philo->start_to_eat > philo->input->time_to_die
			&& philo->need_to_eat != 0)
		{
			sem_wait(philo->input->flag);
			sem_wait(philo->input->print_lock);
			if (philo->input->death_flag == 0)
				printf("%d ms %d died\n", get_time() - philo->data->start_time,
					philo->philo_id + 1);
			sem_post(philo->input->print_lock);
			philo->input->death_flag = 1;
			exit (1);
		}
	}
	return (NULL);
}

void	*thread_create(void *smth)
{
	t_philo	*philo;

	philo = (t_philo *)smth;
	pthread_create(&(philo->data->thread[philo->philo_id]),
		NULL, death_check, smth);
	if (philo->philo_id % 2 == 0)
		usleep(100);
	while (philo->need_to_eat != 0 && philo->input->death_flag != 1)
	{
		philo_eating(philo);
		sleep_think(philo);
	}
	return (NULL);
}

int	process(t_data *data)
{
	int		i;
	pid_t	pid;

	i = 0;
	data->start_time = get_time();
	while (i < data->ph_count)
	{
		pid = fork();
		if (pid < 0)
			return (1);
		if (pid == 0)
			thread_create(&data->philo[i]);
		data->philo[i].pid = pid;
		i++;
	}
	return (0);
}

void	free_fun(t_data *data)
{
	free(data->input);
	free(data->philo);
	free(data->thread);
	free(data);
}

int	main(int argc, char **argv)
{
	t_data	*data;
	int		i;
	int		status;

	i = 0;
	if (argc != 5 && argc != 6)
		return (printf("Wrong number of arguments!\n"));
	data = (t_data *)malloc(sizeof(t_data));
	if (!data)
		return (printf("Error in memory allocation!\n"));
	if (input_init(data, argc, argv) != 0 || data->input->must_to_eat == 0)
		exit(1);
	data->input->death_flag = 0;
	if (process(data) == 1)
		exit(1);
	waitpid(-1, &status, WUNTRACED);
	i = 0;
	while (i < data->ph_count)
	{
		kill(data->philo[i].pid, SIGTERM);
		i++;
	}
	free_fun(data);
	return (0);
}
