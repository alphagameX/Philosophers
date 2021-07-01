#include "source/philo.h"

void mutex_printer(t_philo *philo, char const *str, long long int ms, int id)
{
	(void)str;
	(void)id;
	(void)ms;
	(void)id;
	(void)philo;
	pthread_mutex_lock(philo->printer);
	if (philo->conf->running == 1 )
	{
		ft_putnbr((int)ms);
		ft_putchar(' ');
		ft_putnbr(id);
		ft_putchar(' ');
		ft_putstr(str);
	}
	// printf(str, ms, id);
	pthread_mutex_unlock(philo->printer);
}

void take_forks(t_philo *philo, pthread_mutex_t *forks)
{
	pthread_mutex_lock(&forks[philo->id]);

	mutex_printer(philo, "has taken a fork\n", elapsed_time(philo->conf->elapsed), philo->id);
	if (philo->id < philo->conf->number_of_philo - 1)
		pthread_mutex_lock(&forks[philo->id + 1]);
	else
		pthread_mutex_lock(&forks[0]);
	mutex_printer(philo, "has taken a fork\n", elapsed_time(philo->conf->elapsed), philo->id);
}

void eat(t_philo *philo, pthread_mutex_t *forks)
{
	(void)forks;
	philo->have_eat++;
	philo->last_meal = utc_time_in_usec(now());
	mutex_printer(philo, "is eating\n", elapsed_time(philo->conf->elapsed), philo->id);
	sleep_time(philo->conf->time_to_eat);
}

void drop_forks(t_philo *philo, pthread_mutex_t *forks)
{
	if (philo->id < philo->conf->number_of_philo - 1)
		pthread_mutex_unlock(&forks[philo->id + 1]);
	else
		pthread_mutex_unlock(&forks[0]);
	pthread_mutex_unlock(&forks[philo->id]);
}