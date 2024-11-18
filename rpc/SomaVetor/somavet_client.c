/*
 * This is sample code generated by rpcgen.
 * These are only templates and you can use them
 * as a guideline for developing your own functions.
 */

#include "somavet.h"
#include <stdio.h>
#include <stdlib.h>

void
somavet_prog_1(char *host)
{
	CLIENT *clnt;
	int  *result_1;
	vetor  soma_vetor_1_arg;

#ifndef	DEBUG
	clnt = clnt_create (host, SOMAVET_PROG, SOMAVET_VERS, "udp");
	if (clnt == NULL) {
		clnt_pcreateerror (host);
		exit (1);
	}
#endif	/* DEBUG */

	result_1 = soma_vetor_1(&soma_vetor_1_arg, clnt);
	if (result_1 == (int *) NULL) {
		clnt_perror (clnt, "call failed");
	}
#ifndef	DEBUG
	clnt_destroy (clnt);
#endif	 /* DEBUG */
}


vetor *cria_vetor(int valores[], int n) {
    vetor *vet = (vetor *) malloc(sizeof(vetor));
    vet->tamanho = n;
    vet->numeros.numeros_len = n;
    vet->numeros.numeros_val = (int *) malloc(n * sizeof(int));

    for (int i = 0; i < n; i++) {
        vet->numeros.numeros_val[i] = valores[i];
    }

    return vet;
}

int main(int argc, char *argv[]) {
    CLIENT *clnt;
    vetor *vet;
    int *soma;
    int *valores;
    int n;

    if (argc < 3) {
        fprintf(stderr, "Uso: %s server_host num1 num2 ... numN\n", argv[0]);
        exit(1);
    }

    n = argc - 2;
    valores = (int *) malloc(n * sizeof(int));

    for (int i = 0; i < n; i++) {
        valores[i] = atoi(argv[i + 2]);
    }

    clnt = clnt_create(argv[1], SOMAVET_PROG, SOMAVET_VERS, "udp");
    if (clnt == NULL) {
        clnt_pcreateerror(argv[1]);
        free(valores);
        exit(1);
    }

    vet = cria_vetor(valores, n);
    free(valores);

    // Chamar a função remota para somar os valores do vetor
    soma = soma_vetor_1(vet, clnt);
    if (soma == NULL) {
        clnt_perror(clnt, "Erro ao chamar SOMA_VETOR");
        exit(1);
    }

    printf("Soma dos valores do vetor: %d\n", *soma);

    clnt_destroy(clnt);
    return 0;
}
