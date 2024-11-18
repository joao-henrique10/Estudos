#include <mpi.h>
#include <stdio.h>

#define MASTER 0

int main(int argc, char **argv){
    
    int rank, size;
    char mensagem[15] = "Oi, Estou vivo!";
    char mensagemRecebida[15];

    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);


    if(rank != 0){
        MPI_Send(&mensagem[0], 15, MPI_CHAR, MASTER, 0, MPI_COMM_WORLD);
    }

    if(rank == 0){
        for(int i = 1; i < size; i++){
            MPI_Recv(&mensagemRecebida[0], 15, MPI_CHAR, i, MPI_ANY_TAG,MPI_COMM_WORLD, MPI_STATUS_IGNORE);
            printf("Processo Master receber do processo %d a seguinte frase: ", i);
            for(int j = 0; j < 15; j++){
                printf("%c",mensagemRecebida[j]);
            }
            printf("\n");
        }
    }

    MPI_Finalize();
    return 0;
}