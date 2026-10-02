/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scene.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdarius- <sdarius-@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/29 10:14:50 by sdarius-          #+#    #+#             */
/*   Updated: 2026/10/02 11:04:16 by sdarius-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SCENE_H
# define SCENE_H
# include "MLX42.h"
# include "tuple.h"
# define WIDTH 1080
# define HEIGHT 1080

typedef struct scene_s
{
	mlx_t		*mlx;
	mlx_image_t	*image;
}				t_scene;

typedef struct s_ray
{
	t_tuple		origin;
	t_tuple		direction;
}				t_ray;


/* give the point position of a ray moved in t time*/
t_tuple ray_position(t_ray ray, double t);
/*initiates a ray*/
t_ray	init_ray(t_tuple origin, t_tuple direction);
#endif
