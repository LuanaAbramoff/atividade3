#include <mpi.h>
#include <iostream>
#include <string>

int main(int argc, char** argv) {
    MPI_Init(&argc, &argv);

    int rank, num_processos;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank); 
    MPI_Comm_size(MPI_COMM_WORLD, &num_processos); 

    if (num_processos < 3) {
        if (rank == 0) {
            std::cout << "O número de processos deve ser maior que 2." << std::endl;
        }
        MPI_Finalize();
        return 0;
    }

    std::string mensagem = "Mensagem do processo " + std::to_string(rank);

    if (rank == 0) {
        MPI_Send(mensagem.c_str(), mensagem.size() + 1, MPI_CHAR, 1, 0, MPI_COMM_WORLD);
        std::cout << "Processo 0 enviou: \"" << mensagem << "\" para o processo 1" << std::endl;

        char buffer[100];
        MPI_Recv(buffer, 100, MPI_CHAR, num_processos - 1, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
        std::cout << "Processo 0 recebeu: \"" << buffer << "\" do processo " << num_processos - 1 << std::endl;
    } else {
        char buffer[100];
        MPI_Recv(buffer, 100, MPI_CHAR, rank - 1, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
        std::cout << "Processo " << rank << " recebeu: \"" << buffer << "\" do processo " << rank - 1 << std::endl;

        int proximo = (rank + 1) % num_processos;
        MPI_Send(mensagem.c_str(), mensagem.size() + 1, MPI_CHAR, proximo, 0, MPI_COMM_WORLD);
        std::cout << "Processo " << rank << " enviou: \"" << mensagem << "\" para o processo " << proximo << std::endl;
    }

    MPI_Finalize();
    return 0;
}
