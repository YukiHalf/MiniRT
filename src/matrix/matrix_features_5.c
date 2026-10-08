/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   matrix_features_5.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdarius- <sdarius-@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/01 11:49:47 by sdarius-          #+#    #+#             */
/*   Updated: 2026/10/08 13:13:26 by sdarius-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "matrix.h"

t_mat4	init_translation(double x, double y, double z)
{
	t_mat4	t;

	t = init_identy_m4();
	t.m[0][3] = x;
	t.m[1][3] = y;
	t.m[2][3] = z;
	return (t);
}

t_mat4	init_scaling(double x, double y, double z)
{
	t_mat4	s;

	s = init_identy_m4();
	s.m[0][0] = x;
	s.m[1][1] = y;
	s.m[2][2] = z;
	return (s);
}

t_mat4	rotation_x(double radians)
{
	t_mat4	r;

	r = init_identy_m4();
	r.m[1][1] = cos(radians);
	r.m[1][2] = -(sin(radians));
	r.m[2][1] = sin(radians);
	r.m[2][2] = cos(radians);
	return (r);
}

t_mat4	rotation_y(double radians)
{
	t_mat4	r;

	r = init_identy_m4();
	r.m[0][0] = cos(radians);
	r.m[0][2] = sin(radians);
	r.m[2][0] = -(sin(radians));
	r.m[2][2] = cos(radians);
	return (r);
}

t_mat4	rotation_z(double radians)
{
	t_mat4	r;

	r = init_identy_m4();
	r.m[0][0] = cos(radians);
	r.m[0][1] = -(sin(radians));
	r.m[1][0] = sin(radians);
	r.m[1][1] = cos(radians);
	return (r);
}
