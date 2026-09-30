/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   matrix_features_2.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdarius- <sdarius-@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/30 11:43:46 by sdarius-          #+#    #+#             */
/*   Updated: 2026/09/30 12:22:33 by sdarius-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "matrix.h"

t_tuple	multy_m4_tup(const double m[static 4][4], const t_tuple t)
{
	t_tuple	result;
	int		row;

	row = 0;
	result.x = m[row][0] * t.x + m[row][1] * t.y + m[row][2] * t.z + m[row][3]
		* t.w;
	row++;
	result.y = m[row][0] * t.x + m[row][1] * t.y + m[row][2] * t.z + m[row][3]
		* t.w;
	row++;
	result.z = m[row][0] * t.x + m[row][1] * t.y + m[row][2] * t.z + m[row][3]
		* t.w;
	row++;
	result.w = m[row][0] * t.x + m[row][1] * t.y + m[row][2] * t.z + m[row][3]
		* t.w;
	return (result);
}

t_mat4	init_identy_m4(void)
{
	t_mat4	indenty_m4;
	int		i;
	int		k;

	i = 0;
	while (i < 4)
	{
		k = 0;
		while (k < 4)
		{
			if (i == k)
				indenty_m4.m[i][k] = 1;
			else
				indenty_m4.m[i][k] = 0;
			k++;
		}
		i++;
	}
	return (indenty_m4);
}

t_mat4	multy_m4_identy(const double m[static 4][4])
{
	t_mat4	indenty_m4;

	indenty_m4 = init_identy_m4();
	return (multy_m4(m, indenty_m4.m));
}

t_mat4	transpose_m4(const double m[static 4][4])
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
			result.m[col][row] = m[row][col];
			col++;
		}
		row++;
	}
	return (result);
}

double	deter_m2(const double m[static 2][2])
{
	return ((double)(m[0][0] * m[1][1]) - (m[0][1] * m[1][0]));
}
