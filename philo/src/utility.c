
#include "../philo.h"

long	number_convert(int x, long nbr, const char *str)
{
	long	res;

	res = 0;
	if (str[x] <= '9' && str[x] >= '0')
	{
		while (str[x] <= '9' && str[x] >= '0')
		{
			res *= 10;
			res += str[x] - '0';
			x++;
		}
		return (res * nbr);
	}
	else
		return (0);
}

long	ft_atol(const char *str)
{
	long	x;
	long	nbr;

	nbr = 1;
	x = 0;
	while (str[x] == ' ' || str[x] == '\t' || str[x] == '\n' || str[x] == '\v'
		|| str[x] == '\f' || str[x] == '\r')
		x++;
	if (str[x] == '-' || str[x] == '+')
	{
		if (str[x] == '-')
			nbr *= -1;
		x++;
	}
	if (str)
		nbr = number_convert(x, nbr, str);
	return (nbr);
}
