#include <stdio.h>
#include <stdlib.h>
#include <time.h>

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

void teatro(int reservado[18][20]) {
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
		printf("|---|");
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
		printf("     ");
		printf("\n");
}

int main () {
	srand((unsigned int)time(NULL));
	
	int reservados[18][20];
	
	int i, j;
	for (i = 0; i < 18; i++) {
		for (j = 0; j < 20; j++) {
			reservados[i][j] = 0;
		}
	}
	
	for (i = 0; i < 160; i++) {
		reservados[Get_Random_Int(0, 17)][Get_Random_Int(0, 19)] = 1;
	}
	
	teatro(reservados);
	return 0;
}
