/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_main.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdarius- <sdarius-@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/28 13:20:01 by sdarius-          #+#    #+#             */
/*   Updated: 2026/10/01 11:22:58 by sdarius-         ###   ########.fr       */
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
	m = init_m4((double[4][4]){{8, -5,9,2}, {7, 5, 6,1}, {-6, 0, 9,6},{-3, 0, -9,-4}});
t_mat4	m1 = init_m4((double[4][4]){{8, -5,9,2}, {7, 5, 6,1}, {-6, 0, 9,6},{-3, 0, -9,-4}});
	t_mat4 C = multy_m4(m.m,m1.m);
	DEBUG_print_matrice(4,C.m);
	printf("\n");
	C = multy_m4(C.m,inverse_m4(m1.m).m);
	DEBUG_print_matrice(4,C.m);
	return (0);
}
