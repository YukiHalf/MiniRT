#ifndef MINIRT_H
# define MINIRT_H

# include <stdbool.h>
# include <stdint.h>
# include <stdlib.h>
# include "libft/libft.h"
# include "MLX42.h"
# include "scene.h"
# include "camera.h"
# include "world.h"

# define TITLE "miniRT"
# define WIN_W 1920
# define WIN_H 1080
# define MIN_DIM 100
# define MAX_DIM 32767

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
	t_rt_scene	scene;
	t_cam		camera;
	t_mat4		view;
	t_intersections	xs;
}t_app;

const char	*app_init(t_app *app);
void		app_run(t_app *app);
void		app_cleanup(t_app *app);
void		app_invalidate(t_app *app);
void		app_fail(t_app *app, const char *msg);
void		key_hook(mlx_key_data_t keydata, void *param);
void		resize_hook(int32_t width, int32_t height, void *param);
void		loop_hook(void *param);
uint32_t	color_rgba(uint8_t r, uint8_t g, uint8_t b, uint8_t a);
uint32_t	color_from_unit(double r, double g, double b);
void		pixel_put(t_app *app, int x, int y, uint32_t color);
void		image_fill(t_app *app, uint32_t color);
void		render_step(t_app *app);
int			print_error(const char *msg);

#endif
