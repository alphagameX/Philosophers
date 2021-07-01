/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_string.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arthur <arthur@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/02 01:18:49 by arthur            #+#    #+#             */
/*   Updated: 2021/07/02 01:18:50 by arthur           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../source/philo.h"

void ft_putchar(char c)
{
	write(1, &c, 1);
}

void ft_putstr(const char *str)
{
	int i;

	i = 0;
	while (str[i])
	{
		write(1, &str[i], 1);
		i++;
	}
}

void ft_putnbr(int nbr)
{
	long long int nb = (long long int) nbr; 

	if(nb < 0)
	{
		ft_putchar('-');
		nb *= -1;
	}
	if(nb > 9)
	{
		ft_putnbr(nb / 10);
		ft_putchar((nb % 10) + '0');
	} else
		ft_putchar(nb + '0');
}