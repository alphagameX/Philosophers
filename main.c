#include "source/philo.h"

void *god_philo(void *args)
{
	t_philo *philo;

	philo = (t_philo *)args;
	while (philo->is_alive && philo->conf->running)
	{
		if (utc_time_in_usec(now()) - philo->last_meal > philo->conf->time_to_die && philo->last_meal != 0)
		{
			philo->is_alive = 0;
			mutex_printer(philo, "died\n", elapsed_time(philo->conf->elapsed) - 1, philo->id);
			philo->conf->running = 0;
			break ;
		}
		usleep(10);
	}
	return (NULL);
}

void create_god_philo(t_philo *philo)
{
	int err;
	pthread_t god;

	(void)god_philo;
	err = pthread_create(&god, NULL, god_philo, (void *)philo);
	if (err == -1)
		philo->conf->running = 0;
}

void *philo_forum(void *args)
{
	t_philo *philo;
	pthread_mutex_t *forks;

	philo = (t_philo *)args;
	forks = (pthread_mutex_t *)philo->forks;
	create_god_philo(philo);
	while (philo->is_alive && philo->conf->running)
	{
		take_forks(philo, forks);
		eat(philo, forks);
		if (philo->conf->number_of_times_each_philo_eat != -1 && philo->have_eat >= philo->conf->number_of_times_each_philo_eat)
		{
			philo->is_alive = 0;
			philo->conf->philo_dead++;
		}
		drop_forks(philo, forks);
		if (philo->is_alive && philo->conf->running)
		{
			mutex_printer(philo, "is sleeping\n", elapsed_time(philo->conf->elapsed), philo->id);
			sleep_time(philo->conf->time_to_sleep);
			mutex_printer(philo, "is thinking\n", elapsed_time(philo->conf->elapsed), philo->id);
		}
	}
	return (NULL);
}

pthread_mutex_t	*init_printer(void)
{
	pthread_mutex_t	*printer;

	printer = new (sizeof(pthread_mutex_t), 1);
	if (!printer)
	{
		destroy_stack();
		exit(1);
	}
	pthread_mutex_init(printer, NULL);
	return (printer);
}

void	create_philo(t_conf *conf, t_stack *stack)
{
	int				i;
	int				err;
	pthread_mutex_t	*printer;

	err = 0;
	i = 0;
	printer = init_printer();
	stack->tid = new (sizeof(pthread_t), conf->number_of_philo);
	stack->philos = new (sizeof(t_philo *), conf->number_of_philo);
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
		usleep(10);
		i++;
	}
	while (err < i)
	{
		pthread_join(stack->tid[err], NULL);
		err++;
	}
}

int	main(int argc, char **argv)
{
	t_conf	conf;
	t_stack	stack;

	conf = init_conf(argc, argv);
	stack.forks = init_forks(conf.number_of_philo);
	create_philo(&conf, &stack);
	if (conf.philo_dead == conf.number_of_philo)
		printf("Each philo have eat %d times\n", conf.number_of_times_each_philo_eat);
	destroy_stack();
	return (0);
}