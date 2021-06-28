#include "source/philo.h"

void exit_philo(char *msg)
{
	printf("Error\n");
	printf("%s\n", msg);
	exit(1);
}

void free_philo(t_stack *stack, t_conf conf)
{
	int	i;

	i = 0;
	while (i < conf.number_of_philo)
	{
		pthread_mutex_destroy(&stack->forks[i]);
		i++;
	}
	free(stack->forks);
	free(stack->tid);
}

void print_conf(t_conf conf)
{
	printf("%d\n", conf.number_of_philo);
	printf("%d\n", conf.time_to_die);
	printf("%d\n", conf.time_to_eat);
	printf("%d\n", conf.time_to_sleep);
	printf("%d\n", conf.number_of_times_each_philo_eat);
}

void *philo_forum(void *args)
{
	t_philo *philo;
	pthread_mutex_t *forks;

	philo = (t_philo *)args;
	forks = (pthread_mutex_t *)philo->forks;
	while (philo->is_alive) 
	{
		pthread_mutex_lock(&forks[0]);
		philo->is_alive = 0;
		pthread_mutex_unlock(&forks[0]);
	}
	// pthread_mutex_lock()

	printf("Philo id %d!\n", philo->id);

	return (NULL);
}

void create_philo(t_conf conf, t_stack *stack)
{
	int i;
	int err;

	err = 0;
	i = 0;
	stack->tid = malloc(sizeof(pthread_t) * conf.number_of_philo);
	stack->philos = malloc(sizeof(t_philo *) * conf.number_of_philo);
	if (!stack->tid)
		exit_philo("Error malloc");
	while (i < conf.number_of_philo)
	{
		stack->philos[i] = init_philo(i, stack);
		err = pthread_create(&stack->tid[i], NULL, philo_forum, (void *)stack->philos[i]);
		if(err == -1)
			exit_philo("Error pthread create");
		i++;
	}
	while (err < i)
	{
		pthread_join(stack->tid[err], NULL);
		err++;
	}
}

int main(int argc, char **argv)
{
	t_conf conf;
	t_stack stack;

	conf = init_conf(argc, argv);
	stack.forks = init_forks(conf.number_of_philo);

	create_philo(conf, &stack);
	print_conf(conf);

	free_philo(&stack, conf);
	return (0);
}