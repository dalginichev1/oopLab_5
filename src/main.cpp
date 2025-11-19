#include "customAllocator.hpp"
#include "forwardList.hpp"
#include <iostream>

int main() {
    std::cout << "Простой тест однонаправленного списка с кастомным аллокатором\n";

    FixedCustomMemoryResource resource(1000);
    ForwardList<int> list(&resource);
    
    char choice;
    int value;
    
    while (true) {
        std::cout << "\n1 - Добавить элемент\n";
        std::cout << "2 - Удалить первый элемент\n";
        std::cout << "3 - Показать список\n";
        std::cout << "4 - Очистить список\n";
        std::cout << "5 - Выход\n";
        std::cout << "Выберите действие: ";
        std::cin >> choice;
        
        switch (choice) {
            case '1':
                std::cout << "Введите число: ";
                std::cin >> value;
                list.push_front(value);
                std::cout << "Добавлено: " << value << "\n";
                break;
                
            case '2':
                if (!list.empty()) {
                    list.pop_front();
                    std::cout << "Первый элемент удален\n";
                } else {
                    std::cout << "Список пуст\n";
                }
                break;
                
            case '3':
                if (list.empty()) {
                    std::cout << "Список пуст\n";
                } else {
                    std::cout << "Список: ";
                    for (const auto& item : list) {
                        std::cout << item << " ";
                    }
                    std::cout << "\n";
                }
                break;
                
            case '4':
                list.clear();
                std::cout << "Список очищен\n";
                break;
                
            case '5':
                std::cout << "Выход\n";
                return 0;
                
            default:
                std::cout << "Неверный выбор\n";
        }
    }
}