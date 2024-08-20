#include <iostream>
#include <string>


std::string palavra;
bool eh_palindromo = true;


int main (){

    std::cout << "Digite uma palavra: ";
    std::cin >> palavra;

    int tamanho = palavra.size();

    for (int i = 0; i < tamanho/2; i++){
        if(palavra[i] != palavra[tamanho - 1 - i]){
            eh_palindromo = false;
            break;
        }
    }

    if (eh_palindromo == true){
        std::cout << "É um palíndromo !!!";
    }
    else{
        std::cout << "Não é um palíndromo!";
    }
}