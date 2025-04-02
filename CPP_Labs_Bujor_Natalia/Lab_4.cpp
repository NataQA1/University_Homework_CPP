#include <iostream>
#include <string>
#include <fstream>
#include <algorithm>
#include <vector>
#include <limits>
#include <cstring>
using namespace std;

// Структура для хранения данных о телефоне
struct Phone {
    char imei[50];
    char brand[50];
    char model[50];
    char color[50];
    char country[50];
    double price;

    // Конструктор по умолчанию для корректной работы с файлами
    Phone() {
        memset(imei, 0, sizeof(imei));
        memset(brand, 0, sizeof(brand));
        memset(model, 0, sizeof(model));
        memset(color, 0, sizeof(color));
        memset(country, 0, sizeof(country));
        price = 0.0;
    }
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
    string temp;
    cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Очистка буфера перед вводом
    cout << "Enter IMEI: ";
    getline(cin, temp);
    strncpy(phone.imei, temp.c_str(), sizeof(phone.imei) - 1);
    cout << "Enter brand: ";
    getline(cin, temp);
    strncpy(phone.brand, temp.c_str(), sizeof(phone.brand) - 1);
    cout << "Enter model: ";
    getline(cin, temp);
    strncpy(phone.model, temp.c_str(), sizeof(phone.model) - 1);
    cout << "Enter color: ";
    getline(cin, temp);
    strncpy(phone.color, temp.c_str(), sizeof(phone.color) - 1);
    cout << "Enter country: ";
    getline(cin, temp);
    strncpy(phone.country, temp.c_str(), sizeof(phone.country) - 1);
    cout << "Enter price: ";
    while (!(cin >> phone.price)) {
        cout << "Invalid price. Enter a number: ";
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }
    return phone;
}

// Функция для чтения всех записей из файла в вектор
vector<Phone> readFile(const string& filename) {
    vector<Phone> phones;
    ifstream file(filename, ios::binary);
    if (file.is_open()) {
        Phone phone;
        while (file.read(reinterpret_cast<char*>(&phone), sizeof(Phone))) {
            phones.push_back(phone);
        }
        file.close();
    }
    return phones;
}

// Функция для записи вектора в файл
void writeFile(const string& filename, const vector<Phone>& phones) {
    ofstream file(filename, ios::binary | ios::trunc);
    if (file.is_open()) {
        for (const auto& phone : phones) {
            file.write(reinterpret_cast<const char*>(&phone), sizeof(Phone));
        }
        file.close();
    } else {
        cout << "Error opening file for writing\n";
    }
}

// Основная программа
int main() {
    const string filename = "phones.dat"; // Имя бинарного файла
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
        case 1: { // Создание списка телефонов
            int size;
            cout << "Enter the number of telephones: ";
            if (!(cin >> size)) {
                cout << "Invalid input. Please enter a number.\n";
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                break;
            }
            vector<Phone> phones;
            for (int i = 0; i < size; i++) {
                cout << "\nEntering data for the phone " << i + 1 << ":\n";
                phones.push_back(inputPhone());
            }
            writeFile(filename, phones);
            cout << "Phone list created and saved to file\n";
            break;
        }

        case 2: { // Вывод списка
            vector<Phone> phones = readFile(filename);
            if (phones.empty()) {
                cout << "The file is empty or does not exist\n";
            } else {
                for (size_t i = 0; i < phones.size(); i++) {
                    cout << "Phone " << i + 1 << ": ";
                    printPhone(phones[i]);
                }
            }
            break;
        }

        case 3: { // Добавление телефона
            vector<Phone> phones = readFile(filename);
            cout << "\nEntering data for a new phone:\n";
            phones.push_back(inputPhone());
            writeFile(filename, phones);
            cout << "The phone has been added to the file\n";
            break;
        }

        case 4: { // Редактирование телефона
            vector<Phone> phones = readFile(filename);
            if (phones.empty()) {
                cout << "The file is empty\n";
            } else {
                int editIndex;
                cout << "Enter the phone number to edit (1-" << phones.size() << "): ";
                if (!(cin >> editIndex)) {
                    cout << "Invalid input. Please enter a number.\n";
                    cin.clear();
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                    break;
                }
                if (editIndex >= 1 && editIndex <= static_cast<int>(phones.size())) {
                    cout << "\nEditing phone " << editIndex << ":\n";
                    phones[editIndex - 1] = inputPhone();
                    writeFile(filename, phones);
                    cout << "Phone data has been updated in the file\n";
                } else {
                    cout << "Wrong number\n";
                }
            }
            break;
        }

        case 5: { // Удаление телефона
            vector<Phone> phones = readFile(filename);
            if (phones.empty()) {
                cout << "The file is empty\n";
            } else {
                int delIndex;
                cout << "Enter the phone number to be deleted (1-" << phones.size() << "): ";
                if (!(cin >> delIndex)) {
                    cout << "Invalid input. Please enter a number.\n";
                    cin.clear();
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                    break;
                }
                if (delIndex >= 1 && delIndex <= static_cast<int>(phones.size())) {
                    phones.erase(phones.begin() + (delIndex - 1));
                    writeFile(filename, phones);
                    cout << "Phone has been deleted from the file\n";
                } else {
                    cout << "Wrong number\n";
                }
            }
            break;
        }

        case 6: { // Сортировка по цене с выводом
            vector<Phone> phones = readFile(filename);
            if (phones.empty()) {
                cout << "The file is empty\n";
            } else {
                sort(phones.begin(), phones.end(), [](const Phone& a, const Phone& b) {
                    return a.price < b.price;
                });
                writeFile(filename, phones);
                cout << "File is sorted by price:\n";
                for (size_t i = 0; i < phones.size(); i++) {
                    cout << "Phone " << i + 1 << ": ";
                    printPhone(phones[i]);
                }
            }
            break;
        }

        case 7: { // Поиск по бренду
            vector<Phone> phones = readFile(filename);
            if (phones.empty()) {
                cout << "The file is empty\n";
            } else {
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                string searchBrand;
                cout << "Enter brand to search: ";
                getline(cin, searchBrand);
                bool found = false;
                for (const auto& phone : phones) {
                    if (string(phone.brand) == searchBrand) {
                        printPhone(phone);
                        found = true;
                    }
                }
                if (!found) cout << "Phone not found\n";
            }
            break;
        }

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