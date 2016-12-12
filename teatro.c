#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <locale.h>
#include <string.h>
#define MAX 20
#define MAX_PESSOAS 50
#define RESERVADO '#'
#define VENDIDO 'X'
#define VAGO 'O'
#define LIMITE 10

typedef struct tm *Data;

FILE *arq;

typedef struct {
	char nome[50];
	long CPF;
	long conta_bancaria;
}Pessoa;

typedef struct {
    char status[2];
	Pessoa pessoa;
}Assento;

typedef Assento Sessao[18][20];

typedef struct {
    Pessoa Item[MAX_PESSOAS];
    int Inicio, Fim, Total;
}Fila_est;

typedef struct {
	char nome[50];
	int codigo;
	Sessao sessao;
	long long data;
	float ingresso;
	Fila_est fila_espera;
}Espetaculo;

typedef struct {
    Espetaculo Item[MAX];
    int Prim, Ult;
}Lista_est;

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
    return((Espera.Fim + 1) % MAX_PESSOAS == Espera.Fim );
}

void Tempo_Atual(long long *data) {
	time_t tempo_atual;
	time(&tempo_atual);
	Data temp = localtime(&tempo_atual);
	*data = mktime(temp);
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

void Exibir_Espetaculo(Espetaculo espetaculo) {
	printf("Código: %d", espetaculo.codigo);
	printf("\nNome do espetaculo: %s", espetaculo.nome);
	printf("\nData do espetaculo: %s", ctime(&espetaculo.data));
	printf("\nPreco do ingresso: %.2f", espetaculo.ingresso);
	printf("\nLotacao da sessao:\n");
	printf("\n%c - VAGO\n%c - RESERVADO\n%c - VENDIDO\n\n", VAGO, RESERVADO, VENDIDO);
	Exibir_Sessao(espetaculo.sessao);
}

void Insere_Elemento_Lista(Lista_est *Teatro, Espetaculo espetaculo) {
	int p;

	p = Teatro->Prim;
	if(Verifica_Lista_Cheia(*Teatro)){
		printf("Foi atingida a capacidade máxima de espetáculos do teatro!\n");
	}
	else {
		long long hoje;
		Tempo_Atual(&hoje);
		if (hoje > espetaculo.data) {
			printf("\nEspetaculo expirado.\n");
			Exibir_Espetaculo(espetaculo);
		} else {
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
}

void Enfileirar(Fila_est* Espera, Pessoa pessoa) {
    if(Verifica_Fila_Cheia(*Espera)) {
        printf("Nao podem ser inseridos mais pessoas, fila de espera cheia.\n");
    }
    else {
        Espera->Item[Espera->Fim] = pessoa;
        Espera->Fim = (Espera->Fim + 1) % MAX_PESSOAS;
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
        Espera->Inicio = (Espera->Inicio + 1) % MAX_PESSOAS;
        Espera->Total--;
    }
}

void Exibir_Pessoa(Pessoa pessoa) {

    printf("--------------------------------");
    printf("Nome: %s", pessoa.nome);
    printf("CPF: %d", pessoa.CPF);
    printf("--------------------------------");

}

void Exibir_Fila_Espera(Fila_est Espera) {
	Exibir_Pessoa(Espera.Item[Espera.Inicio]);
}

void Vender_Ingresso(int l, int c, Sessao sessao, Pessoa pessoa) {
	if(sessao[l][c].status[0] == VAGO) {
		sessao[l][c].status[0] = VENDIDO;
		sessao[l][c].pessoa = pessoa;
		printf("Poltrona Ocupada com Sucesso.");
	} else {
		printf("Poltrona nao Disponivel.");
	}
}

void Reservar_Ingresso(int l, int c, Sessao sessao, Pessoa pessoa) {
	if(sessao[l][c].status[0] == VAGO) {
        sessao[l][c].status[0] = RESERVADO;
        sessao[l][c].pessoa = pessoa;
		printf("Poltrona Ocupada com Sucesso.");
	} else {
		printf("Poltrona nao Disponivel.");
	}
}

int Pessoa_Igual(Pessoa a, Pessoa b) {
	if (a.conta_bancaria == b.conta_bancaria && a.CPF == b.CPF && strcmp(a.nome, b.nome) == 0) {
		return 1;
	}
	return 0;
}

void Confirmar_Reserva(int l, int c, Sessao sessao, Pessoa pessoa) {
	if(sessao[l][c].status[0] == RESERVADO && Pessoa_Igual(sessao[l][c].pessoa, pessoa)) {
        sessao[l][c].status[0] = VENDIDO;
		printf("Reserva confirmada com Sucesso.");
	} else {
		printf("Falha na confirmacao da reserva.");
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

int Verificar_Sessao_Cheia(Sessao sessao) {
	int i, j;
	for (i = 0; i < 18; i++) {
		for (j = 0; j < 20; j++) {
			if(sessao[i][j].status[0] == VAGO) {
                return 0;
			}
		}
	}
	return 1;
}

void Ler_Data(time_t *data) {
	char dia[11], hora[6];
	setbuf(stdin, NULL);
	printf("\nData do espetaculo (dd/mm/aaaa): ");
	scanf("%[^\n]s", dia);
	setbuf(stdin, NULL);
	printf("\nHorario do espetaculo (hh:mm): ");
	scanf("%[^\n]s", hora);
	
	Data evento;
	evento->tm_sec = 0;
	evento->tm_min = (hora[3] - '0') * 10 + (hora[4] - '0');
	evento->tm_hour = (hora[0] - '0') * 10 + (hora[1] - '0');
	evento->tm_mday = (dia[0] - '0') * 10 + (dia[1] - '0');
	evento->tm_mon = ((dia[3] - '0') * 10 + (dia[4] - '0')) - 1;
	evento->tm_year = ((dia[6] - '0') * 1000 + (dia[7] - '0') * 100 + (dia[8] - '0') * 10 + (dia[9] - '0')) - 1900;
	evento->tm_isdst = -1;

	*data = mktime(evento);
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
	Tempo_Atual(&espetaculo->data);
	Ler_Data(&espetaculo->data); //Temporário
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
        printf("Nao ha espetaculos cadastrados.\n");
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
        else printf("Espetaculo nao cadastrado.\n");
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
	setbuf(stdin, NULL);
	printf("\nDigite o numero do sua conta bancaria: ");
	scanf("%d", &pessoa->conta_bancaria);
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
	Fila_est espera;
	Pessoa pessoa;
	Ler_Arquivo(&espetaculo, &Teatro);

	int index = -1, escolha, erros = 0, opcao;

	while (index != 0 && erros < LIMITE) {
		//Fornece as opcoes do TAD.
		printf("=============MENU MACHADO DE ASSIS=============\n\n");
		printf("Escolha alguma das opcoes abaixo:\n\n");
		printf("0 - Sair do Sistema.\n");
		printf("1 - Inserir Novo Espetaculo\n");
		printf("2 - Exibir Todos os Espetaculos\n");
		printf("3 - Buscar Espetaculo\n");
		printf("4 - Comprar Ingresso\n");
		printf("5 - Reservar Poltrona\n");
		printf("6 - Confirmar Reserva\n");
		printf("7 - Exibir primeiro da lista de espera\n");
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
				if(!Verificar_Sessao_Cheia(Teatro.Item[espe].sessao)) {
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
                        Ler_Pessoa(&pessoa);
                        Vender_Ingresso(linha, coluna-1, Teatro.Item[espe].sessao, pessoa);
                    }
				}
				else {
                    printf("\nSessão Cheia. Adicionando na lista de Espera");
                    Ler_Pessoa(&pessoa);
                    Enfileirar(&Teatro.Item[espe].fila_espera, pessoa);
                    printf("Adicionado na Lista de espera:\n");
                    Exibir_Pessoa(pessoa);
				}
			    break;

			case 5:
			    printf("Digite o Codigo do Espetaculo: ");
				scanf("%d", &escolha);
                espe = Consultar_Espetaculo(Teatro, escolha);
                if(!Verificar_Sessao_Cheia(Teatro.Item[espe].sessao)) {
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
                        Ler_Pessoa(&pessoa);
                        Reservar_Ingresso(linha, coluna-1, Teatro.Item[espe].sessao, pessoa);
                    }
                }
                else {
                    printf("\nSessão Cheia. Adicionando na lista de Espera");
                    Ler_Pessoa(&pessoa);
                    Enfileirar(&Teatro.Item[espe].fila_espera, pessoa);
                    printf("Adicionado na Lista de espera:\n");
                    Exibir_Pessoa(pessoa);
                }
			    break;

			case 6:
				printf("Digite o Codigo do Espetaculo: ");
				scanf("%d", &escolha);
                espe = Consultar_Espetaculo(Teatro, escolha);
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
                Ler_Pessoa(&pessoa);
                Confirmar_Reserva(linha, coluna-1, Teatro.Item[espe].sessao, pessoa);
			    break;

			case 7:
				printf("Digite o Codigo do Espetaculo: ");
				scanf("%d", &escolha);
                espe = Consultar_Espetaculo(Teatro, escolha);
                Exibir_Fila_Espera(Teatro.Item[espe].fila_espera);
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
