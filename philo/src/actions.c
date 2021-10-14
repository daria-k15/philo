/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: heveline <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/30 20:46:29 by heveline          #+#    #+#             */
/*   Updated: 2021/09/14 14:47:13 by heveline         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

void	philo_sleep_think(t_philo *philo)
{
	if (philo->input->death_flag == 1)
		return ;
	pthread_mutex_lock(philo->print_lock);
	printf("%d ms %d is sleeping\n", get_time() - philo->data->start_time,
		philo->philo_id + 1);
	pthread_mutex_unlock(philo->print_lock);
	philo_sleep(philo->input->time_to_sleep, philo);
	if (philo->input->death_flag == 1)
		return ;
	pthread_mutex_lock(philo->print_lock);
	printf("%d ms %d is thinking\n", get_time() - philo->data->start_time,
		philo->philo_id + 1);
	pthread_mutex_unlock(philo->print_lock);
}

void	philo_eating_cont(t_philo *philo)
{
	philo->start_to_eat = get_time();
	philo_sleep(philo->input->time_to_eat, philo);
	pthread_mutex_unlock(philo->right_fork);
	pthread_mutex_unlock(philo->left_fork);
	if (philo->need_to_eat > 0)
		philo->need_to_eat--;
	if (philo->need_to_eat == 0)
		philo->input->finish_eating++;
}

void	philo_eating(t_philo *philo)
{
	pthread_mutex_lock(philo->left_fork);
	if (philo->input->death_flag == 1)
	{
		pthread_mutex_unlock(philo->left_fork);
		return ;
	}
	pthread_mutex_lock(philo->print_lock);
	printf("%d ms %d has taken fork\n", get_time() - philo->data->start_time,
		philo->philo_id + 1);
	pthread_mutex_unlock(philo->print_lock);
	pthread_mutex_lock(philo->right_fork);
	if (philo->input->death_flag == 1)
	{
		pthread_mutex_unlock(philo->right_fork);
		return ;
	}
	pthread_mutex_lock(philo->print_lock);
	printf("%d ms %d has taken fork\n", get_time() - philo->data->start_time,
		philo->philo_id + 1);
	printf("%d ms %d is eating\n", get_time() - philo->data->start_time,
		philo->philo_id + 1);
	pthread_mutex_unlock(philo->print_lock);
	philo_eating_cont(philo);
}
