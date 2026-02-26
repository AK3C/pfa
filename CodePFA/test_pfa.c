/******************************************************/
/* Program to run and test the integration functions. */
/* Creation date: 31 July, 2025                       */
/******************************************************/

#include "pfa.h"

/* Code here anything you want to test your pfa functions and to show your numerical results */
int main()
{
	Option *option = malloc(sizeof(Option));
	option->type = 1;
	option->S0 = 100;
	option->T = 2;
	option->mu = 0.05;
	option->K = 115;
	option->sig = 0.02;

	InsuredClient *client = malloc(sizeof(InsuredClient));
	client->m = 1;
	client->s = 1;
	client->p = malloc(sizeof(int)*3);
	*(client->p) = 0.9;
	*(client->p+1) = 0.05;
	*(client->p+2) = 0.05;

	init_integration("gauss3", 0.1);

	double a = clientPDF_X(client, 1);
	printf("%lf\n", a);
	return 0;

}

