/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arthur <arthur@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/02 01:18:24 by arthur            #+#    #+#             */
/*   Updated: 2021/07/14 17:32:30 by arthur           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../source/philo.h"

void	take_forks(t_philo *philo, pthread_mutex_t *forks)
{
	if (philo->single_ready == 0 || philo->single_ready == -1)
	{
		pthread_mutex_lock(&forks[philo->id]);
		if (philo->conf->number_of_philo == 1)
			single_philo_fix(philo);
		mutex_printer(philo, "has taken a fork\n",
			elapsed_time(philo->conf->elapsed), philo->id);
	}
	if (philo->conf->number_of_philo > 1)
	{
		if (philo->id < philo->conf->number_of_philo - 1)
			pthread_mutex_lock(&forks[philo->id + 1]);
		else
			pthread_mutex_lock(&forks[0]);
		if (philo->conf->first_philo_ready == 0)
		{
			pthread_mutex_lock(philo->conf->runner);
			philo->conf->first_philo_ready = 1;
			pthread_mutex_unlock(philo->conf->runner);
		}
		mutex_printer(philo, "has taken a fork\n",
			elapsed_time(philo->conf->elapsed), philo->id);
	}
}

void	eat(t_philo *philo, pthread_mutex_t *forks)
{
	(void)forks;
	philo->have_eat++;
	pthread_mutex_lock(philo->eater);
	philo->last_meal = utc_time_in_usec(now());
	pthread_mutex_unlock(philo->eater);
	mutex_printer(philo, "is eating\n",
		elapsed_time(philo->conf->elapsed), philo->id);
	sleep_time(philo->conf->time_to_eat);
}

void	is_sated(t_philo *philo, pthread_mutex_t *forks)
{
	(void)forks;
	if (philo->conf->number_of_times_each_philo_eat != -1
		&& philo->have_eat >= philo->conf->number_of_times_each_philo_eat)
	{
		pthread_mutex_lock(philo->aliver);
		philo->is_alive = 0;
		pthread_mutex_unlock(philo->aliver);
		pthread_mutex_lock(philo->conf->deader);
		philo->conf->philo_dead++;
		pthread_mutex_unlock(philo->conf->deader);
	}
}

void	drop_forks(t_philo *philo, pthread_mutex_t *forks)
{
	if (philo->id < philo->conf->number_of_philo - 1)
		pthread_mutex_unlock(&forks[philo->id + 1]);
	else
		pthread_mutex_unlock(&forks[0]);
	pthread_mutex_unlock(&forks[philo->id]);
}

void	sleep_and_think(t_philo *philo, pthread_mutex_t *forks)
{
	(void)forks;
	if (philo->is_alive && philo->conf->running)
	{
		mutex_printer(philo, "is sleeping\n",
			elapsed_time(philo->conf->elapsed), philo->id);
		sleep_time(philo->conf->time_to_sleep);
		mutex_printer(philo, "is thinking\n",
			elapsed_time(philo->conf->elapsed), philo->id);
	}
}
