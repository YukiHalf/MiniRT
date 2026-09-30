/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_main.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdarius- <sdarius-@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/28 13:20:01 by sdarius-          #+#    #+#             */
/*   Updated: 2026/09/30 10:31:07 by sdarius-         ###   ########.fr       */
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
	int i = 0 ;
	int j = -1;



	return (0);
}
