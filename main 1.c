/** \file main.c
	\brief Numerical integration of a polynomial
	\author Paolo Gastaldo

	first version of this software
	
*/

#include <stdio.h> 
#include <stdlib.h> 
#include "mathf.h"
#include "struct.h"
#include "io.h"


/*! \brief the main function
		
	here we define the polynomial, set the integration range and set the number of equally spaced intervals in which the range should be divided 
	the points delimiting the intervals are defined and then the integration is finalized 
*/

int main() { 
	FILE* fPTR;
	poly_s pol;
	float x_inf;
	float x_sup;
	int intervals;
	char filePath[100]= "file_config";
	int cf; //variabile per controllare la corretta esecuzion delle funzioni
	float integ1 = 0.;
	float integ2 = 0.;
	int i;
	float in;
	float gap;
	float* fvalues = NULL;

	fPTR = OpenFile(filePath);
	if (fPTR == NULL){
		printf("Error in the main file in the opening of the file");
		exit(-1);
	}

	cf = ReadConfigFile(fPTR, &pol, &x_inf, &x_sup, &intervals);
	if ( cf == -1){
		printf("Error in the main file in the reading of the file");
		exit(-1);
	}

	cf = CloseFile(fPTR);
	if ( cf == -1){
		printf("Error in the main file in the closing of the file");
		exit(-1);
	}

	in = (float)x_inf;
	gap = (float)(x_sup-x_inf)/(float)intervals;
	
	/* this array will store the (steps+1) values of the polynomial that are delimiting the equally spaced intervals*/
	fvalues = (float*)malloc(sizeof(float)*(intervals+1));
	if (fvalues == NULL) {
		printf("\nERROR: cannot allocate memory\n");
		exit(-1);
	}

	/* to get the value of the polynomial at the different points that are delimiting the intervals */
	for (i=0; i<=intervals; i++) {
		fvalues[i] = Polynomial(pol, in);
		in += gap;
	}

	/* to compute the integral according to the rectangular rule */
	Rectangular(fvalues,intervals+1,gap,&integ1,&integ2);
	printf("\nRectangular rule - The integral between %f and %f is in the interval: [%f,%f]\n", x_inf,x_sup,integ1,integ2);
	
	/* to compute the integral according to the trapezoidal rule */
	integ1 = Trapezoidal(fvalues,intervals+1,gap);
	printf("\nTrapezoidal rule - The integral between %f and %f is : %f\n", x_inf,x_sup,integ1);
	
	/* deallocation */
	if (fvalues != NULL)
		free(fvalues);

	if (pol.coeffs != NULL)
		free (pol.coeffs);
	
	return 0;
}