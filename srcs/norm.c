/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   norm.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arthur <arthur@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/02 14:33:20 by arthur            #+#    #+#             */
/*   Updated: 2021/07/10 17:32:23 by arthur           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../source/philo.h"

pthread_mutex_t	*get_allocer(void)
{
	static pthread_mutex_t	*allocer = NULL;

	if (allocer == NULL)
	{
		allocer = new(sizeof(pthread_mutex_t), 1);
		pthread_mutex_init(allocer, NULL);
	}
	return (allocer);
}

void	*mutex_new(size_t size, size_t count)
{
	void	*mem;

	pthread_mutex_lock(get_allocer());
	mem = new(size, count);
	pthread_mutex_unlock(get_allocer());
	return (mem);
}

pthread_mutex_t	*init_printer(void)
{
	pthread_mutex_t	*printer;

	printer = mutex_new(sizeof(pthread_mutex_t), 1);
	if (!printer)
	{
		destroy_stack();
		exit(1);
	}
	pthread_mutex_init(printer, NULL);
	return (printer);
}

void	mutex_printer(t_philo *philo, char const *str, long long int ms, int id)
{
	pthread_mutex_lock(philo->printer);
	if (philo->conf->running == 1 )
	{
		ft_putnbr((int)ms);
		ft_putchar(' ');
		ft_putnbr(id + 1);
		ft_putchar(' ');
		ft_putstr(str);
	}
	pthread_mutex_unlock(philo->printer);
}

void	single_philo_fix(t_philo *philo)
{
	philo->conf->first_philo_ready = 1;
	philo->single_ready = 1;
	pthread_mutex_lock(philo->eater);
	philo->last_meal = utc_time_in_usec(now());
	pthread_mutex_unlock(philo->eater);
}
