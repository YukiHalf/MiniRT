#include "../inc/minirt.h"

static void	render_row(t_app *app, int y)
{
	int	x;

	x = 0;
	while (x < app->width)
	{
		pixel_put(app, x, y, shade_pixel(app, x, y));
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
