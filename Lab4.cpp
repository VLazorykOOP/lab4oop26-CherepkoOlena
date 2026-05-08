//
// Created by acer_ on 07.05.2026.
//

#include "Lab4.h"
#include <iostream>
#include "Task1.h"
#include "Task2.h"


int main(){
    int choise = 0;

    std::cout << "Choose the task"<< std::endl;
    std::cout << "1. Vector3D" << std::endl;
    std::cout << "2. Group dictionari" << std::endl;
    std::cin >> choise;

    if (choise == 1)
        Task1();
    if (choise == 2)
        Task2();

    return 0;
}