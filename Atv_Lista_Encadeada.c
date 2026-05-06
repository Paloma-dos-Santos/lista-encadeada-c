#include <stdio.h>
#include <stdlib.h>

typedef struct ponto {
	int valor;
	struct ponto *proxPonto; 
} ponto;

typedef struct noCabeca {
	ponto *inicio;
	ponto *fim;
	int qtde;
} noCabeca;


void inicializa(noCabeca *gerenciador) {
	gerenciador->inicio = NULL;
	gerenciador->fim = NULL;
	gerenciador->qtde = 0;
	return;
}


void insereVazio(noCabeca *gerenciador, int valor) {
	ponto *novoPonto;
	novoPonto = (ponto*) malloc(sizeof(ponto));
	if (novoPonto == NULL) {
		printf("Erro\n");
		return;
	}
	novoPonto->valor = valor;
	novoPonto->proxPonto = NULL;
	gerenciador->inicio = novoPonto;
	gerenciador->fim = novoPonto;
	gerenciador->qtde += 1;
	return;
}


void insereInicio(noCabeca *gerenciador, int valor) {
	ponto *novoPonto;
	
	if (gerenciador->inicio == NULL) {
		insereVazio(gerenciador, valor);
		return;
	}
	
	novoPonto = (ponto*) malloc(sizeof(ponto));
	novoPonto->valor = valor;
	novoPonto->proxPonto = gerenciador->inicio;
	gerenciador->inicio = novoPonto;
	gerenciador->qtde += 1;
	return;
}


void insereFim(noCabeca *gerenciador, int valor){
	ponto *novoPonto;
	ponto *auxiliar = gerenciador->fim;
	
	if (gerenciador->fim == NULL) {
		insereVazio(gerenciador, valor);
		return;
	}
	
	novoPonto = (ponto*) malloc(sizeof(ponto));
	if (novoPonto == NULL) {
		printf("Erro");
		return;
	}
	
	novoPonto->valor = valor;
	novoPonto->proxPonto = NULL;
	auxiliar->proxPonto = novoPonto;
	gerenciador->fim = novoPonto;
	gerenciador->qtde += 1;
}


void removeInicio(noCabeca *gerenciador) {
	ponto *auxiliar = gerenciador->inicio;
	gerenciador->inicio = auxiliar->proxPonto;
	gerenciador->qtde -= 1;
	free(auxiliar);
	return;
}


void removeFim(noCabeca *gerenciador) {
	ponto *auxiliar = gerenciador->inicio;
	
	while(1) {
		if(auxiliar->proxPonto == NULL) {
			gerenciador->fim->proxPonto = NULL;
			free(auxiliar);
			break;
		}
		
		if (auxiliar->proxPonto->proxPonto == NULL) {
			gerenciador->fim = auxiliar;
			gerenciador->qtde -= 1;
		}
		auxiliar = auxiliar->proxPonto;
	}
	return;		
}


int pesquisar(noCabeca *gerenciador, int valor) {
	ponto *percorre = gerenciador->inicio;
	
	int i;
	for(i = 0; i < gerenciador->qtde; i++) {
		if (percorre->valor == valor) {
			return i;
		}
		
		percorre = percorre->proxPonto;
	}
	return -1;
}


void inserePos(noCabeca *gerenciador, int valor, int pos) {
	if (pos > gerenciador->qtde) {
		printf("Posicao invalida\n");
		return;
	}
	
	ponto *percorre = gerenciador->inicio;
	ponto *novoPonto = (ponto*) malloc(sizeof(ponto));
	if (novoPonto == NULL) {
		printf("Erro\n");
		return;
	}
	
	if (pos == 0) {
		insereInicio(gerenciador, valor);
		return;
	} else if (pos == (gerenciador->qtde - 1)) {
		insereFim(gerenciador, valor);
		return;
	}
	
	int i;
	for(i = 0; i < gerenciador->qtde; i++) {
		if (i == (pos-1)) {
			novoPonto->proxPonto = percorre->proxPonto;
			percorre->proxPonto = novoPonto;
			novoPonto->valor = valor;
			gerenciador->qtde += 1;
			return;
		}
		
		percorre = percorre->proxPonto;
	}
	return;
}


void removePos(noCabeca *gerenciador, int pos) {
	if (pos > gerenciador->qtde) {
		printf("Posicao invalida\n");
		return;
	}
	
	if (pos == 0) {
		removeInicio(gerenciador);
		return;
	} else if (pos == (gerenciador->qtde - 1)) {
		removeFim(gerenciador);
		return;
	}
	
	ponto *auxiliar, *percorre = gerenciador->inicio;
	
	int i;
	for(i = 0; i < gerenciador->qtde; i++) {
		if (i == (pos-1)) {
			auxiliar = percorre->proxPonto;
			percorre->proxPonto = percorre->proxPonto->proxPonto;
			gerenciador->qtde -= 1;
			free(auxiliar);
			return;
		}	
	}
	return;
}


void destruir(noCabeca *gerenciador) {
	ponto *percorre, *auxiliar = gerenciador->inicio;
	
	int i;
	for(i = 0; i < gerenciador->qtde; i++) {
		percorre = auxiliar->proxPonto;
		free(auxiliar);
		auxiliar = percorre;
	}
	
	gerenciador->inicio = NULL;
	gerenciador->fim = NULL;
	gerenciador->qtde = 0;
	return;
}


void mostraPontos(noCabeca *gerenciador) {
	ponto *percorre = gerenciador->inicio;
	
	while(percorre != NULL) {
		printf("%d\n", percorre->valor);
		percorre = percorre->proxPonto;
	}	
	return;
}


int main() {
	int acao, valor, pos;
	noCabeca gerenciador;
	inicializa(&gerenciador);
	
	while(1) {
		printf("\n");
		printf("Deseja realizar qual acao?\n1-InserirInicio\n2-InserirFim\n3-RemoverInicio\n4-RemoverFim\n5-InserirPosX\n6-RemoverPosX\n7-PesquisarValor\n8-Mostrar\n9-Destruir\n");
		printf("Digite o numero da acao desejada: ");
		scanf("%d", &acao);
		
		printf("\n");
		
		switch(acao) {
			case 1:
				printf("Digite o valor que deseja inserir no inicio: ");
				scanf("%d", &valor);
				insereInicio(&gerenciador, valor);
				break;
			
			case 2:
				printf("Digite o valor que deseja inserir no fim: ");
				scanf("%d", &valor);
				insereFim(&gerenciador, valor);
				break;
				
			case 3:
				printf("Elemento inicial removido.\n");
				removeInicio(&gerenciador);
				break;
				
			case 4:
				printf("Elemento final removido.\n");
				removeFim(&gerenciador);
				break;
				
			case 5:
				printf("Digite o valor que deseja inserir: ");
				scanf("%d", &valor);
				printf("Digite a posi  o que deseja inserir: ");
				scanf("%d", &pos);		
				inserePos(&gerenciador, valor, pos);		
				break;
				
			case 6:
				printf("\nDigite a posicao que deseja remover: ");
				scanf("%d", &pos);
				removePos(&gerenciador, pos);
				break;
				
			case 7:
				printf("Digite o valor que deseja procurar: ");
				scanf("%d", &valor);
				pos = pesquisar(&gerenciador, valor);
				if (pos == -1) {
					printf("Valor nao encontrado\n");
				} else {
					printf("Valor encontrador na pos %d\n", pos);
				}
				break;
				
			case 8:
				mostraPontos(&gerenciador);
				break;
				
			case 9:
				printf("Lista destruida, encerrando programa\n");
				destruir(&gerenciador);
				return 0;
				break;
				
			default:
				printf("Opcao invalida\n");	
		}
	}
	

	return 0;
}

