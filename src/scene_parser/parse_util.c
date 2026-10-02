#include "parser.h"

bool	is_blank(char c)
{
	return (c == ' ' || c == '\t' || c == '\r'
		|| c == '\v' || c == '\f');
}
