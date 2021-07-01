/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arthur <arthur@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/02 01:18:20 by arthur            #+#    #+#             */
/*   Updated: 2021/07/02 01:18:21 by arthur           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
#define PHILO_H
#include <pthread.h>
#include <unistd.h>
#include <sys/time.h>
#include "../utils/mem/mem.h"

typedef struct s_conf
{
	int number_of_philo;
	int running;
	int time_to_die;
	int time_to_eat;
	int time_to_sleep;
	int number_of_times_each_philo_eat;
	struct timeval elapsed;
	int philo_dead;
} t_conf;

typedef struct s_philo
{
	int id;
	int is_alive;
	int have_eat;
	long long int last_meal;

	t_conf *conf;
	pthread_mutex_t *forks;
	pthread_mutex_t *printer;
} t_philo;

typedef struct s_stack
{
	pthread_mutex_t *forks;
	pthread_t *tid;
	t_philo **philos;

} t_stack;

t_conf init_conf(int argc, char **argv);
pthread_mutex_t *init_forks(int fork_count);
t_philo *init_philo(int id, t_stack *stack, t_conf *conf, pthread_mutex_t *printer);
void exit_philo(char *msg);
int elapsed_time_ms(struct timeval start);
long long int utc_time_in_usec(struct timeval time);
long long int elapsed_time(struct timeval start);
struct timeval now(void);
void sleep_time(int time);

void take_forks(t_philo *philo, pthread_mutex_t *forks);
void eat(t_philo *philo, pthread_mutex_t *forks);
void drop_forks(t_philo *philo, pthread_mutex_t *forks);
void mutex_printer(t_philo *philo, char const *str, long long int ms, int id);
t_philo **all_philos(t_philo **philos);


void ft_putnbr(int nbr);
void ft_putstr(const char *str);
void ft_putchar(char c);

/*
** UTILS 
**
*/

int ft_isdigit(int c);
int ft_atoi(const char *str);
int ft_isnumber(char *str);

#endif