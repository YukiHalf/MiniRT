/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   matrix_features.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdarius- <sdarius-@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/29 12:13:56 by sdarius-          #+#    #+#             */
/*   Updated: 2026/09/30 11:44:18 by sdarius-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "matrix.h"

t_mat4	init_m4(const double a[static 4][4])
{
	int		i;
	int		j;
	t_mat4	l_matr;

	i = 0;
	while (i < 4)
	{
		j = 0;
		while (j < 4)
		{
			l_matr.m[i][j] = a[i][j];
			j++;
		}
		i++;
	}
	return (l_matr);
}

t_mat3	init_m3(const double a[static 3][3])
{
	int		i;
	int		j;
	t_mat3	l_matr;

	i = 0;
	while (i < 3)
	{
		j = 0;
		while (j < 3)
		{
			l_matr.m[i][j] = a[i][j];
			j++;
		}
		i++;
	}
	return (l_matr);
}

t_mat2	init_m2(const double a[static 2][2])
{
	int		i;
	int		j;
	t_mat2	l_matr;

	i = 0;
	while (i < 2)
	{
		j = 0;
		while (j < 2)
		{
			l_matr.m[i][j] = a[i][j];
			j++;
		}
		i++;
	}
	return (l_matr);
}

bool	is_matrix_equal(size_t size, const double a[size][size],
		const double b[size][size])
{
	int	i;
	int	k;

	i = 0;
	while (i < size)
	{
		k = 0;
		while (k < size)
		{
			if (!(d_equality(a[i][k], b[i][k])))
				return (false);
			k++;
		}
		i++;
	}
	return (true);
}

t_mat4	multy_m4(const double a[static 4][4], const double b[static 4][4])
{
	t_mat4	result;
	int		row;
	int		col;

	row = 0;
	while (row < 4)
	{
		col = 0;
		while (col < 4)
		{
			result.m[row][col] = a[row][0] * b[0][col] + a[row][1] * b[1][col]
				+ a[row][2] * b[2][col] + a[row][3] * b[3][col];
			col++;
		}
		row++;
	}
	return (result);
}
