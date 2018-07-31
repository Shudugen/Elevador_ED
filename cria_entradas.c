#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h> 
/*primeiro numero eh a capacidade, o segundo eh o tamanho do predio*/ 

void quick_sort(int *a, int left, int right);

int main (){
    
    int tempo_max;
	int i, k, tempo, andar_origem, andar_destino;
	srand(time(NULL));
    
    i = 0;
    
    int capacidade_aux;
    int andares_aux;
    int quantidade_de_eventos_aux;
    int l;
    
    printf("\033[0;33m");
    printf("Escreva a capacidade do elevador, o numero de andares do predio em questao, a quantidade de eventos a ser gerada e o tempo maximo de ocorrencia um evento (apenas em numeros inteiros)\n");
	printf("\033[0m");
    scanf("%d %d %d %d", &capacidade_aux, &andares_aux, &quantidade_de_eventos_aux, &tempo_max);
    
    int tempos_totais[quantidade_de_eventos_aux];
    
    for(k=0; k<=quantidade_de_eventos_aux; k++){
        tempos_totais[k]=0;
    }
    
    for(k=0; k<=quantidade_de_eventos_aux; k++){
        tempos_totais[k] = (rand() % (tempo_max));
        for(l = 0; l<k; l++){
          if(tempos_totais[k]==tempos_totais[l]){
              tempos_totais[l] = (rand() % (tempo_max));
          }
        }
    }
    

	FILE *fp2;
	fp2 = fopen("Ambiente.txt", "w");
    fprintf(fp2, "%d\n", quantidade_de_eventos_aux);
	fprintf(fp2, "%d %d\n", capacidade_aux, andares_aux); 
	fclose(fp2);
    
	FILE *fp;
	fp = fopen("usuarios.txt", "w");
	
	i= quantidade_de_eventos_aux; /*quantidade de eventos */
    
     quick_sort(tempos_totais, 0, (quantidade_de_eventos_aux - 1));
    
	for(k=0; k<i; k++){
            tempo = tempos_totais[k];
            andar_origem = (rand() % andares_aux);
            andar_destino = (rand() % andares_aux);
	    if(andar_origem == andar_destino){      /*pro andar de origem e de destino serem diferentes*/
	        while(andar_origem == andar_destino){
		      andar_destino = (rand() % andares_aux);
		}
            }
            fprintf(fp, "%d %d %d\n", tempo, andar_origem, andar_destino);    
	}
	fclose(fp);

    return 0;
}

void quick_sort(int *a, int left, int right) {
    int i, j, x, y;
     
    i = left;
    j = right;
    x = a[(left + right) / 2];
     
    while(i <= j) {
        while(a[i] < x && i < right) {
            i++;
        }
        while(a[j] > x && j > left) {
            j--;
        }
        if(i <= j) {
            y = a[i];
            a[i] = a[j];
            a[j] = y;
            i++;
            j--;
        }
    }
     
    if(j > left) {
        quick_sort(a, left, j);
    }
    if(i < right) {
        quick_sort(a, i, right);
    }
}
