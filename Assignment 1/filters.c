#include "filters.h"

// Feel free to change return statement and arguments
int lowPassFilter(int x)
{


	i = i+1;
	yBufferArr[i] = 2*yBufferArr[((i-1)+11)%12] - yBufferArr[(i-2+11)%12] + (1/32)*(xBufferArr[(i+11)%12]-
			2*xBufferArr[(i-6+11)%12]+xBufferArr[(i-12+11)%12]);
	return 2*yBufferArr[((i-1)+11)%12] - yBufferArr[(i-2+11)%12] + (1/32)*(xBufferArr[(i+11)%12]-
				2*xBufferArr[(i-6+11)%12]+xBufferArr[(i-12+11)%12]);

	}
int highPassFilter(int x){

}
