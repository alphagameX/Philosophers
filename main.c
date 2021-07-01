#include "source/philo.h"

void *philo_forum(void *args)
{
	t_philo *philo;
	pthread_mutex_t *forks;

	philo = (t_philo *)args;
	forks = (pthread_mutex_t *)philo->forks;
	while (philo->is_alive && philo->conf->running)
	{
		take_forks(philo, forks);
		should_die(philo, forks);
		eat(philo, forks);
		if (philo->conf->number_of_times_each_philo_eat != -1 && philo->have_eat >= philo->conf->number_of_times_each_philo_eat)
		{
			printf("%6.0d %d died\n", elapsed_time_ms(philo->conf->elapsed), philo->id);
			philo->is_alive = 0;
			philo->conf->philo_dead++;
		}
		drop_forks(philo, forks);
		mutex_printer(philo, "%6.0d %d is sleeping\n", elapsed_time_ms(philo->conf->elapsed), philo->id);
		usleep(philo->conf->time_to_sleep);
		mutex_printer(philo, "%6.0d %d is thinking\n", elapsed_time_ms(philo->conf->elapsed), philo->id);
	}
	return (NULL);
}

pthread_mutex_t *init_printer()
{
	pthread_mutex_t *printer;

	printer = new (sizeof(pthread_mutex_t), 1);
	if (!printer)
		exit(1);
	pthread_mutex_init(printer, NULL);
	return (printer);
}


void create_philo(t_conf *conf, t_stack *stack)
{
	int i;
	int err;
	pthread_mutex_t *printer;

	err = 0;
	i = 0;
	printer = init_printer();
	stack->tid = new(sizeof(pthread_t), conf->number_of_philo);
	stack->philos = new(sizeof(t_philo *), conf->number_of_philo);
	if (!stack->tid || !stack->philos)
	{
		destroy_stack();
		exit(1);
	}
	while (i < conf->number_of_philo)
	{
		stack->philos[i] = init_philo(i, stack, conf, printer);
		err = pthread_create(&stack->tid[i], NULL, philo_forum, (void *)stack->philos[i]);
		if (err == -1)
		{
			destroy_stack();
			exit(1);
		}
		usleep(500);
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
	create_philo(&conf, &stack);
	if (conf.philo_dead == conf.number_of_philo)
		printf("All philo eat\n");
	destroy_stack();
	return (0);
}