#include "../philo.h"


int forks_init(t_all *all)
{
	int i;

	i = 0;
	all->forks = (pthread_mutex_t **)malloc(sizeof(pthread_mutex_t) * all->philo_count);
	if (!all->forks)
		return (printf("Error in memory allocation!\n"));
	while (i < all->philo_count)
	{
		all->forks[i] = malloc(sizeof(pthread_mutex_t));
		if (!all->forks[i])
			return (printf("Error in memory allocation!\n"));
		i++;
	}
	i = 0;
	while (i < all->philo_count)
	{
		pthread_mutex_init(all->forks[i], NULL);
		i++;
	}
	return (0);
}

int philo_init(t_all *all)
{
	int i;

	i = 0;
	all->philo = (t_philo *)malloc(sizeof(t_philo) * all->philo_count);
	if (!all->philo)
		return (printf("Error in memory allocation!\n"));
	all->thread = malloc(sizeof(pthread_t) * all->philo_count);
	if (!all->thread)
		return (printf("Error in memory allocation!\n"));
	while(i < all->philo_count)
	{
		all->philo[i].philo_num = i;
		all->philo[i].start_to_eat = get_time();
		all->philo[i].need_to_eat = all->input->eat_sum;
		all->philo[i].death_flag = 0;
		all->philo[i].end_to_eat = 0;
		all->philo[i].max_eat = all->input->eat_sum;
		all->philo[i].right_fork = all->forks[i];
		if (i == 0)
			all->philo[i].left_fork = all->forks[all->philo_count - 1];
		else
			all->philo[i].left_fork = all->forks[i - 1];
		all->philo[i].print_lock = all->forks[all->philo_count];
		i++;
	}
	return (0);	
}

int input_init(t_all *all, int argc, char **argv)
{
	all->input->num_of_philo = ft_atoi(argv[1]);
	all->input->time_to_die = ft_atoi(argv[2]);
	all->input->time_to_eat = ft_atoi(argv[3]);
	all->input->time_to_sleep = ft_atoi(argv[4]);
	if (argc == 6)
		all->input->eat_sum = ft_atoi(argv[5]);
	else
		all->input->eat_sum = 0;
	all->philo_count = all->input->num_of_philo;
	all->start_time = 0;
	forks_init(all);
	philo_init(all);
	return (0);
}

void *thread_create(void *thread)
{
	// t_philo *philo;
	static int i;
	thread = 0;
	// i = 0;
	// while (i < philo->philo_num)
	printf("thread number = %d\n", i++);
	return (0);	
}

int	main(int argc, char **argv)
{
	t_all *all;
	int i;

	i = 0;
	if (argc != 5 && argc != 6)
		return (printf("Wrong number of arguments!\n"));
	all = (t_all *)malloc(sizeof(t_all));
	if (!all)
		return (printf("Error in memory allocation!\n"));
	all->input = (t_input *)malloc(sizeof(t_input));
	if (!all->input)
		return (printf("Error in memory allocation!\n"));
	input_init(all, argc, argv);
	// printf("philo num = %d\n", all->philo_count);
	all->start_time = get_time();
	all->philo->death_flag = 0;
	while (i < all->philo_count)
	{
		pthread_create(&(all->thread[i]), NULL, thread_create, (void *)&(all->philo[i]));
		i++;
	}
	i = 0;
	while (i < all->philo_count)
	{
		pthread_join((all->thread[i]), NULL);
		i++;
	}
}