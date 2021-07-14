/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_mem.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arthur <arthur@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/02 01:18:53 by arthur            #+#    #+#             */
/*   Updated: 2021/07/10 15:47:56 by arthur           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mem.h"

t_mem_stack	*create_mem_stack(void *ptr)
{
	t_mem_stack	*new;

	new = malloc(sizeof(t_mem_stack) * 1);
	new->next = NULL;
	new->previous = NULL;
	new->ptr = ptr;
	return (new);
}

void	push_back_mem_stack(t_mem_stack **stack, void *ptr)
{
	t_mem_stack	*p;
	t_mem_stack	*new;

	p = *stack;
	new = create_mem_stack(ptr);
	while (p->next != NULL)
		p = p->next;
	new->previous = p;
	p->next = new;
}

void	push_front_mem_stack(t_mem_stack **stack, void *ptr)
{
	t_mem_stack	*p;
	t_mem_stack	*new;

	p = *stack;
	new = create_mem_stack(ptr);
	while (p->previous != NULL)
		p = p->previous;
	new->next = p;
	p->previous = new;
	*stack = new;
}

t_mem_stack	**mem_stack(void *ptr, int edit)
{
	static t_mem_stack	*m_stack = NULL;

	if (ptr != NULL && edit)
	{
		if (m_stack == NULL)
			m_stack = create_mem_stack(ptr);
		else
			push_front_mem_stack(&m_stack, ptr);
	}
	return (&m_stack);
}

void	*new(size_t size, size_t count)
{
	void	*mem;

	mem = malloc(size * count);
	if (!mem)
	{
		destroy_stack();
		exit(1);
	}
	mem_stack(mem, 1);
	return (mem);
}
