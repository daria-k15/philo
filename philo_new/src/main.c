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
		all->philo[i].philo_index = i;
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
		all->input->eat_sum = -1;
	all->philo_count = all->input->num_of_philo;
	forks_init(all);
	philo_init(all);
	return (0);
}


void eat_fun(t_philo *philo)
{
	pthread_mutex_lock(philo->right_fork);
	if (philo->death_flag == 1)
	{
		pthread_mutex_unlock(philo->right_fork);
		return ;
	}
	pthread_mutex_lock(philo->print_lock);
	printf("%d %d has taken a fork\n", get_work_time(philo->start_time), philo->philo_index);
	pthread_mutex_unlock(philo->print_lock);
}

void *thread_create(t_philo *philo)
{
	// t_philo *philo;
	
	// philo = (t_philo *)thread;
	printf("death flag = %d\n", philo->death_flag);
	printf("death flag = %d\n", philo->need_to_eat);
	if (philo->philo_index % 2 == 0)
		usleep(200);
	while (philo->death_flag != 1 && philo->need_to_eat != 0)
	{
		printf("check\n");
		eat_fun(philo);
	}
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
	all->philo->start_time = get_time();
	// printf("start time = %ld\n", all->philo->start_time);
	all->philo->death_flag = 0;
	while (i < all->philo_count)
	{
		pthread_create(&(all->thread[i]), NULL, (void *)thread_create, (void *)&(all->philo[i]));
		i++;
	}
	// i = 0;
	// while (i < all->philo_count)
	// {
	// 	pthread_join((all->thread[i]), NULL);
	// 	i++;
	// }
}