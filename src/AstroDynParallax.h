// Conditions against cyclic includes
#ifndef AstroDynParallax_H
#define AstroDynParallax_H

// Constants definition
#define CONST_SUN_MASS 1.989E30
#define CONST_SUN_MAGNITUDE 4.9E0
#define CONST_SUN_LUMINOSITY 3.827E26

// Define a structure to hold multiple return values
typedef struct {
	float a;
	float a_degrees;
	float a_radians;
	float a_au;
	float time_cycle;
	float distance_au;
	float distance_pc;
	float mag1_abs;
	float mag2_abs;
	float L1;
	float L2;
	float mass1;
	float mass2;
	float mag1_rel;
	float mag2_rel;
	float mass_sum;
	float mass_sum_prev;
	int itteration;
} DynParallaxResults;

// Functions prototype
float accuracy_calculation (float m, float m_prev);
void print_output (DynParallaxResults dyn_params);
DynParallaxResults calc_dyn_parallax (DynParallaxResults dyn_params);

#endif
