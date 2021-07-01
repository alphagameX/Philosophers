/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arthur <arthur@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/02 01:18:28 by arthur            #+#    #+#             */
/*   Updated: 2021/07/02 01:20:27 by arthur           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../source/philo.h"

void fail_parse(char *msg)
{
	printf("Error\n");
	printf("%s\n", msg);
	destroy_stack();
	exit(1);
}

t_conf init_conf(int argc, char **argv)
{
	t_conf new;
	int i;
	int res;

	if (argc < 5)
		fail_parse("Invalid args number");
	if (argc > 6)
		fail_parse("Too many args number");
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
				fail_parse("One parameter is negative");
		}
		else
			fail_parse("One parameter is not a number");
		i++;
	}
	gettimeofday(&new.elapsed, NULL);
	new.philo_dead = 0;
	new.running = 1;
	return (new);
}

pthread_mutex_t *init_forks(int fork_count)
{
	int i;
	pthread_mutex_t *forks;

	forks = new(sizeof(pthread_mutex_t), fork_count);
	if (!forks)
	{
		destroy_stack();
		exit(1);
	}
	i = 0;
	while (i < fork_count)
	{
		pthread_mutex_init(&forks[i], NULL);
		i++;
	}
	return (forks);
}

t_philo *init_philo(int id, t_stack *stack, t_conf *conf, pthread_mutex_t *printer)
{
	t_philo *philo;

	philo = new (sizeof(t_philo), 1);
	if(!philo)
	{
		destroy_stack();
		exit(1);
	}
	philo->id = id;
	philo->is_alive = 1;
	philo->have_eat = 0;
	philo->conf = conf;
	philo->last_meal = 0;
	philo->printer = printer;
	philo->forks = (void *)stack->forks;
	return (philo);
}