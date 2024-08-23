#include <iostream>
#include <vector>
#include <chrono>

using namespace std;
using namespace std::chrono;

int main() {
    int N = 1000; // Tamanho da matriz

    // Aloca memória para uma matriz dinâmica usando std::vector
    vector<vector<int>> matriz(N, vector<int>(N));

    // Inicializa a matriz com valores
    for (int i = 0; i < N; ++i) {
        for (int j = 0; j < N; ++j) {
            matriz[i][j] = i + j;
        }
    }

    // Realiza uma operação de soma simples na matriz
    auto inicio = high_resolution_clock::now();
    long long soma = 0;
    for (int i = 0; i < N; ++i) {
        for (int j = 0; j < N; ++j) {
            soma += matriz[i][j];
        }
    }
    auto fim = high_resolution_clock::now();
    auto duracao = duration_cast<milliseconds>(fim - inicio).count();

    cout << "Soma de todos os elementos: " << soma << endl;
    cout << "Tempo de execução: " << duracao << "ms" << endl;

    return 0;
}
