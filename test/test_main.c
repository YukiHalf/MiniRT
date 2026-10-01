/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_main.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdarius- <sdarius-@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/28 13:20:01 by sdarius-          #+#    #+#             */
/*   Updated: 2026/10/01 12:25:50 by sdarius-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "color.h"
#include "matrix.h"
#include "mlx_f.h"
#include "scene.h"
#include "tuple.h"
#include <stdio.h>
#include <stdlib.h>

void	DEBUG_print_matrice(size_t size, double m[static size][size])
{
	for (int i = 0; i < size; i++)
	{
		for (int k = 0; k < size; k++)
		{
			printf("%f ", m[i][k]);
		}
		printf("\n");
	}
	printf("\n");
}

void DEBUG_print_tuple(t_tuple tup)
{
	printf("%f %f %f %f\n",tup.x,tup.y,tup.z, tup.w);
}

int	main(int argc, char **argv)
{
	t_scene	*scene;
	t_mat4	a;
	t_mat4	b;
	int		i;
	int		k;
	t_mat4	m;

	scene = malloc(sizeof(*scene));
	inti_mlx(scene->mlx, scene->image);
	i = 0;
	while (i < 4)
	{
		k = 0;
		while (k < 4)
		{
			a.m[i][k] = i;
			b.m[i][k] = i;
			k++;
		}
		i++;
	}
	// printf("%s ",is_matrix_equal(4,a.m,b.m) ? "true" : "false");
	double pi = M_PI;
	t_tuple p = init_point(0,0,1);
	DEBUG_print_tuple(multy_m4_tup(rotation_y(pi/2).m,p));

	return (0);
}
