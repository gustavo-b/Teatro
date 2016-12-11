#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <locale.h>
#define MAX 100
#define RESERVADO '#'
#define VENDIDO 'X'
#define VAGO 'O'
#define LIMITE 10

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
		printf("Foi atingida a capacidade máxima de espetáculos do teatro!\n");
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
        printf("Nao podem ser inseridos mais pessoas, fila de espera cheia.\n");
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
        printf("Nao ha setores na fila.");
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
	scanf("%s", espetaculo->nome);
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

	Criar_Lista_Vazia(&Teatro);

    ler_Arquivo(espetaculo, &Teatro);
    //Antes de tudo ele acrescenta na Lista os Espetaculos

    int index = -1, escolha, erros = 0, opcao;

		while (index != 0 && erros < LIMITE){
		//Fornece as opcoes do TAD.
		printf("=============MENU MACHADO DE ASSIS=============\n\n");
		printf("Escolha alguma das opcoes abaixo:\n\n");
		printf("0 - Sair do Sistema.\n");
		printf("1 - Inserir Novo Espetaculo\n");
		printf("2 - Exibir Espetaculo\n");
		printf("===============================================\n");

		scanf("%d", &index);

    switch (index) {

		case 0:
		    gravar_Arquivo(&espetaculo, &Teatro);
		    printf("Obrigado por usar nosso programa.");
			return 0;

		case 1:
		    Ler_Espetaculo(&espetaculo);
            Insere_Elemento_Lista(&Teatro, espetaculo);
            break;

		case 2:
		    Exibir_Espetaculo(espetaculo);
			break;

		case 3:
			break;
		case 4:
		    break;

		case 5:
		    break;

		case 6:
		    break;

		case 7:
            break;

		case 8:

            break;

        case 9:
        	break;

        case 10:
        	break;

		default:
            erros++;
            break;
		}

		getchar();

		cls();
	}

	return 0;
}
