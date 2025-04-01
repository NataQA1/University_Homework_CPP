#include <iostream>
#include <vector>

using namespace std;

// Функция для вычисления произведения нечетных элементов вектора
int productOfOddElements(const vector<int>& vec) {
    int product = 1;
    bool hasOdd = false; // Флаг для проверки наличия нечетных элементов

    for (int num : vec) {
        if (num % 2 != 0) { // Проверка на нечетность
            product *= num;
            hasOdd = true;
        }
    }

    return hasOdd ? product : 0; // Если нечетные элементы отсутствуют, возвращаем 0
}

// Функция для вычисления произведения элементов главной диагонали матрицы
int productOfMainDiagonal(const vector<vector<int>>& matrix) {
    int product = 1;
    int size = matrix.size(); // Предполагаем, что матрица квадратная

    for (int i = 0; i < size; ++i) {
        product *= matrix[i][i]; // Элементы главной диагонали
    }

    return product;
}

int main() {
    // Пример работы с вектором
    vector<int> vec = {1, 2, 3, 4, 5, 6, 7, 8, 9};
    int oddProduct = productOfOddElements(vec);
    cout << "The product of odd elements of the vector: " << oddProduct << endl;

    // Пример работы с матрицей
    vector<vector<int>> matrix = {
        {1, 2, 3},
        {4, 5, 6},
        {7, 8, 9}
    };
    int diagonalProduct = productOfMainDiagonal(matrix);
    cout << "Product of elements of the main diagonal of a matrix: " << diagonalProduct << endl;

    return 0;
}