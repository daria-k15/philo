/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: heveline <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/14 14:45:57 by heveline          #+#    #+#             */
/*   Updated: 2021/09/14 14:46:03 by heveline         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo_bonus.h"

int	get_time(void)
{
	struct timeval	curr_time;

	gettimeofday(&curr_time, NULL);
	return ((curr_time.tv_sec * 1000) + (curr_time.tv_usec / 1000));
}

void	philo_sleep(int time_to, t_philo *philo)
{
	struct timeval	tv;
	int				cur_time;
	int				res;

	gettimeofday(&tv, NULL);
	cur_time = tv.tv_sec * 1000 + tv.tv_usec / 1000;
	res = cur_time + time_to;
	while (cur_time < res && philo->input->death_flag == 0)
	{
		usleep(100);
		gettimeofday(&tv, NULL);
		cur_time = tv.tv_sec * 1000 + tv.tv_usec / 1000;
		if (philo->input->death_flag == 1)
			break ;
	}
}

int	ft_atoi(const char *str)
{
	size_t	i;
	int		sign;
	long	nb;

	i = 0;
	sign = 1;
	nb = 0;
	while (str[i] == 32 || (str[i] > 8 && str[i] < 14))
		i++;
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			sign = -1;
		i++;
	}
	while (str[i] >= '0' && str[i] <= '9')
	{
		nb = (nb * 10) + (str[i] - '0');
		if (nb < -2147483647 && sign == -1)
			return (0);
		if (nb > 2147483647 && sign == 1)
			return (-1);
		i++;
	}
	return (nb * sign);
}

int	not_num(const char *str)
{
	size_t	i;

	i = 0;
	while (str[i])
	{
		if ((str[i] >= 'A' && str[i] <= 'Z')
			|| (str[i] >= 'a' && str[i] <= 'z'))
			return (1);
		i++;
	}
	return (0);
}
