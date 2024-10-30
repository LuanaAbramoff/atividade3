#include <iostream>
#include <mpi.h>
#include <string>

using namespace std;

int main(int argc, char**argv){
    MPI_Init(&argc , &argv);

    int rank, num_proc;
    MPI_Comm_rank(MPI_COMM_WORLD , &rank);
    MPI_Comm_size(MPI_COMM_WORLD,  &num_proc);

    if(num_proc < 2){
        if(rank == 0){
            cout << "O número de processos deve ser maior que 1." << endl;
        }
        MPI_Finalize();
        return 0;
    }

    int mensagem;

    if(rank == 0){
        for(int i = 1; i < num_proc; i++){
            string mensagem = "Mensagem para o processo " + to_string(i);
            MPI_Send( mensagem.c_str(), mensagem.size() + 1, MPI_CHAR, i, i, MPI_COMM_WORLD);
            cout << "Processo 0 enviou: \"" << mensagem << "\" para o processo " << i << endl;
        }
    }
    else{
        char buffer[100];
        MPI_Recv( buffer , 100, MPI_CHAR, 0, rank, MPI_COMM_WORLD , MPI_STATUS_IGNORE);
        cout << "Processo " << rank << " recebeu mensagem \"" << buffer << endl;
    }

    MPI_Finalize();
    return 0;
}