//Hugo Bessa nº 18602
//IPCA EST - EDA 2022/2023

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "gestor.h"
#include <stdbool.h>
#pragma warning(disable : 4996)

// Função para ler os usuários do arquivo de usuários
int lerUsuarios(Utilizador users[]) {
    int numeroUsers = 0;
    FILE* arquivo = fopen("users.txt", "r");

    if (arquivo == NULL) {
        printf("Erro ao abrir o arquivo de utilizadores\n");
        return -1;
    }

    while (fscanf(arquivo, "%s %s %d", users[numeroUsers].username, users[numeroUsers].password, &users[numeroUsers].gestor) != EOF) {
        numeroUsers++;
    }

    fclose(arquivo);
    return numeroUsers;
}

bool isGestor(Utilizador* user) {
    if (user->gestor == 1) {
        return true;
    } else return false;
}

// Função para fazer o login
int fazerLogin(Utilizador users[], int numUsers) {
    char username[50], password[50];
    printf("Username: ");
    scanf("%s", username);
    printf("Password: ");
    scanf("%s", password);

    for (int i = 0; i < numUsers; i++) {
        if (strcmp(username, users[i].username) == 0 && strcmp(password, users[i].password) == 0) {
            return users[i].gestor;
        }
    }
    return 0;
}

/*int main() {
    int opcao, gestor;
    Utilizador usuarios[MAX_USERS];
    int numUsuarios = lerUsuarios(usuarios);

    if (numUsuarios < 0) {
        return -1;
    }

    gestor = fazerLogin(usuarios, numUsuarios);

    if (gestor < 0) {
        printf("Usuario ou senha invalidos\n");
        return -1;
    }

    printf("Login efetuado com sucesso!\n");

    // Aqui você pode implementar o menu com as opções do programa
    // Verifique a variável gestor para saber se é gestor ou não
    // Se não for gestor, algumas opções podem ser omitidas

    return 0;
}*/