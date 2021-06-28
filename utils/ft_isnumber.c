#include "../source/philo.h"

int	ft_isnumber(char *str)
{
	int i;

	i = 0;
	while(str[i])
	{
		if(!ft_isdigit((int)str[i]) && str[i] != '-' && str[i] != '+')
			return (0);
		i++;
	}
	return (1);
}