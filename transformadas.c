#include <stdio.h>
#include <stdlib.h>
#include <complex.h>
#include <math.h>
#include <stdbool.h>
#include "transformadas.h"
#define PI 3.1415


float* transformada_inversa(float complex* ck, int N) {


    
    int k;
    int j;
    
    
    /*INICIALIZAR VALORES F(XJ) E XJ E CK*/
    
    float * F_xj = malloc (sizeof (float) * 2*N);
    float xj[2*N];
    float complex sum = 0 ;
    
    
     for(j = 0 ; j < 2*N; j++) {
        
        xj[j] = j*PI/(float)N;
        
     }
    
    
    
    /*CALCULO DOS F(XJ)*/
    for ( j= 0; j<2*N ; j++) {
        
        for ( k=0; k<2*N; k++) {
            
            sum = sum + ( ck[k]*cexp(I*k*xj[j]) );
        }
        
        F_xj[j] = sum ;
        sum = 0;
 
        
    }

    
    return F_xj;
}


float complex * transformada_direta (float * F_xj, int N) {
    
    int k;
    int j;
    float xj[2*N];
    float complex sum = 0 ;
    float complex*  ck = malloc (sizeof(float complex) * 2*N );
    
    
     for(j = 0 ; j < 2*N; j++) {
        
        xj[j] = j*PI/(float)N;
        
     }
         /*CALCULO DOS CK*/
    for ( k= 0; k<2*N ; k++) {
        
        for ( j=0; j<2*N; j++) {
            
            sum = sum + ( F_xj[j]*cexp(-I*k*xj[j]) );
        }
        
        ck[k] = sum/(2*N) ;
        sum = 0;
        
    }
    return ck;
}

float complex * fftrec (float complex * c, float complex *f, int N, bool dir) {
    

   float complex*  even = malloc (sizeof(float complex) *N );
   float complex*  odd = malloc (sizeof(float complex) *N );
   float complex*  fe = malloc (sizeof(float complex) * N );
   float complex*  fo = malloc (sizeof(float complex) *N );

   int j;
   float complex eij;
   
   
   
   if (N == 1) {
       c[0] = f[0] + f[1];
       c[1] = f[0] - f[1];
   }
   else {
       for (j=0; j<N ; j++) {
           
           fe[j] = f[2*j];
           fo[j] = f[2*j + 1];
           even[j] = c[2*j];
           odd[j] = c[2*j + 1];
           
       }
       fftrec(even,fe,N/2,dir);
       fftrec(odd,fo,N/2,dir);
   
       for (j=0; j<N; j++) {
           
           if (dir == true) {
               eij = cexp(-1*I*j*PI/N);
           }
           else {
               eij = cexp(1*I*j*PI/N);
           }
           c[j] = even[j] + eij*odd[j];
           c[j+N] = even[j] - eij*odd[j];
       }
   }
   
   return c;
   
       
   
}
