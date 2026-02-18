



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
		
		*(qf->wk) = 1;
		*(qf->xk) = 0;
	}
	if (strcmp(name, "right")==0){
		qf->n = 0;
		*(qf->wk) = 1;
		*(qf->xk) = 1;
	}
	if (strcmp(name, "middle")==0){
		qf->n = 0;
		*(qf->wk) = 1;
		*(qf->xk) = 1/2.;
	}
	if (strcmp(name, "trapezes")==0){
		
		qf->n = 1;
		*(qf->wk +0) = 1/2.;
		*(qf->wk +1) = 1/2.;
		*(qf->xk +0) = 0.;
		*(qf->xk +1) = 1.;
	}

	if (strcmp(name, "simpson")==0){
		qf->n = 2;
		*(qf->wk +0) = 1/6.;
		*(qf->wk +1) = 2/3.;
		*(qf->wk +2) = 1/6.;
		*(qf->xk +0) = 0.;
		*(qf->xk +1) = 1/2.;
		*(qf->xk +2) = 1.;
	}

	if (strcmp(name, "gauss2")==0){
		qf->n = 1;
		qf->wk = malloc(sizeof(double)*2);
		qf->xk = malloc(sizeof(double)*2);
		*(qf->wk +0) = 1/6.;
		*(qf->wk +1) = 2/3.;
		double aaa = 2*sqrt(3.);
		double aa = 1/aaa;
		*(qf->xk +0) = 1/2. - aa;
		*(qf->xk +1) = 1/2. + aa;
	}
	if (strcmp(name, "gauss3")==0){
		qf->n = 2;
		qf->wk = malloc(sizeof(double)*3);
		qf->xk = malloc(sizeof(double)*3);
		*(qf->wk +0) = 5/18.;
		*(qf->wk +1) = 4/9.;
		*(qf->wk +2) = 5/18.;
		double aa = 1/(2*sqrt(3.));
		*(qf->xk +0) = 1/2. * (1-sqrt(3/5.));
		*(qf->xk +1) = 1/2.;
		*(qf->xk +2) = 1/2. * (1+sqrt(3/5.));
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



	for (int i=0;i<N;i++){

		float inside_sum = 0;
		float ai = a+i*bemoinzasurenne;
		float bi = a+(i+1)*bemoinzasurenne;
		for (int ii=0;ii<(qf->n +1);ii++){
			
			inside_sum += *((qf->wk) +ii) * (f(ai+ *(qf->xk+ii) *(bi-ai)  ));
		}
		sum+=(bemoinzasurenne) * inside_sum;
	}

	return sum;


}

double integrate_dx(double (*f)(double), double a, double b, double dx, QuadFormula* qf)
{
  return 0.0;
}


