#include "contador.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX_PALAVRAS 100

typedef struct {
    char argp[128];
    int contador;
} Dicionario;

static Dicionario dicionario[MAX_PALAVRAS];
static int tamanho_dicionario = 0;

Resposta *contabilizar_palavra_1_svc(Palavra *argp, struct svc_req *rqstp) {
    static Resposta resposta;
    memset(&resposta, 0, sizeof(resposta));

    // Verificar se o argumento é NULL
    if (argp == NULL) {
        strcpy(resposta.resultado, "Erro: argumento nulo.");
        return &resposta;
    }

    // Se a palavra for "IMPRIMIR", lista o dicionário
    if (strcmp(argp->texto, "IMPRIMIR") == 0) {
        char buffer[1024] = "";
        for (int i = 0; i < tamanho_dicionario; i++) {
            char linha[128];
            snprintf(linha, sizeof(linha), "%.100s: %d\n", dicionario[i].argp, dicionario[i].contador);
            strncat(buffer, linha, sizeof(buffer) - strlen(buffer) - 1);
        }
        strncpy(resposta.resultado, buffer, sizeof(resposta.resultado) - 1);
        return &resposta;
    }

    // Verifica se a palavra já existe no dicionário
    for (int i = 0; i < tamanho_dicionario; i++) {
        if (strcmp(dicionario[i].argp, argp->texto) == 0) {
            dicionario[i].contador++;
            strcpy(resposta.resultado, "Palavra incrementada.");
            return &resposta;
        }
    }

    // Se a palavra não existe, adiciona ao dicionário
    if (tamanho_dicionario < MAX_PALAVRAS) {
        strncpy(dicionario[tamanho_dicionario].argp, argp->texto, sizeof(dicionario[tamanho_dicionario].argp) - 1);
        dicionario[tamanho_dicionario].contador = 1;
        tamanho_dicionario++;
        strcpy(resposta.resultado, "Palavra adicionada.");
    } else {
        strcpy(resposta.resultado, "Dicionário cheio.");
    }

    return &resposta;
}
