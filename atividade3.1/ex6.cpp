#include <iostream>

int vetor[10];
int maior_numero = 0;

int main(){

    for (int i = 0; i < 10; i++){
       std::cout << "Digite um numero ";
       std::cin >> vetor[i];
       if (vetor[i] > maior_numero){
        maior_numero = vetor[i];
       }
    }

    std::cout << maior_numero;
}