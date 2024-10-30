#include <mpi.h>
#include <stdio.h>
#include <string.h>

using namespace std;

int main(int argc, char *argv[]) {
    MPI_Init(&argc, &argv);

    int rank;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);

    if (rank == 0) {
        char mensagem_envio[] = "Olá";
        MPI_Send(mensagem_envio, strlen(mensagem_envio) + 1, MPI_CHAR, 1, 0, MPI_COMM_WORLD);
        printf("Processo 0 enviou: %s\n", mensagem_envio);

        char mensagem_recebida[10];
        MPI_Recv(mensagem_recebida, 10, MPI_CHAR, 1, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
        printf("Processo 0 recebeu: %s\n", mensagem_recebida);

    } else if (rank == 1) {
        char mensagem_recebida[10];
        MPI_Recv(mensagem_recebida, 10, MPI_CHAR, 0, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
        printf("Processo 1 recebeu: %s\n", mensagem_recebida);

        char mensagem_envio[] = "Oi";
        MPI_Send(mensagem_envio, strlen(mensagem_envio) + 1, MPI_CHAR, 0, 0, MPI_COMM_WORLD);
        printf("Processo 1 enviou: %s\n", mensagem_envio);
    }

    MPI_Finalize();
    return 0;
}
