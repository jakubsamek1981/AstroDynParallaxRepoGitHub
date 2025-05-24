// Conditions against cyclic includes
#ifndef AstroDynParallax_H
#define AstroDynParallax_H

// Constants definition
#define CONST_SUN_MASS 1.989E30
#define CONST_SUN_LUMINOSITY 3.827E26

// Functions prototype
float accuracy_calculation (float m1, float m2, float m1_prev, float m2_prev);
float temp_converg (float m1, float accuracy_threshold);

#endif
