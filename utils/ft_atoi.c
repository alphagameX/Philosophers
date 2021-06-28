#include "../source/philo.h"

int is_whitespace(char c)
{
	if (c == '\n' || c == '\t' || c == '\f' || c == '\r' || c == '\v' || c == ' ')
		return (1);
	return (0);
}

int ft_atoi(const char *str)
{
	int i = 0;
	int sign = 1;
	unsigned long long res = 0;

	if (!str)
		return 0;

	while (is_whitespace(str[i]))
		i++;
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			sign *= -1;
		i++;
	}
	while (ft_isdigit(str[i]))
	{
		res = res * 10 + (str[i] - '0');
		i++;
	}
	return (res * sign);
}