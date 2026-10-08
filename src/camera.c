#include "camera.h"
#include <math.h>

static void setup_orientation(double o[4][4], t_tuple f, t_tuple l)
{
  t_tuple tu;

  tu = cross_arr(l, f);
  o[0][0] = l.x;
	o[0][1] = l.y;
	o[0][2] = l.z;
	o[0][3] = 0;
	o[1][0] = tu.x;
	o[1][1] = tu.y;
	o[1][2] = tu.z;
	o[1][3] = 0;
	o[2][0] = -f.x;
	o[2][1] = -f.y;
	o[2][2] = -f.z;
	o[2][3] = 0;
	o[3][0] = 0;
	o[3][1] = 0;
	o[3][2] = 0;
	o[3][3] = 1;
}

t_mat4	view_transform(t_tuple from, t_tuple to, t_tuple up)
{
	t_tuple	forward;
	t_tuple	left;
	double	orientation[4][4];
	t_mat4	orient;
	t_mat4	move;
	
	forward = norm_tup(subst_tup(to, from));
	up = norm_tup(up);
	left = cross_arr(forward, up);
  setup_orientation(orientation, forward, left);
	orient = init_m4(orientation);
	move = init_translation(-from.x, -from.y, -from.z);
	return (multy_m4(inverse_m4(orient.m).m, move.m));
}

void	camera_init(t_cam *cam, int hsize, int vsize, double field_of_view)
{
	double	half_view;
	double	aspect;

	half_view = tan(field_of_view / 2.0);
	aspect = (double)hsize / (double)vsize;
	cam->hsize = hsize;
	cam->vsize = vsize;
	cam->field_of_view = field_of_view;
	cam->half_width = half_view;
	cam->half_height = half_view;
	if (aspect >= 1.0)
		cam->half_height = half_view / aspect;
	else
		cam->half_width = half_view * aspect;
	cam->pixel_size = (cam->half_width * 2.0) / (double)hsize;
	cam->transform = init_identy_m4();
}

t_ray	ray_for_pixel(const t_cam *cam, double px, double py)
{
	double	world_x;
	double	world_y;
	t_mat4	inv;
	t_tuple	pixel;
	t_tuple	origin;

	world_x = (px + 0.5) * cam->pixel_size - cam->half_width;
	world_y = cam->half_height - (py + 0.5) * cam->pixel_size;
	inv = inverse_m4(cam->transform.m);
	pixel = multy_m4_tup(inv.m, init_point(world_x, world_y, -1));
	origin = multy_m4_tup(inv.m, init_point(0, 0, 0));
	return (init_ray(origin, norm_tup(subst_tup(pixel, origin))));
}
