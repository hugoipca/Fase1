//Hugo Bessa nº 18602
//IPCA EST - EDA 2022/2023

#include <stdio.h>
#include <stdlib.h>

typedef struct structCliente {
	int pos;
	char nome[50];
	int NIF;
	char morada[100];
	struct structCliente* seguinte;
} Cliente;


Cliente* inserirCliente(Cliente* inicio, int pos, char nome[], int nif, char morada[]);

int existeCliente(Cliente* inicio, int nif);

void listarClientes(Cliente* inicio);

//void guardarClientesTxt(Cliente* clientes, char* nomeArquivo);

Cliente* removerCliente(Cliente* inicio, int cod);

int guardarClientes(Cliente* inicio);

Cliente* lerClientes();