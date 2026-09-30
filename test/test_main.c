/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_main.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdarius- <sdarius-@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/28 13:20:01 by sdarius-          #+#    #+#             */
/*   Updated: 2026/09/30 11:20:50 by sdarius-         ###   ########.fr       */
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
			b.m[i][k] = k;
			k++;
		}
		i++;
	}
	//printf("%s ",is_matrix_equal(4,a.m,b.m) ? "true" : "false");

	t_mat4 res = multy_m4(a.m,b.m);

	DEBUG_print_matrice(4,a.m);
	printf("-------a------\n");
	DEBUG_print_matrice(4,b.m);
		printf("-------b------\n");
	DEBUG_print_matrice(4,res.m);


	return (0);
}
