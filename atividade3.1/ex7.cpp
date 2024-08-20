#include <iostream>

int vetor[7] = {12, 8, 13, 17, 157, 2, 152};

void bubbleSort (int vetor[7]){
    int i, j;
    bool troca;

    for (i = 0; i < 7; i++){
        troca = false;
        for (j = 0; j < 7 - i -1; j++){
            if (vetor[j] > vetor[j + 1]){
                std::swap(vetor[j], vetor[j+1]);
                troca = true;
            }
        }

        if (troca == false){
            break;
        }
    }
}

int main (){

    bubbleSort(vetor);

    for (int i = 0; i < 7; i++){
        std::cout << vetor[i];
        std::cout << ",";
    }
}