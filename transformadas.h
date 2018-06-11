#ifndef TRANSFORMADAS_H
#define TRANSFORMADAS_H

#include <math.h>

float*    transformada_inversa(float complex * ck, int N);
float complex * transformada_direta (float * F_xj, int N);

#endif /* TRANSFORMADAS_H */

