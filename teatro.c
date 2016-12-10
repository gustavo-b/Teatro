#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#define RESERVADO '#'
#define VENDIDO 'X'
#define VAGO 'O'

typedef struct {
	char posicao[4];
	char status[2];
}Assento;

typedef Assento Sessao[18][20];

typedef struct {
	char nome[20];
	Sessao sessao;
	//reservado para cadastro de hora
}Espetaculo;

int Get_Random_Int(int min, int max) {
    int r;
    const unsigned int range = 1 + max - min;
    const unsigned int buckets = RAND_MAX / range;
    const unsigned int limit = buckets * range;

    do {
        r = rand();
    } while (r >= limit);

    return min + (r / buckets);
}

void Exibir_Sessao(Sessao reservado) {
	int i, j;
	for (i = 0; i < 18; i++) {
		printf("%c\t|---| ", i + 'A');
		for (j = 0; j < 10; j++) {
			if (reservado[i][j].status[0] == RESERVADO) {
				printf("%c  ", RESERVADO);
			} else {
				if (reservado[i][j].status[0] == VENDIDO) {
					printf("%c  ", VENDIDO);
				} else {
					printf("%c  ", VAGO);
				}
			}
		}
		printf("\b|-----| ");
		for (j; j < 20; j++) {
			if (reservado[i][j].status[0] == RESERVADO) {
				printf("%c  ", RESERVADO);
			} else {
				if (reservado[i][j].status[0] == VENDIDO) {
					printf("%c  ", VENDIDO);
				} else {
					printf("%c  ", VAGO);
				}
			}
		}
		printf("\b|---|");
		printf("\n");
	}
	printf(" \t      ");
		for (j = 0; j < 10; j++) {
			if (j < 9) {
				printf("%d  ", j + 1);
			} else {
				printf("%d ", j + 1);
			}
		}
		printf("\b        ");
		for (j; j < 20; j++) {
			if (j < 9) {
				printf("%d  ", j + 1);
			} else {
				printf("%d ", j + 1);
			}
		}
		printf("\b     ");
		printf("\n");
}

void Preencher(Sessao reservado) {
	int i, j;
	for (i = 0; i < 360; i++) {
		reservado[Get_Random_Int(0, 17)][Get_Random_Int(0, 19)].status[0] = VENDIDO;
	}
	for (i = 0; i < 60; i++) {
		reservado[Get_Random_Int(0, 17)][Get_Random_Int(0, 19)].status[0] = RESERVADO;
	}
}

void Inicializar(Sessao reservado) {
	int i, j;
	for (i = 0; i < 18; i++) {
		for (j = 0; j < 20; j++) {
			reservado[i][j].status[0] = VAGO;
		}
	}
}

int main () {
	srand((unsigned int)time(NULL));
	
	Sessao reservado;
	
	Inicializar(reservado);
	Preencher(reservado);
	Exibir_Sessao(reservado);
	
	return 0;
}
