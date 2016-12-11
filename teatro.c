#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <locale.h>
#define MAX 20
#define RESERVADO '#'
#define VENDIDO 'X'
#define VAGO 'O'
#define LIMITE 10
#define MAX_SESSAO 360

typedef struct tm *Data;

FILE *arq;

typedef struct {
	char nome[50];
	int CPF;
}Pessoa;

typedef struct {
    char status[2];
	Pessoa pessoa;
}Assento;

typedef Assento Sessao[18][20];

typedef struct {
	char nome[50];
	int codigo;
	Sessao sessao;
	time_t data;
	float ingresso;
	int lotacao;
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

void Vender_Ingresso(Espetaculo espetaculo, int l, int c, Sessao sessao) {
	if(sessao[l][c].status[0] == VAGO) {
		sessao[l][c].status[0] = VENDIDO;
		printf("Poltrona Ocupada com Sucesso");
		espetaculo.lotacao--;
	} else {
		printf("Poltrona nao Disponivel");
	}
}

void Reservar_Ingresso(Espetaculo espetaculo, int l, int c, Sessao sessao) {
	if(sessao[l][c].status[0] == VAGO) {
        sessao[l][c].status[0] = RESERVADO;
		printf("Poltrona Ocupada com Sucesso");
		espetaculo.lotacao--;
	} else {
		printf("Poltrona nao Disponivel");
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

void Tempo_Atual(time_t *data) {
	time_t tempo_atual;
	time(&tempo_atual);
	Data temp = localtime(&tempo_atual);
	*data = mktime(temp);
}

void Ler_Espetaculo(Espetaculo *espetaculo) {

	setbuf(stdin, NULL);
	printf("\nNome do espetaculo: ");
	scanf("%[^\n]s", espetaculo->nome);
	setbuf(stdin, NULL);
	printf("\nDigite o Codigo de Identificacao do Espetaculo: ");
	scanf("%d", &espetaculo->codigo);
	setbuf(stdin, NULL);
	printf("\nPreco do ingresso: ");
	scanf("%f", &espetaculo->ingresso);
	Inicializar_Sessao(espetaculo->sessao);
	Tempo_Atual(&espetaculo->data); //Temporário
	espetaculo->lotacao = MAX_SESSAO;
}

void Exibir_Espetaculo(Espetaculo espetaculo) {
	printf("Código: %d", espetaculo.codigo);
	printf("\nNome do espetaculo: %s", espetaculo.nome);
	printf("\nData do espetaculo: %s", ctime(&espetaculo.data));
	printf("\nPreco do ingresso: %.2f", espetaculo.ingresso);
	printf("\nLotacao da sessao:\n");
	Exibir_Sessao(espetaculo.sessao);
}

void Exibir_Todos_Espetaculos(Lista_est Teatro) {
    int P = Teatro.Prim;
    if(Verifica_Lista_Vazia(Teatro)) {
        printf("Nao ha espetaculos cadastrados.");
    }
    else {
        while(P < Teatro.Ult) {
        Exibir_Espetaculo(Teatro.Item[P]);
        P++;
        }
    }
}

int Consultar_Espetaculo(Lista_est Teatro, int codigo){

    int i;

    if(Verifica_Lista_Vazia(Teatro)) {
        printf("Nao ha espetaculos cadastrados\n");
        return 0;
    }
    else {
        i = Teatro.Prim;

        while ((i < Teatro.Ult) && (codigo != Teatro.Item[i].codigo))
            i++;
        if(i < Teatro.Ult) {
            Exibir_Espetaculo(Teatro.Item[i]);
            printf("%d\n", i);
            return i;
        }
        else printf("Espetaculo nao cadastrado\n");
        return 0;
    }

}

void Ler_Pessoa(Pessoa *pessoa) {
    setbuf(stdin, NULL);
	printf("\nDigite seu nome: ");
	scanf("%[^\n]s", pessoa->nome);
	setbuf(stdin, NULL);
	printf("\nDigite seu CPF: ");
	scanf("%d", &pessoa->CPF);
}

void Gravar_Arquivo(Lista_est *Teatro) {
	arq = fopen("arquivo.dat", "wb+");
    if(arq != NULL) {
        fwrite(&(Teatro->Item), sizeof(Espetaculo), Teatro->Ult, arq);
        fclose(arq);
    }
}

void Ler_Arquivo (Espetaculo *espetaculo, Lista_est *Teatro) {
    arq = fopen("arquivo.dat", "rb");
    Criar_Lista_Vazia(&(*Teatro));
    if (arq!=NULL) {
        while (!feof(arq)) {
            fread(&(*espetaculo), sizeof(Espetaculo), 1, arq);
            Insere_Elemento_Lista(&(*Teatro), *espetaculo);
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

	Espetaculo espetaculo;
	Lista_est Teatro;
	Ler_Arquivo(&espetaculo, &Teatro);

	int index = -1, escolha, erros = 0, opcao;

	while (index != 0 && erros < LIMITE) {
		//Fornece as opcoes do TAD.
		printf("=============MENU MACHADO DE ASSIS=============\n\n");
		printf("Escolha alguma das opcoes abaixo:\n\n");
		printf("0 - Sair do Sistema.\n");
		printf("1 - Inserir Novo Espetaculo\n");
		printf("2 - Exibir Todos os Espetaculo\n");
		printf("3 - Buscar Espetaculo\n");
		printf("4 - Comprar Ingresso\n");
		printf("5 - Reservar Poltrona\n");
		printf("===============================================\n");

		scanf("%d", &index);

	    switch (index) {

			case 0:
			   	Gravar_Arquivo(&Teatro);
			    printf("Obrigado por usar nosso programa.\n");
				return 0;

			case 1:
			    Ler_Espetaculo(&espetaculo);
	            Insere_Elemento_Lista(&Teatro, espetaculo);
	            break;

			case 2:
			    Exibir_Todos_Espetaculos(Teatro);
				break;

			case 3:
				printf("Digite o codigo do Espetaculo: ");
				scanf("%d", &escolha);
				Consultar_Espetaculo(Teatro, escolha);
				break;
			case 4:
				printf("Digite o Codigo do Espetaculo: ");
				scanf("%d", &escolha);
				int espe = Consultar_Espetaculo(Teatro, escolha);
				if(espe >= 0) {
                    printf("\nEscolha a poltrona Desejada: ");
                    char poltrona[4];
                    scanf("%s", poltrona);
                    if(poltrona[0] > 90) {
                        poltrona[0] = poltrona[0] - 32;
                        //Converter minúsculo para maiúsculo
                    }
                    int linha = poltrona[0] - 'A';
                    int i = 1;
                    int coluna = 0;
                    while(poltrona[i] != '\0') {
                        coluna = (coluna * 10) + (poltrona[i] - '0');
                        i++;
                    }
                    Ler_Pessoa(&Teatro.Item[espe].sessao[linha][coluna].pessoa);
                    Vender_Ingresso(Teatro.Item[espe], linha, coluna-1, Teatro.Item[espe].sessao);
                    printf("\nHa um total de %d cadeiras livres.", espetaculo.lotacao);
				}
			    break;

			case 5:

			    printf("Digite o Codigo do Espetaculo: ");
				scanf("%d", &escolha);
                espe = Consultar_Espetaculo(Teatro, escolha);
                if(espe >= 0) {
                    printf("\nEscolha a poltrona Desejada: ");
                    char poltrona[4];
                    scanf("%s", poltrona);
                    if(poltrona[0] > 90) {
                        poltrona[0] = poltrona[0] - 32;
                    }
                    int linha = poltrona[0] - 'A';
                    int i = 1;
                    int coluna = 0;
                    while(poltrona[i] != '\0') {
                        coluna = (coluna * 10) + (poltrona[i] - '0');
                        i++;
                    }
                    Ler_Pessoa(&Teatro.Item[espe].sessao[linha][coluna].pessoa);
                    Reservar_Ingresso(Teatro.Item[espe], linha, coluna-1, Teatro.Item[espe].sessao);
                }

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
		getchar();

		cls();
	}
	return 0;
}
