#include <iostream>
#include <string>
using namespace std;

// Абстрактный базовый класс
class LengthConverter {
protected:
    double length; // Длина
    string unit;   // Единица измерения

public:
    // Конструктор
    LengthConverter(double len, string u) : length(len), unit(u) {}

    // Чисто виртуальный метод для преобразования
    virtual double convert() const = 0;

    // Виртуальный метод для вывода результата
    virtual void display() const {
        cout << "Length: " << length << " " << unit << endl;
    }

    // Метод для получения длины
    double getLength() const {
        return length;
    }

    // Виртуальный деструктор
    virtual ~LengthConverter() {}
};

// Производный класс для преобразования сантиметров в дюймы
class CmToInch : public LengthConverter {
public:
    // Конструктор
    CmToInch(double len) : LengthConverter(len, "cm") {}

    // Реализация метода преобразования
    double convert() const override {
        return length * 0.393701; // 1 см = 0.393701 дюйма
    }

    // Переопределение метода вывода
    void display() const override {
        LengthConverter::display();
        cout << "Converted: " << convert() << " inches" << endl;
    }

    ~CmToInch() override {}
};

// Производный класс для преобразования дюймов в сантиметры
class InchToCm : public LengthConverter {
public:
    // Конструктор
    InchToCm(double len) : LengthConverter(len, "inches") {}

    // Реализация метода преобразования
    double convert() const override {
        return length * 2.54; // 1 дюйм = 2.54 см
    }

    // Переопределение метода вывода
    void display() const override {
        LengthConverter::display();
        cout << "Converted: " << convert() << " cm" << endl;
    }

    ~InchToCm() override {}
};

int main() {
    // Создание массива указателей на базовый класс для демонстрации полиморфизма
    LengthConverter* converters[] = {
        new CmToInch(100.0),  // 100 см
        new InchToCm(50.0),   // 50 дюймов
        new CmToInch(25.5),   // 25.5 см
        new InchToCm(10.0)    // 10 дюймов
    };

    // Демонстрация полиморфизма
    cout << "Demonstrating polymorphism:\n";
    for (int i = 0; i < 4; ++i) {
        cout << "Converter " << i + 1 << ":\n";
        converters[i]->display(); // Вызов переопределённого метода
        cout << endl;
    }

    // Очистка памяти
    for (int i = 0; i < 4; ++i) {
        delete converters[i];
    }

    return 0;
}