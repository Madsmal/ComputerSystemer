#include "qsr.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "filters.h"

int peaksTime[24] = {0};
int peaksValue[24] = {0};
int RpeakTime[8] = {0};
int RpeakValue[8] = {0};
int counter = 0;
int counter1 = 0;
int threshold1 = 0;
int threshold2 = 0;
int NPKF = 0;
int SPKF = 2500;
int RR = 0;
int RR_missCounter = 0;
int RRaverage2 = 0;
int RR_low = 0;
int RR_high = 0;
int RR_miss = 0;

void peakDetection(int *mwiBuffY, int timeInMiliSec) {

	if ((mwiBuffY[0]>mwiBuffY[2])&&(mwiBuffY[0]>mwiBuffY[1])) {

		peaksValue[counter] = mwiBuffY[0];
		peaksTime[counter] = timeInMiliSec;


	}

	RR = (peaksTime[counter] - peaksTime[((counter+23)%24)]);
	 //printf("%d\n",RR);

	if (peaksValue[counter] < threshold1) {
		NPKF = peaksValue[counter] / 8 + (7 * NPKF) / 8;
		threshold1 = NPKF + (SPKF - NPKF) / 4;
		threshold2 = threshold1 / 2;

	}

	int sum = peaksTime[counter]+peaksTime[((counter+23)%24)]+peaksTime[((counter+22)%24)]+peaksTime[((counter+21)%24)]
																+peaksTime[((counter+20)%24)]+peaksTime[((counter+19)%24)]+peaksTime[((counter+18)%24)]+peaksTime[((counter+17)%24)];
	int RRaverage1 =sum/8;
	int Rsum = RpeakTime[counter]+RpeakTime[((counter+7)%8)]+RpeakTime[((counter+6)%8)]+RpeakTime[((counter+5)%8)]
																										+RpeakTime[((counter+4)%8)]+RpeakTime[((counter+3)%8)]+RpeakTime[((counter+2)%8)]+RpeakTime[((counter+1)%8)];


	// if ((Rsum/8)*0.92 < RR && RR < (Rsum/8)*1.16)

	if ((RR_low < RR && RR < RR_high) || (RR == 0)) {
		RpeakValue[counter1] = peaksValue[counter];
		RpeakTime[counter1] = peaksTime[counter];
		SPKF = peaksValue[counter]/8 + (7*SPKF)/8;
		RRaverage2 = Rsum/8 ;
		RR_low = RRaverage2 * 0.92;
		RR_high = RRaverage2 * 1.16;
		RR_miss = RRaverage2 * 1.66;
		threshold1 = NPKF + (SPKF - NPKF) / 4;
		threshold2 = threshold1 / 2;
		RR_missCounter = 0;

		// printf("%d\n",RpeakValue[counter]);
		printf("%d\n",counter);

	}
	else if (RR > RR_miss){
		RR_missCounter ++;
		if(RR_missCounter >= 5){
			// printf("5 missed RR intervals \n");
		}

		for (int i = counter;i>=counter-7;i--){
			if (peaksValue[i]>threshold2){

				RpeakValue[counter1] = peaksValue[i];
				RpeakTime[counter1] = peaksTime[i];
				SPKF = peaksValue[counter]/8 + (7*SPKF)/8;
				RRaverage1 = Rsum/8 ;
				RR_low = RRaverage1 * 0.92;
				RR_high = RRaverage1 * 1.16;
				RR_miss = RRaverage1 * 1.66;
				threshold1 = NPKF + (SPKF - NPKF) / 4;
				threshold2 = threshold1 / 2;
				printf("daller  %d\n",counter);
				// printf("%d\n",RpeakValue[counter]);
				if (RpeakValue[counter1]<2000){
				// printf("Value of R-peak less than 2000\n");
					printf("diller %d\n",counter);

				}

				}
			break;
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
