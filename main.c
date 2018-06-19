#include <stdio.h>
#include <stdlib.h>
#include <complex.h>
#include <math.h>
#include <stdbool.h>
# include "fftpack4.h"
# include "fftpack4_precision.h"
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
   
    float  F_xj[2*N];        /*Vetor f usado na fft nao rec*/
    float complex frec[2*N]; /*Vetor f usado na fftrec*/
    float xj[2*N];
    float complex ck[2*N];
    float complex sum = 0 ;
    int modo;
    int k;
    int j;
    int metodo;
    float * p ;
    float complex * p_rec;
    float complex * q;
    
    double* x;
    double azero;
    int N_fftpack = 2*N;
    int nh = N/2;
    double *a = ( double * ) malloc ( nh * sizeof ( double ) );
    double* b = ( double * ) malloc ( nh * sizeof ( double ) );
    double *wsave ;
    int *ifac;
    
 
   /*---------------------------------------*/
    
    printf("TRANSFORMADA : Direta : 0 ; Inversa : 1\n");
    scanf("%d",&modo);
    printf("METODO:  Direto : 0 ; Recursivo : 1 ;  FFTPACK : 2 \n");
    scanf("%d",&metodo);
   
    
    
    /*----------------------TRANSFORMADA DIRETA-------------------------*/
    
    
    if (modo == 0) { 
    
    /*INICIALIZAR VALORES DE F(XJ)*/
    for(j = 0 ; j < 2*N; j++) {
        
        printf("F(X%d) = ",j);
        scanf("%f", &F_xj[j]);
        frec[j] = F_xj[j] + 0*I; /*Inicializa frec a partir de F_xj*/
                  
    }
   
    /*METODO DIRETO*/
    if (metodo == 0) {
        q = transformada_direta(F_xj,N); 
    }
    /*METODO RECURSIVO*/
    else if (metodo == 1){
        q = fftrec(ck,frec,N,true); 
        for (j=0;j<2*N;j++) {       /*Divisao dos valores de fftrec por 2N*/
            q[j] = q[j]/(2*N);
        }
    /*METODO FFTPACK4*/  
    } else if (metodo == 2) {
        wsave = ( double * ) malloc ( ( 3 * N + 15 ) * sizeof ( double ) );
        ifac = ( int * ) malloc ( 8 * sizeof ( int ) );

        ezffti(&N_fftpack,wsave,ifac);  
        ezfftf (&N_fftpack, F_xj, &azero, a, b, wsave, ifac);
        
    }
    
    /*PRINTAR OS CK*/  
    for (k = 0; k < 2*N; k++){
        if (metodo == 0 || metodo == 1) {
            
        printf("c%d = (%.2f, %.2f) \n",k,creal( *(q+k) ),cimag( *(q+k) ) ); /*Impressao dos ck*/
        
        } else {
           printf ( " a0 =  %g\n", azero );
        }
    }
      /*-------------------------------------------------------------------*/

    
     /*-------------------TRANSFORMADA INVERSA---------------------------*/
    }  else  {   /*TRANSFORMADA INVERSA*/
    
        
        
        /*INICIALIZAR VALORES DE CK*/
        for(k = 0 ; k < 2*N; k++) {
        
        float imag;
        float real;    
        printf("c%d = ",k);
        scanf("%f %f", &real, &imag);
        ck[k] = real + I*imag;
    }
        if (metodo == 0 ) {
            p = transformada_inversa(ck,N);
        }
        else {
            p_rec = fftrec(frec,ck,N,false);
        }
         for (j=0; j<2*N; j++) {
            if(metodo == 0) {
                printf("F(x%d) = %.2f\n", j,(*(p+j)) ); /*Print do metodo direto*/
            }
            else {
                printf("F(x%d) = %.2f\n",j, creal( *(p_rec+j) ) );  /*Print do metodo recursivo*/
            }
         }
        
        
    }

    
    
    
return 0;
}
