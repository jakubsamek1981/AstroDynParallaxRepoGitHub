/*
 ============================================================================
 Name        : AstroDynParallax.c
 Author      : Jakub Samek
 Version     : 3.0
 Copyright   : Your copyright notice
 Description : Program calculate Binary star parameters with specified accuracy
               - input type and range check
               - structure reorder (.h file)
               - temp_converg function introduction shows correctness of while cycle
 ============================================================================
 */

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#include "AstroDynParallax.h"

float accuracy = 2.0;

int main(void) {

  float h;
  float m1;
  float m2;
  float accuracy_threshold;

  float m1_prev = 1;
  float m2_prev = 1;

  double previousValue = 1.0, currentValue = 2.0;


  float a = 4.5;
  float b = 3.4;

  int iteration = 0;

  printf("The mass of the Sun is approximately %.3e kg.\n", CONST_SUN_MASS);

  h = sqrt(pow(a, 2) - pow(b, 2));
  printf("Eccentricity: %.4f\n", h);


  printf("Enter a accuracy threshold in range (0.1 - 100.0): ");

  // Checking if the input is a valid floating-point number
  if (scanf("%f", &accuracy_threshold) != 1) {
    printf("Invalid input! Please enter a valid floating-point number.\n");
    return 1;  // Exit with error code
  }
  // Checking the input is in range 0.1 - 100.0
  if (accuracy_threshold < 0.1f && accuracy_threshold > 100.0f)
  {
    printf("Accuracy threshold is out of range 0.1 - 100.0 \n");
  }

  m1 = temp_converg (m1_prev, accuracy_threshold);

  accuracy = accuracy_calculation (m1, 5.5, m1_prev, 2.2);
  printf("Accuracy calc: %lf\n", accuracy);

  while (accuracy >= accuracy_threshold) {

	iteration++;

	m1_prev = m1;
    m1 = temp_converg (m1_prev, accuracy_threshold);

    accuracy = accuracy_calculation (m1, 5.5, m1_prev, 2.2);
    printf("Iteration %d: Accuracy = %f\n", iteration, accuracy);

  }

  printf("Accuracy %f achieved in Iterations %d \n", accuracy, iteration);

  return 0;
}

float accuracy_calculation (float m1, float m2, float m1_prev, float m2_prev)
{
	float accuracy;
	accuracy = 100*fabs((m1_prev - m1) / m1_prev);
	return accuracy;
}

float temp_converg (float m, float accuracy_threshold)
{
	m = (m * 0.9) + (accuracy_threshold*0.5);
	return m;
}
