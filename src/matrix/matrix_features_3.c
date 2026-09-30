/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   matrix_features_3.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdarius- <sdarius-@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/30 12:27:31 by sdarius-          #+#    #+#             */
/*   Updated: 2026/09/30 15:07:15 by sdarius-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "matrix.h"

t_mat2	submatrix_m3_t_m2(const double m[static 3][3], int row, int col)
{
	t_mat2	result;
	int		i;
	int		k;

	i = 0;
	while (i < 2)
	{
		k = 0;
		while (k < 2)
		{
			result.m[i][k] = m[i + (i >= row)][k + (k >= col)];
			k++;
		}
		i++;
	}
	return (result);
}

t_mat3	submatrix_m4_t_m3(const double m[static 4][4], int row, int col)
{
	t_mat3	result;
	int		i;
	int		k;

	i = 0;
	while (i < 3)
	{
		k = 0;
		while (k < 3)
		{
			result.m[i][k] = m[i + (i >= row)][k + (k >= col)];
			k++;
		}
		i++;
	}
	return (result);
}

double	minor_m3(const double m[static 3][3], int row, int col)
{
	return (deter_m2(submatrix_m3_t_m2(m, row, col).m));
}

#include <stdio.h>

double	cofractor_m3(const double m[static 3][3], int row, int col)
{
	int	i;

	if ((row + col) % 2 == 0)
		i = 1;
	else
		i = -1;
	return (minor_m3(m, row, col) * i);
}
