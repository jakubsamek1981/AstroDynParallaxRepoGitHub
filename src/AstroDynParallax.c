/*
 ============================================================================
 Name        : AstroDynParallax.c
 Author      : Jakub Samek
 Version     : 2.0
 Copyright   : Your copyright notice
 Description : Program calculate Binary star parameters with specified accuracy
 ============================================================================
 */

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#include "AstroDynParallax.h"

int main(void) {



  double previousValue = 1.0, currentValue = 2.0;
  double accuracy_threshold;

  float a = 4.5;
  float b = 3.4;
  float h;

  h = sqrt(pow(a, 2) - pow(b, 2));
  printf("Result: %.4f\n", h);


  printf("Enter a accuracy threshold in range (0.1 - 100.0): ");
  // Checking if the input is a valid floating-point number
  if (scanf("%lf", &accuracy_threshold) != 1) {
    printf("Invalid input! Please enter a valid floating-point number.\n");
    return 1;  // Exit with error code
  }

  printf("The mass of the Sun is approximately %.3e kg.\n", CONST_SUN_MASS);

  while (fabs((currentValue - previousValue) / currentValue) > accuracy_threshold) {
    previousValue = currentValue;
	currentValue = previousValue / 2.0;  // Example calculation
	printf("Current Value: %lf\n", currentValue);
  }

  printf("Final Accuracy Achieved: %lf\n", fabs((currentValue - previousValue) / currentValue));

  return 0;
}
