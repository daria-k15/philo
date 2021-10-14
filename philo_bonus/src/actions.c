/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: heveline <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/14 14:45:02 by heveline          #+#    #+#             */
/*   Updated: 2021/09/14 14:45:23 by heveline         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo_bonus.h"

void	eating_cont(t_philo *philo)
{
	philo->start_to_eat = get_time();
	philo_sleep(philo->input->time_to_eat, philo);
	sem_post(philo->input->forks);
	sem_post(philo->input->forks);
	if (philo->need_to_eat > 0)
		philo->need_to_eat--;
	if (philo->need_to_eat == 0)
		philo->input->finish_eating++;
}

void	philo_eating(t_philo *philo)
{
	sem_wait(philo->input->forks);
	sem_wait(philo->input->forks);
	if (philo->input->death_flag == 1)
	{
		sem_post(philo->input->forks);
		return ;
	}
	sem_wait(philo->input->print_lock);
	printf("%d ms %d has taken a fork\n",
		get_time() - philo->data->start_time, philo->philo_id + 1);
	sem_post(philo->input->print_lock);
	if (philo->input->death_flag == 1)
	{
		sem_post(philo->input->forks);
		return ;
	}
	sem_wait(philo->input->print_lock);
	printf("%d ms %d has taken a fork\n",
		get_time() - philo->data->start_time, philo->philo_id + 1);
	printf("%d ms %d is eating\n",
		get_time() - philo->data->start_time, philo->philo_id + 1);
	sem_post(philo->input->print_lock);
	eating_cont(philo);
}

void	sleep_think(t_philo *philo)
{
	if (philo->input->death_flag == 1)
		return ;
	sem_wait(philo->input->print_lock);
	printf("%d ms %d is sleeping\n",
		get_time() - philo->data->start_time, philo->philo_id + 1);
	sem_post(philo->input->print_lock);
	philo_sleep(philo->input->time_to_sleep, philo);
	sem_wait(philo->input->print_lock);
	printf("%d ms %d is thinking\n",
		get_time() - philo->data->start_time, philo->philo_id + 1);
	sem_post(philo->input->print_lock);
}
