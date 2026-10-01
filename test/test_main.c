/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_main.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdarius- <sdarius-@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/28 13:20:01 by sdarius-          #+#    #+#             */
/*   Updated: 2026/10/01 14:04:13 by sdarius-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "color.h"
#include "matrix.h"
#include "mlx_f.h"
#include "scene.h"
#include "tuple.h"
#include <stdio.h>
#include <stdlib.h>
#include <scene.h>
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
	t_rgb c;

	c.r = 1;
	c.g = 1;
	c.b = 1;

	scene = malloc(sizeof(*scene));
	init_mlx(scene);
	write_pixel_mlx(scene->image,c,64,64);
	mlx_loop(scene->mlx);
	mlx_terminate(scene->mlx);
	free(scene);
	return (0);
}
