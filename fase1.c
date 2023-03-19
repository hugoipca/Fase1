//Hugo Bessa nº 18602
//IPCA EST - EDA 2022/2023

#include <stdio.h>
#include "meio.h"
#include <locale.h>
#include "cliente.h"
#include "gestor.h"

#pragma warning(disable : 4996) //scanf_s
#pragma warning(disable : 6031)

int menuGestor() {
	int op;
	printf(" ---------------------- M E N U     G E S T O R ----------------------\n\n");
	printf("	1. Inserir Meio\n");
	printf("	2. Listar Meios\n");
	printf("	3. Remover Meio\n");
	printf("	4. Guardar Meios (.txt)\n");
	printf("	5. Ler Meios (.txt)\n");
	printf("	6. Organizar meios por ordem de autonomia\n");
	printf("	7. Listar meios por geocódigo\n");
	printf("\n");
	printf("	7. Inserir Cliente\n");
	printf("	8. Listar Clientes\n");
	printf("	9. Remover Clientes\n");
	printf("	10. Guardar Clientes (.txt)\n");
	printf("	11. Ler Clientes (.txt)\n");
	printf("	0. Sair\n\n");
	printf("	Opcao: ");
	scanf("%d", &op);
	printf("\n");
	return op;
}

int menuCliente() {
	int op;
	printf(" ---------------------- M E N U     C L I E N T E ----------------------\n\n");
	printf("	1. Listar meios disponiveis para alugar\n");
	printf("	2. Ler Meios .txt\n");
	printf("	3. Listar meios por autonomia\n");
	printf("	4. Alugar um meio de transporte\n"); //listar todos os alugaveis
	printf("	0. Sair\n");
	printf("	Opção: ");
	scanf("%d", &op);
	return op;
}


int main() {
	setlocale(LC_ALL, "Portuguese");
	
	//parte gestor
	int opcao;
	Utilizador usuarios[MAX_USERS];
	int numUsuarios = lerUsuarios(usuarios);
	int gestor = fazerLogin(usuarios, numUsuarios);

	if (gestor == 0) { //still buggy - i think done
		printf("Login falhado. Abrindo menu como cliente...\n");
		gestor = false;
	} else {
		printf("Login efetuado com sucesso! Abrindo menu como gestor...\n");
		gestor = true;
		//mostrar painel de gestor
	}

	MeioTransporte* meios = NULL; // Lista ligada vazia 
	Cliente* clientes = NULL;
	
	int operacao, isAlugado, codigoMeio, posicao, nif;
	float bateria, autonomia;
	char tipo[50], geocode[30], nome[30], morada[50];


	do {
		if (gestor == false) {
			operacao = menuCliente();
		} else operacao = menuGestor();
		
		switch (operacao) {
		case 1:
			if (gestor == true) { //codigo menu gestor - 1. inserir meio
				printf("   ----- 1. Inserir Meio -----");
				printf("\nCodigo : ");
				scanf("%d", &codigoMeio);
				scanf("%*c");
				printf("\nTipo/Nome : ");
				scanf("%[^\n]s", tipo);
				printf("\nNivel da bateria (mAh) : ");
				scanf("%f", &bateria);
				printf("\nAutonomia (mins) : ");
				scanf("%f", &autonomia);
				printf("\nGeocode : ");
				scanf("%s", geocode);
				printf("\nAlugado? (0/1) : ");
				scanf("%d", &isAlugado);
				meios = inserirMeio(meios, codigoMeio, tipo, bateria, autonomia, geocode, isAlugado);
				break;
			}
			else {
				//codigo menu cliente
				//listar meios disponiveis para alugar
				printf("   ----- 1. Meios disponiveis para alugar -----\n");
				listarMeiosAlugaveis(meios);
				break;
			}
			

		case 2:
			if (gestor == true) {
				printf("   ----- 2. Listar Meios -----\n\n"); //gestor
				listarMeios(meios);
				break;
			}
			else {
				printf("   ----- 2. Ler meios .txt -----\n\n"); //cliente
				printf("\n\n");
				meios = lerMeios();
				printf("Meios lidos com sucesso.");
				break;
			}

		case 3:
			if (gestor == true) { //cod gestor
				printf("   ----- 3. Remover meio -----\n\n");
				printf("\n\nCodigo do meio de mobilidade a remover? : ");
				scanf("%d", &codigoMeio);
				meios = removerMeio(meios, codigoMeio);
				printf("\nMeio removido com sucesso.\n\n");
				listarMeios(meios);
				break;
			}
			else {
				//cod cliente - listar meios por autonomia
				printf("   ----- 6. Listar meios por ordem decrescente de autonomia -----\n\n");
				listarPorAutonomia(meios);
				break;
			}
			

			//listar meios por autonomia

		case 4:
			if (gestor == true) {
				printf("   ----- 4. Guardar meios .txt -----\n\n");

				guardarMeios(meios);
				printf("Meios guardado com sucesso");
				break;
			}
			else {
				//alugar um meio
				int codmeioaalugar;
				char nomealuguer[30];
				printf("Qual o codigo do meio a alugar?: ");
				fflush(stdin);
				scanf("%d", &codmeioaalugar);
				printf("Guardar o aluguer em que nome?: ");
				fflush(stdin);
				scanf("%s", nomealuguer);
				alugarMeio(meios, codmeioaalugar);
				registarAluguer(codmeioaalugar, nomealuguer, 1);
				break;
				//alugarmeio
				//registaraluguer

			}
			
			

		case 5:
			//ler meios de um ficheiro txt
			printf("   ----- 5. Ler meios .txt -----\n\n");
			printf("\n\n");
			meios = lerMeios();
			printf("Meios lidos com sucesso.");

			break;

		case 6:
			printf("   ----- 6. Listar meios por ordem decrescente de autonomia -----\n\n");
			listarPorAutonomia(meios);
			break;

		case 7:
			//listar por geocode
			printf("Insira o geocode a procurar: ");
			scanf("%s", geocode);
			listarMeiosGeocode(meios, geocode);
			break;

		case 8:
			//inserir cliente
			printf("   ----- 8. Inserir Cliente -----\n\n");
			printf("\nCodigo : ");
			scanf("%d", &posicao);
			scanf("%*c");
			printf("\nNome : ");
			scanf("%[^\n]s", nome);
			scanf("%*c");
			printf("\nNIF : ");
			scanf("%d", &nif);
			scanf("%*c");
			printf("\nMorada : ");
			scanf("%[^\n]s", morada);
			scanf("%*c");
			
			if (clientes = inserirCliente(clientes, posicao, nome, nif, morada)) {
				printf("\nCliente inserido com sucesso!");
			}
			else printf("Erro ao inserir cliente!");
			
			break;

		case 9:
			//listar clientes
			listarClientes(clientes);
			break;

		case 10:
			//remover cliente
			printf("   ----- 10. Remover cliente -----\n\n");
			printf("\n\nCodigo do cliente a remover? : ");
			scanf("%d", &posicao);
			removerCliente(clientes, posicao);
			break;

		case 11:
			//guardar txt
			printf("   ----- 11. Guardar clientes .txt -----\n\n");
			guardarClientes(clientes);
			printf("Clientes guardado com sucesso");
			break;

		case 12:
			//ler txt
			printf("   ----- 12. Ler clientes .txt -----\n\n");
			printf("\n\n");
			clientes = lerClientes();
			break;

		default:
			break;
		}
		
	} while (operacao != 0);

	//codigo teste antigo
	/* //Teste main antigo
	meios = inserirMeio(meios, 1, "Bicicleta", 5000, 30, "geocode1");
	meios = inserirMeio(meios, 2, "Bicicleta 2", 10000, 60, "geocode1");
	meios = inserirMeio(meios, 3, "Trotinete Eletrica", 7500, 45, "geocode2");
	meios = inserirMeio(meios, 4, "Hoverboard", 3200, 15, "geocode3");
	meios = inserirMeio(meios, 5, "Tesla", 80000, 8600, "test");
	meios = inserirMeio(meios, 6, "Hyundai", 66000, 7800, "geocode1");
	
	
	clientes = inserirCliente(clientes, 1, "Hugo", 260205125, "rua d dinis");
	clientes = inserirCliente(clientes, 2, "Berto", 199458632, "rua dois");
	clientes = inserirCliente(clientes, 3, "Filipe", 231458741, "rua tres");
	clientes = inserirCliente(clientes, 4, "Pedro", 200156789, "rua setenta");
	

	listarClientes(clientes);

	
	if (existeCliente(clientes, 260205125)) printf("\n\nExiste cliente com nif ");
	else printf("\n\nN existe cliente com nif");


	
	printf(" [*] Listar todos os meios inseridos (1 a 6)\n");
	listarMeios(meios);
	//printf("\n\n");
	printf("\n\n [*] Meios por geocode (geocode1): \n");
	listarMeiosGeocode(meios, "geocode1"); //works mas e sloppy

	printf("\n\n [*] Meios por autonomia: \n");
	listarPorAutonomia(meios);

	printf("\n\n [*] Checkar existencia de meios:\n");
	if (existeMeio(meios, 1)) printf("Meio 1 existe\n");
	else printf("Meio 1 nao existe\n");
 
	if (existeMeio(meios, 8)) printf("Meio 8 existe\n");
	else printf("Meio 8 nao existe\n");

	meios = removerMeio(meios, 2);
	meios = removerMeio(meios, 3);
	
	printf("\n\n [*] Listar meios (apenas meio 1 e 4)\n");
	listarMeios(meios);

	printf("\n\n [*] Alterar dados do meio 1 : \n");
	alterarDadosMeio(meios, 1);

	printf("\n\n [*] Listar dados da lista 'meios' : \n\n");
	listarMeios(meios);
	*/

	return false;
}