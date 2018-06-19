#ifndef TRANSFORMADAS_H
#define TRANSFORMADAS_H

#include <math.h>

float*    transformada_inversa(float complex * ck, int N);
float complex * transformada_direta (float * F_xj, int N);
float complex * fftrec (float complex * c, float complex *f, int N, bool dir);

#endif /* TRANSFORMADAS_H */

