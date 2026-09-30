/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_main.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdarius- <sdarius-@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/28 13:20:01 by sdarius-          #+#    #+#             */
/*   Updated: 2026/09/30 11:03:51 by sdarius-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tuple.h"
#include <stdio.h>
#include "color.h"
#include <stdlib.h>
#include "scene.h"
#include "mlx_f.h"
#include "matrix.h"


int	main(int argc, char **argv)
{
	t_scene *scene;

	scene = malloc(sizeof(*scene));

	inti_mlx(scene->mlx,scene->image);

	t_mat2 a;
	t_mat2 b;

	int i = 0;
	while( i < 2)
	{
		int k =0;
		while(k < 2)
		{
			a.m[i][k] = i;
			b.m[i][k] = k;
			k++;
		}
		i++;
	}
	printf("%s ",is_matrix_equal(2,a.m,b.m) ? "true" : "false");

	return (0);
}
