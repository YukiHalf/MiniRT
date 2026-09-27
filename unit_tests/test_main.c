#include "test_lib.h"


int main(int argc, char** argv)
{
	int exit_code;
	float *p;
	float *p1;
	float *sumAr;
	float epsilon;

	epsilon = (float)1 / 1048576;

	p = create_arr(3,2,1,0);
	p1= create_arr(5,6,7,1);


	exit_code = 0;

	sumAr = add_arrs(p,p1);

	printf("%f %f %f %f\n",sumAr[0],sumAr[1],sumAr[2],sumAr[3]);
	free(sumAr);
	sumAr = subst_arr(p,p1);
	printf("%f %f %f %f\n",sumAr[0],sumAr[1],sumAr[2],sumAr[3]);
	free(p);
	free(p1);
	nega_arr(sumAr);
	printf("%f %f %f %f\n",sumAr[0],sumAr[1],sumAr[2],sumAr[3]);
	norm_arr(sumAr);
	printf("%f %f %f %f\n",sumAr[0],sumAr[1],sumAr[2],sumAr[3]);
	printf("%f\n",magn_arr(sumAr));
	free(sumAr);
	return(exit_code);
}
