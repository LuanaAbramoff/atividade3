#include <iostream>
#include <mpi.h>

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

        mensagem = 18;
        MPI_Send( &mensagem , 1, MPI_INT, 1, 0, MPI_COMM_WORLD);
        cout << "Processo" << rank << "enviou mensagem " << mensagem << "para o processo 1" << endl;
    }
    else{
        MPI_Recv( &mensagem , 1, MPI_INT, rank - 1, 0, MPI_COMM_WORLD , MPI_STATUS_IGNORE);

        if(rank == num_proc){
            cout << "Processo de último rank com número " << rank << " recebeu mensagem final" << mensagem << " do processo " << (rank - 1) << endl;
        }

        if(rank < num_proc - 1){
            mensagem = rank*2 + mensagem;
            MPI_Send( &mensagem , 1, MPI_INT, rank + 1, 0, MPI_COMM_WORLD);
            cout << "Processo " << rank << " enviou mensagem " << mensagem << " para o processo " << (rank + 1) << endl;
        }
    }

    MPI_Finalize();
    return 0;
}