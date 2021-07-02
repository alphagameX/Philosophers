/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mem.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arthur <arthur@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/02 01:18:53 by arthur            #+#    #+#             */
/*   Updated: 2021/07/02 14:41:57 by arthur           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mem.h"

t_mem_stack	*create_mem_stack(void *ptr)
{
	t_mem_stack	*new;

	new = malloc(sizeof(t_mem_stack) * 1);
	new->next = NULL;
	new->id = 0;
	new->ptr = ptr;
	return (new);
}

void	push_mem_stack(t_mem_stack **stack, void *ptr)
{
	t_mem_stack	*p;

	p = *stack;
	while (p->next != NULL)
		p = p->next;
	p->next = create_mem_stack(ptr);
}

t_mem_stack	*mem_stack(void *ptr)
{
	static t_mem_stack	*m_stack = NULL;

	if (m_stack == NULL)
		m_stack = create_mem_stack(NULL);
	if (ptr != NULL)
		push_mem_stack(&m_stack, ptr);
	return (m_stack);
}

void	destroy_stack(void)
{
	t_mem_stack	*m_stack;
	t_mem_stack	*tmp;

	m_stack = mem_stack(NULL);
	while (m_stack != NULL)
	{
		if (m_stack->ptr != NULL)
			free(m_stack->ptr);
		tmp = m_stack;
		m_stack = m_stack->next;
		free(tmp);
	}
}

void	*new(size_t size, size_t count)
{
	void	*mem;

	mem = malloc(size * count);
	if (!mem)
		printf("invalid\n");
	mem_stack(mem);
	return (mem);
}
