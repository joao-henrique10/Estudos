// Elabore um programa MPI com N processos, sendo o master o responsável por
// inicializar o vetor e os slaves, responsáveis por imprimir uma porção do vetor,
// proporcional ao número de slaves idencados pelo programa.

#include <stdio.h>
#include <stdlib.h>
#include <mpi.h>

#define TAG 0
#define MASTER 0

int main (int argc, char **argv){
    int rank, size, tamVet, chunk, inicio, fim, slaves, resto;
    tamVet = rand() % 8 + 8;
    int *vetor;

    MPI_Init( &argc , &argv);
    MPI_Comm_size( MPI_COMM_WORLD , &size);
    MPI_Comm_rank( MPI_COMM_WORLD , &rank);

    slaves = size - 1;
    chunk = tamVet / slaves;
    inicio = (rank - 1) * chunk;
    fim = inicio + chunk;
    resto = tamVet % slaves;

    if (rank == slaves){
        fim = fim + resto;
    }

    vetor = (int *)malloc(sizeof(int) * tamVet);

    if (rank == 0){

        printf("Vetor inicializado pelo MASTER: ");
        for (int i = 0; i < tamVet; i++){
            vetor[i] = i;
            printf("%d ", vetor[i]);
        }
        printf("\n");

        for (int i = 1; i < size; i++){
            MPI_Send( vetor , tamVet , MPI_INT , i , TAG , MPI_COMM_WORLD);
        }
    }
    else{
        MPI_Recv( vetor , tamVet , MPI_INT , MASTER , MPI_ANY_TAG , MPI_COMM_WORLD , MPI_STATUS_IGNORE);

        printf("Vetor printado pelo processo %d; ", rank);
        for(int i = inicio; i < fim; i++){
            printf("%d ", vetor[i]);
        }
        printf("\n");
    }
    free(vetor);

    MPI_Finalize();
    return 0;
}