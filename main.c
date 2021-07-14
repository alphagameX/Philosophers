/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arthur <arthur@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/02 01:18:11 by arthur            #+#    #+#             */
/*   Updated: 2021/07/09 13:36:30 by arthur           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "source/philo.h"

int	main(int argc, char **argv)
{
	t_conf	conf;
	t_stack	stack;

	conf = init_conf(argc, argv);
	stack.forks = init_forks(conf.number_of_philo);
	create_philo(&conf, &stack);
	if (conf.philo_dead == conf.number_of_philo)
		printf("Each philo have eat %d times\n",
			conf.number_of_times_each_philo_eat);
	destroy_stack();
	return (0);
}
