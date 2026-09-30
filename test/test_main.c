/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_main.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdarius- <sdarius-@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/28 13:20:01 by sdarius-          #+#    #+#             */
/*   Updated: 2026/09/30 11:54:16 by sdarius-         ###   ########.fr       */
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
			a.m[i][k] = 2;
			b.m[i][k] = 2;
			k++;
		}
		i++;
	}
	//printf("%s ",is_matrix_equal(4,a.m,b.m) ? "true" : "false");
	t_tuple tup = init_vector(5,3,1);


	tup =multy_m4_tup(a.m,tup);

	printf("%f\n%f\n%f\n%f\n",tup.x,tup.y,tup.z,tup.w);



	return (0);
}
