/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_main.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdarius- <sdarius-@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/28 13:20:01 by sdarius-          #+#    #+#             */
/*   Updated: 2026/09/30 15:07:31 by sdarius-         ###   ########.fr       */
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
			printf("%6.0f ", m[i][k]);
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
	m = init_m4((double[4][4]){{1, 0,0,0}, {4, 3, 5,0}, {7, 2, -1,-7},{6, 6, -1,5}});
	DEBUG_print_matrice(4,m.m);
	printf("\n");
	t_mat3 m3= submatrix_m4_t_m3(m.m,0,0);
	DEBUG_print_matrice(3,m3.m);
	printf("\n%6.0f",cofractor_m3(m3.m,1,0));
	return (0);
}
