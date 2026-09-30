/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_main.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdarius- <sdarius-@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/28 13:20:01 by sdarius-          #+#    #+#             */
/*   Updated: 2026/09/30 12:25:45 by sdarius-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tuple.h"
#include <stdio.h>
#include "color.h"
#include <stdlib.h>
#include "scene.h"
#include "mlx_f.h"
#include "matrix.h"

void DEBUG_print_matrice(size_t size, double m[static size][size])
{
	for(int i = 0;i < size;i++)
	{
		for(int k = 0;k < size;k++)
		{
			printf("%6.0f ",m[i][k]);
		}
		printf("\n");
	}
}



int	main(int argc, char **argv)
{
	t_scene *scene;

	scene = malloc(sizeof(*scene));

	inti_mlx(scene->mlx,scene->image);

	t_mat4 a;
	t_mat4 b;

	int i = 0;
	while( i < 4)
	{
		int k =0;
		while(k < 4)
		{
			a.m[i][k] = i;
			b.m[i][k] = i;
			k++;
		}
		i++;
	}
	//printf("%s ",is_matrix_equal(4,a.m,b.m) ? "true" : "false");
	t_mat2 m = init_m2((double[2][2]){{1,5},{-3,2}});
	printf("%f",deter_m2(m.m));
	return (0);
}
