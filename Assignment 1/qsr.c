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
int SPKF = 2250;
int RR = 0;
int RR_missCounter = 0;
int RRaverage2 = 0;
int RR_low = 0;
int RR_high = 0;
int RR_miss = 25;

void peakDetection(int *mwiBuffY, int timeInMiliSec) {

	// Tjekker om der er et peak
	if ((mwiBuffY[1]>mwiBuffY[2])&&(mwiBuffY[0]<mwiBuffY[1])) {

		peaksValue[counter] = mwiBuffY[0];
		peaksTime[counter] = timeInMiliSec;

		RR = (peaksTime[counter] - peaksTime[((counter+23)%24)]);

		// Tjekker om værdierne er under threshold, hvis dette er tilfældet, så sættes en ny threshold.
		if (peaksValue[counter] < threshold1) {
			NPKF = peaksValue[counter] / 8 + (7 * NPKF) / 8;
			threshold1 = NPKF + (SPKF - NPKF) / 4;
			threshold2 = threshold1 / 2;
		}
		// sum og Rsum bestemmes ved brug af circular array. Dette kunne også skrives pænere op med for-loop
		int sum = peaksTime[counter]+peaksTime[((counter+23)%24)]+peaksTime[((counter+22)%24)]+peaksTime[((counter+21)%24)]
																										 +peaksTime[((counter+20)%24)]+peaksTime[((counter+19)%24)]+peaksTime[((counter+18)%24)]+peaksTime[((counter+17)%24)];
		int RRaverage1 =sum/8;
		int Rsum = RpeakTime[counter]+RpeakTime[((counter+7)%8)]+RpeakTime[((counter+6)%8)]+RpeakTime[((counter+5)%8)]
																									  +RpeakTime[((counter+4)%8)]+RpeakTime[((counter+3)%8)]+RpeakTime[((counter+2)%8)]+RpeakTime[((counter+1)%8)];
		// Tjekker om RR værdien er mellem RR_low og RR_high. Første gang denne køres, vil RR_low og RR_high være lig 0
		if (((RR_low < RR) && (RR < RR_high)) || (RR == 0)) {
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

			// Det går noget galt her. Den printer ikke warnings til alle værdier og ændrer på dem
			// if (RpeakValue[counter1]<2000){
			//	printf("Warning! Value of R-peak less than 2000. ");

			//}

			// Hvis der ikke er et peak
		}
		else{
			// Hvis et peak misses 5 gange, så der printes en warning, som der heller ikke printes.
			if (RR>RR_miss){
				RR_missCounter ++;
			}
			if(RR_missCounter >= 5){
				printf("5 missed RR intervals \n");
			}
			int ii = counter;
			// Searchback funktionen implementeres her
			for (int i = 0; i<8;i++){
				if (peaksValue[ii]>threshold2){

					RpeakValue[counter1] = peaksValue[ii];
					RpeakTime[counter1] = peaksTime[ii];
					SPKF = peaksValue[ii]/8 + (7*SPKF)/8;
					RRaverage1 = Rsum/8 ;
					RR_low = RRaverage1 * 0.92;
					RR_high = RRaverage1 * 1.16;
					RR_miss = RRaverage1 * 1.66;
					threshold1 = NPKF + (SPKF - NPKF) / 4;
					threshold2 = threshold1 / 2;

					// Endnu en warning skal printes.
					if (RpeakValue[counter1]<2000){
							printf("Warning! Value of R-peak less than 2000. ");
					}
					ii = (ii+7)%8;
					break;
				}

			}

		}
		// Counters som går fra 0 til 23, og derfor resetter sig selv.
		counter = (counter+1)%24;
		counter1 = (counter1+1)%8;

	}


}
