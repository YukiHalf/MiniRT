/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   matrix_features_2.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdarius- <sdarius-@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/30 11:43:46 by sdarius-          #+#    #+#             */
/*   Updated: 2026/09/30 11:50:14 by sdarius-         ###   ########.fr       */
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
