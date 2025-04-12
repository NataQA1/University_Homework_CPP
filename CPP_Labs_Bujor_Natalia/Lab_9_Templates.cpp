#include <iostream>
#include <algorithm>
#include <limits>

// Шаблонная функция для поиска второго по величине элемента
template <typename T>
T findSecondMax(const T* arr, int size) {
    if (size < 2) {
        throw std::invalid_argument("Массив должен содержать как минимум 2 элемента");
    }

    // Создаем копию массива, чтобы не менять оригинал
    T* temp = new T[size];
    std::copy(arr, arr + size, temp);

    // Сортируем по убыванию
    std::sort(temp, temp + size, std::greater<T>());

    // Находим второй по величине элемент
    T secondMax = temp[1];

    delete[] temp; // Освобождаем память
    return secondMax;
}

// Шаблонный класс множества
template <typename T>
class Set {
private:
    T* elements; // Динамический массив для хранения элементов
    int capacity; // Вместимость массива
    int length; // Текущая длина множества

    // Вспомогательная функция для проверки, есть ли элемент
    bool contains(const T& item) const {
        for (int i = 0; i < length; i++) {
            if (elements[i] == item) {
                return true;
            }
        }
        return false;
    }

    // Вспомогательная функция для увеличения вместимости
    void resize() {
        capacity *= 2;
        T* newElements = new T[capacity];
        for (int i = 0; i < length; i++) {
            newElements[i] = elements[i];
        }
        delete[] elements;
        elements = newElements;
    }

public:
    // Конструктор по умолчанию
    Set() : capacity(10), length(0) {
        elements = new T[capacity];
    }

    // Конструктор копирования
    Set(const Set& other) : capacity(other.capacity), length(other.length) {
        elements = new T[capacity];
        for (int i = 0; i < length; i++) {
            elements[i] = other.elements[i];
        }
    }

    // Деструктор
    ~Set() {
        delete[] elements;
    }

    // Добавление элемента
    void add(const T& item) {
        if (!contains(item)) {
            if (length >= capacity) {
                resize();
            }
            elements[length++] = item;
        }
    }

    // Проверка наличия элемента
    bool in(const T& item) const {
        return contains(item);
    }

    // Удаление элемента
    void remove(const T& item) {
        for (int i = 0; i < length; i++) {
            if (elements[i] == item) {
                for (int j = i; j < length - 1; j++) {
                    elements[j] = elements[j + 1];
                }
                length--;
                break;
            }
        }
    }

    // Получение длины множества
    int getLength() const {
        return length;
    }

    // Оператор объединения (+)
    Set operator+(const Set& other) const {
        Set result = *this; // Копия текущего множества
        for (int i = 0; i < other.length; i++) {
            result.add(other.elements[i]);
        }
        return result;
    }

    // Оператор пересечения (*)
    Set operator*(const Set& other) const {
        Set result;
        for (int i = 0; i < length; i++) {
            if (other.contains(elements[i])) {
                result.add(elements[i]);
            }
        }
        return result;
    }

    // Оператор разности (-)
    Set operator-(const Set& other) const {
        Set result;
        for (int i = 0; i < length; i++) {
            if (!other.contains(elements[i])) {
                result.add(elements[i]);
            }
        }
        return result;
    }

    // Оператор вывода
    friend std::ostream& operator<<(std::ostream& os, const Set& set) {
        os << "{ ";
        for (int i = 0; i < set.length; i++) {
            os << set.elements[i];
            if (i < set.length - 1) {
                os << ", ";
            }
        }
        os << " }";
        return os;
    }

    // Оператор ввода
    friend std::istream& operator>>(std::istream& is, Set& set) {
        int n;
        std::cout << "Enter the number of elements: ";
        while (!(is >> n) || n < 0) {
            std::cout << "Invalid input. Enter a non-negative number: ";
            is.clear(); // Очищаем состояние ошибки
            is.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // Игнорируем некорректный ввод
        }
        set.length = 0; // Очищаем множество
        T item;
        for (int i = 0; i < n; i++) {
            std::cout << "Element " << i + 1 << ": ";
            while (!(is >> item)) {
                std::cout << "Invalid input. Enter a valid value: ";
                is.clear(); // Очищаем состояние ошибки
                is.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // Игнорируем некорректный ввод
            }
            set.add(item);
        }
        return is;
    }
};

// Основная функция программы
int main() {
    // Пример использования функции findSecondMax
    int arr[] = {0, 2, 3, 4, 3, 6};
    int size = sizeof(arr) / sizeof(arr[0]);

    try {
        std::cout << "Array: ";
        for (int i = 0; i < size; i++) {
            std::cout << arr[i] << " ";
        }
        std::cout << "\nSecond largest element: " << findSecondMax(arr, size) << "\n\n";
    } catch (const std::exception& e) {
        std::cout << "Error: " << e.what() << "\n";
    }

    // Пример использования класса Set
    Set<int> set1, set2;

    // Ввод первого множества
    std::cout << "Enter elements for the first set:\n";
    std::cin >> set1;
    std::cout << "Set 1: " << set1 << "\n";

    // Ввод второго множества
    std::cout << "Enter elements for the second set:\n";
    std::cin >> set2;
    std::cout << "Set 2: " << set2 << "\n";

    // Операции с множествами
    std::cout << "Union: " << (set1 + set2) << "\n";
    std::cout << "Intersection: " << (set1 * set2) << "\n";
    std::cout << "Difference (set1 - set2): " << (set1 - set2) << "\n";

    // Проверка наличия элемента
    int value;
    std::cout << "Enter value to check in the first set: ";
    std::cin >> value;
    std::cout << "Element " << value << (set1.in(value) ? " is present" : " is absent") << "\n";

    // Удаление элемента
    std::cout << "Enter value to remove from the first set: ";
    std::cin >> value;
    set1.remove(value);
    std::cout << "Set 1 after removal: " << set1 << "\n";

    return 0;
}