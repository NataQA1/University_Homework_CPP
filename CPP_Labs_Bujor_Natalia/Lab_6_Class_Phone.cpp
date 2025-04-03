#include <iostream>
#include <string>
#include <limits>
using namespace std;

// Класс для хранения данных о телефоне
class Phone {
private:
    string imei;
    string brand;
    string model;
    string color;
    string country;
    double price; // Цена в евро

public:
    // Конструктор без параметров
    Phone() : imei(""), brand(""), model(""), color(""), country(""), price(0.0) {}

    // Конструктор со всеми параметрами
    Phone(string imei_, string brand_, string model_, string color_, string country_, double price_)
        : imei(imei_), brand(brand_), model(model_), color(color_), country(country_), price(price_) {}

    // Конструктор с некоторыми параметрами (только IMEI, бренд и цена)
    Phone(string imei_, string brand_, double price_)
        : imei(imei_), brand(brand_), model("Unknown"), color("Unknown"), country("Unknown"), price(price_) {}

    // Методы для чтения полей
    string getIMEI() const { return imei; }
    string getBrand() const { return brand; }
    string getModel() const { return model; }
    string getColor() const { return color; }
    string getCountry() const { return country; }
    double getPrice() const { return price; }

    // Методы для отображения полей
    void displayIMEI() const { cout << "IMEI: " << imei << endl; }
    void displayBrand() const { cout << "Brand: " << brand << endl; }
    void displayModel() const { cout << "Model: " << model << endl; }
    void displayColor() const { cout << "Color: " << color << endl; }
    void displayCountry() const { cout << "Country: " << country << endl; }
    void displayPrice() const { cout << "Price (EUR): " << price << endl; }

    // Метод для отображения всех данных
    void displayAll() const {
        cout << "IMEI: " << imei << ", Brand: " << brand << ", Model: " << model
             << ", Color: " << color << ", Country: " << country << ", Price (EUR): " << price << endl;
    }

    // Функция для конвертации цены из евро в леи (1 EUR = 19.5 MDL)
    double convertPriceToLei() const {
        const double exchangeRate = 19.5; // Курс евро к леям
        return price * exchangeRate;
    }

    // Перегрузка оператора == для сравнения двух объектов
    bool operator==(const Phone& other) const {
        return imei == other.imei && brand == other.brand && model == other.model &&
               color == other.color && country == other.country && price == other.price;
    }

    // Перегрузка оператора + для увеличения цены на заданное значение
    Phone operator+(double priceIncrease) const {
        Phone result = *this;
        result.price += priceIncrease;
        return result;
    }
};

// Функция для ввода данных о телефоне
Phone inputPhone() {
    string imei, brand, model, color, country;
    double price;

    cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Очистка буфера перед вводом
    cout << "Enter IMEI: ";
    getline(cin, imei);
    cout << "Enter brand: ";
    getline(cin, brand);
    cout << "Enter model: ";
    getline(cin, model);
    cout << "Enter color: ";
    getline(cin, color);
    cout << "Enter country: ";
    getline(cin, country);
    cout << "Enter price (in EUR): ";
    while (!(cin >> price)) {
        cout << "Invalid price. Enter a number: ";
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }

    return Phone(imei, brand, model, color, country, price);
}

// Основная программа
int main() {
    const int MAX_SIZE = 100; // Максимальный размер массива
    Phone phones[MAX_SIZE];   // Массив объектов класса Phone
    int size = 0;             // Текущий размер массива
    int choice;

    do {
        cout << "\nMenu:\n";
        cout << "1. Create phone list\n";
        cout << "2. Print the list\n";
        cout << "3. Add phone\n";
        cout << "4. Edit phone\n";
        cout << "5. Delete phone\n";
        cout << "6. Convert price to Lei\n";
        cout << "7. Compare two phones\n";
        cout << "8. Increase price of a phone\n";
        cout << "9. Exit\n";
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
                    phones[i].displayAll();
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
                    cout << "Phone has been deleted\n";
                } else {
                    cout << "Wrong number\n";
                }
            }
            break;

        case 6: // Конвертация цены в леи
            if (size == 0) {
                cout << "The array is empty\n";
            } else {
                int index;
                cout << "Enter the phone number to convert price (1-" << size << "): ";
                if (!(cin >> index)) {
                    cout << "Invalid input. Please enter a number.\n";
                    cin.clear();
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                    break;
                }
                if (index >= 1 && index <= size) {
                    cout << "Phone " << index << " price in Lei: " << phones[index - 1].convertPriceToLei() << " MDL\n";
                } else {
                    cout << "Wrong number\n";
                }
            }
            break;

        case 7: // Сравнение двух телефонов
            if (size < 2) {
                cout << "Need at least two phones to compare\n";
            } else {
                int index1, index2;
                cout << "Enter the first phone number to compare (1-" << size << "): ";
                if (!(cin >> index1)) {
                    cout << "Invalid input. Please enter a number.\n";
                    cin.clear();
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                    break;
                }
                cout << "Enter the second phone number to compare (1-" << size << "): ";
                if (!(cin >> index2)) {
                    cout << "Invalid input. Please enter a number.\n";
                    cin.clear();
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                    break;
                }
                if (index1 >= 1 && index1 <= size && index2 >= 1 && index2 <= size) {
                    if (phones[index1 - 1] == phones[index2 - 1]) {
                        cout << "The phones are identical\n";
                    } else {
                        cout << "The phones are different\n";
                    }
                } else {
                    cout << "Wrong number(s)\n";
                }
            }
            break;

        case 8: // Увеличение цены телефона
            if (size == 0) {
                cout << "The array is empty\n";
            } else {
                int index;
                double increase;
                cout << "Enter the phone number to increase price (1-" << size << "): ";
                if (!(cin >> index)) {
                    cout << "Invalid input. Please enter a number.\n";
                    cin.clear();
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                    break;
                }
                if (index >= 1 && index <= size) {
                    cout << "Enter the amount to increase price (in EUR): ";
                    if (!(cin >> increase)) {
                        cout << "Invalid input. Please enter a number.\n";
                        cin.clear();
                        cin.ignore(numeric_limits<streamsize>::max(), '\n');
                        break;
                    }
                    phones[index - 1] = phones[index - 1] + increase;
                    cout << "Price updated for phone " << index << ":\n";
                    phones[index - 1].displayPrice();
                } else {
                    cout << "Wrong number\n";
                }
            }
            break;

        case 9: // Выход
            cout << "Quitting the program\n";
            break;

        default:
            cout << "Wrong choice, try again\n";
            break;
        }
    } while (choice != 9);

    return 0;
}