



#define INTEGRATION_C

#include "integration.h"

bool setQuadFormula(QuadFormula* qf, char* name)
{

	//our code, only updates the name for now

	if (strcmp(name, "left")!=0 && strcmp(name, "right")!=0 && strcmp(name,"middle")!=0 && strcmp(name, "trapezes")!=0 && strcmp(name, "simpson")!=0 && strcmp("gauss2",name)!=0 && strcmp(name,"gauss3")!=0){

		return false;


	}

	int current = 0;
	while (*(name+current)!=0){

		(*qf).name[current] = *(name+current);
		current++;

	}

	if (strcmp(name, "left")==0){
		qf->n = 0;
		qf->wk = malloc(sizeof(double));
		qf->xk = malloc(sizeof(double));
		qf
	}


	(*qf).name[current] = '\0';

	return true;
}

/* This function is not required ,but it may useful to debug */
void printQuadFormula(QuadFormula* qf)
{
  printf("Quadratic formula: %s\n", qf->name);
  /* Print everything else that may be useful */
}


/* Approximate the integral of function f from a to b.
   - f is a pointer to a function pointer
   - a and b are the integration bounds
   - Interval [a,b] is split in N subdivisions [ai,bi]
   - Integral of f on each subdivision [ai,bi] is approximated by the quadrature formula qf.
*/
double integrate(double (*f)(double), double a, double b, int N, QuadFormula* qf)
{
	float sum = 0;
	float bemoinzasurenne = (b-a)/N;

	if (strcmp(qf->name, "left")==0){
		for (int i=0;i<N;i++){
			sum+=f(a+i*bemoinzasurenne) *bemoinzasurenne;
		}
	}
	if (strcmp(qf->name, "right")==0){
		for (int i=1;i<N+1;i++){
			sum+=f(a+(i)*bemoinzasurenne) * bemoinzasurenne;
		}
	}
	if (strcmp(qf->name, "middle")==0){
		for (int i=0;i<N;i++){
			sum+= f( a+  i*bemoinzasurenne + (bemoinzasurenne   )/2 ) *bemoinzasurenne;
		}
	}

	if (strcmp(qf->name, "trapezes")){
		for (int i=0;i<N;i++){
			ai = a+i*bemoinzasurenne;
			bi = a+(i+1)*bemoinzasurenne;

		}
	}
	if (strcmp(qf->name, "simpson")){

	}
	if (strcmp(qf->name, "gauss2")){
		
	}
	if (strcmp(qf->name, "gauss3")){

	}
	
	return sum;
	return 0.0;
}

double integrate_dx(double (*f)(double), double a, double b, double dx, QuadFormula* qf)
{
  return 0.0;
}


