#include <stdio.h>
#include <stdlib.h>
#include <complex.h>
#include <math.h>
#include <stdbool.h>
#include <string.h>


double * get_init_data (FILE* sound_data, char* filepath) {
    
    //   [ A, A2, sample_rate, Channels ]
    
    double * init_data = (double*) malloc (5*sizeof(double));
    int A;
    int A2;
    int ch;
    int sample_rate;
    int channels;
    sound_data = fopen(filepath, "rb");
    
     if (sound_data == NULL) {
            printf("CANT OPEN FILE");
        }
         
    /*Obter numero de amostras*/
        
    while(!feof(sound_data)) {           
        ch = fgetc(sound_data);
        if(ch == '\n') {
            A++;
        }
    }
        
    rewind(sound_data);
    A = A -2; /*Excluir linhas que nao sao dados*/
        
    A2 = A;
    A2--;
    A2 |= A2 >> 1;
    A2 |= A2 >> 2;
    A2 |= A2 >> 4;
    A2 |= A2 >> 8;
    A2 |= A2 >> 16;
    A2++;
        
        
        /*Obter sample rate*/
        fseek(sound_data,14,SEEK_SET);
        fscanf(sound_data, "%d", &sample_rate);
        printf("Sample Rate is : %d\n",sample_rate);
         
       
        /*Obter numero de canais*/
        fseek(sound_data,12,SEEK_CUR);
        fscanf(sound_data, "%d", &channels);
        printf("Number of channels is : %d\n\n",channels);
        
        fclose(sound_data);
        
        init_data[0] = A;
        init_data[1] = A2;
        init_data[2] = sample_rate;
        init_data[3] = channels;
    
        
    return init_data;
        
              
}

