#include "qsr.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "filters.h"

int peaksTime[24] = { 0 };
int peaksValue[24] = { 0 };
int RpeakTime[8] = { 0 };
int RpeakValue[8] = { 0 };
int counter = 0;
int counter1 = 0;
int threshold1 = 0;
int threshold2 = 0;
int NPKF = 0;
int SPKF = 2500;
int RR = 0;

void peakDetection(int myIndex, int *mwiBuffY, int timeInMiliSec) {
	printf("Peak-ish\n");
	if ((mwiBuffY[myIndex - 1] < mwiBuffY[myIndex]) && (mwiBuffY[myIndex] > mwiBuffY[myIndex + 1])) {
		peaksValue[counter] = mwiBuffY[myIndex];
		peaksTime[counter] = timeInMiliSec;
	}


	RR = (peaksTime[counter] + peaksTime[counter - 1]) / 2;
// if (peaksValue[counter] > threshold1) {
// }
	if (peaksValue[counter] < threshold1) {
			NPKF = peaksValue[counter] / 8 + (7 * NPKF) / 8;
			threshold1 = NPKF + (SPKF - NPKF) / 4;
			threshold2 = threshold1 / 2;

	}

	int sum = 0;
	for (int i = 7;i>=1;i--){
		sum = sum + (peaksTime[i]-peaksTime[i-1]);
	}
	int RRaverage1 =sum/8;
	int Rsum = 0;
	for (int i = 7;i>=1;i--){
			Rsum = Rsum + (RpeakTime[i]-RpeakTime[i-1]);
		}


	int RRaverage2 = 0;
	int RR_low = 0;
	int RR_high = 0;
	int RR_miss = 0;

	if (RR_low < RR && RR < RR_high) {
			RpeakValue[counter] = peaksValue[counter];
			RpeakTime[counter] = peaksTime[counter];
			SPKF = peaksValue[counter]/8 + (7*SPKF)/8;
			RRaverage2 = Rsum/8 ;
			RR_low = RRaverage2 * 0.92;
			RR_high = RRaverage2 * 1.16;
			RR_miss = RRaverage2 * 1.66;
			threshold1 = NPKF + (SPKF - NPKF) / 4;
			threshold2 = threshold1 / 2;


	}
	else if (RR > RR_miss){
		// Implement Searchback here
		for (int i = counter;i>=counter-7;i--){
			if (peaksValue[i]>threshold2){
							printf("Hejsa\n");
							RpeakValue[counter] = peaksValue[i];
							RpeakTime[counter] = peaksTime[i];
							SPKF = peaksValue[counter]/8 + (7*SPKF)/8;
							RRaverage1 = Rsum/8 ;
							RR_low = RRaverage1 * 0.92;
							RR_high = RRaverage1 * 1.16;
							RR_miss = RRaverage1 * 1.66;
							threshold1 = NPKF + (SPKF - NPKF) / 4;
							threshold2 = threshold1 / 2;
							if (RpeakValue[counter]<2000){
								printf("Value less than 2000\n");
							}
							break;
			}
		}

	}
	if (counter < 23) {
		counter++;

	} else if (counter == 23) {
		counter = 0;
	}

	if (counter1 < 7) {
		counter1++;

	} else if (counter1 == 7) {
		counter1 = 0;
	}
}
