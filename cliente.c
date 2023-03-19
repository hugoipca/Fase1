//Hugo Bessa nº 18602
//IPCA EST - EDA 2022/2023

#include "cliente.h"
#pragma warning(disable : 4996) //fopen_S

Cliente* inserirCliente(Cliente* inicio, int pos, char nome[], int nif, char morada[]) {
	if (!existeCliente(inicio, pos)) {
		Cliente* novoCliente = malloc(sizeof(struct structCliente));
		if (novoCliente != NULL) {
			novoCliente->pos = pos;
			strcpy(novoCliente->nome, nome);
			novoCliente->NIF = nif;
			strcpy(novoCliente->morada, morada);
			novoCliente->seguinte = inicio;
			return novoCliente;
		}
	}
	else return inicio;
	return 0;
}

int existeCliente(Cliente* inicio, int nif) {
	while (inicio != NULL) {
		if (inicio->NIF == nif) {
			return 1;
		}
		inicio = inicio->seguinte;
	}
	return 0;
}

void listarClientes(Cliente* inicio) {
	while (inicio != NULL) {
		printf("%d %s %d %s\n", inicio->pos, inicio->nome, inicio->NIF, inicio->morada);
		inicio = inicio->seguinte;
	}
}

/*void guardarClientesTxt(Cliente* clientes, char* nomeArquivo) {
	FILE* arquivo = fopen(nomeArquivo, "w"); //write mode
	if (arquivo == NULL) {
		perror("");
		return;
	}

	Cliente* atual = clientes;
	while (atual != NULL) {
		fprintf(arquivo, "%d|%s|%d|%s\n",atual->pos, atual->nome, atual->NIF, atual->morada);
		atual = atual->seguinte;
	}

	fclose(arquivo);
	printf("Clientes guardados em %s.\n", nomeArquivo);
}*/

Cliente* removerCliente(Cliente* inicio, int cod) {

	Cliente* anterior = inicio, * atual = inicio, * auxiliar;

	if (atual == NULL) {
		return NULL; // lista ligada vazia
	}
	else if (atual->pos == cod) { // remoção do 1º registo
		auxiliar = atual->seguinte;
		free(atual);
		return auxiliar;
	}
	else {
		while ((atual != NULL) && (atual->pos != cod)) {
			anterior = atual;
			atual = atual->seguinte;
		}
		if (atual == NULL) {
			return inicio;
		}
		else {
			anterior->seguinte = atual->seguinte;
			free(atual);
			return inicio;
		}
	}
}

int guardarClientes(Cliente* inicio) {
	FILE* fp;
	fp = fopen("clientes.txt", "w"); //write mode
	if (fp != NULL) {
		Cliente* aux = inicio;
		while (aux != NULL) {
			fprintf(fp, "%d %s %d %s\n", aux->pos, aux->nome, aux->NIF, aux->morada);
			aux = aux->seguinte;
		}
		fclose(fp);
		return 1;
	}
	else return 0;
}

Cliente* lerClientes() {
	FILE* fp;
	char line[100]; // cada linha do ficheiro n pode ter mais de 100 chars
	int pos, nif;
	char nome[50], morada[100];
	Cliente* aux = NULL;
	//pos nome nif morada

	fp = fopen("clientes.txt", "r"); //read mode
	if (fp != NULL) {
		while (fgets(line, sizeof(line), fp) != NULL) {
			(void)sscanf(line, "%d %s %d %s", &pos, nome, &nif, morada);
			aux = inserirCliente(aux, pos, nome, nif, morada);
		}
		fclose(fp);
	}
	return aux;
}