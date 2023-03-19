//Hugo Bessa nº 18602
//IPCA EST - EDA 2022/2023

#include <stdio.h>
// Remover um meio a partir do seu código

typedef struct structRegisto {
	int codigo; // código do meio de mobilidade elétrica
	char tipo[50];
	float bateria;
	float autonomia;
	char geocodigo[50];
	int isAlugado; //0 = nao, 1 = sim
	struct structRegisto *seguinte; // endereço de memória para uma struct registo
} MeioTransporte;
//Exemplo : 1, Trotinete Eletrica, 5000, 30, face.sorters.cheater






// Inserção de um novo registo
MeioTransporte *inserirMeio(MeioTransporte *inicio, int cod, char tipo[], float bateria, float autonomia, char geocodigo[], int alugado);

// listar na consola o conteúdo da lista ligada
void listarMeios(MeioTransporte *inicio); 

// Determinar existência do 'codigo' na lista ligada 'inicio'
int existeMeio(MeioTransporte *inicio, int codigo); 

// Remover um meio a partir do seu código
MeioTransporte* removerMeio(MeioTransporte *inicio, int cod);



//Teste 09 03 2023 - listar meios a partir de geocodigo - meio DONE sloppy af
void listarMeiosGeocode(MeioTransporte *inicio, char geocode[]);


//Teste 09 03 2023 - listar meios a partir do ordem decrescente de autonomia - DONE
void listarPorAutonomia(MeioTransporte *inicio);


//15-03-2023
int alterarDadosMeio(MeioTransporte *inicio, int codigo);
int guardarMeios(MeioTransporte* inicio);
MeioTransporte* lerMeios();
void listarMeiosAlugaveis(MeioTransporte* inicio);

void registarAluguer(int cod, char* nomeUser, int estadoAluguer);

int alugarMeio(MeioTransporte* inicio, int codigo);