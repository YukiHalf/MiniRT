/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   matrix_features_6.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdarius- <sdarius-@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/01 13:18:49 by sdarius-          #+#    #+#             */
/*   Updated: 2026/10/01 13:31:06 by sdarius-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "matrix.h"

t_mat4	init_shearing(t_shear amounts)
{
	t_mat4	result;

	result = init_identy_m4();
	result.m[0][1] = amounts.xy;
	result.m[0][2] = amounts.xz;
	result.m[1][0] = amounts.yx;
	result.m[1][2] = amounts.yz;
	result.m[2][0] = amounts.zx;
	result.m[2][1] = amounts.zy;
	return(result);
}
