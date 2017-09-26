#include "filters.h"
int lowBuffY[2] = {0};
int lowBuffX[12] = {0};

int highBuffY = 0;
int highBuffX[32] = {0};

int deriBuffX[4] = {0};

int mwiBuffX[30] = {0};
int mwiBuffY[3] = {0};
// Feel free to change return statement and arguments
int lowPassFilter(int x)
{


	int yn;
	//printf("%d\n",x);
	yn = 2*lowBuffY[0] - lowBuffY[1]	 + ((x-(2*lowBuffX[5])+lowBuffX[11])/32);


	for(int i = 11; i >= 1; i--){
		lowBuffX[i] = lowBuffX[i-1];

	}
	lowBuffX[0] = x;

	lowBuffY[1] = lowBuffY[0];
	lowBuffY[0] = yn;
	// printf("%d\n",yn);
	// for (int i = 0;i<12;i++){
	// printf("%d,",lowBuffX[i]);
	// }
	// printf("\n");
	return yn;

	// i = i+1;
	// yBufferArr[i] = 2*yBufferArr[((i-1)+11)%12] - yBufferArr[(i-2+11)%12] + (1/32)*(xBufferArr[(i+11)%12]-
	//		2*xBufferArr[(i-6+11)%12<]+xBufferArr[(i-12+11)%12]);
	// return 2*yBufferArr[((i-1)+11)%12] - yBufferArr[(i-2+11)%12] + (1/32)*(xBufferArr[(i+11)%12]-
	//			2*xBufferArr[(i-6+11)%12]+xBufferArr[(i-12+11)%12]);

	}
int highPassFilter(int x) {

	int yn;

// printf("x val %d \n", x);
	yn = highBuffY - (x/32) + highBuffX[15] - highBuffX[16] + (highBuffX[31]/32);
	// printf("%d,%d,%d,%d,%d\n",highBuffY,x,highBuffX[15],highBuffX[16],highBuffX[31]);
	// printf("%d\n",yn);
	for (int i = 31; i >= 1; i--){
		highBuffX[i] = highBuffX[i-1];
	}
	highBuffX[0] = x;
	highBuffY = yn;
	for (int i = 0;i<12;i++){
		//printf("%d,",lowBuffX[i]);
		 }
		 //printf("\n");
	return yn;
}

int derivativeFilter(int x) {

		int yn;

		yn = (2*x+deriBuffX[0]-deriBuffX[2]-2*deriBuffX[3])/8;

		for (int i = 3; i >= 1; i--){
			deriBuffX[i] =deriBuffX[i-1];
		}
		deriBuffX[0] = x;
		// printf("%d\n",yn);
		return yn;
}

int squarePass(int x){

	return x*x;

}

int mwiPass(int x){
	int N = 30;
	int sum = x;


	for (int i = 0; i < 30; i++){
		sum = sum + mwiBuffX[i];

	}
	for (int i = 29; i >= 1; i--){
					mwiBuffX[i] = mwiBuffX[i-1];
	}

	mwiBuffX[0]=x;
	for(int i=2;i>=1;i--){
		mwiBuffY[i]=mwiBuffY[i+1];
	}
	mwiBuffY[0]=sum/N;

	// printf("%d\n",sum/N);
	return sum/N;

}
