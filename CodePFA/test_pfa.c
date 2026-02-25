/******************************************************/
/* Program to run and test the integration functions. */
/* Creation date: 31 July, 2025                       */
/******************************************************/

#include "pfa.h"

/* Code here anything you want to test your pfa functions and to show your numerical results */
int main()
{
	Option *option = malloc(sizeof(Option));
	option->type = 0;
	option->S0 = 100;
	option->T = 2;
	option->mu = 0.05;
	option->K = 100;
	option->sig = 0.02;
	init_integration("gauss3", 0.1);

	double a = optionPrice(option);
	printf("%lf\n", a);
	return 0;
}
