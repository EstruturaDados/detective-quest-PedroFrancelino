#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Definição da estrutura Sala
typedef struct Sala {
    char nome[50];
    struct Sala* esquerda;
    struct Sala* direita;
} Sala;

// Função que cria dinamicamente uma sala
Sala* criarSala(char* nome) {
    Sala* nova = (Sala*) malloc(sizeof(Sala));
    if (nova == NULL) {
        printf("Erro ao alocar memoria!\n");
        exit(1);
    }
    strcpy(nova->nome, nome);
    nova->esquerda = NULL;
    nova->direita = NULL;
    return nova;
}

// Função para explorar a mansão
void explorarSalas(Sala* atual) {
    char escolha;

    while (atual != NULL) {
        printf("\nVoce esta em: %s\n", atual->nome);

        // Checa se é nó-folha (sem caminhos)
        if (atual->esquerda == NULL && atual->direita == NULL) {
            printf("Fim do caminho! Nao ha mais saidas.\n");
            break;
        }

        printf("Escolha o caminho: (e = esquerda, d = direita, s = sair): ");
        scanf(" %c", &escolha);

        if (escolha == 'e' && atual->esquerda != NULL) {
            atual = atual->esquerda;
        } 
        else if (escolha == 'd' && atual->direita != NULL) {
            atual = atual->direita;
        } 
        else if (escolha == 's') {
            printf("Voce decidiu sair da exploracao.\n");
            break;
        } 
        else {
            printf("Opcao invalida! Tente novamente.\n");
        }
    }
}

int main() {
    // Criação manual do mapa da mansão
    Sala* hall = criarSala("Hall de Entrada");
    Sala* salaEstar = criarSala("Sala de Estar");
    Sala* cozinha = criarSala("Cozinha");
    Sala* biblioteca = criarSala("Biblioteca");
    Sala* jardim = criarSala("Jardim");
    Sala* escritorio = criarSala("Escritorio");

    // Conexões (árvore binária)
    hall->esquerda = salaEstar;
    hall->direita = cozinha;

    salaEstar->esquerda = biblioteca;
    salaEstar->direita = jardim;

    cozinha->direita = escritorio;

    // Início da exploração
    printf("=== Bem-vindo ao Detective Quest ===\n");
    explorarSalas(hall);

    return 0;
}