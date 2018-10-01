#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <windows.h>
#include <malloc.h>

#define UM 49
#define DOIS 50
#define TRES 51
#define QUATRO 52
#define CINCO 53
#define SEIS 54
#define ACIMA 72
#define ABAIXO 80
#define DIREITA 77
#define ESQUERDA 75
#define del 22

int quant = 0;
int i=0;
int profundidade = 0;

	int ajuda = 0;
	int sair = 0;
	int ops;


struct arvore
{
	int valor;
	int balanceamento;
	struct arvore *ant;
	struct arvore *direita;
	struct arvore *esquerda;
} NO;

arvore *atual = NULL;
	arvore *posisaoAnterior = NULL;
	arvore *primeiro = NULL;
	arvore *aux = NULL;
	arvore *posicaoAtual = NULL;
	boolean teste = true,testarq=false;


int valores[50];
int ops2 = 1, num;
int cont = 0;
int vetortxt[50];

typedef struct arvore *PontNo;

//typedef NO* PontNo;

void apagar(){
	arvore *temporaria = posicaoAtual;
	posicaoAtual = temporaria->ant;
	
	if (temporaria->direita == NULL && temporaria->esquerda != NULL){//Com filho a esquerda
		if (temporaria->ant->direita == temporaria){
			temporaria->ant->direita = temporaria->esquerda;
			temporaria->esquerda->ant = temporaria->ant;
			free(temporaria);
			
		}else if (temporaria->ant->esquerda == temporaria){
			temporaria->ant->esquerda = temporaria->esquerda;
			temporaria->esquerda->ant = temporaria->ant;
		}
	}else if (temporaria->esquerda == NULL && temporaria->direita != NULL){//Com filho a direita
		if (temporaria->ant->direita == temporaria){
			temporaria->ant->direita = temporaria->direita;
			temporaria->direita->ant = temporaria->ant;
		}else if (temporaria->ant->esquerda == temporaria){
			temporaria->ant->esquerda = temporaria->direita;
			temporaria->direita->ant = temporaria->ant;
		}
	}else if (temporaria->esquerda != NULL && temporaria->direita != NULL){//Com 2 filhos
		if (temporaria->esquerda->direita == NULL){
			temporaria->esquerda->direita = temporaria->direita;
			temporaria->esquerda->ant = NULL;
		}else {
			arvore *excluir = temporaria;
			excluir = excluir->esquerda;
			while (excluir->direita != NULL){
				excluir = excluir->direita;
			}
			if (excluir->esquerda == NULL){
				temporaria->valor = excluir->valor;
				excluir->ant->direita = NULL;
				free(excluir);
			}else if (excluir->esquerda != NULL){
				temporaria->valor = excluir->valor;
				excluir->ant->direita = excluir->esquerda;
				excluir->esquerda->ant = excluir->ant;
				free(excluir);
			}
		}
		posicaoAtual = temporaria;
	}else if (temporaria->direita == NULL && temporaria->esquerda == NULL) {
		if (temporaria->ant->direita == temporaria){
			temporaria->ant->direita = NULL;
			free(temporaria);
		}else if (temporaria->ant->esquerda == temporaria){
			temporaria->ant->esquerda = NULL;
			free(temporaria);
		}
	}
}

/* Exibe arvore Em Ordem         */
void exibirArvoreEmOrdem(PontNo raiz){
  	if (raiz == NULL) return;
  	exibirArvoreEmOrdem(raiz->esquerda);
  	printf("%i ",raiz->valor);
  	exibirArvoreEmOrdem(raiz->direita);
}

/* Exibe arvore Pre Ordem         */
void exibirArvorePreOrdem(PontNo raiz){
  	if (raiz == NULL) return;
  	printf("%i ",raiz->valor);
  	exibirArvorePreOrdem(raiz->esquerda);
  	exibirArvorePreOrdem(raiz->direita);
}

/* Exibe arvore Pos Ordem         */
void exibirArvorePosOrdem(PontNo raiz){
  	if (raiz == NULL) return;
  	exibirArvorePosOrdem(raiz->esquerda);
  	exibirArvorePosOrdem(raiz->direita);
  	printf("%i ",raiz->valor);
}

void balanceamentoMenos(PontNo aux){
	aux->balanceamento = aux->balanceamento - 1;
	if(aux->ant != NULL){
		balanceamentoMenos(aux->ant);	
	}
}

void balanceamentoSoma(PontNo aux){
	aux->balanceamento = aux->balanceamento + 1;
	if(aux->ant != NULL){
		balanceamentoSoma(aux->ant);	
	}
}

int contadorProfundidadeArvore(PontNo raiz){
	if(raiz != NULL){
		int altura_esquerda = contadorProfundidadeArvore(raiz->esquerda);
		int altura_direita = contadorProfundidadeArvore(raiz->direita);
		if(altura_esquerda > altura_direita){
			return altura_esquerda + 1;
		}else {
			return altura_direita + 1;
		}
	}
}

int main()
{
	//menu de opsões

	while (sair == 0){
		system("cls");
		printf("1--> Inserir elementos na arvore\n");
		printf("2--> Procurar um numero na arvore\n");
		printf("3--> Percorer a arvore\n");
		printf("4--> Em Ordem\n");
		printf("5--> Pre-Ordem\n");
		printf("6--> Pos-Ordem ");
		ops = _getch();
		if (ops == SEIS){
			profundidade = 0;
			exibirArvorePosOrdem(primeiro);
			printf("\n\nProfundidade = %i", contadorProfundidadeArvore(primeiro) - 1);
			system("pause");
		}
		else if (ops==CINCO){
			profundidade = 0;
			exibirArvorePreOrdem(primeiro);
			printf("\n\nProfundidade = %i", contadorProfundidadeArvore(primeiro) - 1);
			system("pause");
		}
		else if (ops == QUATRO){
			system("cls");
			if (primeiro == NULL){
				printf("\n\nArvore vazia!!!");
			}
			else{
				profundidade = 0;
				exibirArvoreEmOrdem(primeiro);
				printf("\n\nProfundidade = %i", contadorProfundidadeArvore(primeiro) - 1);
				printf("\n\n\n");
				system("pause");

			}
		}

		// inserir elementos na arvore

		else if (ops == UM){

			//se a arvore estiver vazia-------------------------------------------------------------------------------------------

			if (primeiro == NULL){
				system("cls");
				aux = (struct arvore *)malloc(sizeof(struct arvore));
				atual = aux;
				printf("Informe um numero ");
				scanf("%d", &aux->valor);
				fflush(stdin);
				aux->ant = NULL;
				aux->direita = NULL;
				aux->esquerda = NULL;
				primeiro = aux;
				posicaoAtual = aux;
			}

			// se ja tem numeros na arvore

			else if (primeiro != NULL){
				system("cls");
				printf("Informe um numero ");
				scanf("%d", &ajuda);
				gravar:
				fflush(stdin);
				arvore *fim = primeiro;
				posisaoAnterior = primeiro;

				//percorendo a arvore-------------------------------------------------------------------------------------------

				while (fim != NULL){
					if (ajuda > fim->valor){
						fim = fim->direita;
					}
					else if (ajuda < fim->valor){
						fim = fim->esquerda;
					}
					else if (ajuda == fim->valor){
						fim = NULL;
						teste = false;
					}
					if (fim != NULL){
						posisaoAnterior = fim;
					}
				}

				//configurando os ponteiros----------------------------------------------------------------------------------

				if (teste == true){
					aux = (struct arvore *)malloc(sizeof(struct arvore));
					atual = aux;
					aux->valor = ajuda;
					aux->direita = NULL;
					aux->esquerda = NULL;
					aux->ant = posisaoAnterior;
					aux = aux->ant;

					//testando o lado que sera salvo--------------------------------------------------------------------------------

					if (ajuda < aux->valor){
						aux->esquerda = atual;
						/*aux->balanceamento = aux->balanceamento - 1;*/
						
						balanceamentoMenos(aux);						
						/*if(aux->ant != NULL){
							aux->ant->balanceamento = aux->ant->balanceamento - 1;
							if(aux->ant->ant != NULL){
								aux->ant->ant->balanceamento = aux->ant->ant->balanceamento - 1;
								if(aux->ant->ant->ant != NULL){
									aux->ant->ant->ant->balanceamento = aux->ant->ant->ant->balanceamento - 1;
									if(aux->ant->ant->ant->ant != NULL){
										aux->ant->ant->ant->ant->balanceamento = aux->ant->ant->ant->ant->balanceamento - 1;
									}
								}
							}
						}*/
					}
					else if (ajuda > aux->valor){
						aux->direita = atual;
						/*aux->balanceamento = aux->balanceamento + 1;*/
						balanceamentoSoma(aux);
						/*if(aux->ant != NULL){
							aux->ant->balanceamento = aux->ant->balanceamento + 1;
							if(aux->ant->ant != NULL){
								aux->ant->ant->balanceamento = aux->ant->ant->balanceamento + 1;
								if(aux->ant->ant->ant != NULL){
									aux->ant->ant->ant->balanceamento = aux->ant->ant->ant->balanceamento + 1;
									if(aux->ant->ant->ant->ant != NULL){
										aux->ant->ant->ant->ant->balanceamento = aux->ant->ant->ant->ant->balanceamento + 1;
									}
								}
							}
						}*/
					}
				}
			}
			system("cls");
			if (testarq == true){
				printf("\n\nDados restaurados com sucesso !\n\n");
			}
			if (teste == true){
				printf("\n\n\n\nValor (%d) salvo na arvore!!!\n\n", atual->valor);
			}
			else{
				printf("\n\n\n\nO valor (%d) ja esta salvo na arvore, portanto não sera repitido!!!\n\n", ajuda);
			}
			teste = true;
			_getch();
		}

		//caminhando entre os galhos da arvore

		else if (ops == TRES){
			int tecla = 0;
			int test;
			posicaoAtual = primeiro;
			if (primeiro == NULL){
				system("cls");
				printf("\n\n\nArvore vazia!!!");
				_getch();
			}

			if (primeiro != NULL){
				while (tecla != ABAIXO){
					if ((posicaoAtual != NULL) && (posicaoAtual->esquerda != NULL) && (posicaoAtual->direita != NULL)){
						system("cls");
						printf("\n\nPara percorer a arvore use as seta <^>, para deletar precione 1, e para sair precione a tecla para baixo\n\n\n");
						printf("\n\n----------");
						printf("[%d](%d)", posicaoAtual->valor, posicaoAtual->balanceamento);
						printf("----------\n"
							"------[%d]----[%d]------", posicaoAtual->esquerda->valor, posicaoAtual->direita->valor);
						test = 111;
					}
					else if ((posicaoAtual != NULL) && (posicaoAtual->direita != NULL) && (posicaoAtual->esquerda == NULL)){
						system("cls");
						printf("\n\nPara percorer a arvore use as seta <^>, para deletar precione 1, e para sair precione a tecla para baixo\n\n\n");
						printf("\n\n----------");
						printf("[%d](%d)", posicaoAtual->valor, posicaoAtual->balanceamento);
						printf("----------\n"
							"-------[*]----[%d]------", posicaoAtual->direita->valor);
						test = 101;
					}
					else if ((posicaoAtual != NULL) && (posicaoAtual->esquerda != NULL) && (posicaoAtual->direita == NULL)){
						system("cls");
						printf("\n\nPara percorer a arvore use as seta <^>, para deletar precione 1, e para sair precione a tecla para baixo\n\n\n");
						printf("\n\n----------");
						printf("[%d](%d)", posicaoAtual->valor, posicaoAtual->balanceamento);
						printf("----------\n"
							"------[%d]----[*]-------", posicaoAtual->esquerda->valor);
						test = 110;
					}
					else if ((posicaoAtual != NULL) && (posicaoAtual->esquerda == NULL) && (posicaoAtual->direita == NULL)){
						system("cls");
						printf("\n\nPara percorer a arvore use as seta <^>, para deletar precione 1, e para sair precione a tecla para baixo\n\n\n");
						printf("\n\n----------");
						printf("[%d](%d)", posicaoAtual->valor, posicaoAtual->balanceamento);
						printf("----------\n"
							"-------[*]----[*]-------");
						test = 100;
					}
					tecla = _getch();
					if (tecla == ACIMA){
						if (posicaoAtual != primeiro){
							posicaoAtual = posicaoAtual->ant;
						}
					}
					else if (tecla == ESQUERDA){
						if (posicaoAtual->esquerda != NULL){
							posicaoAtual = posicaoAtual->esquerda;
						}
					}
					else if (tecla == DIREITA){
						if (posicaoAtual->direita != NULL){
							posicaoAtual = posicaoAtual->direita;
						}
					}

					//Deletar termos

					else if (tecla == UM){
						apagar();
					}test = 0;
				}
			}
		}

		// encontra um numero especifico

		else if (ops == DOIS){
			if (primeiro == NULL){
				system("cls");
				printf("\n\n\nArvore vazia!!!");
			}
			else if (primeiro != NULL){
				int valor;
				int fim = NULL;
				posicaoAtual = primeiro;
				system("cls");
				printf("\n\n Informe o valor a ser procurado\n ");
				scanf("%d", &valor);
				fflush(stdin);
				while (fim == NULL){
					if (valor == posicaoAtual->valor){
						printf("\n\nO numero [%d] esta na arvore!!!\n\n", posicaoAtual->valor);
						fim = 1;
					}
					else if (valor > posicaoAtual->valor){
						posicaoAtual = posicaoAtual->direita;
					}
					else if (valor < posicaoAtual->valor){
						posicaoAtual = posicaoAtual->esquerda;
					}
					if (posicaoAtual == NULL){
						printf("\n\nO numero [%d] não pertence a esta arvore\n\n!!!", valor);
						fim = 1;
					}
				}
			}
			_getch();
		}
		else{
			system("cls");
			printf("\n\nComando não reconhacido pelo sistema!!!");
			_getch();
			system("cls");
		}
	}
}
