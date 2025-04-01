#include <iostream>
#include <string>
#include <algorithm>
#include <limits>
using namespace std;

// Структура для хранения данных о телефоне
struct Phone {
    string imei;
    string brand;
    string model;
    string color;
    string country;
    double price;
};

// Функция для вывода информации о телефоне
void printPhone(const Phone& phone) {
    cout << "IMEI: " << phone.imei << ", Brand: " << phone.brand
         << ", Model: " << phone.model << ", Color: " << phone.color
         << ", Country: " << phone.country << ", Price: " << phone.price << endl;
}

// Функция для ввода данных о телефоне
Phone inputPhone() {
    Phone phone;
    cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Очистка буфера перед вводом
    cout << "Enter IMEI: ";
    getline(cin, phone.imei);
    cout << "Enter brand: ";
    getline(cin, phone.brand);
    cout << "Enter model: ";
    getline(cin, phone.model);
    cout << "Enter color: ";
    getline(cin, phone.color);
    cout << "Enter country: ";
    getline(cin, phone.country);
    cout << "Enter price: ";
    while (!(cin >> phone.price)) {
        cout << "Invalid price. Enter a number: ";
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }
    return phone;
}

// Основная программа
int main() {
    const int MAX_SIZE = 100; // Максимальный размер массива
    Phone phones[MAX_SIZE];   // Массив структур
    int size = 0;             // Текущий размер массива
    int choice;

    do {
        cout << "\nMenu:\n";
        cout << "1. Create phone list\n";
        cout << "2. Print the list\n";
        cout << "3. Add phone\n";
        cout << "4. Edit phone\n";
        cout << "5. Delete phone\n";
        cout << "6. Sort by price\n";
        cout << "7. Search by brand\n";
        cout << "8. Exit\n";
        cout << "Select an action: ";

        if (!(cin >> choice)) {
            cout << "Invalid input. Please enter a number.\n";
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            continue;
        }

        switch (choice) {
        case 1: // Создание списка телефонов
            cout << "Enter the number of telephones: ";
            if (!(cin >> size)) {
                cout << "Invalid input. Please enter a number.\n";
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                break;
            }
            if (size > MAX_SIZE) {
                cout << "The maximum array size has been exceeded (" << MAX_SIZE << ")\n";
                size = MAX_SIZE;
            }
            for (int i = 0; i < size; i++) {
                cout << "\nEntering data for the phone " << i + 1 << ":\n";
                phones[i] = inputPhone();
            }
            break;

        case 2: // Вывод списка
            if (size == 0) {
                cout << "The array is empty\n";
            } else {
                for (int i = 0; i < size; i++) {
                    cout << "Phone " << i + 1 << ": ";
                    printPhone(phones[i]);
                }
            }
            break;

        case 3: // Добавление телефона
            if (size < MAX_SIZE) {
                cout << "\nEntering data for a new phone:\n";
                phones[size] = inputPhone();
                size++;
                cout << "The phone has been added\n";
            } else {
                cout << "The array is complete\n";
            }
            break;

        case 4: // Редактирование телефона
            if (size == 0) {
                cout << "The array is empty\n";
            } else {
                int editIndex;
                cout << "Enter the phone number to edit (1-" << size << "): ";
                if (!(cin >> editIndex)) {
                    cout << "Invalid input. Please enter a number.\n";
                    cin.clear();
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                    break;
                }
                if (editIndex >= 1 && editIndex <= size) {
                    cout << "\nEditing phone " << editIndex << ":\n";
                    phones[editIndex - 1] = inputPhone();
                    cout << "Phone data has been updated\n";
                } else {
                    cout << "Wrong number\n";
                }
            }
            break;

        case 5: // Удаление телефона
            if (size == 0) {
                cout << "The array is empty\n";
            } else {
                int delIndex;
                cout << "Enter the phone number to be deleted (1-" << size << "): ";
                if (!(cin >> delIndex)) {
                    cout << "Invalid input. Please enter a number.\n";
                    cin.clear();
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                    break;
                }
                if (delIndex >= 1 && delIndex <= size) {
                    for (int i = delIndex - 1; i < size - 1; i++) {
                        phones[i] = phones[i + 1];
                    }
                    size--;
                    cout << "Phone's been deleted\n";
                } else {
                    cout << "Wrong number\n";
                }
            }
            break;

        case 6: // Сортировка по цене с выводом
            if (size == 0) {
                cout << "The array is empty\n";
            } else {
                sort(phones, phones + size, [](const Phone& a, const Phone& b) {
                    return a.price < b.price;
                });
                cout << "Array is sorted by price:\n";
                for (int i = 0; i < size; i++) {
                    cout << "Phone " << i + 1 << ": ";
                    printPhone(phones[i]);
                }
            }
            break;

        case 7: // Поиск по бренду
            if (size == 0) {
                cout << "The array is empty\n";
            } else {
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                string searchBrand;
                cout << "Enter brand to search: ";
                getline(cin, searchBrand);
                bool found = false;
                for (int i = 0; i < size; i++) {
                    if (phones[i].brand == searchBrand) {
                        printPhone(phones[i]);
                        found = true;
                    }
                }
                if (!found) cout << "Phone not found\n";
            }
            break;

        case 8: // Выход
            cout << "Quitting the program\n";
            break;

        default:
            cout << "Wrong choice, try again\n";
            break;
        }
    } while (choice != 8);

    return 0;
}











