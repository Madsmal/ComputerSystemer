#include "filters.h"
int lowBuffY[2] = {0};
int lowBuffX[12] = {0};

int highBuffY = 0;
int highBuffX[32] = {0};

int deriBuffX[4] = {0};

int mwiBuffX[30] = {0};

int lowPassFilter(int x)
{


	int yn;

	yn = 2*lowBuffY[0] - lowBuffY[1]	 + ((x-(2*lowBuffX[5])+lowBuffX[11])/32);


	for(int i = 11; i >= 1; i--){
		lowBuffX[i] = lowBuffX[i-1];

	}
	lowBuffX[0] = x;

	lowBuffY[1] = lowBuffY[0];
	lowBuffY[0] = yn;

	return yn;


	}
int highPassFilter(int x) {

	int yn;


	yn = highBuffY - (x/32) + highBuffX[15] - highBuffX[16] + (highBuffX[31]/32);

	for (int i = 31; i >= 1; i--){
		highBuffX[i] = highBuffX[i-1];
	}
	highBuffX[0] = x;
	highBuffY = yn;
	for (int i = 0;i<12;i++){

		 }

	return yn;
}

int derivativeFilter(int x) {

		int yn;

		yn = (2*x+deriBuffX[0]-deriBuffX[2]-2*deriBuffX[3])/8;

		for (int i = 3; i >= 1; i--){
			deriBuffX[i] =deriBuffX[i-1];
		}
		deriBuffX[0] = x;

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

	return sum/N;

}
