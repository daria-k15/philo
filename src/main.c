#include "../philo.h"

int input_init(t_all *all, int argc, char **argv)
{
	all->input->philo_count = ft_atoi(argv[1]);
	all->philo_count = all->input->philo_count;
	all->input->time_to_die = ft_atoi(argv[2]);
	all->input->time_to_eat = ft_atoi(argv[3]);
	all->input->time_to_sleep = ft_atoi(argv[4]);
	all->input->death_flag = 0;
	if (argc == 6)
		all->input->eating_sum = ft_atoi(argv[5]);
	else
		all->input->eating_sum = 0;
	all->philo = (t_philo *)malloc(sizeof(t_philo) * all->philo_count);
	if (!all->philo)
		return (printf("Error in memory allocation!\n"));
	init_forks(all);
	philo_init(all);
	return (1);
}

int	philo_init(t_all *all)
{
	int i;
	i = 0;
	
	all->thread = malloc(sizeof(pthread_t) * all->philo_count);
	if (!all->thread)
		return (printf("Error in memory allocation!\n"));
	while (i < all->philo_count)
	{
		all->philo[i].philo_num = i;
		all->philo[i].max_eat = all->input->eating_sum;
		all->philo[i].need_to_eat = all->input->eating_sum;
		all->philo->eat_start_time = get_time();
		all->philo->right_fork = all->forks[i];
		if (i == 0)
			all->philo->left_fork = all->forks[all->philo_count - 1];
		else
			all->philo->right_fork = all->forks[i - 1];
		all->philo->print_lock = all->forks[all->philo_count];
		all->philo->input = all->input;
		i++;
	}
	return (0);
}

int init_forks(t_all *all)
{
	int i;

	i = 0;
	all->forks = (pthread_mutex_t **)malloc(sizeof(pthread_mutex_t*) * all->philo_count + 1);
	if (!all->forks)
		return (printf("Error in memory allocation!\n"));
	while (i++ <= all->philo_count)
	{
		all->forks[i] = malloc(sizeof(pthread_mutex_t));
		if (!all->forks[i])
			return (printf("Error in memory allocation!\n"));
	}
	i = 0;
	while (i++ <= all->philo_count)
		pthread_mutex_init(all->forks[i], NULL);
	return (0);
}

void *thread_create(void *smth)
{
	t_philo *philo;

	philo = (t_philo *)smth;
	printf("philo count = %d\n", philo->input->philo_count);
	return (NULL);
}

int main(int argc, char **argv)
{
	t_all *all;
	int i;

	if (argc != 5 && argc != 6)
		return (printf("Wrong number of arguments!\n"));
	all = (t_all *)malloc(sizeof(t_all));
	if (!all)
		return (printf("Error in memory allocation!\n"));
	all->input = (t_input *)malloc(sizeof(t_input));
	if (!all->input)
		return (printf("Error in memory allocation\n"));
	input_init(all, argc, argv);
	i = 0;
	all->start_time = get_time();
	// printf("%d\n", all->input->death_flag);
	all->input->death_flag = 0;
	while (i++ < all->philo_count)
		pthread_create(&(all->thread[i]), NULL, thread_create, (void *)&(all->philo[i]));
	return (0);
}