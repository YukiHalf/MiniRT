#include "test_lib.h"

t_projectile	*tick(t_enviroment *envir, t_projectile *proj)
{
	t_projectile	*new_proj;

	new_proj = malloc(sizeof(t_projectile));
	new_proj->position = proj->position + proj->velocity;
	new_proj->velocity = proj->velocity + envir->gravity + envir->wind;
	return (new_proj);
}
