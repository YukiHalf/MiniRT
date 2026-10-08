#ifndef CAMERA_H
# define CAMERA_H

# include "matrix.h"
# include "scene.h"

typedef struct s_cam
{
	int			hsize;
	int			vsize;
	double		field_of_view;
	t_mat4		transform;
	double		half_width;
	double		half_height;
	double		pixel_size;
}			t_cam;

/*returns the view transformation matrix that moves the world so the camera
sits at the origin looking down the -z axis (chapter 7, view transform)*/
t_mat4	view_transform(t_tuple from, t_tuple to, t_tuple up);
/*initializes a camera for the given raster size and fov in radians,
computing pixel_size and the half width/height of the canvas*/
void	camera_init(t_cam *cam, int hsize, int vsize, double field_of_view);
/*returns the ray that starts at the camera origin and passes through
the center of the given pixel*/
t_ray	ray_for_pixel(const t_cam *cam, double px, double py);

#endif
