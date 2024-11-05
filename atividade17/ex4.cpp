#include <mpi.h>
#include <omp.h>
#include <iostream>
#include <vector>

int main(int argc, char** argv) {
    MPI_Init(&argc, &argv);

    int rank, num_processos;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &num_processos);

    int tamanho_vetor = 100; // Tamanho do vetor
    int valor_a_buscar = 5; // Valor a ser encontrado
    std::vector<int> vetor;

    // Inicialização do vetor no processo raiz
    if (rank == 0) {
        vetor.resize(tamanho_vetor);
        for (int i = 0; i < tamanho_vetor; ++i) {
            vetor[i] = rand() % 10; // Valores aleatórios entre 0 e 9
        }
    }

    // Define o tamanho do subvetor de cada processo
    int tamanho_subvetor = tamanho_vetor / num_processos;
    std::vector<int> subvetor(tamanho_subvetor);

    // Distribui o vetor entre os processos
    MPI_Scatter(vetor.data(), tamanho_subvetor, MPI_INT, subvetor.data(), tamanho_subvetor, MPI_INT, 0, MPI_COMM_WORLD);

    // Realiza a busca paralela no subvetor com OpenMP
    std::vector<int> posicoes_local;
    #pragma omp parallel for
    for (int i = 0; i < tamanho_subvetor; ++i) {
        if (subvetor[i] == valor_a_buscar) {
            #pragma omp critical
            posicoes_local.push_back(i + rank * tamanho_subvetor); // Posição global
        }
    }

    // Número de posições encontradas localmente
    int num_posicoes_local = posicoes_local.size();

    // Vetores para armazenar os resultados no processo raiz
    std::vector<int> num_posicoes_totais(num_processos);
    MPI_Gather(&num_posicoes_local, 1, MPI_INT, num_posicoes_totais.data(), 1, MPI_INT, 0, MPI_COMM_WORLD);

    // Calcular os deslocamentos para MPI_Gatherv
    std::vector<int> deslocamentos(num_processos);
    int total_posicoes = 0;
    if (rank == 0) {
        for (int i = 0; i < num_processos; ++i) {
            deslocamentos[i] = total_posicoes;
            total_posicoes += num_posicoes_totais[i];
        }
    }

    // Recolhe todas as posições encontradas
    std::vector<int> all_positions(total_posicoes);
    MPI_Gatherv(posicoes_local.data(), num_posicoes_local, MPI_INT, all_positions.data(),
                num_posicoes_totais.data(), deslocamentos.data(), MPI_INT, 0, MPI_COMM_WORLD);

    // O processo raiz exibe o resultado
    if (rank == 0) {
        std::cout << "O valor " << valor_a_buscar << " foi encontrado nas posições globais: ";
        for (int pos : all_positions) {
            std::cout << pos << " ";
        }
        std::cout << std::endl;
    }

    MPI_Finalize();
    return 0;
}
