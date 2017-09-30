#include "sensor.h"
#include "filters.h"
#include "qsr.h"
#include <stdio.h>
#include <stdlib.h>


	int yBufferArr[12]={0};
	int xBufferArr[12]={0};
	int myIndex = 0;
	int timeCounter = 0;
	int timeInMiliSec = 0;
	int finalData[3];

// Main function for organizing the program execution.
// The functions and object predefined are just for inspiration.
// Please change orden,names arguments to fit your solution.

int main()
{	

  //  QRS_params qsr_params;       // Instance of the made avaiable through: #include "qsr.h"
	FILE *file;                  // Pointer to a file object
	file = openfile("ECG.txt");

	int x;
	int lowPassY;
	int highPassY;
	int derivY;
	int squareY;
	finalData[3] = 0;


    //getNextData(file);          // Read Data from Sensor
    while (!feof(file)){
    	x = getNextData(file);
    	lowPassY = lowPassFilter(x);
    	// printf("%d\n",lowPassY);
    	highPassY = highPassFilter(lowPassY);
    	derivY = derivativeFilter(highPassY);
    	squareY = squarePass(derivY);
    	// printf("Reads first while \n");

    		for(int i=2;i>0;i--){
    			finalData[i]=finalData[i-1];

    		}
    		finalData[0]= mwiPass(squareY);

    	// while (myIndex < 3){
    	if (myIndex >= 3) {
    	peakDetection(myIndex, finalData, timeInMiliSec);
    		// printf("%d\n",finalData[myIndex]);

    	}

    	myIndex++;
    	// }
    	// printf("Done with while 2 %d\n");

    	timeCounter++;
    	timeInMiliSec = timeCounter/2.5;

    }



	return 0;
}
