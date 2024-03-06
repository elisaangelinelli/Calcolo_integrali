/** \file main.c
	\brief Numeric integration of a polynomial
	\author Elisa Angelinelli

	Version without the functions 
*/

/*! \mainpage 
 *
 * \section intro_sec Introduction
 *
 * This is a software in C language for calculating numerical integration by adopting different techniques
 *
 * \section install_sec Installation
 *
 * 
 *
 * etc...
 */

#include <stdio.h> 
#include <stdlib.h> 
#include <string.h>
#include "mathf.h"

/*! \brief the main function
		
	here we define the polynomial, set the integration range and set the number of equally spaced intervals in which the range should be divided 
	the points delimiting the intervals are defined and then the integration is finalized 
	
*/
int main() {

	/* setting all the parameters */
	float fcoeff[4] = {-10.0,1.0,0.0,2.0};	/* the polynomial */
	float fcoeff_2[8] = {12.0, 14.0, 0.0, 1.0, 8.0, 2.0, 3.0, 10.0};
	float fcoeff_3[6] = {2.0, 4.0, 6.0, 8.0, 7.0, 5.0};
	float xmin = 0.0; 						/* the integration range */ 
	float xmax= 5.0; 	
	//float xmin_2 = ;
	//float xmax = ;				
	int intervals = 1000; 					/* number of equally spaced intervals */ 
	
	
	float integ1, integ2;
	
	int i; 
	float in = xmin;
	float gap = (xmax-xmin)/(float)intervals;
	float* fvalues = NULL;
	float* fvalues_2 = NULL;
	float* fvalues_3 = NULL;
	
	/* this array will store the (steps+1) values of the polynomial that are delimiting the equally spaced intervals*/
	fvalues = (float*)malloc(sizeof(float)*(intervals+1)); /*ricordare di controllare che sia stato creato nel giusto modo e messaggio d'errore sensato*/
	if (fvalues == NULL) {
		printf("\nERROR: cannot allocate memory\n");
		exit(-1);
	}

	/* to get the value of the polynomial at the different points that are delimiting the intervals */
	for (i=0; i<=intervals; i++) {
		fvalues[i] = Polynomial(fcoeff,4,in);
		in += gap;
	}

	/* this array will store the (steps+1) values of the polynomial that are delimiting the equally spaced intervals*/
	fvalues_2 = (float*)malloc(sizeof(float)*(intervals+1)); /*ricordare di controllare che sia stato creato nel giusto modo e messaggio d'errore sensato*/
	if (fvalues_2 == NULL) {
		printf("\nERROR: cannot allocate memory\n");
		exit(-1);
	}

	/* to get the value of the polynomial at the different points that are delimiting the intervals */
	for (i=0; i<=intervals; i++) {
		fvalues_2[i] = Polynomial(fcoeff,8,in);
		in += gap;
	}

	/* this array will store the (steps+1) values of the polynomial that are delimiting the equally spaced intervals*/
	fvalues_3 = (float*)malloc(sizeof(float)*(intervals+1)); /*ricordare di controllare che sia stato creato nel giusto modo e messaggio d'errore sensato*/
	if (fvalues_3 == NULL) {
		printf("\nERROR: cannot allocate memory\n");
		exit(-1);
	}

	/* to get the value of the polynomial at the different points that are delimiting the intervals */
	for (i=0; i<=intervals; i++) {
		fvalues_3[i] = Polynomial(fcoeff,6,in);
		in += gap;
	}
	
	integ1= 0.; 
	integ2= 0.;

	/* to compute the integral according to the rectangular rule */
	Rectangular(fvalues,intervals+1,gap,&integ1,&integ2);
	printf("\nRectangular rule - The integral between %f and %f is in the interval: [%f,%f]\n", xmin,xmax,integ1,integ2);
	
	/* to compute the integral according to the trapezoidal rule */
	integ1 = Trapezoidal(fvalues,intervals+1,gap);
	printf("\nTrapezoidal rule - The integral between %f and %f is : %f\n", xmin,xmax,integ1);
	
	printf("\nSecond try.");
	/* to compute the integral according to the rectangular rule */
	Rectangular(fvalues_2,intervals+1,gap,&integ1,&integ2);
	printf("\nRectangular rule - The integral between %f and %f is in the interval: [%f,%f]\n", xmin,xmax,integ1,integ2);
	
	/* to compute the integral according to the trapezoidal rule */
	integ1 = Trapezoidal(fvalues_2,intervals+1,gap);
	printf("\nTrapezoidal rule - The integral between %f and %f is : %f\n", xmin,xmax,integ1);

	printf("\nThird try.");
	/* to compute the integral according to the rectangular rule */
	Rectangular(fvalues_3,intervals+1,gap,&integ1,&integ2);
	printf("\nRectangular rule - The integral between %f and %f is in the interval: [%f,%f]\n", xmin,xmax,integ1,integ2);
	
	/* to compute the integral according to the trapezoidal rule */
	integ1 = Trapezoidal(fvalues_3,intervals+1,gap);
	printf("\nTrapezoidal rule - The integral between %f and %f is : %f\n", xmin,xmax,integ1);
	
	/* deallocation */
	if (fvalues != NULL)
		free(fvalues);
	/* deallocation */
	if (fvalues_2 != NULL)
		free(fvalues_2);
	/* deallocation */
	if (fvalues_3 != NULL)
		free(fvalues_3);

	return 0;
}