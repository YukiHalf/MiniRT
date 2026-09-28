/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_main.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdarius- <sdarius-@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/28 13:20:01 by sdarius-          #+#    #+#             */
/*   Updated: 2026/09/28 13:20:03 by sdarius-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "test_lib.h"

int	main(int argc, char **argv)
{
	int				exit_code;
	float			epsilon;
	t_projectile	*p;
	t_enviroment	*e;
	int				i;
	t_tuple			*tmp_pos;
	t_tuple			*tmp_vel;

	p = malloc(sizeof(t_projectile));
	e = malloc(sizeof(t_enviroment));
	p->position = init_point(0, 1, 0);
	p->velocity = init_vector(1, 1, 0);
	norm_tup(p->velocity);
	e->gravity = init_vector(0, -0.1, 0);
	e->wind = init_vector(-0.01, 0, 0);
	i = 0;
	while (p->position->y >= 0)
	{
		p.position = add_tup(p->position, p->velocity) *p->velocity = printf("%f
				%f %f\n", p->position->x, p->position->y, p->position->z);
		i++;
	}
	printf("Total ticks: %d\n", i);
	return (exit_code);
}
