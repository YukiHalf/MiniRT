/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   matrix_features.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdarius- <sdarius-@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/29 12:13:56 by sdarius-          #+#    #+#             */
/*   Updated: 2026/09/29 12:31:38 by sdarius-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "matrix.h"

t_mat4	init_m4(const double a[4][4])
{
	int		i;
	int		j;
	t_mat4	l_matr;

	while (i < 4)
	{
		while (j < 4)
		{
			l_matr.m[i][j] = a[i][j];
			j++;
		}
		i++;
	}
	return (l_matr);
}
