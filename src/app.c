/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   app.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdarius- <sdarius-@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/08 13:17:55 by sdarius-          #+#    #+#             */
/*   Updated: 2026/10/08 13:17:56 by sdarius-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"
#include "parser.h"

const char	*app_init(t_app *app)
{
	app->mlx = mlx_init(WIN_W, WIN_H, TITLE, true);
	if (!app->mlx)
		return (mlx_strerror(mlx_errno));
	app->img = mlx_new_image(app->mlx, WIN_W, WIN_H);
	if (!app->img)
		return (mlx_strerror(mlx_errno));
	if (mlx_image_to_window(app->mlx, app->img, 0, 0) < 0)
		return (mlx_strerror(mlx_errno));
	app->width = WIN_W;
	app->height = WIN_H;
	mlx_set_window_limit(app->mlx, MIN_DIM, MIN_DIM, MAX_DIM, MAX_DIM);
	mlx_key_hook(app->mlx, key_hook, app);
	mlx_resize_hook(app->mlx, resize_hook, app);
	mlx_loop_hook(app->mlx, loop_hook, app);
	if (!init_intersections(&app->xs))
		return ("memory allocation failed");
	app_invalidate(app);
	return (NULL);
}

void	app_run(t_app *app)
{
	mlx_loop(app->mlx);
}

void	app_cleanup(t_app *app)
{
	free(app->xs.items);
	app->xs.items = NULL;
	if (app->mlx)
		mlx_terminate(app->mlx);
	app->mlx = NULL;
	app->img = NULL;
	scene_free(&app->scene);
}

void	app_invalidate(t_app *app)
{
	app->next_row = 0;
}

void	app_fail(t_app *app, const char *msg)
{
	if (!app->error)
		app->error = msg;
	if (app->mlx)
		mlx_close_window(app->mlx);
}
