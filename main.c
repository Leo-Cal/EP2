#include <stdio.h>
#include <stdlib.h>
#include <complex.h>
#include <math.h>
#include "transformadas.h"
#define PI 3.1415
/*
π * 
 */


int main() {

     int N;
    /*NUMERO DE PONTOS TABELADOS*/
    printf("Valor de N : ");
    scanf("%d", &N);
    
    /*INICIALIZACAO DE VARIAVEIS*/
   
    float F_xj[2*N];
    float xj[2*N];
    float complex ck[2*N];
    float complex sum = 0 ;
    int modo;
    int k;
    int j;
    float * p ;
    float complex * q;
    
 
   /*---------------------------------------*/
    
    printf("Transformada Direta : 0 ; Inversa : 1\n");
    scanf("%d",&modo);
       
    
    if (modo == 0) {  /*TRANSFORMADA DIRETA*/
    
    /*INICIALIZAR VALORES DE F(XJ)*/
     
    for(j = 0 ; j < 2*N; j++) {
        
        printf("F(X%d) = ",j);
        scanf("%f", &F_xj[j]);
                  
    }
    
    q = transformada_direta(F_xj,N);
    
    for (k = 0; k < 2*N; k++){
    
        printf("c%d = (%.2f, %.2f) \n",k,creal( *(q+k) ),cimag( *(q+k) ) );
        
    }
        
    
      
     
    }  else  {   /*TRANSFORMADA INVERSA*/
    
        
        
        /*INICIALIZAR VALORES DE CK*/
        for(k = 0 ; k < 2*N; k++) {
        
        float imag;
        float real;    
        printf("c%d = ",k);
        scanf("%f %f", &real, &imag);
        ck[k] = real + I*imag;
    }
    
         p = transformada_inversa(ck,N);
         
         for (j=0; j<2*N; j++) {
             
             printf("F(x%d) = %.2f\n", j,*(p+j) ); 
         }
        
        
    }

    
    
    
return 0;
}
