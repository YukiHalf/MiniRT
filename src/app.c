#include "minirt.h"

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
	app_invalidate(app);
	return (NULL);
}

void	app_run(t_app *app)
{
	mlx_loop(app->mlx);
}

void	app_cleanup(t_app *app)
{
	if (app->mlx)
		mlx_terminate(app->mlx);
	app->mlx = NULL;
	app->img = NULL;
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
