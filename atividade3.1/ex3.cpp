#include <iostream>

int numero1;


int main(){
    std::cin >> numero1;

    if (numero1 % 2 == 0){
        std::cout << "par";
    }
    else{
        std::cout << "impar";
    }

}
