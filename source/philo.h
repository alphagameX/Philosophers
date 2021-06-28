#ifndef PHILO_H
# define PHILO_H
# include <stdio.h>
# include <stdlib.h>
# include <pthread.h>
# include <unistd.h>

typedef struct s_conf 
{
	int number_of_philo;
	int time_to_die;
	int time_to_eat;
	int time_to_sleep;
	int	number_of_times_each_philo_eat;
}				t_conf;

typedef struct s_philo
{
	int id;
	int is_alive;
	pthread_mutex_t *forks;
} t_philo;

typedef struct s_stack
{
	pthread_mutex_t *forks;
	pthread_t *tid;
	t_philo **philos;
} t_stack;



t_conf			init_conf(int argc, char **argv);
pthread_mutex_t	*init_forks(int fork_count);
t_philo			*init_philo(int id, t_stack *stack);
void exit_philo(char *msg);

/*
** UTILS 
**
*/

int				ft_isdigit(int c);
int				ft_atoi(const char *str);
int				ft_isnumber(char *str);

#endif