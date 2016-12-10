#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <locale.h>
#define MAX 100
#define RESERVADO '#'
#define VENDIDO 'X'
#define VAGO 'O'

typedef struct tm *Data;

FILE *arq;

typedef struct {
	char nome[200];
	int CPF;
}Pessoa;

typedef struct {
	char posicao[4];
	char status[2];
	Pessoa pessoa;
}Assento;

typedef Assento Sessao[18][20];

typedef struct {
	char nome[200];
	Sessao sessao;
	Data data;
	float ingresso;
}Espetaculo;

typedef struct {
    Espetaculo Item[MAX];
    int Prim, Ult;
}Lista_est;

typedef struct {
    Pessoa Item[MAX];
    int Inicio, Fim, Total;
} Fila_est;

void Criar_Lista_Vazia(Lista_est *Teatro) {
    Teatro->Prim = 0;
    Teatro->Ult = Teatro->Prim;
}

void Criar_Fila_Vazia(Fila_est *Espera) {
    Espera->Inicio = 0;
    Espera->Fim = 0;
    Espera->Total = 0;
}

int Verifica_Lista_Vazia(Lista_est Teatro) {
    return (Teatro.Prim == Teatro.Ult);
}

int Verifica_Fila_Vazia(Fila_est Espera) {
    return(Espera.Inicio == Espera.Fim);
}

int Verifica_Lista_Cheia(Lista_est Teatro) {
	return (Teatro.Ult == MAX);
}

int Verifica_Fila_Cheia(Fila_est Espera) {
    return((Espera.Fim + 1) % MAX == Espera.Fim );
}

void Insere_Elemento_Lista(Lista_est *Teatro, Espetaculo espetaculo) {
	int p;

	p = Teatro->Prim;
	if(Verifica_Lista_Cheia(*Teatro)){
		printf("Lista lotada, não pode ser adicionado mais dados.\n");
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

void Enfileirar(Fila_est* Espera, Pessoa pessoa) {
    if(Verifica_Fila_Cheia(*Espera)) {
        printf("Nao podem ser inseridos mais pessoas, fila cheia.\n");
    }
    else {
        Espera->Item[Espera->Fim] = pessoa;
        Espera->Fim = (Espera->Fim + 1) % MAX;
        Espera->Total++;
    }
}

void Remove_Elemento_Lista(Lista_est *Teatro, Espetaculo *espetaculo) {
	int p, i;

	if (Verifica_Lista_Vazia(*Teatro)) {
		printf("A lista já está vazia, impossível remover elemento.\n");
	}
	else {
		p = Teatro->Prim;

		while ((p < Teatro->Ult) && (espetaculo->data != Teatro->Item[p].data)) {
			p++;
		}
		if (p == Teatro->Ult) {
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

void Desenfileirar(Fila_est *Espera, Pessoa *pessoa) {
    if (Verifica_Fila_Vazia(*Espera)) {
        printf("Nao hÃ¡ setores na fila.");
    }
    else {
        *pessoa = Espera->Item[Espera->Inicio];
        printf("Pessoa removida:\n");
		//Exibir_Pessoa(*pessoa);
        Espera->Inicio = (Espera->Inicio + 1) % MAX;
        Espera->Total--;
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

void Preencher_Sessao(Sessao sessao) {
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

void Tempo_Atual(Data *data) {
	time_t tempo_atual;
	time(&tempo_atual);
	*data = localtime(&tempo_atual);
}

void Ler_Espetaculo(Espetaculo *espetaculo) {
	printf("\nNome do espetaculo: ");
	fgets (espetaculo->nome, 200, stdin);
	printf("\nPreco do ingresso: ");
	scanf("%f", &espetaculo->ingresso);
	Inicializar_Sessao(espetaculo->sessao);
	Preencher_Sessao(espetaculo->sessao);
	Tempo_Atual(&espetaculo->data); //Temporário
}

void Exibir_Espetaculo(Espetaculo espetaculo) {
	printf("\nNome do espetaculo: %s", espetaculo.nome);
	printf("\nData do espetaculo: %s", asctime(espetaculo.data));
	printf("\nPreco do ingresso: %.2f", espetaculo.ingresso);
	printf("\nLotacao da sessao:\n");
	Exibir_Sessao(espetaculo.sessao);
}

void Ler_Pessoa(Pessoa *pessoa) {
	printf("\nDigite seu nome: ");
	fgets (pessoa->nome, 200, stdin);
	printf("\nDigite seu CPF: ");
	scanf("%d", &pessoa->CPF);
}

void gravar_Arquivo(Espetaculo *espetaculo, Lista_est *Teatro) {
    arq = fopen("arquivo.dat", "wb");
    if(arq!=NULL)
    {
        int p = Teatro->Prim;
        int i;
        for(i = Teatro->Ult; i > p; i--)
        {
            fwrite(&(Teatro->Item[i]), sizeof(Espetaculo),1,arq);
        }
        fclose(arq);
    }
}

void ler_Arquivo (Espetaculo espetaculo, Lista_est *Teatro) {
    arq = fopen("arquivo.dat", "rb");
    if (arq!=NULL) {
        Criar_Lista_Vazia(&(*Teatro));
        espetaculo.nome[0] = NULL;
        while (!feof(arq))
        {
            if(espetaculo.nome[0]  != NULL)
            Insere_Elemento_Lista(&(*Teatro), espetaculo);
            fread(&espetaculo, sizeof(Espetaculo), 1, arq);   //fechamento
        }
        fclose(arq);
    }
}

void cls(void){
    #ifdef LINUX
        printf("\e[H\e[2J");
        #elif defined WIN32
        system ("cls");
    #else
        printf("\e[H\e[2J");
    #endif
}

int main () {
	srand((unsigned int)time(NULL));

	Sessao sessao;
	Espetaculo espetaculo;
	Lista_est Teatro;

	ler_Arquivo(espetaculo, &Teatro);
	//Ler_Espetaculo(&espetaculo);
    Exibir_Espetaculo(espetaculo);




	Exibir_Espetaculo(espetaculo);

	gravar_Arquivo(&espetaculo, &Teatro);

	return 0;
}
