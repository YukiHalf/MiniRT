/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   matrix_features_4.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdarius- <sdarius-@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/01 09:52:37 by sdarius-          #+#    #+#             */
/*   Updated: 2026/10/01 11:18:08 by sdarius-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "matrix.h"
#include <stdio.h>

double	minor_m4(const double m[static 4][4], int row, int col)
{
	return (deter_m3(submatrix_m4_t_m3(m, row, col).m));
}

double	cofractor_m4(const double m[static 4][4], int row, int col)
{
	int	i;

	if ((row + col) % 2 == 0)
		i = 1;
	else
		i = -1;
	return (minor_m4(m, row, col) * i);
}

double	deter_m4(const double m[static 4][4])
{
	double	deter;
	int		i;

	deter = 0;
	i = 0;
	while (i < 4)
	{
		deter += m[0][i] * cofractor_m4(m, 0, i);
		i++;
	}
	return (deter);
}

bool	is_invertible_m4(const double m[static 4][4])
{
	return (!(deter_m4(m) == 0));
}

t_mat4	inverse_m4(const double m[static 4][4])
{
	t_mat4	result;
	int		row;
	int		col;
	double	c;

	if (!is_invertible_m4)
	{
		ft_putendl_fd("Not invertible", STDERR_FILENO);
		return (init_m4(m));
	}
	row = 0;
	while (row < 4)
	{
		col = 0;
		while (col < 4)
		{
			c = cofractor_m4(m, row, col);
			result.m[col][row] = c / deter_m4(m);
			col++;
		}
		row++;
	}
	return (result);
}
