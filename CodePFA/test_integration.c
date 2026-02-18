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

	qf.wk = malloc(sizeof(double)*4);
	qf.xk = malloc(sizeof(double)*4);
	
	
	setQuadFormula(&qf, "trapezes");
	I1 = integrate(f, 0, 1, 3, &qf);
	setQuadFormula(&qf, "simpson");
	I2 = integrate(f, 0, 1, 3, &qf);
	
	
	setQuadFormula(&qf, "gauss2");
	I3 = integrate(f, 0, 1, 300, &qf);
	
	printf("%f, %f, %f", I1, I2, I3);
	return 0;
}





