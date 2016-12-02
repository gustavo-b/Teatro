#include <stdio.h>
#include <stdlib.h>
#include <time.h>

typedef int Teatro[18][20];

int Get_Random_Int(int min, int max){
    int r;
    const unsigned int range = 1 + max - min;
    const unsigned int buckets = RAND_MAX / range;
    const unsigned int limit = buckets * range;

    do{
        r = rand();
    } while (r >= limit);

    return min + (r / buckets);
}

void Exibir_Teatro(Teatro reservado) {
	int i, j;
	for (i = 0; i < 18; i++) {
		printf("%c\t|---| ", i + 'A');
		for (j = 0; j < 10; j++) {
			if (reservado[i][j] == 1) {
				printf("X  ");
			} else {
				printf("#  ");
			}
		}
		printf("\b|-----| ");
		for (j; j < 20; j++) {
			if (reservado[i][j] == 1) {
				printf("X  ");
			} else {
				printf("#  ");
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

void Preencher(Teatro reservado) {
	int i, j;
	for (i = 0; i < 160; i++) {
		reservado[Get_Random_Int(0, 17)][Get_Random_Int(0, 19)] = 1;
	}
}

void Inicializar(Teatro reservado) {
	int i, j;
	for (i = 0; i < 18; i++) {
		for (j = 0; j < 20; j++) {
			reservado[i][j] = 0;
		}
	}
}

int main () {
	srand((unsigned int)time(NULL));
	
	Teatro reservado;
	
	Inicializar(reservado);
	Preencher(reservado);
	Exibir_Teatro(reservado);
	
	return 0;
}
