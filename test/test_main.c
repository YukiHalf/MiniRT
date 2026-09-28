/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_main.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdarius- <sdarius-@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/28 13:20:01 by sdarius-          #+#    #+#             */
/*   Updated: 2026/09/28 14:31:51 by sdarius-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tuple.h"
#include <stdio.h>
#include "color.h"
#include <stdlib.h>
int	main(int argc, char **argv)
{
	t_rgb c1;
	t_rgb c2;

	c1 = init_rgb(1,0.2,0.4);
	c2 = init_rgb(0.9,1,0.1);
	printf("%f %f %f\n",c1.r,c1.b,c1.g);
	printf("%f %f %f\n",c2.r,c2.b,c2.g);
	c1 = sub_rgb(c1,c2);
	printf("%f %f %f\n",c1.r,c1.b,c1.g);
	c1 = mult_scalar_rgb(c1,2);
		printf("%f %f %f\n",c1.r,c1.b,c1.g);
	c1 = mult_color_rgb(c1,c2);
			printf("%f %f %f\n",c1.r,c1.b,c1.g);
	return (0);
}
