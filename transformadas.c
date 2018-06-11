#include <stdio.h>
#include <stdlib.h>
#include <complex.h>
#include <math.h>
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