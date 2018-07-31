#include <stdio.h>
#include <stdlib.h>


struct comando{
	int tempo_chegada; 
	int andar_chamada;
	int andar_destino;
	int atendimento;
	int tempo_entrada;
	int tempo_saida;
	int DIST;
};

struct distancia{
int tempo_entrada1;
int tempo_saida1;
int Distancias;
};

typedef struct lista Lista;

typedef struct fila Fila;

Fila* cria_Fila();

void libera_Fila(Fila* fi);

int insere_Fila(Fila* fi, struct comando usuario);

int remove_Fila(Fila* fi);

int consulta_Fila(Fila* fi, struct comando *usuario);

Lista* cria_Lista();

void libera_Lista(Lista* li);

int tamanho_Lista(Lista* li);

int lista_vazia(Lista* li);

int insere_lista_ordenada(Lista* li, struct comando DIST, int MAX);

int remove_lista_inicio(Lista* li);

int consulta_Lista(Lista* li, int pos, struct comando *usuario3);

int lista_cheia(Lista* li, int MAX);

int remove_lista_posicao(Lista* li, int pos);

int insere_lista_inicio(Lista* li, struct comando usuario, int MAX);

int insere_lista_posicao(Lista* li, struct comando usuario3, int pos, int MAX);
