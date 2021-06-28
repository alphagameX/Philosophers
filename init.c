#include "source/philo.h"

t_conf init_conf(int argc, char **argv)
{
	t_conf new;
	int i;
	int res;

	if (argc < 5)
		exit_philo("Invalid args number");
	if (argc > 6)
		exit_philo("Too many args number");
	i = 1;
	while (i < argc)
	{
		if (ft_isnumber(argv[i]) == 1)
		{
			res = ft_atoi(argv[i]);
			if (res >= 0)
			{
				if (i == 1)
					new.number_of_philo = res;
				if (i == 2)
					new.time_to_die = res;
				if (i == 3)
					new.time_to_eat = res;
				if (i == 4)
					new.time_to_sleep = res;
				if (i == 5)
					new.number_of_times_each_philo_eat = res;
				else
					new.number_of_times_each_philo_eat = -1;
			}
			else
				exit_philo("One parameter is negative");
		}
		else
			exit_philo("One parameter is not a number");
		i++;
	}
	return (new);
}

pthread_mutex_t *init_forks(int fork_count)
{
	int i;
	pthread_mutex_t *forks;

	forks = malloc(sizeof(pthread_mutex_t) * fork_count);
	if (!forks)
		exit_philo("Error malloc");
	i = 0;
	while (i < fork_count)
	{
		pthread_mutex_init(&forks[i], NULL);
		i++;
	}
	return (forks);
}

t_philo *init_philo(int id, t_stack *stack, t_conf conf)
{
	t_philo *philo;

	philo = malloc(sizeof(t_philo) * 1);
	if(!philo)
		exit_philo("Error malloc");
	philo->id = id;
	philo->is_alive = 1;
	philo->have_eat = 0;
	philo->conf = conf;
	philo->forks = (void *)stack->forks;
	return (philo);
}