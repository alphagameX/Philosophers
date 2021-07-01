#ifndef MEM_H
# define MEM_H
# include <stdio.h>
# include <stdlib.h>

typedef struct s_mem_stack
{
	void *ptr;
	int id;
	struct s_mem_stack *next;
} t_mem_stack;

typedef struct s_test {
	char *str;
	int *tab;
} t_test;


void *new (size_t size, size_t count);
void destroy_stack(void);

#endif