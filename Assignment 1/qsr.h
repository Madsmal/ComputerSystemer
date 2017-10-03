#ifndef QSR_H
#define QSR_H


typedef struct
{
	int SPKF;
	int NPKF;
	int THRESHOLD1;


} QRS_params;


void peakDetection(int *mwiBuffY, int timeInMiliSec);

#endif
