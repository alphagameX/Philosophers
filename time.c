#include "source/philo.h"

long long int utc_time_in_usec(struct timeval time)
{
	return (((long long int)time.tv_sec * 1000) + (time.tv_usec / 1000));
}

struct timeval now(void)
{
	struct timeval n;

	gettimeofday(&n, NULL);
	return (n);
}

long long int elapsed_time(struct timeval start)
{
	return (utc_time_in_usec(now()) - utc_time_in_usec(start));
}

// int elapsed_time_ms(struct timeval start)
// {
// 	return (elapsed_time(start) / 1000);
// }

void sleep_time(int time)
{
	long long int n;

	n = utc_time_in_usec(now());
	while(utc_time_in_usec(now()) - n < time)
		usleep(100);
}
