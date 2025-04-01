#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

// Структура для хранения информации о мобильных телефонах
struct MobilePhone {
    string IMEI;
    string brand;
    string model;
    string color;
    string country;
    double price;
};

// Функция для вывода данных
void displayPhones(const vector<MobilePhone>& phones) {
    if (phones.empty()) {
        cout << "The phone list is empty\n";
        return;
    }
    for (size_t i = 0; i < phones.size(); ++i) {
        cout << i + 1 << ". IMEI: " << phones[i].IMEI
             << ", Brand: " << phones[i].brand
             << ", Model: " << phones[i].model
             << ", Color: " << phones[i].color
             << ", Country: " << phones[i].country
             << ", Price: " << phones[i].price << "\n";
    }
}

// Функция для добавления нового телефона
void addPhone(vector<MobilePhone>& phones) {
    MobilePhone phone;
    cout << "Enter IMEI: "; cin >> phone.IMEI;
    cout << "Enter brand: "; cin >> phone.brand;
    cout << "Enter model: "; cin >> phone.model;
    cout << "Enter color: "; cin >> phone.color;
    cout << "Enter country: "; cin >> phone.country;
    cout << "Enter price: "; cin >> phone.price;
    phones.push_back(phone);
}

// Функция для редактирования данных
void editPhone(vector<MobilePhone>& phones) {
    int index;
    displayPhones(phones);
    cout << "Enter the phone number to edit: ";
    cin >> index;
    if (index < 1 || index > phones.size()) {
        cout << "Incorrect choice.\n";
        return;
    }
    index--;
    cout << "Enter new IMEI: "; cin >> phones[index].IMEI;
    cout << "Enter new brand: "; cin >> phones[index].brand;
    cout << "Enter new model: "; cin >> phones[index].model;
    cout << "Enter new color: "; cin >> phones[index].color;
    cout << "Enter new country: "; cin >> phones[index].country;
    cout << "Enter new price: "; cin >> phones[index].price;
}

// Функция для удаления телефона
void deletePhone(vector<MobilePhone>& phones) {
    int index;
    displayPhones(phones);
    cout << "Enter the phone number to delete: ";
    cin >> index;
    if (index < 1 || index > phones.size()) {
        cout << "Incorrect choice.\n";
        return;
    }
    phones.erase(phones.begin() + index - 1);
}

// Функция для сортировки по цене
void sortPhones(vector<MobilePhone>& phones) {
    sort(phones.begin(), phones.end(), [](const MobilePhone& a, const MobilePhone& b) {
        return a.price < b.price;
    });
    cout << "Phones sorted by price.\n";
}

// Функция для поиска по марке
void searchByBrand(const vector<MobilePhone>& phones) {
    string brand;
    cout << "Enter the brand to search for: "; cin >> brand;
    bool found = false;
    for (const auto& phone : phones) {
        if (phone.brand == brand) {
            cout << "Found: " << phone.IMEI << " " << phone.model << " " << phone.price << "\n";
            found = true;
        }
    }
    if (!found) cout << "No phone with this brand was found.\n";
}

int main() {
    vector<MobilePhone> phones;
    int choice;
    do {
        cout << "\nMenu:\n";
        cout << "1. Add phone\n";
        cout << "2. Print the list\n";
        cout << "3. Edit phone\n";
        cout << "4. Delete phone\n";
        cout << "5. Sort by price\n";
        cout << "6. Search by brand\n";
        cout << "7. Exit\n";
        cout << "Select an action: ";
        cin >> choice;
        switch (choice) {
            case 1: addPhone(phones); break;
            case 2: displayPhones(phones); break;
            case 3: editPhone(phones); break;
            case 4: deletePhone(phones); break;
            case 5: sortPhones(phones); break;
            case 6: searchByBrand(phones); break;
            case 7: cout << "Exit...\n"; break;
            default: cout << "Incorrect input, try again.\n";
        }
    } while (choice != 7);
    return 0;
}
