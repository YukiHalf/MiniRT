#include "test_lib.h"

projectile_t *tick(enviroment_t *envir,projectile_t *proj)
{
	projectile_t *new_proj;

	new_proj = malloc(sizeof(projectile_t));

	new_proj->position = proj->position + proj->velocity;
	new_proj->velocity = proj->velocity + envir->gravity + envir->wind;
	return (new_proj);
}
