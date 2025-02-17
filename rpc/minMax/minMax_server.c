/*
 * This is sample code generated by rpcgen.
 * These are only templates and you can use them
 * as a guideline for developing your own functions.
 */

#include "minMax.h"

MinMax *
find_min_max_1_svc(IntArray *argp, struct svc_req *rqstp)
{
static MinMax result; // Variável estática para armazenar o resultado
    result.min = argp->values[0];
    result.max = argp->values[0];

    // Iterando sobre o vetor para encontrar o mínimo e o máximo
    for (int i = 1; i < 100; i++) {
        if (argp->values[i] < result.min) {
            result.min = argp->values[i];
        }
        if (argp->values[i] > result.max) {
            result.max = argp->values[i];
        }
    }

    return &result;
}
