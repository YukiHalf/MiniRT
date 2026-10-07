#include "minirt.h"

static void	render_row(t_app *app, int y)
{
	t_ray	ray;
	t_rgb	color;
	int		x;

	x = 0;
	while (x < app->width)
	{
		ray = ray_for_pixel(&app->camera, x, y);
		color = color_at(&app->scene, &ray, &app->xs);
		pixel_put(app, x, y, color_from_unit(color.r, color.g, color.b));
		x++;
	}
}

void	render_step(t_app *app)
{
	while (app->next_row < app->height)
	{
		render_row(app, app->next_row);
		app->next_row++;
	}
}
