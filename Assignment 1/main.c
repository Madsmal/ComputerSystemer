#include "sensor.h"
#include "filters.h"
#include "qsr.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// Værdier defineres

int yBufferArr[12]={0};
int xBufferArr[12]={0};
int myIndex = 0;
int timeCounter = 0;
float timeInMiliSec = 0;
int finalData[3];

// Køretiden for programmet er markeret som kommentar, da vi ikke vil have, at den skal vise det hver gang programmet kører.
// Køretiden står i rapporten.


// clock_t start, end;
// double cpu_time_used;




int main()
{
	// Bruges til køretid:
	// start = clock();


	// Filen læses - defineret i sensor.c
	FILE *file;
	file = openfile("ECG.txt");

	int x;
	int lowPassY;
	int highPassY;
	int derivY;
	int squareY;
	finalData[3] = 0;


	// Kører filen igennem til sidste datapunkt
	while (!feof(file)){


		x = getNextData(file);
		lowPassY = lowPassFilter(x);
		highPassY = highPassFilter(lowPassY);
		derivY = derivativeFilter(highPassY);
		squareY = squarePass(derivY);

		for(int i=2;i>0;i--){
			finalData[i]=finalData[i-1];

		}
		finalData[0]= mwiPass(squareY);

		// Hvis myIndex er større end lig med 3, så sendes data og tid videre til peakDetection i qsr.c
		if (myIndex >= 3) {
			peakDetection(finalData, timeInMiliSec);
		}

		myIndex++;

		timeCounter++;
		timeInMiliSec = timeCounter/2.5;


	}
	// Til køretid
	// end = clock();
	// cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;
	// printf("%f\n",cpu_time_used);


	return 0;
}
