#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#define MAX 100
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
	int data;//reservado para cadastro de hora
}Espetaculo;

typedef struct {
    Espetaculo Item[MAX];
    int Prim, Ult;
}Lista_est;

void Criar_Lista_Vazia(Lista_est *Teatro) {
    Teatro->Prim = 0;
    Teatro->Ult = Teatro->Prim;
}

int Verifica_Lista_Vazia(Lista_est Teatro) {
    return (Teatro.Prim == Teatro.Ult);
}

int Verifica_Lista_Cheia(Lista_est Teatro) {
	return (Teatro.Ult == MAX);
}

void Insere_Elemento_Lista(Lista_est *Teatro, Espetaculo espetaculo) {
	int p;

	p = Teatro->Prim;
	if(Verifica_Lista_Cheia(*Teatro)){
		printf("Lista lotada, não pode ser adicionado mais dados.");
	}
	else {
		p = Teatro->Prim;
		while ((p < Teatro->Ult) && (espetaculo.data > Teatro->Item[p].data)) {
			p++;
		}
		if (p == Teatro->Ult) {
			Teatro->Item[p] = espetaculo;
			Teatro->Ult++;
		}
		else {
			if ((espetaculo.data != Teatro->Item[p].data)) {
				int i;
				for (i = Teatro->Ult; i > p; i--) {
					Teatro->Item[i] = Teatro->Item[i - 1];
				}
				Teatro->Item[p] = espetaculo;
				Teatro->Ult++;
			}
		}
	}
}

void Remove_Elemento_Lista(Lista_est *Teatro, Espetaculo *espetaculo) {
	int p, i;

	if (Verifica_Lista_Vazia(*Teatro)) {
		printf("A lista já está vazia, impossível remover elemento.");
	}
	else {
		p = Teatro->Prim;

		while ((p < Teatro->Ult) && (espetaculo->data != Teatro->Item[p].data)) {
			p++;
		}
		if (p == Teatro->Ult){
			printf("Espetaculo nao foi encontrado no sistema!\n");
		}
		else {
			*espetaculo = Teatro->Item[p];
            printf("Espetaculo removido do sistema!\n");
			for (i = p; i < Teatro->Ult; i++) {
				Teatro->Item[i] = Teatro->Item[i + 1];
			}
			Teatro->Ult--;
		}
	}
}

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

void Exibir_Sessao(Sessao sessao) {
	int i, j;
	for (i = 0; i < 18; i++) {
		printf("%c\t|---| ", i + 'A');
		for (j = 0; j < 10; j++) {
			if (sessao[i][j].status[0] == RESERVADO) {
				printf("%c  ", RESERVADO);
			} else {
				if (sessao[i][j].status[0] == VENDIDO) {
					printf("%c  ", VENDIDO);
				} else {
					printf("%c  ", VAGO);
				}
			}
		}
		printf("\b|-----| ");
		for (j; j < 20; j++) {
			if (sessao[i][j].status[0] == RESERVADO) {
				printf("%c  ", RESERVADO);
			} else {
				if (sessao[i][j].status[0] == VENDIDO) {
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

void Preencher(Sessao sessao) {
	int i, j;
	for (i = 0; i < 360; i++) {
		sessao[Get_Random_Int(0, 17)][Get_Random_Int(0, 19)].status[0] = VENDIDO;
	}
	for (i = 0; i < 60; i++) {
		sessao[Get_Random_Int(0, 17)][Get_Random_Int(0, 19)].status[0] = RESERVADO;
	}
}

void Inicializar_Sessao(Sessao sessao) {
	int i, j;
	for (i = 0; i < 18; i++) {
		for (j = 0; j < 20; j++) {
			sessao[i][j].status[0] = VAGO;
		}
	}
}

int main () {
	srand((unsigned int)time(NULL));
	
	Sessao sessao;
	
	Inicializar_Sessao(sessao);
	Preencher(sessao);
	Exibir_Sessao(sessao);
	
	return 0;
}
