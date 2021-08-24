#include "../philo.h"

int input_init(t_input *input, int argc, char **argv)
{
	input->philo_count = ft_atoi(argv[1]);
	input->time_to_die = ft_atoi(argv[2]);
	input->time_to_eat = ft_atoi(argv[3]);
	input->time_to_sleep = ft_atoi(argv[4]);
	if (argc == 6)
		input->eating_sum = ft_atoi(argv[5]);
	else
		input->eating_sum = 0;
	return (1);
}

int main(int argc, char **argv)
{
	t_all *all;
	if (argc != 5 && argc != 6)
		return (printf("Wrong number of arguments!\n"));
	all = (t_all *)malloc(sizeof(t_all));
	if (!all)
		return (printf("Error in memory allocation!\n"));
	all->input = (t_input *)malloc(sizeof(t_input));
	if (!all->input)
		return (printf("Error in memory allocation\n"));
	input_init(all->input, argc, argv);

}