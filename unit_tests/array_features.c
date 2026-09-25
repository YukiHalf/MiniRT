#include "test_lib.h"

float	*nega_arr(float *arr)
{
	int	i;

	i = 0;
	while (i < 4)
	{
		arr[i] = -arr[i];
		i++;
	}
	return (arr);
}

float	*multy_arr(float *arr, float x)
{
	int	i;

	i = 0;
	while (i < 4)
	{
		arr[i] = arr[i] * x;
		i++;
	}
	return (arr);
}

float	*subst_arr(float *arr, float *arr2)
{
	int		i;
	float	*new_arr;

	new_arr = malloc(sizeof(float) * 4);
	if (!new_arr)
	{
		ft_putendl_fd("Malloc failed!", STDERR_FILENO);
		return (NULL);
	}
	i = 0;
	while (i < 3)
	{
		new_arr[i] = arr[i] - arr2[i];
		i++;
	}
	new_arr[3] = fabs((arr[3] - arr2[3]));
	return (new_arr);
}

float	*add_arrs(float *arr, float *arr2)
{
	int		i;
	float	*new_arr;

	new_arr = malloc(sizeof(float) * 4);
	if (!new_arr)
	{
		ft_putendl_fd("Malloc failed!", STDERR_FILENO);
		return (NULL);
	}
	i = 0;
	while (i < 3)
	{
		new_arr[i] = arr[i] + arr2[i];
		i++;
	}
	if (arr[i] == 1 || arr2[i] == 1)
		new_arr[3] = 1;
	else
		new_arr[3] = 0;
	return (new_arr);
}

float	*create_arr(float a, float b, float c, float d)
{
	float	*arr;

	arr = malloc(sizeof(float) * 4);
	if (!arr)
	{
		ft_putendl_fd("Malloc failed!", STDERR_FILENO);
		return (NULL);
	}
	arr[0] = a;
	arr[1] = b;
	arr[2] = c;
	arr[3] = d;
	return (arr);
}
