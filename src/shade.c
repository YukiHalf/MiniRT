#include "minirt.h"

uint32_t	shade_pixel(const t_app *app, int x, int y)
{
	if (x == 0 || y == 0 || x == app->width - 1 || y == app->height - 1)
		return (color_rgba(255, 255, 255, 255));
	return (color_from_unit((double)x / (app->width - 1),
			(double)y / (app->height - 1), 0.25));
}
