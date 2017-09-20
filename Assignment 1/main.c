#include "sensor.h"
#include "filters.h"
#include "qsr.h"
#include <stdio.h>
#include <stdlib.h>


int yBufferArr[12]={0,0,0,0,0,0,0,0,0,0,0,0};
	int xBufferArr[12]={0,0,0,0,0,0,0,0,0,0,0,0};
	int i = 0;

// Main function for organizing the program execution.
// The functions and object predefined are just for inspiration.
// Please change orden,names arguments to fit your solution.

int main()
{	

    QRS_params qsr_params;       // Instance of the made avaiable through: #include "qsr.h"
	FILE *file;                  // Pointer to a file object
	file = openfile("ECG.txt");
	int x;
	int lowPassY;
	int highPassY;
	int derivY;
	int squareY;
	int mwiY;
    //getNextData(file);          // Read Data from Sensor
    while (!feof(file)){
    	x = getNextData(file);
    	lowPassY = lowPassFilter(x);
    	highPassY = highPassFilter(lowPassY);
    	derivY = derivativeFilter(highPassY);
    	squareY = squarePass(derivY);
    	mwiY = mwiPass(squareY);
    	i++;
    }
    lowPassFilter();            // Filter Data
                                
    peakDetection(&qsr_params); // Perform Peak Detection

	return 0;
}
