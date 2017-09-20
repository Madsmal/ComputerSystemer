#include "filters.h"

// Feel free to change return statement and arguments
int lowPassFilter(int x)
{
	int ybuff[2] = {0};
	int xbuff[12] = {0};
	int yn;

	yn = 2*ybuff[0]-ybuff[1] + (1/32)*(x-2*xbuff[5]+xbuff[11]);
	for (int i = 11; i <= 1; i--){
		xbuff[i] = xbuff[i-1];
	}
	xbuff[0] = x;
	ybuff[1] = ybuff[0];
	ybuff[0] = yn;

	return yn;

	// i = i+1;
	// yBufferArr[i] = 2*yBufferArr[((i-1)+11)%12] - yBufferArr[(i-2+11)%12] + (1/32)*(xBufferArr[(i+11)%12]-
	//		2*xBufferArr[(i-6+11)%12<]+xBufferArr[(i-12+11)%12]);
	// return 2*yBufferArr[((i-1)+11)%12] - yBufferArr[(i-2+11)%12] + (1/32)*(xBufferArr[(i+11)%12]-
	//			2*xBufferArr[(i-6+11)%12]+xBufferArr[(i-12+11)%12]);

	}
int highPassFilter(int x) {

	int yn;
	int yn1 = 0;
	int xbuff[32] = {0};

	yn = yn1 - (x/32) + xbuff[15] - xbuff[16] + (xbuff[31]/32);

	for (int i = 31; i <= 1; i--){
			xbuff[i] = xbuff[i-1];
	}
	xbuff[0] = x;
	yn1 = yn;
	return yn;
}

int derivativeFilter(int x) {

		int yn;
		int xbuff[4] = {0};

		yn = (1/8)*(2*x+xbuff[0]-xbuff[2]-2*xbuff[3]);

		for (int i = 3; i <= 1; i--){
				xbuff[i] = xbuff[i-1];
		}
		xbuff[0] = x;

		return yn;
}

int squarePass(int x){

	return x*x;

}

int mwiPass(int x){
	int xbuff[30] = {0};
	int N = 30;
	int sum = 0;

	for (int i = 0; i < 30; i++){
		sum = sum + xbuff[i];
	}
	return sum/N;

}


