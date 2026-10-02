#include "minirt.h"

void	key_hook(mlx_key_data_t keydata, void *param)
{
	t_app	*app;

	app = param;
	if (keydata.key == MLX_KEY_ESCAPE && keydata.action == MLX_PRESS)
		mlx_close_window(app->mlx);
}

void	resize_hook(int32_t width, int32_t height, void *param)
{
	t_app	*app;

	app = param;
	app->resize_w = width;
	app->resize_h = height;
	app->resize_pending = true;
}

static void	apply_resize(t_app *app)
{
	app->resize_pending = false;
	if (app->resize_w < MIN_DIM || app->resize_h < MIN_DIM
		|| app->resize_w > MAX_DIM || app->resize_h > MAX_DIM)
		return ;
	if (app->resize_w == app->width && app->resize_h == app->height)
		return ;
	if (!mlx_resize_image(app->img, app->resize_w, app->resize_h))
	{
		app_fail(app, mlx_strerror(mlx_errno));
		return ;
	}
	app->width = app->resize_w;
	app->height = app->resize_h;
	app_invalidate(app);
}

void	loop_hook(void *param)
{
	t_app	*app;

	app = param;
	if (app->resize_pending)
		apply_resize(app);
	render_step(app);
}
