/*
 ============================================================================
 Name        : AstroDynParallax.c
 Author      : 
 Version     :
 Copyright   : Your copyright notice
 Description : Hello World in C, Ansi-style
 ============================================================================
 */

#include <stdio.h>
#include <stdlib.h>

int main(void) {
  double previousValue = 1.0, currentValue = 2.0;
  double accuracy_threshold;

  printf("Enter a accuracy threshold in range (0.1 - 100.0): ");
  // Checking if the input is a valid floating-point number
  if (scanf("%lf", &accuracy_threshold) != 1) {
    printf("Invalid input! Please enter a valid floating-point number.\n");
    return 1;  // Exit with error code
  }



  while (fabs((currentValue - previousValue) / currentValue) > accuracy_threshold) {
    previousValue = currentValue;
	currentValue = previousValue / 2.0;  // Example calculation
	printf("Current Value: %lf\n", currentValue);
  }

  printf("Final Accuracy Achieved: %lf\n", fabs((currentValue - previousValue) / currentValue));

  return 0;
}
