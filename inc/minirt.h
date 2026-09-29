#ifndef MINIRT_H
# define MINIRT_H

# include <stdlib.h>
# include <stdint.h>
# include <stdbool.h>
# include "libft/libft.h"
# include "../MLX42/include/MLX42/MLX42.h"

# define TITLE "miniRT"
# define WIN_W 1280
# define WIN_H 720
# define MIN_DIM 100
# define MAX_DIM 32767

/*
** width/height: size of the image, always equal to the window size once a
**   resize has been applied. This is the size the ray tracer renders at.
** next_row: next row to render. next_row >= height means "image finished".
** resize_*: last size reported by the resize hook, applied next frame.
** error: set by app_fail(), printed by main after a clean shutdown.
*/
typedef struct s_app
{
	mlx_t		*mlx;
	mlx_image_t	*img;
	int			width;
	int			height;
	int			next_row;
	int			resize_w;
	int			resize_h;
	bool		resize_pending;
	const char	*error;
}	t_app;

// app.c
const char	*app_init(t_app *app);
void		app_run(t_app *app);
void		app_cleanup(t_app *app);
void		app_invalidate(t_app *app);
void		app_fail(t_app *app, const char *msg);

// hooks.c
void		key_hook(mlx_key_data_t keydata, void *param);
void		resize_hook(int32_t width, int32_t height, void *param);
void		loop_hook(void *param);

// pixel.c
uint32_t	color_rgba(uint8_t r, uint8_t g, uint8_t b, uint8_t a);
uint32_t	color_from_unit(double r, double g, double b);
void		pixel_put(t_app *app, int x, int y, uint32_t color);
void		image_fill(t_app *app, uint32_t color);

// render.c
void		render_step(t_app *app);

// shade.c lowk we just have to work on this function, right?
uint32_t	shade_pixel(const t_app *app, int x, int y);

// error.c
int			print_error(const char *msg);

#endif
