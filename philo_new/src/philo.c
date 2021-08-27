#include "../philo.h"

t_philo *philo_init(t_all *all)
{
	t_philo *philo;
	int i;

	i = 0;
	philo = (t_philo *)malloc(sizeof(t_philo) * all->num_of_philo);
	if (!(philo))
		return (NULL);
	philo->thread = (pthread_t *)malloc(sizeof(pthread_t ) * all->num_of_philo);
	if (!philo->thread)
		return (NULL);
	i = 0;
	while (i < all->num_of_philo)
	{
		philo[i].philo_index = i;
		philo[i].start_to_eat = 0;
		philo[i].need_to_eat = all->eat_sum;
		philo[i].death_flag = 0;
		philo[i].end_to_eat = 0;
		philo[i].max_eat = 0;
		philo[i].right_fork = &all->forks[i];
		philo[i].left_fork = &all->forks[all->num_of_philo - i - 1];
		// philo[i].all = all;
		philo[i].philo_count = all->num_of_philo;
		i++;
	}
	return (philo);
}

int mutex_init(t_all *all)
{
	all->print_lock = (pthread_mutex_t *)malloc(sizeof(pthread_mutex_t));
	if (!(all->print_lock))
		return (0);
	all->die_lock = (pthread_mutex_t *)malloc(sizeof(pthread_mutex_t));
	if (!(all->die_lock))
		return (0);
	pthread_mutex_init(all->print_lock, NULL);
	pthread_mutex_init(all->die_lock, NULL);
	all->forks = (t_forks *)malloc(sizeof(t_forks) * all->num_of_philo);
	if (!(all->forks))
		return (0);
	return (1);
}

t_all *input_init(int argc, char **argv)
{
	t_all *all;
	int i;

	all = (t_all *)malloc(sizeof(t_all));
	if (!(all))
		return (NULL);
	all->num_of_philo = ft_atoi(argv[1]);
	all->time_to_die = ft_atoi(argv[2]);
	all->time_to_eat = ft_atoi(argv[3]);
	all->time_to_sleep = ft_atoi(argv[4]);
	if (argc == 6)
		all->eat_sum = ft_atoi(argv[5]);
	else
		all->eat_sum = -1;
	if (!(mutex_init(all)))
		return (NULL);
	i = 0;
	while (i++ < all->num_of_philo)
	{
		all->forks[i].fork_mutex = (pthread_mutex_t *)malloc(sizeof(pthread_mutex_t));
		if(!(all->forks[i].fork_mutex))
			return (NULL);
		pthread_mutex_init(all->forks[i].fork_mutex, NULL);
	}
	return (all);
}

void	create_thread(t_philo *philo)
{
	// int i = 0;
	printf("philo num is %d\n", philo->philo_count);

	// while (i++ < philo->all->num_of_philo)
	// {
	// 	printf("this is philo %d\n", philo->philo_index);
	// }
	// return (NULL);
}

int main(int argc, char **argv)
{
	t_all *all;
	int i;

	if (argc != 5 && argc != 6)
		return (printf("Wrong number of arguments!\n"));
	all = input_init(argc, argv);
	if (!all)
		return (printf("Error in memory allocation!\n"));
	all->philo = philo_init(all);
	if (!all->philo)
		return (printf("Error in memory allocation!\n"));
	all->start_time = get_time();
	// printf("time = %d\n", all->start_time);
	// printf("%d\n", all->num_of_philo);
	i = 0;
	while (i++ < all->num_of_philo)
	{
		pthread_create(all->philo[i].thread, NULL, (void *)create_thread, &all->philo[i]);
	}
	// for (int i = 0; i < all->num_of_philo; i++)
	// {
	// 	pthread_join(all->philo[i].thread, NULL);
	// }
}