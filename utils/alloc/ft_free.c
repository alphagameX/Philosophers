/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arthur <arthur@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/09 19:42:43 by arthur            #+#    #+#             */
/*   Updated: 2021/07/10 17:29:52 by arthur           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mem.h"

int	ft_free_front_mem(t_mem_stack **mem, t_mem_stack *ptr, t_mem_stack *tmp)
{
	if (ptr->previous == NULL)
	{
		ptr = ptr->next;
		ptr->previous = NULL;
		*mem = ptr;
		free(tmp);
		return (1);
	}
	return (0);
}

int	ft_free_back_mem(t_mem_stack **mem, t_mem_stack *ptr, t_mem_stack *tmp)
{
	(void)mem;
	if (ptr->next == NULL)
	{
		ptr->previous->next = NULL;
		free(tmp);
		return (1);
	}
	return (0);
}

void	ft_free(void *addr)
{
	t_mem_stack	**mem;
	t_mem_stack	*ptr;
	t_mem_stack	*tmp;

	mem = mem_stack(NULL, 0);
	ptr = *mem;
	while (ptr != NULL)
	{
		if (ptr->ptr == addr)
		{
			tmp = ptr;
			free(ptr->ptr);
			if (ft_free_front_mem(mem, ptr, tmp))
				break ;
			if (ft_free_back_mem(mem, ptr, tmp))
				break ;
			ptr = ptr->next;
			tmp->previous->next = ptr;
			free(tmp);
			break ;
		}
		ptr = ptr->next;
	}
}

void	destroy_stack(void)
{
	t_mem_stack	**mem;
	t_mem_stack	*tmp;

	mem = mem_stack(NULL, 0);
	while ((*mem) != NULL)
	{
		if ((*mem)->ptr != NULL)
			free((*mem)->ptr);
		tmp = *mem;
		*mem = (*mem)->next;
		free(tmp);
	}
	*mem = NULL;
}
