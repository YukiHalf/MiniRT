/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_main.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdarius- <sdarius-@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/28 13:20:01 by sdarius-          #+#    #+#             */
/*   Updated: 2026/09/28 13:58:46 by sdarius-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tuple.h"
#include <stdio.h>

int	main(int argc, char **argv)
{
	int				exit_code;
	float			epsilon;
	t_projectile	p;
	t_enviroment	e;
	int				i;

	p.position = init_point(0, 1, 0);
	p.velocity = init_vector(1, 1, 0);
	p.velocity = norm_tup(p.velocity);
	e.gravity = init_vector(0, -0.1, 0);
	e.wind = init_vector(-0.01, 0, 0);
	i = 0;
	while (p.position.y >= 0)
	{
		printf("Position: %f %f %f\n",p.position.x,p.position.y,p.position.z);
		p.position = add_tup(p.position,p.velocity);
		p.velocity = add_tup(p.velocity,add_tup(e.gravity,e.wind));
		i++;
	}
	printf("Position: %f %f %f\n",p.position.x,p.position.y,p.position.z);

	printf("Total ticks: %d\n", i);
	return (exit_code);
}
