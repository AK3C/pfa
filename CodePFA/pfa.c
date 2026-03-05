

// #define GRAPHIC

#define PFA_C

#include "pfa.h"

#include "integration.h"


/* Initialize the integration variables.
   Arguments :
   - quadrature : name of the quadrature formula that will be used. It can be "left", "right", 
     "middle", "trapezes", "simpson", "gauss2" or "gauss3".
   - dt : a positive value, which will be used to decide the number of subdivisions of an 
          interval [a,b], when computing the integration.
          The number of subdivisions will be N such that (b-a)/N ~ dt
*/
bool init_integration(char* quadrature, double dt)
{ 
	
	if (dt<0){
		return false;
	}

	bool a = setQuadFormula(&pfaQF, quadrature);
	if (a){
		pfa_dt = dt;
	}
	return a;

}



/* Density of the normal distribution */
double phi(double x)
{
  return 0.398942280401433 * exp( -x*x/2 );
}

/* Cumulative distribution function of the normal distribution */
double PHI(double x)
{
	
	return 1/2. + integrate_dx(&phi, 0, x, pfa_dt, &pfaQF);
}

/* =====================================
   Finance function: price of an option 
*/
double optionPrice(Option* option)
{
  //printf("%d, %lf, %lf, %lf, %lf, %lf\n", option->type, option->S0,option->T, option->mu, option->K, option->sig);
	
	double z0 = (log((option->K) / (option->S0))-(  (option->mu - (pow(option->sig, 2)/2.))   * (option->T) ) )  /  ( (option->sig) * sqrt(option->T) ) ; 
	
	
	if (option->type==0){
		return option->S0 *exp(option->mu * option->T) * PHI(option->sig * sqrt(option->T) - z0) - option->K * PHI(-z0); 
	}
	 
	return -(option->S0 *exp(option->mu * option->T) * PHI( -(option->sig * sqrt(option->T)) + z0) ) + option->K * PHI(z0); 


}



/* ===============================================*/
/* Insurance functions */

/* Probability density function (PDF) of variable X.
   X is the reimbursement in case of a claim from the client.
*/
double clientPDF_X(InsuredClient* client, double x)
{
  if (x <= 0)
  {
    return 0.0;
  }
  double res = (log(x) - client->m) / client->s;
  res = phi(res);
  res *= 1/(client->s * x);
  return res;
  
}


/* Cumulative distribution function (CDF) of variable X.
   X is the reimbursement in case of a claim from the client.
*/
double clientCDF_X(InsuredClient* client, double x)
{
  if (x <= 0)
  {
    return 0.0;
  }
  double res = (log(x) - client->m) / client->s;
  res = PHI(res);
  return res;
}


/* Probability density function (PDF) of variable X1+X2.
   X1 and X2 are the reimbursements of the two claims from the client (assuming there are 
   two claims).
*/
double global_sum;
InsuredClient *global_client;
double g(double t) {
    if (t <= 0 || t >= global_sum) 
    {
        return 0.0;
    }
    return clientPDF_X(global_client, t) * clientPDF_X(global_client, global_sum - t);
}
double clientPDF_X1X2(InsuredClient* client, double x)
{
  if (x <= 0)
  {
    return 0.0;
  }
  global_sum = x;
  global_client = client;
  return integrate_dx(&g, 0, global_sum, pfa_dt, &pfaQF);
  

}


/* Cumulative distribution function (CDF) of variable X1+X2.
   X1 and X2 are the reimbursements of the two claims from the client (assuming there are 
   two claims).
*/
InsuredClient *global_client2;
double global_x2;
#include <stdio.h>
double auxi(double t)
{
  double a = clientPDF_X1X2(global_client2, t);
  printf("t=%lf pdf=%.12e\n", t, a);
  return a;
}
double clientCDF_X1X2(InsuredClient* client, double x)
{
  if (x <= 0)
  {
    return 0.0;
  }
  global_client2 = client;
  global_x2 = x;
  return integrate_dx(&auxi, 0, global_x2, pfa_dt, &pfaQF);
}




/* Cumulative distribution function (CDF) of variable S.
   Variable S is the sum of the reimbursements that the insurance company will pay to client.
*/
double clientCDF_S(InsuredClient* client, double x)
{
  if (x<0)
  {
    return 0.0;
  }
  else if (x == 0)
  {
    return *(client->p);
  }
  return *(client-> p) + *(client-> p + 1) * clientCDF_X(client,x) + *(client-> p + 2) * clientCDF_X1X2(client,x);
}


