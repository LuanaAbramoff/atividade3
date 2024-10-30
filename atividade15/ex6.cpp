#include <mpi.h>
#include <iostream>
#include <string>

using namespace std;

int main(int argc, char** argv) {
    MPI_Init(&argc, &argv);

    int rank, num_proc;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank); 
    MPI_Comm_size(MPI_COMM_WORLD, &num_proc); 

    if (num_processos < 2) {
        if (rank == 0) {
            std::cout << "O número de processos deve ser maior que 1." << std::endl;
        }
        MPI_Finalize();
        return 0;
    }

    if (rank == 0) {
        for (int i = 1; i < num_proc; ++i) {
            string mensagem_envio = "Mensagem do processo 0 para o processo " + to_string(i);
            MPI_Send(mensagem_envio.c_str(), mensagem_envio.size() + 1, MPI_CHAR, i, 0, MPI_COMM_WORLD);
            cout << "Processo 0 enviou: \"" << mensagem_envio << "\" para o processo " << i << endl;

            char buffer[100];
            MPI_Recv(buffer, 100, MPI_CHAR, i, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
            cout << "Processo 0 recebeu: \"" << buffer << "\" do processo " << i << endl;
        }
    } else {
        char buffer[100];
        MPI_Recv(buffer, 100, MPI_CHAR, 0, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
        cout << "Processo " << rank << " recebeu: \"" << buffer << "\" do processo 0" << std::endl;

        string mensagem_resposta = "Resposta do processo " + to_string(rank) + " para o processo 0";
        MPI_Send(mensagem_resposta.c_str(), mensagem_resposta.size() + 1, MPI_CHAR, 0, 0, MPI_COMM_WORLD);
        cout << "Processo " << rank << " enviou: \"" << mensagem_resposta << "\" para o processo 0" << endl;
    }

    MPI_Finalize();
    return 0;
}
