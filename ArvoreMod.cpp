#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <windows.h>

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

	int ajuda = 0;
	int sair = 0;
	int ops;


struct arvore
{
	int valor;
	struct arvore *ant;
	struct arvore *direita;
	struct arvore *esquerda;
};

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

//GRAVA OS VALORES ORGANIZADOS EM "pre-ordem.txt"

void grava(){
	FILE *arqGRAVA;
	arqGRAVA = fopen("pre-ordem.txt", "w");
	for (int i = 0; i <= cont; i++){
		fprintf(arqGRAVA, " %d", valores[i]);
	}
	fclose(arqGRAVA);
	_getch();
}

void apaga(){
	remove("pre-ordem.txt");
}



//PEGA OS VALORES DO ARQUIVO "pega.txt" 

void pega(){
	FILE *arqPEGA;
	arqPEGA = fopen("pre-ordem.txt", "r");
	if (arqPEGA == NULL){
		printf("ERROR 404 FILE NOT FOUND");
	}
	else{
		while ((fscanf(arqPEGA, "%i ", &num)) != EOF)
			(vetortxt[quant] = num, quant++);

		fclose(arqPEGA);
	}
}

//ORGANIZA OS VALORES DA ARVORE EM PRÉ-ORDEM

void backup(arvore *raiz)
{
	if (ops2 == 1){
		if (raiz != NULL){
			if (raiz->valor != 0){
				printf(" %i|", raiz->valor);
			}
			valores[cont] = raiz->valor;
			cont++;
			backup(raiz->esquerda);
			backup(raiz->direita);
		}
	}
}

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

void preOrdem(){
	// pre Ordem
			arvore *preOrdem= primeiro;
			int i;
			int j=0;
			int fim=0;
			int vetor [20];
			for(i=0;i<20;i++){
				vetor[i]=999;
			}
			
			int flag=0;
			int nav=0;//Fica andando pela arvore contando se esta subindo ou descendo
			int profundidade=0;
			
			
			vetor[j]=preOrdem->valor;
			j++;
			
			for(;;){
				if(flag == 0){//esquerda
					if(preOrdem->esquerda != NULL){
						preOrdem = preOrdem->esquerda;
						vetor[j] = preOrdem->valor;
						j++;
						nav+=1;
						if(nav > profundidade){
							profundidade = nav;
						}
					}else if((preOrdem->esquerda == NULL)&&(preOrdem->direita != NULL)){
						flag=1;
					}else if((preOrdem->esquerda == NULL)&&(preOrdem->direita == NULL)){
						flag=2;
					}
					
				}else if(flag == 1){//direita
					if(preOrdem->direita != NULL){
						preOrdem=preOrdem->direita;
						vetor[j]=preOrdem->valor;
						j++;
						
						nav+=1;
						if(nav > profundidade){
							profundidade = nav;
						}
						
						if(preOrdem->esquerda != NULL){
							flag=0;
						}
						
					}else if((preOrdem->esquerda == NULL)&&(preOrdem->direita == NULL)){
						flag=2;
					}
				}else if(flag == 2){//subindo
					if(preOrdem->ant != NULL){
						preOrdem=preOrdem->ant;
						
						nav-=1;
						
						int pe=0;
						int pd=0;
						for(i=0;i<20;i++){
							
							if(preOrdem->esquerda != NULL){
								if(preOrdem->esquerda->valor == vetor[i]){
									pe=1;
								}
							}else{
								pe=1;
							}
							if(preOrdem->direita != NULL){
								if(preOrdem->direita->valor == vetor[i]){
									pd=1;
								}
							}else{
								pd=1;
							}
						}
						if((pe==1)&&(pd==1)){
							flag=2;
						}else if((pe==0)&&(pd==1)){
							flag=0;
						}else if((pe==1)&&(pd==0)){
							flag=1;
						}
						
					}else if(preOrdem->direita == NULL){
						flag=3;
					}else if(preOrdem->direita != NULL){
						flag=1;
						fim+=2;
						if(fim == 2){
							flag=3;
						}
					}
				}else if(flag == 3){//acabou
					break;
				}	
			}
	
			printf("\nVetor Pronto \n\n");
			for(i=0;i<20;i++){
				if(vetor[i] != 999){
					printf(" %i -",vetor[i]);	
				}
			}
			printf("\n\nA profundidade maxima da arvore e igual a {%i}\n\n", profundidade);
				
			system("pause");
		
		//fim Pre Ordem
}

void emOrdem(){
	arvore *preOrdem= primeiro;
	int vetor[20];
	int i=0;
	int flagD = 0;
	int flagE = 0;
	int flag = 0;
	
	for(int j=0;j<20;j++){
		vetor[j] = 999;
	}
	
	while(preOrdem->esquerda != NULL){
		preOrdem = preOrdem->esquerda;
	}
	
	vetor[i] = preOrdem->valor;
	i++;
	
	for(;;){
		for(int j=0;j<20;j++){
			flag=0;
			flagE=0;
			flagD=0;
			
			if(vetor[j] == preOrdem->valor){
				flag = 1;
				printf("Flag\n\n");
				break;
			}else if (vetor[j] == preOrdem->esquerda->valor){
				flagE = 1;
				printf("FlagE\n\n");
				break;
			}else if (vetor[j] == preOrdem->direita->valor){
				flagD = 1;
				printf("FlagD\n\n");
				break;
			}else if (flag==1 && flagE==1 && flagD==1) {
				preOrdem = preOrdem->ant;
				printf("Voltei\n\n");
				break;
			}
		}
		
			
		if(flag == 0){
			vetor[i] = preOrdem->valor;
			i++;
			printf("%d ", preOrdem->valor);
		}else if(flagE == 0){
			preOrdem = preOrdem->esquerda;
			vetor[i] = preOrdem->valor;
			i++;
			printf("%d ", preOrdem->valor);
		}else if(flagD == 0){
			preOrdem = preOrdem->direita;
			vetor[i] = preOrdem->valor;
			i++;
			printf("%d ", preOrdem->valor);
		}
	}
	
	
	for(int j=0;j<20;j++){
		printf("%d - ", vetor[j]);
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
		printf("6--> Sair ");
		ops = _getch();
		if (ops == SEIS){
			char a;
			system("cls");
			printf("Realmente deseja sair? (1 sair/2 continuar)\n");
			a = _getch();
			if ((a == UM)){
				sair++;
			}
		}
		else if (ops==CINCO){
			preOrdem();
		}
		else if (ops == QUATRO){
			system("cls");
			if (primeiro == NULL){
				printf("\n\nArvore vazia!!!");
			}
			else{
				emOrdem();

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
					}
					else if (ajuda > aux->valor){
						aux->direita = atual;
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
						printf("[%d]", posicaoAtual->valor);
						printf("----------\n"
							"------[%d]----[%d]------", posicaoAtual->esquerda->valor, posicaoAtual->direita->valor);
						test = 111;
					}
					else if ((posicaoAtual != NULL) && (posicaoAtual->direita != NULL) && (posicaoAtual->esquerda == NULL)){
						system("cls");
						printf("\n\nPara percorer a arvore use as seta <^>, para deletar precione 1, e para sair precione a tecla para baixo\n\n\n");
						printf("\n\n----------");
						printf("[%d]", posicaoAtual->valor);
						printf("----------\n"
							"-------[*]----[%d]------", posicaoAtual->direita->valor);
						test = 101;
					}
					else if ((posicaoAtual != NULL) && (posicaoAtual->esquerda != NULL) && (posicaoAtual->direita == NULL)){
						system("cls");
						printf("\n\nPara percorer a arvore use as seta <^>, para deletar precione 1, e para sair precione a tecla para baixo\n\n\n");
						printf("\n\n----------");
						printf("[%d]", posicaoAtual->valor);
						printf("----------\n"
							"------[%d]----[*]-------", posicaoAtual->esquerda->valor);
						test = 110;
					}
					else if ((posicaoAtual != NULL) && (posicaoAtual->esquerda == NULL) && (posicaoAtual->direita == NULL)){
						system("cls");
						printf("\n\nPara percorer a arvore use as seta <^>, para deletar precione 1, e para sair precione a tecla para baixo\n\n\n");
						printf("\n\n----------");
						printf("[%d]", posicaoAtual->valor);
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
