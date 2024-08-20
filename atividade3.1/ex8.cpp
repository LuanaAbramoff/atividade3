#include <iostream>

int main() {
    int matriz[3][3];
    int soma_diagonal_principal = 0;

    // Solicitando ao usuário que insira os elementos da matriz 3x3
    std::cout << "Insira os elementos da matriz 3x3:\n";
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            std::cin >> matriz[i][j];
        }
    }

    // Calculando a soma dos elementos na diagonal principal
    for (int i = 0; i < 3; i++) {
        soma_diagonal_principal += matriz[i][i];
    }

    // Exibindo a soma da diagonal principal
    std::cout << "A soma dos elementos na diagonal principal é: " << soma_diagonal_principal << std::endl;

    return 0;
}
