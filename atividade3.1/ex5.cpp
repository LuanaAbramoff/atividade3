#include <iostream>

int vetor[5];
int soma;

int main(){

    for (int i = 0; i < 5; i++){
       std::cout << "Digite um numero ";
       std::cin >> vetor[i];
       soma += vetor[i];
    }

    std::cout << soma;
}