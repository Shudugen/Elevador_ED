#include <stdio.h>
#include <stdlib.h>
#include "Fila.h"
#include <sys/time.h>
#include <sys/resource.h>
#include <unistd.h>
#include <limits.h>
#include <string.h>

/*
Feito por:

Gabriel Matheus da Rocha de Oliveira
Guilherme Braga Pinto

Last Update: 27/04/2018
UnB
*/


struct elevador{
    int andar_atual_do_elevador;
	int andar_destino_do_elevador[1000];
	int passageiros;
	int tempo_com_passageiros;
	int tempo_sem_passageiros;
};

struct fila{
	struct elemento *inicio;
	struct elemento *final;
};
struct lista{
	int qtd;
	struct comando dados[100];
};

struct elemento{
	struct comando dados;
	struct elemento *prox;
};

typedef struct elemento Elem;



int main(int argc, char *argv[]){


struct elevador ELEVADOR;
struct elevador *ELEVADOR2;

struct rusage usage;
struct timeval start, end;

getrusage(RUSAGE_SELF, &usage);

start = usage.ru_stime;

void elevador_sobe(struct elevador *ELEVADOR);
void elevador_desce(struct elevador *ELEVADOR);

void prinENTRADA(int i, struct elevador *ELEVADOR2, struct comando *usuario2, int t, FILE *file3);
void prinSAIDA(int i, struct elevador *ELEVADOR2, struct comando *usuario2, struct comando usuario, int t, FILE *file3);

int tamanho_do_predio;
tamanho_do_predio = 0;

double aux_medio;
aux_medio = 0;

int capacidade_max_elevador;
capacidade_max_elevador = 0;

double tempo_medio_passageiro = 0;
int numero_de_pessoas = 0;
int numero_de_pessoasE = 0;
int numero_de_pessoasS = 0;


ELEVADOR2 =&ELEVADOR;
ELEVADOR.andar_atual_do_elevador = 0;
ELEVADOR.passageiros = 0;
ELEVADOR.tempo_com_passageiros = 0;
ELEVADOR.tempo_sem_passageiros = 0;

int i, n, t, te, y, min, cont;
int MAX;


FILE *file;
file = fopen("usuarios.txt", "r");
FILE *file2;
file2 = fopen("Ambiente.txt", "r");
FILE *file3;
file3 = fopen("resultados.txt", "w");


Fila *fi;
Lista *li;
Fila *fi2;

struct comando usuario;
struct comando *usuario2;
struct comando usuario3;


fi = cria_Fila();
li = cria_Lista();
fi2 =cria_Fila();

consulta_Fila(fi, &usuario);

int calcula_distancia(struct elevador *ELEVADOR2, struct comando usuario);

te = INT_MAX;
fscanf(file2, "%d", &n);

usuario2 = (struct comando*) malloc(n*sizeof(struct comando));

fscanf(file2, "%d %d", &capacidade_max_elevador, &tamanho_do_predio);

MAX = capacidade_max_elevador;
min = tamanho_do_predio;

for(i = 0; i < n; i++){
	fscanf(file, "%d %d %d", &usuario2[i].tempo_chegada, &usuario2[i].andar_chamada, &usuario2[i].andar_destino);
}

/*--------------------------------------------------------- FCFS ----------------------------------------------------------------*/

if( strcmp(argv[1], "fcfs") == 0 ){

/* -------------------------------------------------- Representação do Tempo ----------------------------------------------------*/

for(i = 0; i <= te; i++){

/*----------------------------------------------- Criação da Lista de Acontecimentos -----------------------------------------------------*/

	for(t = 0; t < n; t++){
        if(usuario2[t].tempo_chegada == i){
            insere_Fila(fi, usuario2[t]); }
        }
        if(ELEVADOR2->passageiros != 0){
            ELEVADOR2->tempo_com_passageiros++;
        }
        if(ELEVADOR2->passageiros == 0){
            ELEVADOR2->tempo_sem_passageiros++;
        }

/*------------------------------------------------ Comportamento do Elevador Vazio -------------------------------------------------*/

if(fi2->inicio == NULL){

if(ELEVADOR2->andar_atual_do_elevador <= usuario2[numero_de_pessoas].andar_chamada && usuario2[numero_de_pessoas].tempo_chegada <= i ){

	elevador_sobe(ELEVADOR2);
	for(t = 0; t < n; t++){
	if(usuario2[t].andar_chamada == ELEVADOR2->andar_atual_do_elevador && usuario2[t].tempo_chegada <= i && usuario2[t].atendimento == 0 && ELEVADOR2->passageiros < capacidade_max_elevador){
		usuario2[t].atendimento = 1;
		usuario2[t].tempo_entrada = i + 1;
		insere_Fila(fi2, usuario2[t]);

		numero_de_pessoasE++;

		ELEVADOR2->passageiros++;

        if((ELEVADOR2->passageiros) != 0){
			ELEVADOR2->tempo_com_passageiros++;
		}
		if((ELEVADOR2->passageiros) == 0){
			ELEVADOR2->tempo_sem_passageiros++;
		}
		prinENTRADA( i, ELEVADOR2, usuario2, t, file3);
	}
}

}else if(ELEVADOR2->andar_atual_do_elevador >= usuario2[numero_de_pessoas].andar_chamada && usuario2[numero_de_pessoas].tempo_chegada <= i){
	elevador_desce(ELEVADOR2);
	for(t = 0; t < n; t++){
	if(usuario2[t].andar_chamada == ELEVADOR2->andar_atual_do_elevador && usuario2[t].tempo_chegada <= i && usuario2[t].atendimento == 0 && ELEVADOR2->passageiros < capacidade_max_elevador){
		usuario2[t].atendimento = 1;
		usuario2[t].tempo_entrada = i + 1;
		insere_Fila(fi2, usuario2[t]);

        if(usuario2[t].andar_chamada == ELEVADOR2->andar_atual_do_elevador){

        numero_de_pessoasE++;
        }
		ELEVADOR2->passageiros++;

        if((ELEVADOR2->passageiros) != 0){
			ELEVADOR2->tempo_com_passageiros++;
		}
		if((ELEVADOR2->passageiros) == 0){
			ELEVADOR2->tempo_sem_passageiros++;
		}
		prinENTRADA( i, ELEVADOR2, usuario2, t, file3);

	}
}
}

}

/*----------------------------------------- Comportamento do Elevador Ocupado --------------------------------------------------*/

	else {
	consulta_Fila(fi2, &usuario);

	if(ELEVADOR2->andar_atual_do_elevador <= usuario.andar_destino){
	elevador_sobe(ELEVADOR2);
	for(t = 0; t < n; t++){
	if(usuario2[t].andar_chamada == ELEVADOR2->andar_atual_do_elevador && usuario2[t].tempo_chegada <= i && usuario2[t].atendimento == 0 && ELEVADOR2->passageiros < capacidade_max_elevador){
		usuario2[t].atendimento = 1;
		usuario2[t].tempo_entrada = i + 1;
		insere_Fila(fi2, usuario2[t]);

		numero_de_pessoasE++;

		ELEVADOR2->passageiros++;

        if((ELEVADOR2->passageiros) != 0){
			ELEVADOR2->tempo_com_passageiros++;
		}
		if((ELEVADOR2->passageiros) == 0){
			ELEVADOR2->tempo_sem_passageiros++;
		}
		prinENTRADA( i, ELEVADOR2, usuario2, t, file3);

	}
	if(fi2->inicio != NULL){
	consulta_Fila(fi2, &usuario);
	if(usuario.andar_destino == ELEVADOR2->andar_atual_do_elevador){

		remove_Fila(fi2);

        numero_de_pessoasS++;

		ELEVADOR2->passageiros--;

		if((ELEVADOR2->passageiros) != 0){
			ELEVADOR2->tempo_com_passageiros++;
		}
		if((ELEVADOR2->passageiros) == 0){
			ELEVADOR2->tempo_sem_passageiros++;
		}
		prinSAIDA(i, ELEVADOR2, usuario2, usuario, t, file3);
	}
}
}
} else if(ELEVADOR2->andar_atual_do_elevador >= usuario.andar_destino){
	elevador_desce(ELEVADOR2);
	for(t = 0; t < n; t++){
	if(usuario2[t].andar_chamada == ELEVADOR2->andar_atual_do_elevador && usuario2[t].tempo_chegada <= i && usuario2[t].atendimento == 0 && ELEVADOR2->passageiros < capacidade_max_elevador){
		usuario2[t].atendimento = 1;
		usuario2[t].tempo_entrada = i + 1;
		insere_Fila(fi2, usuario2[t]);

		numero_de_pessoasE++;

		ELEVADOR2->passageiros++;

        if((ELEVADOR2->passageiros) != 0){
			ELEVADOR2->tempo_com_passageiros++;
		}
		if((ELEVADOR2->passageiros) == 0){
			ELEVADOR2->tempo_sem_passageiros++;
		}
		prinENTRADA( i, ELEVADOR2, usuario2, t, file3);
	}
	if(fi2->inicio != NULL){
	consulta_Fila(fi2, &usuario);
	if(usuario.andar_destino == ELEVADOR2->andar_atual_do_elevador){
		remove_Fila(fi2);

        numero_de_pessoasS++;

		ELEVADOR2->passageiros--;

        if((ELEVADOR2->passageiros) != 0){
			ELEVADOR2->tempo_com_passageiros++;
		}
		if((ELEVADOR2->passageiros) == 0){
			ELEVADOR2->tempo_sem_passageiros++;
		}
		prinSAIDA(i, ELEVADOR2, usuario2, usuario, t, file3);

	}
}
}
}
for(t = 0; t < n; t++){
if(usuario2[t].atendimento == 0){
	numero_de_pessoas = t;
	break;
}
}


}

if(numero_de_pessoasS == n){
	break;
}

}

aux_medio = ELEVADOR2->tempo_com_passageiros;
tempo_medio_passageiro = ((aux_medio) / n);

fclose(file);
fclose(file2);
fclose(file3);

getrusage(RUSAGE_SELF, &usage);
end = usage.ru_stime;

printf("\033[1;34m");
printf("\nNumero de usuarios atendidos: %d", numero_de_pessoasS);
printf("\nO tempo que o elevador ficou ocupado eh de %d zepslons", ELEVADOR2->tempo_com_passageiros);
printf("\nO tempo que o elevador ficou vazio eh de %d zepslons", ELEVADOR2->tempo_sem_passageiros);
printf("\nO tempo que o elevador ficou ocupado dividido pela quantidade de passageiros foi de: %.2lf zepslons", tempo_medio_passageiro);
printf("\033[0m");

printf("\033[0;33m");
printf("\n\n\nTEMPO DE EXECUCAO:\n");
printf("Comecou no: %ld.%lds\n", start.tv_sec, start.tv_usec);
printf("Acabou no: %ld.%lds\n", end.tv_sec, end.tv_usec);
printf("\033[0m");

        libera_Fila(fi);

}

/*---------------------------------------------------------------- SJF --------------------------------------------------------- */


if (strcmp(argv[1], "sjf") == 0) {


/* -------------------------------------------------- Representação do Tempo ----------------------------------------------------*/

for(i = 0; i <= te; i++){

/*----------------------------------------------- Criação da Lista de Acontecimentos -----------------------------------------------------*/

	for(t = 0; t < n; t++){
        if(usuario2[t].tempo_chegada == i){
            insere_Fila(fi, usuario2[t]); }
        }
        if(ELEVADOR2->passageiros != 0){
            ELEVADOR2->tempo_com_passageiros++;
        }
        if(ELEVADOR2->passageiros == 0){
            ELEVADOR2->tempo_sem_passageiros++;
        }
/*------------------------------------------ Comportamento do Elevador Vazio -------------------------------------------------------*/


        if(li->qtd == 0){
            if(ELEVADOR2->andar_atual_do_elevador <= usuario2[numero_de_pessoas].andar_chamada && usuario2[numero_de_pessoas].tempo_chegada <= i){
                    elevador_sobe(ELEVADOR2);

                        for(y = 1; y <= li->qtd; y++){
                            consulta_Lista(li, y, &usuario3);
                            usuario3.DIST = calcula_distancia(ELEVADOR2, usuario3);
                            usuario3.DIST = calcula_distancia(ELEVADOR2, usuario3);
                            remove_lista_posicao(li, y - 1);
                            insere_lista_posicao(li, usuario3, y - 1, MAX);
                            }

                        for(t = 0; t < n; t++){
                            if(usuario2[t].andar_chamada == ELEVADOR2->andar_atual_do_elevador && usuario2[t].tempo_chegada <= i && usuario2[t].atendimento == 0 && ELEVADOR2->passageiros < capacidade_max_elevador){
                                usuario2[t].atendimento = 1;
                                usuario2[t].tempo_entrada = i + 1;
                                usuario2[t].DIST = calcula_distancia(ELEVADOR2, usuario2[t]);
                                insere_lista_ordenada(li, usuario2[t], MAX);
                                /*  i++;  */
                                ELEVADOR2->passageiros++;

                                    if((ELEVADOR2->passageiros) != 0){
                                        ELEVADOR2->tempo_com_passageiros++;
                                    }
                                    if((ELEVADOR2->passageiros) == 0){
                                        ELEVADOR2->tempo_sem_passageiros++;
                                    }
                                    prinENTRADA( i, ELEVADOR2, usuario2, t, file3);

                            }
                        }

                }else if(ELEVADOR2->andar_atual_do_elevador >= usuario2[numero_de_pessoas].andar_chamada && usuario2[numero_de_pessoas].tempo_chegada <= i){
                    elevador_desce(ELEVADOR2);

                        for(y = 1; y <= li->qtd; y++){
                            consulta_Lista(li, y, &usuario3);
                            usuario3.DIST = calcula_distancia(ELEVADOR2, usuario3);
                            usuario3.DIST = calcula_distancia(ELEVADOR2, usuario3);
                            remove_lista_posicao(li, y - 1);
                            insere_lista_posicao(li, usuario3, y - 1, MAX);
                            }

                    for(t = 0; t < n; t++){
                        if(usuario2[t].andar_chamada == ELEVADOR2->andar_atual_do_elevador && usuario2[t].tempo_chegada <= i && usuario2[t].atendimento == 0 && ELEVADOR2->passageiros < capacidade_max_elevador){
                            usuario2[t].atendimento = 1;
                            usuario2[t].tempo_entrada = i + 1;
                            usuario2[t].DIST = calcula_distancia(ELEVADOR2, usuario2[t]);
                            insere_lista_ordenada(li, usuario2[t], MAX);
                           /* i++;   */
                            ELEVADOR2->passageiros++;

                                if((ELEVADOR2->passageiros) != 0){
                                    ELEVADOR2->tempo_com_passageiros++;
                                }
                                if((ELEVADOR2->passageiros) == 0){
                                    ELEVADOR2->tempo_sem_passageiros++;
                                }
                                prinENTRADA( i, ELEVADOR2, usuario2, t, file3);

                        }
                    }
                }
        }

/*---------------------------------------------- Comportamento do Elevador Ocupado (SUBIDA) -----------------------------------------------*/

	else{
        consulta_Lista(li, 1, &usuario);
            if(ELEVADOR2->andar_atual_do_elevador <= usuario.andar_destino){
                elevador_sobe(ELEVADOR2);

                    for(y = 1; y <= li->qtd; y++){
                        consulta_Lista(li, y, &usuario3);
                        usuario3.DIST = calcula_distancia(ELEVADOR2, usuario3);
                        usuario3.DIST = calcula_distancia(ELEVADOR2, usuario3);
                        remove_lista_posicao(li, y - 1);
                        insere_lista_posicao(li, usuario3, y - 1, MAX);
                    }

/*---------------------------------------------------------CONFERINDO DISTANCIAS ----------------------------------------------*/

                    for(t = 0; t < n; t++){
                        if(usuario2[t].andar_chamada == ELEVADOR2->andar_atual_do_elevador && usuario2[t].tempo_chegada <= i && usuario2[t].atendimento == 0 && ELEVADOR2->passageiros < capacidade_max_elevador){
                            usuario2[t].atendimento = 1;
                            usuario2[t].tempo_entrada = i + 1;
                            usuario2[t].DIST = calcula_distancia(ELEVADOR2, usuario2[t]);
                            insere_lista_ordenada(li, usuario2[t], MAX);
                            /*  i++;   */
                            ELEVADOR2->passageiros++;

                                if((ELEVADOR2->passageiros) != 0){
                                    ELEVADOR2->tempo_com_passageiros++;
                                }
                                if((ELEVADOR2->passageiros) == 0){
                                    ELEVADOR2->tempo_sem_passageiros++;
                                }
                                prinENTRADA( i, ELEVADOR2, usuario2, t, file3);

						}

                                if(li->qtd != 0){
                                    consulta_Lista(li, 1, &usuario);
                                    if(usuario.andar_destino == ELEVADOR2->andar_atual_do_elevador){
                                        remove_lista_inicio(li);
                                        /*  i++;  */
                                        numero_de_pessoasS++;
                                        ELEVADOR2->passageiros--;

                                        if((ELEVADOR2->passageiros) != 0){
                                            ELEVADOR2->tempo_com_passageiros++;
                                        }
                                        if((ELEVADOR2->passageiros) == 0){
                                            ELEVADOR2->tempo_sem_passageiros++;
                                        }
                                        prinSAIDA(i, ELEVADOR2, usuario2, usuario, t, file3);
                                }
                            }
                    }
            }

/*---------------------------------------------- Comportamento do Elevador Ocupado (DESCIDA) -----------------------------------------------*/

            else if(ELEVADOR2->andar_atual_do_elevador >= usuario.andar_destino){
                elevador_desce(ELEVADOR2);

                    for(y = 1; y <= li->qtd; y++){
                        consulta_Lista(li, y, &usuario3);
                        usuario3.DIST = calcula_distancia(ELEVADOR2, usuario3);
                        remove_lista_posicao(li, y - 1);
                        insere_lista_posicao(li, usuario3, y - 1, MAX);
                    }


                    for(t = 0; t < n; t++){
                        if(usuario2[t].andar_chamada == ELEVADOR2->andar_atual_do_elevador && usuario2[t].tempo_chegada <= i && usuario2[t].atendimento == 0 && ELEVADOR2->passageiros < capacidade_max_elevador){
                            usuario2[t].atendimento = 1;
                            usuario2[t].tempo_entrada = i + 1;
                            usuario2[t].DIST = calcula_distancia(ELEVADOR2, usuario2[t]);
                            insere_lista_ordenada(li, usuario2[t], MAX);
                            /* i++; */
                            ELEVADOR2->passageiros++;

                            if((ELEVADOR2->passageiros) != 0){
                                ELEVADOR2->tempo_com_passageiros++;
                            }
                            if((ELEVADOR2->passageiros) == 0){
                                ELEVADOR2->tempo_sem_passageiros++;
                            }
                            prinENTRADA( i, ELEVADOR2, usuario2, t, file3);

}
                            if(li->qtd != 0){
                                consulta_Lista(li, 1, &usuario);
                                if(usuario.andar_destino == ELEVADOR2->andar_atual_do_elevador){
                                    remove_lista_inicio(li);
                                    /* i++;  */
                                    numero_de_pessoasS++;
                                    ELEVADOR2->passageiros--;

                                        if((ELEVADOR2->passageiros) != 0){
                                            ELEVADOR2->tempo_com_passageiros++;
                                        }
                                        if((ELEVADOR2->passageiros) == 0){
                                            ELEVADOR2->tempo_sem_passageiros++;
                                        }
                                        prinSAIDA(i, ELEVADOR2, usuario2, usuario, t, file3);

                                }
                            }
                    }
            }


         for(t = 0; t < n; t++){
if(usuario2[t].atendimento == 0){
    cont = calcula_distancia(ELEVADOR2, usuario2[t]);
    if(cont < min){
    numero_de_pessoas = t;
    }
} }
min = tamanho_do_predio;
    }

if(numero_de_pessoasS == n){
	break;
}

}

aux_medio = ELEVADOR2->tempo_com_passageiros;
tempo_medio_passageiro = ((aux_medio) / n);


fclose(file);
fclose(file2);
fclose(file3);
/*tempo*/
getrusage(RUSAGE_SELF, &usage);
end = usage.ru_stime;

printf("\033[1;34m");
printf("\nNumero de usuarios atendidos: %d", numero_de_pessoasS);
printf("\nO tempo que o elevador ficou ocupado eh de %d zepslons", ELEVADOR2->tempo_com_passageiros);
printf("\nO tempo que o elevador ficou vazio eh de %d zepslons", ELEVADOR2->tempo_sem_passageiros);
printf("\nO tempo que o elevador ficou ocupado dividido pela quantidade de passageiros foi de: %.2lf zepslons", tempo_medio_passageiro);
printf("\033[0m");

printf("\033[0;33m");
printf("\n\n\nTEMPO DE EXECUCAO:\n");
printf("Comecou no: %ld.%lds\n", start.tv_sec, start.tv_usec);
printf("Acabou no: %ld.%lds\n", end.tv_sec, end.tv_usec);
printf("\033[0m");

    libera_Lista(li);
    libera_Fila(fi);
    free(usuario2);

    }

return 0;
}


Fila* cria_Fila(){
	Fila* fi = (Fila*)malloc(sizeof(Fila));
	if(fi != NULL){
		fi->final = NULL;
		fi->inicio = NULL;
	}
	return fi;

}

void libera_Fila(Fila* fi){
	if(fi != NULL){
		Elem* no;
		while(fi->inicio != NULL){
			no = fi->inicio;
			fi->inicio = fi->inicio->prox;
			free(no);
		}
		free(fi);
	}
}


int insere_Fila(Fila* fi, struct comando usuario){
	if(fi == NULL) return 0;
	Elem *no = (Elem*)malloc(sizeof(Elem));
	if(no == NULL) return 0;
	no->dados = usuario;
	no->prox = NULL;
	if(fi->final == NULL)
		fi->inicio = no;
	else
		fi->final->prox = no;
	fi->final = no;
	return 1;
}

int remove_Fila(Fila* fi){
	if(fi == NULL){
        return 0;
    }
	if(fi->inicio == NULL){
		return 0;
    }
	Elem *no = fi->inicio;
	fi->inicio = fi->inicio->prox;
	if(fi->inicio == NULL){
		fi->final = NULL;
		free(no);
}
		return 1;
}

int consulta_Fila(Fila* fi, struct comando *usuario){
	if(fi == NULL) return 0;
	if(fi->inicio == NULL)
		return 0;
	*usuario = fi->inicio->dados;
	return 1;

}

void elevador_sobe(struct elevador *ELEVADOR2){
	 ELEVADOR2->andar_atual_do_elevador++;
}

void elevador_desce(struct elevador *ELEVADOR2){
	 ELEVADOR2->andar_atual_do_elevador--;
}

int calcula_distancia(struct elevador *ELEVADOR2, struct comando usuario){
	int resposta;
	resposta = usuario.andar_destino - ELEVADOR2->andar_atual_do_elevador;
	if(resposta < 0){
		resposta = resposta*(-1);
	}
return resposta;
}

Lista* cria_Lista(){
	Lista *li;
	li = (Lista*) malloc(sizeof(struct lista));
	if(li != NULL){
		li->qtd = 0;
	}
	return li;
}

void libera_Lista(Lista* li){
	free(li);
}

int tamanho_lista(Lista* li){
	if(li == NULL){
		return -1;
	}else{
		return li->qtd;
	}
}

int lista_vazia(Lista *li){
	if(li == NULL){
		return -1;
	} return (li->qtd == 0);
}

int lista_cheia(Lista* li, int MAX){
	if(li == NULL){
		return -1;
	}
	return (li->qtd == MAX);
}

int insere_lista_ordenada(Lista* li, struct comando usuario, int MAX){
	if(li == NULL) {
return 0;
	}if(lista_cheia(li, MAX)){
		return 0;
	}
	int k, l = 0;
	while(l<li->qtd && li->dados[l].DIST < usuario.DIST){
		l++;
	}
	for(k = li->qtd-1; k >= l; k--){
		li->dados[k + 1] = li->dados[k];
	}
	li->dados[l] = usuario;
	li->qtd++;
return 1;
}

int remove_lista_inicio(Lista* li){
if(li == NULL){
	return 0;
}if(li->qtd == 0){
	return 0;
}
int m = 0;
for(m = 0; m < li->qtd-1; m++){
	li->dados[m] = li->dados[m + 1];
}
li->qtd--;
return 1;
}

int consulta_Lista(Lista* li, int pos, struct comando *usuario3){
	if(li == NULL || pos <= 0 || pos > li->qtd){
		return 0;
	}
	*usuario3 = li->dados[pos-1];
	return 1;
}

	int remove_lista_posicao(Lista* li, int pos){
		if(li == NULL){
			return 0;
		}
		if(li->qtd == 0){
			return 0;
		}
		int o, p = 0;
while(p<li->qtd && p != pos){
	p++;}
	if(p == li->qtd){
		return 0;
	}
	for(o = p; o < li->qtd-1; o++){
		li->dados[o] = li->dados[o+1];
	}
	li->qtd--;
	return 1;
}

int insere_lista_inicio(Lista* li, struct comando usuario3, int MAX){
	if(li == NULL){
		return 0;
	}
	if(lista_cheia(li, MAX)){
		return 0;
	}
	int w;
	for(w = li->qtd-1; w>= 0; w--){
		li->dados[w + 1] = li->dados[w];
	}
	li->dados[0] = usuario3;
	li->qtd++;
	return 1;
}

int insere_lista_posicao(Lista* li, struct comando usuario3, int pos, int MAX){
	if(li == NULL){
		return 0;
	}
	if(lista_cheia(li, MAX)){
		return 0;
	}
	int w;
	for(w = li->qtd-1; w>= pos; w--){
		li->dados[w + 1] = li->dados[w];
	}
	li->dados[pos] = usuario3;
	li->qtd++;
	return 1;
}

void prinENTRADA(int i, struct elevador *ELEVADOR2, struct comando *usuario2, int t, FILE *file3){

		printf("\033[0;32m");
		printf("No tempo %d e no andar %d entrou o usuario que requisitou o elevador em %d zepslon(s) com destino ao andar %d\n", i + 1, ELEVADOR2->andar_atual_do_elevador ,usuario2[t].tempo_chegada, usuario2[t].andar_destino);
        printf("\033[0m");

        printf("\033[1;32m");
        printf("O usuario esperou: %d zepslons\n", usuario2[t].tempo_entrada - usuario2[t].tempo_chegada);
        printf("\033[0m");

        fprintf(file3, "No tempo %d e no andar %d entrou o usuario que requisitou o elevador em %d zepslon(s) com destino ao andar %d\n", i + 1, ELEVADOR2->andar_atual_do_elevador ,usuario2[t].tempo_chegada, usuario2[t].andar_destino);
		fprintf(file3, "o usuario esperou: %d zepslons\n", usuario2[t].tempo_entrada - usuario2[t].tempo_chegada);



}

void prinSAIDA(int i, struct elevador *ELEVADOR2, struct comando *usuario2, struct comando usuario, int t, FILE *file3){
 printf("\033[0;31m");
		printf("No tempo %d e no andar %d saiu o usuario que requisitou o elevador em %d zepslon(s) com destino ao andar %d\n", i + 1, ELEVADOR2->andar_atual_do_elevador , usuario.tempo_chegada, usuario.andar_destino);
        printf("\033[0m");

        printf("\033[1;31m");
        printf("O usuario ficou %d zepslons dentro do elevador\n",  ((i+1) - usuario.tempo_entrada));
        printf("\033[0m");

        fprintf(file3, "No tempo %d e no andar %d saiu o usuario que requisitou o elevador em %d zepslon(s) com destino ao andar %d\n", i + 1, ELEVADOR2->andar_atual_do_elevador , usuario.tempo_chegada, usuario.andar_destino);
		fprintf(file3, "o usuario ficou %d zepslons dentro do elevador\n",  ((i+1) - usuario.tempo_entrada));
}
