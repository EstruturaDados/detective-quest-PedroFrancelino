#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// ===== Structs =====

// Estrutura de cada sala da mansao
typedef struct Sala {
    char nome[50];          // Nome da sala
    char pista[100];        // Pista encontrada (pode estar vazia)
    struct Sala* esquerda;  // Caminho a esquerda
    struct Sala* direita;   // Caminho a direita
} Sala;

// Estrutura da arvore BST para armazenar pistas
typedef struct PistaNode {
    char pista[100];
    struct PistaNode* esquerda;
    struct PistaNode* direita;
} PistaNode;

// ===== Funcoes =====

// Cria dinamicamente uma sala com nome e pista
Sala* criarSala(const char* nome, const char* pista) {
    Sala* nova = (Sala*) malloc(sizeof(Sala));
    strcpy(nova->nome, nome);
    if (pista != NULL)
        strcpy(nova->pista, pista);
    else
        strcpy(nova->pista, ""); // sem pista
    nova->esquerda = nova->direita = NULL;
    return nova;
}

// Insere pista em ordem alfabetica na BST
PistaNode* inserirPista(PistaNode* raiz, const char* pista) {
    if (raiz == NULL) {
        PistaNode* novo = (PistaNode*) malloc(sizeof(PistaNode));
        strcpy(novo->pista, pista);
        novo->esquerda = novo->direita = NULL;
        return novo;
    }
    if (strcmp(pista, raiz->pista) < 0)
        raiz->esquerda = inserirPista(raiz->esquerda, pista);
    else if (strcmp(pista, raiz->pista) > 0)
        raiz->direita = inserirPista(raiz->direita, pista);
    return raiz;
}

// Exibe pistas em ordem alfabetica (in-order traversal)
void exibirPistas(PistaNode* raiz) {
    if (raiz != NULL) {
        exibirPistas(raiz->esquerda);
        printf("- %s\n", raiz->pista);
        exibirPistas(raiz->direita);
    }
}

// Explora as salas e coleta pistas automaticamente
void explorarSalasComPistas(Sala* salaAtual, PistaNode** pistas) {
    char escolha;
    while (1) {
        printf("\nVoce esta em %s\n", salaAtual->nome);

        if (strlen(salaAtual->pista) > 0) {
            printf("Pista encontrada: %s\n", salaAtual->pista);
            *pistas = inserirPista(*pistas, salaAtual->pista);
        }

        printf("Escolha caminho (e = esquerda, d = direita, s = sair): ");
        scanf(" %c", &escolha);

        if (escolha == 's') break;
        else if (escolha == 'e' && salaAtual->esquerda != NULL)
            salaAtual = salaAtual->esquerda;
        else if (escolha == 'd' && salaAtual->direita != NULL)
            salaAtual = salaAtual->direita;
        else
            printf("Caminho invalido!\n");
    }
}

// ===== Funcao principal =====
int main() {
    // Construindo o mapa fixo da mansao
    Sala* hall = criarSala("Hall de Entrada", "Chave dourada");
    hall->esquerda = criarSala("Sala de Estar", "Diario antigo");
    hall->direita = criarSala("Cozinha", "");
    hall->esquerda->esquerda = criarSala("Biblioteca", "Mapa rasgado");
    hall->esquerda->direita = criarSala("Jardim", "Luvas de couro");

    // Raiz da BST de pistas
    PistaNode* pistas = NULL;

    printf("=== Detective Quest: Nivel Aventureiro ===\n");
    explorarSalasComPistas(hall, &pistas);

    printf("\nPistas coletadas (ordem alfabetica):\n");
    exibirPistas(pistas);

    return 0;
}