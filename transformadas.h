#ifndef TRANSFORMADAS_H
#define TRANSFORMADAS_H

#include <math.h>

double*    transformada_inversa(double complex * ck, int N);
double complex * transformada_direta (double * F_xj, int N);
double complex * fftrec (double complex * c, double complex *f, int N, bool dir);

#endif /* TRANSFORMADAS_H */

