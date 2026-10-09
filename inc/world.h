#ifndef WORLD_H
# define WORLD_H

# include "scene.h"

typedef struct s_comps
{
	double			t;
	const t_object	*object;
	t_tuple			point;
  t_tuple     over_point;
	t_tuple			eyev;
	t_tuple			normalv;
	bool			inside;
}				t_comps;

/*collects the intersections of the ray with every object in the world*/
bool	intersect_world(const t_rt_scene *world, const t_ray *ray, t_intersections *xs);
/*precomputes the useful values of an intersection hit (point, eyev,
normalv and the inside flag)*/
t_comps	prepare_computations(const t_intersection *intersection, t_ray ray);
/*returns the shaded color at the precomputed hit point*/
t_rgb	shade_hit(const t_rt_scene *world, t_comps comps, t_intersections *xs);
/*returns the color of the world seen by the ray, black if nothing is hit*/
t_rgb	color_at(const t_rt_scene *world, const t_ray *ray, t_intersections *xs);

void	prepare_sphere(t_object *o);
void	prepare_plane(t_object *o);
void	prepare_cube(t_object *o);
void	prepare_cylinder(t_object *o);
void	prepare_cone(t_object *o);
void	prepare_parsed_scene(t_rt_scene *scene);
void	prepare_object(t_object *o);
t_mat4	axis_rotation(t_tuple axis);
#endif
