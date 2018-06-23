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
    
    
    /*INICIALIZACAO DE VARIAVEIS*/
    int N;
    int mode;
    int teste;
    FILE* sound_data;
    char filepath[100];
    char str[10];
    float ka;
    double*  F_xj = (double*)malloc (2*N * sizeof(double));        /*Vetor f usado na fft nao rec*/
    double complex* frec = (double complex*) malloc (2*N*sizeof(double complex)); /*Vetor f usado na fftrec*/
    double* xj = (double*) malloc (2*N*sizeof(double));
    double complex* ck = (double complex*) malloc (2*N*sizeof(double complex));
    double complex sum = 0 ;
    int modo;
    int k;
    int j;
    int metodo;
    double * p ;
    double complex * p_rec;
    double complex * q = (double complex*) malloc (2*N*sizeof(double complex));
    double complex * q_rec;
    

    double* x;
    double azero;
    int N_fftpack = 2*N;
    int nh = N_fftpack/2;
    double *a = ( double * ) malloc ( nh * sizeof ( double ) );
    double* b = ( double * ) malloc ( nh * sizeof ( double ) );
    double *wsave ;
    int *ifac;
    
    /*INICIALIZACAO DO PROGRAMA*/
    
    printf("O que deseja fazer?\n");
    printf("Testes Iniciais : 0 ; Inserir Manualmente : 1 ; Sons : 2 \n");
    scanf ("%d",&mode);
    
    if (mode == 0 ) {
        
        printf("------------TESTES INICIAIS------------------\n");
        
        
        printf("Qual teste deseja realizar?\n");
        printf("Teste A : 0 ; Teste B : 1 ; Teste C : 2\n");
        scanf("%d",&teste);
        
        if(teste == 0 ) {
            
            N = 2;
            F_xj[0] = (double) 5;
            F_xj[1] = (double) -1;
            F_xj[2] = (double) 3;
            F_xj[3] = (double) 1;
           
            
        }
        
        else if (teste == 1) {
           
        }
        
        else {
            
        }
                 
    return 0;    
    }
        
       
    
    
    /*********************************************************************/
    /*MODO DE INSERCAO MANUAL*/
    /*********************************************************************/
    else if (mode == 1) {
        printf("-----------INSERCAO MANUAL---------\n");
        
        printf("Digite valor de N :\n");
        scanf("%d",&N);
        
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

        
        
        
        return 1;        
    }
    
    
    else {
       
       
        int sample_rate;
        int channels;
        int ch;
        int A;
        int A2;
        int A1;
        double sum;
        double mean;
        double D;
        double sum_1;
        double sum_2;
        double mean_1;
        double mean_2;
        int A4;
        
        printf("--------ARQUIVOS DE SOM-----------\n");
        
        printf("Digite o caminho do arquivo .dat a ser lido\n");
        scanf("%s",filepath);
        
        
        sound_data = fopen(filepath, "rb");
        //output = fopen("/home/leocal/Desktop/Poli/2018-1/Numérico/EP2/output","w");
        
        /*/home/leocal/Desktop/Poli/2018-1/Numérico/EP2/dados_sons/dog.dat */
        if (sound_data == NULL) {
            printf("ERROR OPENING FILE");
        }
        
        rewind(sound_data);
        
       /*Obter numero de amostras*/
        
        while(!feof(sound_data)) {           
            ch = fgetc(sound_data);
            if(ch == '\n') {
                A++;
            }
        }
        
        rewind(sound_data);
        A = A -2; /*Excluir linhas que nao sao dados*/
        
        printf("Numero de amostras : %d\n",A);
      
        A2 = A;
        A1 = A;
        A2--;
        A2 |= A2 >> 1;
        A2 |= A2 >> 2;
        A2 |= A2 >> 4;
        A2 |= A2 >> 8;
        A2 |= A2 >> 16;
        A2++;
        
        printf("Closest power of 2 to A is : %d\n",A2);
    
        rewind(sound_data);
        
        /*Obter sample rate*/
        fseek(sound_data,14,SEEK_SET);
        fscanf(sound_data, "%d", &sample_rate);
        printf("Sample Rate is : %d\n",sample_rate);
         
       
        /*Obter numero de canais*/
        fseek(sound_data,12,SEEK_CUR);
        fscanf(sound_data, "%d", &channels);
        printf("Number of channels is : %d\n\n",channels);
        
        double* t = ( double * ) malloc ( A2 * sizeof ( double ) );
        double* F_1 = ( double * ) malloc ( A2 * sizeof ( double ) );
        double* F_2 = ( double * ) malloc ( A2 * sizeof ( double ) );
       
       
        
        
        
        /*Caso MONO*/
        /*/home/leocal/Desktop/Poli/2018-1/Numérico/EP2/dados_sons/dog.dat */
        if (channels == 1) { 
            k = 0;
            //OBTENCAO DOS DADOS
            for (k = 0 ; k<A2; k++) {
                if (k>=A) {
                    F_1[k] = mean;
                    t[k] = t[A-1] + (k-A)/(double)sample_rate;
                }
                else {
                fscanf(sound_data,"%lf",&t[k]);
                fscanf(sound_data, "%lf", &F_1[k]);
                
                }
                
                //F_1_rec[k] = F_1[k] + 0*I;
                sum = sum + F_1[k];
                mean = sum/k;
                
                
            }
            
        //-------------------------------------------------
        
            fclose(sound_data);
        }
        
        /*Caso ESTEREO*/
        /*/home/leocal/Desktop/Poli/2018-1/Numérico/EP2/dados_sons/Piano-Sol.dat*/
        if (channels ==2 ) {
            k = 0;
            
            //OBTENCAO DOS DADOS
            for (k = 0 ; k<A2; k++) {
                
                if (k>=A) {
                    F_1[k] = mean_1;
                    F_2[k] = mean_2;
                    t[k] = t[A-1] + (k-A)/(double)sample_rate;
                }
                else {
                fscanf(sound_data,"%lf",&t[k]);
                fscanf(sound_data, "%lf", &F_1[k]);
                fscanf(sound_data, "%lf", &F_2[k]);
                
                
                }
                sum_1 = sum_1 + F_1[k];
                mean_1 = sum_1/k;
                sum_2 = sum_2 + F_2[k];
                mean_2 = sum_2/k;
                
            }
            
        //------------------------------------------------------------------
            
        
        fclose(sound_data);
        
        }
        
        
        /*ESCREVER DADOS EM UM FILE*/
        sound_data = fopen("/home/leocal/Desktop/Poli/2018-1/Numérico/EP2/output.txt","wb");
        
        
        
        for (k=0; k < A2; k++) {
            if (channels == 1) {
                fprintf(sound_data, "%s" "%.5lf        " "%s" "%.5lf\n", "Tempo :   ", t[k], "F_1 :    ", F_1[k] );
            }
            else {
                fprintf(sound_data, "%s" "%.5lf        " "%s" "%.5lf      " "%s" "%.5f\n", "Tempo :   ", t[k], "F_1 :    ", F_1[k], "F_2 :     ", F_2[k] );
 
            }
        }
        
        printf("Dados escritos em output.txt\n");
        fclose(sound_data);
        
        //double complex * ck_sound =  malloc (5*sizeof(double  complex));
        
        /*FAZER TRANSFORMADAS*/
        
       /* printf("Seecione Transformada desejada : 1 : Lenta   ;  2 : Recursiva   ; 3 : FFTPACK4   \n");
        scanf("%d",&metodo);
        
        if (metodo == 1) {
            
        }
        else if (metodo == 2) {
            fourrier_c = fftrec(ck,F_1_rec,A2,true);
            
        }
        else if (metodo == 3) {
            
        }*/
        
        return 2;
        
    }
    
    

    
 
 
return 0;
}
