/*
 ============================================================================
 Name        : AstroDynParallax.c
 Author      : Jakub Samek
 Version     : 5.0
 Copyright   : Your copyright notice
 Description : Program calculate Binary star parameters with specified accuracy
               - input type and range check
               - structure reorder (.h file)
               - temp_converg function introduction shows correctness of while cycle
               - print_output function introduction
               - comments corrections
 ============================================================================
 */

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#include "AstroDynParallax.h"

float accuracy;

int main(void) {

  float h;
  float accuracy_threshold;
  float area_part;
  float area_full;
  float time_cycle;
  float a_au;
  DynParallaxResults dyn_params;

  float time_observation = 11;
  float a = 4.5;
  float b = 3.4;

  printf("CONST_SUN_MASS = %.3e[kg] \n", CONST_SUN_MASS);
  printf("CONST_SUN_MAGNITUDE = %f \n", CONST_SUN_MAGNITUDE);
  printf("CONST_SUN_LUMINOSITY = %.3e[W] \n", CONST_SUN_LUMINOSITY);

  h = sqrt(pow(a, 2) - pow(b, 2));
  printf("Eccentricity: %.4f\n", h);

  // Compute area part
  area_part = a*b*(acos(h / a) - ((h / pow(a, 2)) * sqrt(pow(a, 2) - pow(h, 2))));
  printf("Area part: %.4f\n", area_part);

  // Compute area full
  area_full = a*b*M_PI;
  printf("Area full: %.4f\n", area_full);

  // Compute cycle time
  time_cycle = time_observation*area_full/area_part;
  printf("Time of one cycle: %.4f[years]\n", time_cycle);

  // Compute semi-major-axis
  a_au = pow((2*pow(time_cycle, 2)), (1.0/3.0));
  printf("a_au: %.4f[au]\n", a_au);

  printf("Enter a accuracy threshold in range (0.01 - 100.0): ");
  // Checking if the input is a valid floating-point number
  if (scanf("%f", &accuracy_threshold) == 1) {
	  // Checking if the input is in range 0.01 - 100.0
    if ((accuracy_threshold >= 0.009) && (accuracy_threshold <= 100.0)) {
  	}
    else
    {
	  printf("Invalid input: %.2f is out of range.\n", accuracy_threshold);
	  return 1;  // Exit with error code
	}
  }
  else
  {
    printf("Invalid input! Please enter a valid floating-point number.\n");
	return 1;  // Exit with error code
  }

  dyn_params.a = a;
  dyn_params.a_au = a_au;
  dyn_params.time_cycle = time_cycle;
  dyn_params.mag1_rel = 3.9;
  dyn_params.mag2_rel = 5.3;
  //precondition mass1 = 1 + mass2 = 1 => mass_summ = 2
  dyn_params.mass_sum = 2;
  dyn_params.itteration = 0;

  // first call of function calc_dyn_parallax
  dyn_params = calc_dyn_parallax(dyn_params);

  // first calculation of accuracy
  accuracy = accuracy_calculation (dyn_params.mass_sum, dyn_params.mass_sum_prev);
  printf("Accuracy calc: %lf[%]\n", accuracy);

  //
  while (accuracy >= accuracy_threshold) {

    dyn_params = calc_dyn_parallax (dyn_params);

    accuracy = accuracy_calculation (dyn_params.mass_sum, dyn_params.mass_sum_prev);
    printf("Accuracy = %f[%]\n", accuracy);

  }

  printf("Accuracy %f[%] achieved in Iterations %d \n", accuracy, dyn_params.itteration);

  return 0;
}

float accuracy_calculation (float m, float m_prev)
{
	float accuracy;
	accuracy = 100*fabs((m_prev - m) / m_prev);
	return accuracy;
}

DynParallaxResults calc_dyn_parallax (DynParallaxResults dyn_params)
{
  dyn_params.itteration++;

  dyn_params.a_degrees = ((dyn_params.a/60.0)/60.0);
  dyn_params.a_radians = dyn_params.a_degrees*M_PI/180.0;

  dyn_params.distance_au = dyn_params.a_au/(tan(dyn_params.a_radians));
  dyn_params.distance_pc = dyn_params.distance_au*4.8*pow(10, -6);
  //printf("Distance: %lf [pc]\n", dyn_params.distance_pc);

  dyn_params.mag1_abs = dyn_params.mag1_rel + 5 - (5 * log10(dyn_params.distance_pc));
  dyn_params.mag2_abs = dyn_params.mag2_rel + 5 - (5 * log10(dyn_params.distance_pc));
  //printf("mag1_abs: %lf \n", dyn_params.mag1_abs);
  //printf("mag2_abs: %lf \n", dyn_params.mag2_abs);

  dyn_params.L1 = CONST_SUN_LUMINOSITY*pow(10, ((dyn_params.mag1_abs - CONST_SUN_MAGNITUDE))/-2.5);
  dyn_params.L2 = CONST_SUN_LUMINOSITY*pow(10, ((dyn_params.mag2_abs - CONST_SUN_MAGNITUDE))/-2.5);
  //printf("L1: %.4e [W]\n", dyn_params.L1);
  //printf("L2: %.4e [W]\n", dyn_params.L2);

  dyn_params.mass1 = CONST_SUN_MASS*pow((dyn_params.L1/CONST_SUN_LUMINOSITY), (1.0/3.5));
  dyn_params.mass2 = CONST_SUN_MASS*pow((dyn_params.L2/CONST_SUN_LUMINOSITY), (1.0/3.5));
  //printf("mass1: %.4e \n", dyn_params.mass1);
  //printf("mass2: %.4e \n", dyn_params.mass2);

  dyn_params.mass_sum_prev = dyn_params.mass_sum;
  dyn_params.mass_sum = (dyn_params.mass1/CONST_SUN_MASS) + (dyn_params.mass2/CONST_SUN_MASS);
  //printf("mass_summ: %f \n", dyn_params.mass_sum);

  print_output (dyn_params);

  dyn_params.a_au = pow((dyn_params.mass_sum*(pow(dyn_params.time_cycle,2.0))),(1.0/3.0));

  return dyn_params;
}

void print_output (DynParallaxResults dyn_params)
{
  printf("----------------------------------------------------------------------------------------- \n");
  printf("iteration = %i; a_au = %f[au]; distance = %f[pc]; mag1_abs = %.4f; mag2_abs = %.4f; mass1 = %.4e[kg]; mass2 = %.4e[kg]; \n", dyn_params.itteration, dyn_params.a_au, dyn_params.distance_pc, dyn_params.mag1_abs, dyn_params.mag2_abs, dyn_params.mass1, dyn_params.mass2);
}

