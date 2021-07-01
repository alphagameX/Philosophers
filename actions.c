#include "source/philo.h"

void mutex_printer(t_philo *philo, char const *str, long long int ms, int id)
{
	pthread_mutex_lock(philo->printer);
	if(philo->conf->running == 1)
		printf(str, ms, id);
	pthread_mutex_unlock(philo->printer);
}

void should_die(t_philo *philo, pthread_mutex_t *forks)
{
	(void)forks;
	if (elapsed_time_u(philo->conf->elapsed) - philo->last_meal > (long long int)philo->conf->time_to_die && philo->last_meal != 0)
	{
		mutex_printer(philo, "%6.0d %d died\n", elapsed_time_ms(philo->conf->elapsed), philo->id);
		philo->conf->running = 0;
	}
}

void take_forks(t_philo *philo, pthread_mutex_t *forks)
{
	pthread_mutex_lock(&forks[philo->id]);

	mutex_printer(philo, "%6.0d %d has taken a fork\n", elapsed_time_ms(philo->conf->elapsed), philo->id);
	if (philo->id < philo->conf->number_of_philo - 1)
		pthread_mutex_lock(&forks[philo->id + 1]);
	else
		pthread_mutex_lock(&forks[0]);
	mutex_printer(philo, "%6.0d %d has taken a fork\n", elapsed_time_ms(philo->conf->elapsed), philo->id);
}

void eat(t_philo *philo, pthread_mutex_t *forks)
{
	(void)forks;
	philo->have_eat++;
	philo->last_meal = elapsed_time_u(philo->conf->elapsed);
	mutex_printer(philo, "%6.0d %d is eating\n", elapsed_time_ms(philo->conf->elapsed), philo->id);
	usleep(philo->conf->time_to_eat);
}

void drop_forks(t_philo *philo, pthread_mutex_t *forks)
{
	if (philo->id < philo->conf->number_of_philo - 1)
		pthread_mutex_unlock(&forks[philo->id + 1]);
	else
		pthread_mutex_unlock(&forks[0]);
	pthread_mutex_unlock(&forks[philo->id]);
}