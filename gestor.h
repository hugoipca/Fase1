//Hugo Bessa nº 18602
//IPCA EST - EDA 2022/2023

#pragma once
#include <stdbool.h>

#define MAX_USERS 20

typedef struct structUser {
    char username[50];
    char password[50];
    int gestor;
    struct structUser* seguinte;
} Utilizador;

int lerUsuarios(Utilizador users[]);
int fazerLogin(Utilizador users[], int numUsers);
bool isGestor(Utilizador* user);