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
		pthread_mutex_lock(&forks[philo->id]);
		if(philo->id < philo->conf.number_of_philo - 1)
			pthread_mutex_lock(&forks[philo->id + 1]);
		else
			pthread_mutex_lock(&forks[0]);

		printf("Philo eat | id: %d\n", philo->id);
		philo->have_eat ++;
		usleep(philo->conf.time_to_eat);

		if (philo->conf.number_of_times_each_philo_eat != -1 && philo->have_eat >= philo->conf.number_of_times_each_philo_eat)
		{
			printf("Philo died | id: %d\n", philo->id);
			philo->is_alive = 0;
		}
		if (philo->id < philo->conf.number_of_philo - 1)
			pthread_mutex_unlock(&forks[philo->id + 1]);
		else
			pthread_mutex_unlock(&forks[0]);
		pthread_mutex_unlock(&forks[philo->id]);
		printf("Philo sleeping | id: %d\n", philo->id);
		usleep(philo->conf.time_to_sleep);
		printf("Philo thinking | id: %d\n", philo->id);
	}
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
		stack->philos[i] = init_philo(i, stack, conf);
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