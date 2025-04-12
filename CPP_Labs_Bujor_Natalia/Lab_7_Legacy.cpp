#include <iostream>
#include <string>
#include <limits>
using namespace std;

// Базовый класс Phone из предыдущей лабораторной
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

    // Конструктор копирования
    Phone(const Phone& other)
        : imei(other.imei), brand(other.brand), model(other.model), color(other.color),
          country(other.country), price(other.price) {}

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
    virtual void displayAll() const {
        cout << "IMEI: " << imei << ", Brand: " << brand << ", Model: " << model
             << ", Color: " << color << ", Country: " << country << ", Price (EUR): " << price << endl;
    }

    // Функция для конвертации цены из евро в леи
    double convertPriceToLei() const {
        const double exchangeRate = 19.5;
        return price * exchangeRate;
    }

    // Перегрузка оператора ==
    bool operator==(const Phone& other) const {
        return imei == other.imei && brand == other.brand && model == other.model &&
               color == other.color && country == other.country && price == other.price;
    }

    // Перегрузка оператора +
    Phone operator+(double priceIncrease) const {
        Phone result = *this;
        result.price += priceIncrease;
        return result;
    }

    // Виртуальный деструктор
    virtual ~Phone() {}
};

// Производный класс Phone4G
class Phone4G : public Phone {
protected:
    double internetSpeed; // Скорость интернета (Мбит/с)
    bool hasWiFi;        // Наличие Wi-Fi

public:
    // Конструктор без параметров
    Phone4G() : Phone(), internetSpeed(0.0), hasWiFi(false) {}

    // Конструктор со всеми параметрами
    Phone4G(string imei_, string brand_, string model_, string color_, string country_,
            double price_, double speed, bool wifi)
        : Phone(imei_, brand_, model_, color_, country_, price_), internetSpeed(speed), hasWiFi(wifi) {}

    // Конструктор с некоторыми параметрами
    Phone4G(string imei_, string brand_, double price_, double speed, bool wifi)
        : Phone(imei_, brand_, price_), internetSpeed(speed), hasWiFi(wifi) {}

    // Конструктор копирования
    Phone4G(const Phone4G& other)
        : Phone(other), internetSpeed(other.internetSpeed), hasWiFi(other.hasWiFi) {}

    // Переопределение метода displayAll
    void displayAll() const override {
        Phone::displayAll();
        cout << "Internet Speed: " << internetSpeed << " Mbps" << endl;
        cout << "Wi-Fi: " << (hasWiFi ? "Yes" : "No") << endl;
    }

    // Деструктор
    ~Phone4G() override {}
};

// Производный класс Phone4GMaxSpeed
class Phone4GMaxSpeed : public Phone4G {
private:
    string technology; // Используемая технология (например, LTE, LTE-A)

public:
    // Конструктор без параметров
    Phone4GMaxSpeed() : Phone4G(), technology("Unknown") {}

    // Конструктор со всеми параметрами
    Phone4GMaxSpeed(string imei_, string brand_, string model_, string color_, string country_,
                    double price_, double speed, bool wifi, string tech)
        : Phone4G(imei_, brand_, model_, color_, country_, price_, speed, wifi), technology(tech) {}

    // Конструктор с некоторыми параметрами
    Phone4GMaxSpeed(string imei_, string brand_, double price_, double speed, bool wifi, string tech)
        : Phone4G(imei_, brand_, price_, speed, wifi), technology(tech) {}

    // Конструктор копирования
    Phone4GMaxSpeed(const Phone4GMaxSpeed& other)
        : Phone4G(other), technology(other.technology) {}

    // Переопределение метода displayAll
    void displayAll() const override {
        Phone4G::displayAll();
        cout << "Technology: " << technology << endl;
    }

    // Деструктор
    ~Phone4GMaxSpeed() override {}
};

// Дополнительный производный класс SmartPhone
class SmartPhone : public Phone4G {
private:
    string os; // Операционная система

public:
    // Конструктор без параметров
    SmartPhone() : Phone4G(), os("Unknown") {}

    // Конструктор со всеми параметрами
    SmartPhone(string imei_, string brand_, string model_, string color_, string country_,
               double price_, double speed, bool wifi, string os_)
        : Phone4G(imei_, brand_, model_, color_, country_, price_, speed, wifi), os(os_) {}

    // Конструктор с некоторыми параметрами
    SmartPhone(string imei_, string brand_, double price_, double speed, bool wifi, string os_)
        : Phone4G(imei_, brand_, price_, speed, wifi), os(os_) {}

    // Конструктор копирования
    SmartPhone(const SmartPhone& other)
        : Phone4G(other), os(other.os) {}

    // Переопределение метода displayAll
    void displayAll() const override {
        Phone4G::displayAll();
        cout << "Operating System: " << os << endl;
    }

    // Деструктор
    ~SmartPhone() override {}
};

// Функция для ввода данных о телефоне
Phone inputPhone() {
    string imei, brand, model, color, country;
    double price;

    cin.ignore(numeric_limits<streamsize>::max(), '\n');
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
    // Демонстрация создания объектов
    cout << "Basic Phone:" << endl;
    Phone basicPhone("123456789", "Nokia", "3310", "Black", "Finland", 50.0);
    basicPhone.displayAll();
    cout << "Price in Lei: " << basicPhone.convertPriceToLei() << " MDL" << endl;
    cout << endl;

    cout << "4G Phone:" << endl;
    Phone4G phone4g("987654321", "Samsung", "Galaxy A50", "Blue", "South Korea", 300.0, 50.0, true);
    phone4g.displayAll();
    cout << endl;

    cout << "4G Max Speed Phone:" << endl;
    Phone4GMaxSpeed maxSpeedPhone("1122334455", "Apple", "iPhone 12", "White", "USA", 800.0, 100.0, true, "LTE-A");
    maxSpeedPhone.displayAll();
    cout << endl;

    cout << "SmartPhone:" << endl;
    SmartPhone smartPhone("5566778899", "Xiaomi", "Mi 11", "Red", "China", 500.0, 75.0, true, "Android");
    smartPhone.displayAll();
    cout << endl;

    // Демонстрация операторов
    cout << "Comparing basicPhone and phone4g:" << endl;
    if (basicPhone == phone4g) {
        cout << "Phones are identical" << endl;
    } else {
        cout << "Phones are different" << endl;
    }
    cout << endl;

    cout << "Increasing price of basicPhone by 20 EUR:" << endl;
    basicPhone = basicPhone + 20.0;
    basicPhone.displayPrice();

    return 0;
}