#ifndef FILTERS_H
#define FILTERS_H


// Hvert filter defineres, så de kan bruge i filters.c
int lowPassFilter(int x);
int highPassFilter(int lowPassFilter);
int derivativeFilter(int highPassFilter);
int squarePass(int derivativeFilter);
int mwiPass(int squarePass);




#endif
