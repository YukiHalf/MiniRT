#include "../inc/minirt.h"

int	print_error(const char *msg)
{
	ft_putstr_fd("Error\n", 2);
	ft_putstr_fd((char *)msg, 2);
	ft_putchar_fd('\n', 2);
	return (1);
}
