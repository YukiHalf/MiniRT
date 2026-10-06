#include "parser.h"

bool	is_blank(char c)
{
	return (c == ' ' || c == '\t' || c == '\r'
		|| c == '\v' || c == '\f');
}

int	tokenize(char *s, char **tok, int max)
{
	int	n;

	n = 0;
	while (*s)
	{
		while (*s && is_blank(*s))
		{
			*s = '\0';
			s++;
		}
		if (!*s)
			break ;
		if (n == max)
			return (-1);
		tok[n] = s;
		n++;
		while (*s && !is_blank(*s))
			s++;
	}
	return (n);
}
