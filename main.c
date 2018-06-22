#include <stdio.h>
#include <stdlib.h>
#include <complex.h>
#include <math.h>
#include <stdbool.h>
#include <string.h>
# include "fftpack4.h"
# include "fftpack4_precision.h"
#include "transformadas.h"
#define PI 3.1415
/*
π * 
 */


int main() {
    
    int mode, teste;
    FILE* sound_data;
    char filepath[100];
    char str[10];
    float ka;
    
    /*INICIALIZACAO DO PROGRAMA*/
    
    printf("O que deseja fazer?\n");
    printf("Testes Iniciais : 0 ; Inserir Manualmente : 1 ; Sons : 2 \n");
    scanf ("%d",&mode);
    if (mode == 0 ) {
        printf("Qual teste deseja realizar?\n");
        printf("Teste A : 0 ; Teste B : 1 ; Teste C : 2");
        scanf("%d",&teste);
        
        printf("------------AUTOMATIZAR TESTES------------------");
        
        return 0;
    }
    
    else if (mode == 1) {
        printf("-----------FAZER INSERCAO MANUAL---------");
        return 1;        
    }
    
    else {
        printf("--------ARQUIVOS DE SOM-----------\n");
        
        printf("Digite o caminho do arquivo .dat a ser lido\n");
        scanf("%s",filepath);
        
        sound_data = fopen(filepath, "r");
        
        rewind(sound_data);
        
        fscanf(sound_data, "%s", str);
        ka = atof (str);
        printf("%f", ka);
        
        
        return 2;
        
    }
    
    
     int N;
    /*NUMERO DE PONTOS TABELADOS*/
    printf("Valor de N : ");
    scanf("%d", &N);
    
    /*INICIALIZACAO DE VARIAVEIS*/
   
    double  F_xj[2*N];        /*Vetor f usado na fft nao rec*/
    double complex frec[2*N]; /*Vetor f usado na fftrec*/
    double xj[2*N];
    double complex ck[2*N];
    double complex sum = 0 ;
    int modo;
    int k;
    int j;
    int metodo;
    double * p ;
    double complex * p_rec;
    double complex * q;
    
    double* x;
    double azero;
    int N_fftpack = 2*N;
    int nh = N_fftpack/2;
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
        scanf("%lf", &F_xj[j]);
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
        
      
        /*Obtendo Ck a partir de ak e bk */
        ck[0] = azero + 0*I;
        for (k=1; k< N; k++ ) {
            ck[k] = a[k-1]/2 -I*(b[k-1]/2); 
        }
        
        for (k=N; k<2*N; k++) {
            ck[k] = creal(ck[k-N]) - I*cimag(ck[k-N]);
        }
      
    }
    
    /*PRINTAR OS CK*/  
    for (k = 0; k < 2*N; k++){
        if (metodo == 0 || metodo == 1) {
            
        printf("c%d = (%.2lf, %.2lf) \n",k,creal( *(q+k) ),cimag( *(q+k) ) ); /*ck obtido por recursao ou metodo direto*/
        
        } else {
            
            printf("c%d = (%.2lf, %.2lf)\n",k, creal(ck[k]),cimag(ck[k]) );  /*ck obtido por FFTPACK4*/
          
        }
    }
      /*-------------------------------------------------------------------*/

    
     /*-------------------TRANSFORMADA INVERSA---------------------------*/
    }  else  {   /*TRANSFORMADA INVERSA*/
    
        
        
        /*INICIALIZAR VALORES DE CK*/
        for(k = 0 ; k < 2*N; k++) {
        
        double imag;
        double real;    
        printf("c%d = ",k);
        scanf("%lf %lf", &real, &imag);
        ck[k] = real + I*imag;
        
    }
     
        
        /*METODO DIRETO*/
        if (metodo == 0 ) {
            p = transformada_inversa(ck,N);
        }
        
        /*METODO RECURSIVO*/
        else if (metodo == 1) {
            p_rec = fftrec(frec,ck,N,false);
        }
        
       /*METODO FFTPACK4*/
        else if (metodo == 2) {
            
        wsave = ( double * ) malloc ( ( 3 * N + 15 ) * sizeof ( double ) );
        ifac = ( int * ) malloc ( 8 * sizeof ( int ) );
        azero = creal(ck[0]);
        printf("azero = %.2lf\n",azero);
        for (k=1; k< N; k++) {
            
            a[k-1] = (double) ck[k] + ck[2*N - k]  ;
            b[k-1] = (double) I*(ck[k] - ck[2*N - k]) ;
            printf("a%d = %.2lf ; b%d = %.2lf\n",k,a[k-1],k,b[k-1]);
        }
        
        printf("a1 = %.2lf ; b1 = %.2lf\n",a[0],b[0]);
        ezffti(&N_fftpack,wsave,ifac);  
        ezfftb (&N_fftpack, F_xj, &azero, a, b, wsave, ifac);
                   
        }
        
         for (j=0; j<2*N; j++) {
            if(metodo == 0) {
                printf("F(x%d) = %.2lf\n", j,(*(p+j)) ); /*Print do metodo direto*/
            }
            else if(metodo == 1) {
                printf("F(x%d) = %.2lf\n",j, creal( *(p_rec+j) ) );  /*Print do metodo recursivo*/
            }
            else {
                printf("F(x%d) = %.2lf\n",j, F_xj[j]  ); /*Print do FFTPACK4*/
                
            }
         }
        
        
    }

    
    
  
return 0;
}
