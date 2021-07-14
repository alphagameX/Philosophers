/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arthur <arthur@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/02 14:24:51 by arthur            #+#    #+#             */
/*   Updated: 2021/07/14 17:35:40 by arthur           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../source/philo.h"

void	*god_philo(void *args)
{
	t_philo			*philo;
	long long int	last_meal;
	int				alive;

	philo = (t_philo *)args;
	alive = 1;
	while (alive && philo->conf->running)
	{
		pthread_mutex_lock(philo->eater);
		last_meal = philo->last_meal;
		pthread_mutex_unlock(philo->eater);
		pthread_mutex_lock(philo->aliver);
		alive = philo->is_alive;
		pthread_mutex_unlock(philo->aliver);
		if (utc_time_in_usec(now()) - last_meal
			> philo->conf->time_to_die && last_meal != 0)
		{
			kill_philo(philo, &alive);
			break ;
		}
		usleep(100);
	}
	return (NULL);
}

pthread_t	*create_god_philo(t_philo *philo)
{
	int			err;
	pthread_t	*god;

	god = mutex_new(sizeof(pthread_t), 1);
	err = pthread_create(god, NULL, god_philo, (void *)philo);
	if (err == -1)
		philo->conf->running = 0;
	return (god);
}

void	*philo_forum(void *args)
{
	t_philo			*philo;
	pthread_mutex_t	*forks;
	pthread_t		*god;

	philo = (t_philo *)args;
	forks = (pthread_mutex_t *)philo->forks;
	god = create_god_philo(philo);
	while (philo->is_alive && philo->conf->running)
	{
		take_forks(philo, forks);
		if (philo->single_ready == -1)
		{
			eat(philo, forks);
			is_sated(philo, forks);
			drop_forks(philo, forks);
			sleep_and_think(philo, forks);
		}
	}
	pthread_join(*god, NULL);
	return (NULL);
}

void	create_thread_philo(t_stack *stack, t_conf *conf,
	pthread_mutex_t *printer, int i)
{
	int	err;
	int	ready;
	int	philo_ready;

	stack->philos[i] = init_philo(i, stack, conf, printer);
	err = pthread_create(&stack->tid[i], NULL,
			philo_forum, (void *)stack->philos[i]);
	if (err == -1)
	{
		destroy_stack();
		exit(1);
	}
	ready = 0;
	while (!ready)
	{
		pthread_mutex_lock(conf->runner);
		philo_ready = conf->first_philo_ready;
		pthread_mutex_unlock(conf->runner);
		if (philo_ready == 1)
			ready = 1;
		usleep(100);
	}
	usleep(100);
}

void	create_philo(t_conf *conf, t_stack *stack)
{
	int				i;
	int				err;
	pthread_mutex_t	*printer;

	err = 0;
	i = 0;
	printer = init_printer();
	stack->tid = mutex_new(sizeof(pthread_t), conf->number_of_philo);
	stack->philos = mutex_new(sizeof(t_philo *), conf->number_of_philo);
	if (!stack->tid || !stack->philos)
	{
		destroy_stack();
		exit(1);
	}
	gettimeofday(&conf->elapsed, NULL);
	while (i < conf->number_of_philo)
	{
		create_thread_philo(stack, conf, printer, i);
		i++;
	}
	while (err < i)
	{
		pthread_join(stack->tid[err], NULL);
		err++;
	}
}
