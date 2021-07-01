#include "source/philo.h"

long long int utc_time_in_usec(struct timeval time)
{
	return (((long long int)time.tv_sec * 1000000) + time.tv_usec);
}

struct timeval now(void)
{
	struct timeval n;

	gettimeofday(&n, NULL);
	return (n);
}

long long int elapsed_time_u(struct timeval start)
{
	return (utc_time_in_usec(now()) - utc_time_in_usec(start));
}

int elapsed_time_ms(struct timeval start)
{
	return (elapsed_time_u(start) / 1000);
}