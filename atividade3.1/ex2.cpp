#include <iostream>

int numero1;
int numero2;
char operacao;
int resultado;

int main(){
    std::cin >> numero1;
    std::cin >> numero2;
    std::cin >> operacao;

    if (operacao == '+'){
        resultado = numero1 + numero2;
        std::cout << resultado;
    }

    if (operacao == '-'){
        resultado = numero1 - numero2;
        std::cout << resultado;
    }

    if (operacao == '*'){
        resultado = numero1 * numero2;
        std::cout << resultado;
    }

    if (operacao == '/'){
        resultado = numero1 / numero2;
        std::cout << resultado;
    }

    if (operacao == '%'){
        resultado = numero1 % numero2;
        std::cout << resultado;
    }

}
