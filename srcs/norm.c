/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   norm.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arthur <arthur@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/02 14:33:20 by arthur            #+#    #+#             */
/*   Updated: 2021/07/02 14:42:47 by arthur           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../source/philo.h"

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
