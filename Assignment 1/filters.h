#ifndef FILTERS_H
#define FILTERS_H


// Feel free to change return statement and arguments
int lowPassFilter(int x);
int highPassFilter(int lowPassFilter);
int derivativeFilter(int highPassFilter);
int squarePass(int derivativeFilter);
int mwiPass(int squarePass);


// Implement additional filters
 
#endif // FILTERS_H
