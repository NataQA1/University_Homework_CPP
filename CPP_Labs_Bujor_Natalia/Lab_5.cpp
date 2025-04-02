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

// Структура для узла линейного списка
struct Node {
    Phone phone;
    Node* next;
    Node(const Phone& p) : phone(p), next(nullptr) {}
};

// Класс для управления линейным списком
class PhoneList {
private:
    Node* head;
    int size;

public:
    PhoneList() : head(nullptr), size(0) {}

    // Деструктор для освобождения памяти
    ~PhoneList() {
        Node* current = head;
        while (current != nullptr) {
            Node* temp = current;
            current = current->next;
            delete temp;
        }
    }

    // Функция для добавления элемента в конец списка
    void add(const Phone& phone) {
        Node* newNode = new Node(phone);
        if (head == nullptr) {
            head = newNode;
        } else {
            Node* current = head;
            while (current->next != nullptr) {
                current = current->next;
            }
            current->next = newNode;
        }
        size++;
    }

    // Функция для вывода списка
    void print() const {
        if (head == nullptr) {
            cout << "The list is empty\n";
            return;
        }
        Node* current = head;
        int index = 1;
        while (current != nullptr) {
            cout << "Phone " << index++ << ": ";
            cout << "IMEI: " << current->phone.imei << ", Brand: " << current->phone.brand
                 << ", Model: " << current->phone.model << ", Color: " << current->phone.color
                 << ", Country: " << current->phone.country << ", Price: " << current->phone.price << endl;
            current = current->next;
        }
    }

    // Функция для редактирования элемента по индексу
    bool edit(int index, const Phone& newPhone) {
        if (index < 1 || index > size) return false;
        Node* current = head;
        for (int i = 1; i < index; i++) {
            current = current->next;
        }
        current->phone = newPhone;
        return true;
    }

    // Функция для удаления элемента по индексу
    bool remove(int index) {
        if (index < 1 || index > size) return false;
        Node* current = head;
        if (index == 1) {
            head = head->next;
            delete current;
            size--;
            return true;
        }
        for (int i = 1; i < index - 1; i++) {
            current = current->next;
        }
        Node* temp = current->next;
        current->next = temp->next;
        delete temp;
        size--;
        return true;
    }

    // Функция для сортировки списка по цене
    void sortByPrice() {
        if (size <= 1) return;

        // Преобразуем список в массив для сортировки
        Phone* tempArray = new Phone[size];
        Node* current = head;
        for (int i = 0; i < size; i++) {
            tempArray[i] = current->phone;
            current = current->next;
        }

        // Сортировка массива
        sort(tempArray, tempArray + size, [](const Phone& a, const Phone& b) {
            return a.price < b.price;
        });

        // Обновляем список
        current = head;
        for (int i = 0; i < size; i++) {
            current->phone = tempArray[i];
            current = current->next;
        }
        delete[] tempArray;
    }

    // Функция для поиска по бренду
    void searchByBrand(const string& brand) const {
        bool found = false;
        Node* current = head;
        while (current != nullptr) {
            if (current->phone.brand == brand) {
                cout << "IMEI: " << current->phone.imei << ", Brand: " << current->phone.brand
                     << ", Model: " << current->phone.model << ", Color: " << current->phone.color
                     << ", Country: " << current->phone.country << ", Price: " << current->phone.price << endl;
                found = true;
            }
            current = current->next;
        }
        if (!found) cout << "Phone not found\n";
    }

    // Функция для получения размера списка
    int getSize() const { return size; }
};

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
    PhoneList list;
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
            for (int i = 0; i < size; i++) {
                cout << "\nEntering data for the phone " << i + 1 << ":\n";
                list.add(inputPhone());
            }
            cout << "Phone list created\n";
            break;
        }

        case 2: // Вывод списка
            list.print();
            break;

        case 3: // Добавление телефона
            cout << "\nEntering data for a new phone:\n";
            list.add(inputPhone());
            cout << "The phone has been added\n";
            break;

        case 4: // Редактирование телефона
            if (list.getSize() == 0) {
                cout << "The list is empty\n";
            } else {
                int editIndex;
                cout << "Enter the phone number to edit (1-" << list.getSize() << "): ";
                if (!(cin >> editIndex)) {
                    cout << "Invalid input. Please enter a number.\n";
                    cin.clear();
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                    break;
                }
                if (list.edit(editIndex, inputPhone())) {
                    cout << "Phone data has been updated\n";
                } else {
                    cout << "Wrong number\n";
                }
            }
            break;

        case 5: // Удаление телефона
            if (list.getSize() == 0) {
                cout << "The list is empty\n";
            } else {
                int delIndex;
                cout << "Enter the phone number to be deleted (1-" << list.getSize() << "): ";
                if (!(cin >> delIndex)) {
                    cout << "Invalid input. Please enter a number.\n";
                    cin.clear();
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                    break;
                }
                if (list.remove(delIndex)) {
                    cout << "Phone has been deleted\n";
                } else {
                    cout << "Wrong number\n";
                }
            }
            break;

        case 6: // Сортировка по цене с выводом
            if (list.getSize() == 0) {
                cout << "The list is empty\n";
            } else {
                list.sortByPrice();
                cout << "List is sorted by price:\n";
                list.print();
            }
            break;

        case 7: // Поиск по бренду
            if (list.getSize() == 0) {
                cout << "The list is empty\n";
            } else {
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                string searchBrand;
                cout << "Enter brand to search: ";
                getline(cin, searchBrand);
                list.searchByBrand(searchBrand);
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