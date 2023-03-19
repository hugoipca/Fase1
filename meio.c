//Hugo Bessa nº 18602
//IPCA EST - EDA 2022/2023

#include <stdlib.h>
#include <string.h>
#include "meio.h"
#include "gestor.h"
#pragma warning(disable : 4996) //strcopy_s

// inserção realizada no início da lista ligada
MeioTransporte* inserirMeio(MeioTransporte* inicio, int codigo, char tipo[], float bateria, float autonomia, char geocodigo[], int isAlugado) {
	if (!existeMeio(inicio, codigo)) {
		MeioTransporte *novoMeio = malloc(sizeof(struct structRegisto));
		if (novoMeio != NULL) {
			novoMeio->codigo = codigo;
			strcpy(novoMeio->tipo, tipo);
			novoMeio->bateria = bateria;
			novoMeio->autonomia = autonomia;
			strcpy(novoMeio->geocodigo, geocodigo);
			novoMeio->isAlugado = isAlugado;
			novoMeio->seguinte = inicio;
			return novoMeio;
		}
	} else printf("malloc não conseguiu alocar memória!");
	return inicio;
}

// listar na consola o conteúdo da lista ligada
void listarMeios(MeioTransporte* inicio) {
	while (inicio != NULL) {
		printf("%d %s %f %f %s %d\n", inicio->codigo, inicio->tipo, inicio->bateria, inicio->autonomia, inicio->geocodigo, inicio->isAlugado);
		inicio = inicio->seguinte;
	}
}


// determina se o meio existe
// devolve 1 se existir ou 0 caso contrário
int existeMeio(MeioTransporte* inicio, int cod) {
	while (inicio != NULL) {
		if (inicio->codigo == cod) {
			return 1;
		}
	inicio = inicio->seguinte;
	}
	return 0;
}

/*
Meio* removerMeio(Meio* inicio, int cod) // Remover um meio a partir do seu código
{while (inicio!=NULL)
 {if (inicio->codigo==cod) 
	 {aux = inicio->seguinte;
          free(inicio);
	  return(aux);
	 }
  else {inicio = removerMeio(inicio->seguinte,cod);
	return(inicio);
       }
 }
}
*/

// remover um meio a partir do seu código
MeioTransporte* removerMeio(MeioTransporte* inicio, int cod) {
	MeioTransporte *anterior = inicio, *atual = inicio, *auxiliar;
	if (atual == NULL) {
		return NULL; // lista ligada vazia
	} else if (atual->codigo == cod) { // remoção do 1º registo
		auxiliar = atual->seguinte;
		free(atual);
		return auxiliar;
	} else {
		while ((atual != NULL) && (atual->codigo != cod)) {
			anterior = atual;
			atual = atual->seguinte;
		}	
		if (atual == NULL) {
			return inicio;
		} else {
			anterior->seguinte = atual->seguinte;
			free(atual);
			return inicio;
		}
	}
}

void listarMeiosGeocode(MeioTransporte* inicio, char geocode[]) {
	// test 1
	MeioTransporte* atual = inicio;
	while (atual != NULL) {
		if (strcmp(atual->geocodigo, geocode) == 0) { //string sao iguais
			printf("%d %s %f %f %s %d\n",
				atual->codigo, atual->tipo, atual->bateria, atual->autonomia, atual->geocodigo, atual->isAlugado);
		}
		atual = atual->seguinte;
	}
	return inicio;
}

void listarMeiosAlugaveis(MeioTransporte* inicio) {
	// test 1
	MeioTransporte* atual = inicio;
	while (atual != NULL) {
		if (atual->isAlugado == 0) { //0 = nao alugado, 1 = alugado
			printf("%d %s %f %f %s %d\n",
				atual->codigo, atual->tipo, atual->bateria, atual->autonomia, atual->geocodigo, atual->isAlugado);
		}
		atual = atual->seguinte;
	}
}

int alugarMeio(MeioTransporte* inicio, int codigo) {
	MeioTransporte* atual = inicio;
	while (atual != NULL) {
		if (atual->codigo == codigo && atual->isAlugado == 0) {
			atual->isAlugado = 1;
			//registarAluguer(codigo, , 1)
			return 1;
		}
		atual = atual->seguinte;
	}
	return 0;
}

void registarAluguer(int cod, char* nomeUser, int estadoAluguer) {
	FILE* arquivo;
	arquivo = fopen("aluguer.txt", "a"); // abre o arquivo em modo append

	if (arquivo == NULL) {
		printf("Erro ao abrir arquivo.");
		return;
	}
	fprintf(arquivo, "%d %s %d\n", cod, nomeUser, estadoAluguer);
	fclose(arquivo);
}

void listarPorAutonomia(MeioTransporte* inicio) {
	int tamanho = 0, i, j;
	MeioTransporte *atual = inicio;

	//obter tamanho da lista
	while (atual != NULL) {
		tamanho++;
		atual = atual->seguinte;
	}

	//criar array temporário de apontadores para MeioTransporte
	MeioTransporte **temp = malloc(sizeof(MeioTransporte*) *tamanho);

	//copiar os elementos da lista para o array temporário
	atual = inicio;
	for (i = 0; i < tamanho; i++) {
		temp[i] = atual;
		atual = atual->seguinte;
	}
	
	//ordenar o array por ordem decrescente de autonomia usando o algoritmo bubble sort
	for (i = 0; i < tamanho - 1; i++) {
		for (j = 0; j < tamanho - i - 1; j++) {
			if (temp[j]->autonomia < temp[j + 1]->autonomia) {
				MeioTransporte* temp2 = temp[j];
				temp[j] = temp[j + 1];
				temp[j + 1] = temp2;
			}
		}
	}

	//imprimir os elementos ordenados
	for (i = 0; i < tamanho; i++) {
		printf("Codigo: %d, Tipo: %s, Bateria: %f, Autonomia: %f, Geocodigo: %s\n", 
			temp[i]->codigo, temp[i]->tipo, temp[i]->bateria, temp[i]->autonomia, temp[i]->geocodigo);
	}
	
	//libertar a memoria alocada para o array temporario
	free(temp);
}

int alterarDadosMeio(MeioTransporte *inicio, int codigo) {
	int cod, isAlugado;
	float bat, aut;
	char tipo[50], geocode[50];

	if (!existeMeio(inicio, codigo)) {
		printf("Este codigo nao existe na lista ligada!\n");
	} else {
		MeioTransporte* atual = inicio;
		while (atual != NULL) {
			if (atual->codigo == codigo) {
				printf("Novo codigo (ex: 23) : ");
				scanf_s("%d", &cod);
				atual->codigo = cod;

				printf("Novo tipo (ex: Nave Espacial) : ");
				fflush(stdin);
				scanf("%s", &tipo);
				strcpy(atual->tipo, tipo);

				printf("Nova bateria (em mAh - ex 2500) : ");
				fflush(stdin);
				scanf("%f", &bat);
				atual->bateria = bat;

				printf("Nova autonomia (em mins - ex 120) : ");
				fflush(stdin);
				scanf("%f", &aut);
				atual->autonomia = aut;

				printf("Novo geocodigo (ex: tree.formats.keys): ");
				fflush(stdin);
				scanf("%s", &geocode);
				strcpy(atual->geocodigo, geocode);

				printf("Está alugado? (0 = nao, 1 = sim) : ");
				fflush(stdin);
				scanf("%d", &isAlugado);
				atual->isAlugado = isAlugado;

				printf(" [*] Registo guardado com sucesso.\n");
				printf(" [*] Novo Codigo: %d, Novo Tipo: %s, Nova Bateria: %.2f, Nova Autonomia: %.2f, Novo Geocodigo: %s, Alugado: %d\n",
					atual->codigo, atual->tipo, atual->bateria, atual->autonomia, atual->geocodigo, atual->isAlugado);
				break;
			}
			atual = atual->seguinte;
		}
		return inicio;

	}
	return 0;
}

int guardarMeios(MeioTransporte* inicio) {
	FILE* fp;
	fp = fopen("meios.txt", "w"); //write mode
	if (fp != NULL) {
		MeioTransporte* aux = inicio;
		while (aux != NULL) {
			fprintf(fp, "%d %s %f %f %s %d\n", aux->codigo, aux->tipo, aux->bateria, aux->autonomia, aux->geocodigo, aux->isAlugado);
			aux = aux->seguinte;
		}
		fclose(fp);
		return 1;
	}
	else return 0;
}

MeioTransporte* lerMeios() {
	FILE* fp;
	char line[100]; // cada linha do ficheiro n pode ter mais de 100 chars
	int cod, isAlugado;
	float bat, aut;
	char tipo[50], geocode[50];
	MeioTransporte* aux = NULL;

	fp = fopen("meios.txt", "r"); //read mode
	if (fp != NULL) {
		while (fgets(line, sizeof(line), fp) != NULL) {
			(void)sscanf(line, "%d %s %f %f %s %d", &cod, tipo, &bat, &aut, geocode, &isAlugado);
			aux = inserirMeio(aux, cod, tipo, bat, aut, geocode, isAlugado);
		}
		fclose(fp);
	}
	return aux;
}