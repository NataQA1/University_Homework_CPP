#include <iostream>
#include <cmath>

using namespace std;

// Функция для вычисления суммы последовательности
double calculateSum(int n) {
    double sum = 0.0;
    for (int i = 0; i <= n; i++) {
        sum += pow(-1, i) / pow(2, i);
    }
    return sum;
}

//Функция main() — точка входа в программу.
int main() {
    int n;
    cout << "Enter n: ";
    cin >> n;

    double result = calculateSum(n);
    cout << "Sum of the sequence: " << result << endl;

    return 0;
}
