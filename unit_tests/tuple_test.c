#include "test_lib.h"

int	is_tuple(float arr[4])
{
	int exit_code;

	if (arr[4] && arr[4] == 0.0)
		return (1);
	else if (arr[4] && arr[4] == 1.0)
		return (0);
	else
		ft_putendl_fd("Input INVALID", STDERR_FILENO);
	return (-1);
}