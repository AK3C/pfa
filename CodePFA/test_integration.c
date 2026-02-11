/******************************************************/
/* Program to run and test the integration functions. */
/* Creation date: 31 July, 2025                       */
/******************************************************/

#include "integration.h"

#include <math.h>



double f(double t)
{
return t*t;
}

/* Code here everything you need to test the integration methods and show your numericzal results */

int main()
{
	QuadFormula qf;
	double I1, I2, I3;
	setQuadFormula(&qf, "left");
	I1 = integrate(f, 0, 1, 100, &qf);
	setQuadFormula(&qf, "right");
	I2 = integrate(f, 0, 1, 100, &qf);
	setQuadFormula(&qf, "middle");
	I3 = integrate(f, 0, 1, 100, &qf);
	
	printf("%f, %f, %f", I1, I2, I3);
	return 0;
}





