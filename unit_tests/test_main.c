#include "test_lib.h"


int main(int argc, char** argv)
{
	int exit_code;
	float arr[4] = {3.2,-4.0,1.2,0.0};


	exit_code = 0;

	exit_code = is_tuple(arr);


	return(exit_code);
}