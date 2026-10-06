#include "parser.h"
#include <math.h>

static int	read_digits(const char **s, double *mant)
{
	int	n;

	n = 0;
	while (**s >= '0' && **s <= '9')
	{
		*mant = *mant * 10.0 + (**s - '0');
		(*s)++;
		n++;
	}
	return (n);
}

static double	read_sign(const char **s)
{
	double	sign;

	sign = 1.0;
	if (**s == '-')
		sign = -1.0;
	if (**s == '-' || **s == '+')
		(*s)++;
	return (sign);
}

int	parse_double(const char *s, double *out)
{
	double	mant;
	double	sign;
	int		digits;
	int		frac;

	sign = read_sign(&s);
	mant = 0.0;
	digits = read_digits(&s, &mant);
	frac = 0;
	if (*s == '.')
	{
		s++;
		frac = read_digits(&s, &mant);
	}
	if (*s != '\0' || digits + frac == 0)
		return (0);
	*out = sign * mant / pow(10.0, frac);
	return (!isinf(*out));
}

int	parse_range(const char *s, double lo, double hi, double *out)
{
	if (!parse_double(s, out))
		return (0);
	return (*out >= lo && *out <= hi);
}

int	parse_byte(const char *s, int *out)
{
	int	v;

	if (*s < '0' || *s > '9')
		return (0);
	v = 0;
	while (*s >= '0' && *s <= '9')
	{
		v = v * 10 + (*s - '0');
		if (v > 255)
			return (0);
		s++;
	}
	*out = v;
	return (*s == '\0');
}