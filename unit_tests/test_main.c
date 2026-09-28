#include "test_lib.h"


int main(int argc, char** argv)
{
	int exit_code;
	float epsilon;

	projectile_t *p;
	enviroment_t *e;

	p = malloc(sizeof(projectile_t));
	e = malloc(sizeof(enviroment_t));

	p->position = init_point(0,1,0);
	p->velocity = norm_tup(init_vector(1,1,0));

	e->gravity = init_vector(0,-0.1,0);
	e->wind = init_vector(-0.01,0,0);

	int i = 0;
	tuple_t *tmp_pos;
	tuple_t *tmp_vel;
	while(p->position->y >= 0)
	{
		p.position = add_tup(*p->position,*p->velocity)
		*p->velocity =

		printf("%f %f %f\n",p->position->x,p->position->y,p->position->z);
		i++;
	}
	printf("Total ticks: %d\n",i);

	return(exit_code);
}
