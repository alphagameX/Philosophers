/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mem.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arthur <arthur@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/09 15:35:34 by arthur            #+#    #+#             */
/*   Updated: 2021/07/10 15:46:54 by arthur           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MEM_H
# define MEM_H
# include <stdlib.h>

typedef struct s_mem_stack
{
	void				*ptr;
	struct s_mem_stack	*next;
	struct s_mem_stack	*previous;
}	t_mem_stack;

typedef struct s_test
{
	char	*str;
	int		*tab;
}	t_test;

t_mem_stack	**mem_stack(void *ptr, int edit);
void		*new(size_t size, size_t count);
void		destroy_stack(void);
void		ft_free(void *addr);

#endif