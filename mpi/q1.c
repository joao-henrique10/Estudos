// Elabore um programa MPI com três processos, sendo um master e dois slaves.
// O master deve inicializar o vetor; os slaves devem imprimir, cada um, a metade
// do vetor inicializado pelo master.

#include <mpi.h>
#include <stdio.h>
#include <stdlib.h>

#define MASTER 0
#define TAG 0

int main(int argc, char **argv){
    int rank, size, tamVet = 10;
    int *vetor;
    int *vetorRecebimento;

    MPI_Init( &argc , &argv);
    MPI_Comm_size( MPI_COMM_WORLD, &size);
    MPI_Comm_rank( MPI_COMM_WORLD , &rank);

    if(size != 3){
        if (rank == 0){
           printf("O programa deve ter exatamente 3 processos\n"); 
        }
        MPI_Finalize();
        return 0;
    }

    if (rank == 0){
        vetor = (int *)malloc(sizeof(int) * tamVet);
        printf("Vetor inicializado pelo processo MASTER: ");
        for (int i = 0;i < tamVet; i++){
            vetor[i] = i;
            printf("%d ", vetor[i]);
        }
        printf("\n");

        MPI_Send( vetor , tamVet/2 , MPI_INT , 1 , TAG , MPI_COMM_WORLD);
        MPI_Send( &vetor[5] , 5 , MPI_INT , 2 , TAG , MPI_COMM_WORLD);
        free(vetor);
    }
    else{
        vetorRecebimento = (int *)malloc(sizeof(int) * (tamVet/2));

        MPI_Recv( vetorRecebimento , tamVet/2 , MPI_INT , MASTER , MPI_ANY_TAG , MPI_COMM_WORLD , MPI_STATUS_IGNORE);

        printf("Vetor recebido pelo processo %d: ", rank);
        for (int i = 0; i < (tamVet/2); i++){
            printf("%d ", vetorRecebimento[i]);
        }
        printf("\n");
        free(vetorRecebimento);
    }

    MPI_Finalize();
    return 0;
}