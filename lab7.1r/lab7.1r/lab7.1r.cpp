#include <iostream>
#include <iomanip>
#include <ctime>
#include <vector>
#include <algorithm>

using namespace std;

// Функція для створення матриці випадкових чисел в заданому діапазоні
void CreateMatrix(int** matrix, int rows, int cols, int Low, int High) {
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            matrix[i][j] = Low + rand() % (High - Low + 1);
        }
    }
}

// Функція для виведення матриці
void PrintMatrix(int** matrix, int rows, int cols) {
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            cout << setw(4) << matrix[i][j];
        }
        cout << endl;
    }
}

// Рекурсивна функція для обчислення суми та кількості елементів, які задовольняють критерію
void CalcRecursive(int** matrix, int rows, int cols, int row, int col, int& count, int& sum) {
    // Базовий випадок: якщо всі елементи оброблено
    if (row == rows) return;

    // Перевірка, чи потрібно перейти до наступного рядка
    if (col == cols) {
        CalcRecursive(matrix, rows, cols, row + 1, 0, count, sum); // Перехід до наступного рядка
        return;
    }

    // Перевірка критерію
    if (!(matrix[row][col] > 0 && matrix[row][col] % 2 == 0)) {
        sum += matrix[row][col];
        count++;
        matrix[row][col] = 0; // Заміна елемента на 0
    }

    // Перехід до наступного елемента
    CalcRecursive(matrix, rows, cols, row, col + 1, count, sum);
}

// Рекурсивна функція для сортування матриці
void SortMatrixRecursive(int** matrix, int rows, int cols, int i = 0) {
    if (i >= rows - 1) return; // Базовий випадок

    // Сортування рядків
    sort(matrix, matrix + rows, [cols](int* row1, int* row2) {
        if (row1[0] != row2[0]) return row1[0] > row2[0]; // Сортування за першим стовпчиком у спадному порядку
        if (row1[1] != row2[1]) return row1[1] < row2[1]; // Якщо перший стовпчик однаковий, сортуємо за другим у зростаючому порядку
        return row1[3] > row2[3]; // Якщо перший і другий однакові, сортуємо за четвертим у спадному порядку
        });

    SortMatrixRecursive(matrix, rows, cols, i + 1); // Перехід до наступного рядка
}

// Головна функція
int main() {
    srand(static_cast<unsigned>(time(0))); // Ініціалізація генератора випадкових чисел

    const int rows = 8;
    const int cols = 6;
    const int Low = -26;
    const int High = 23;

    // Створення динамічної матриці
    int** matrix = new int* [rows];
    for (int i = 0; i < rows; i++) {
        matrix[i] = new int[cols];
    }

    // Генерація матриці
    CreateMatrix(matrix, rows, cols, Low, High);

    // Виведення початкової матриці
    cout << "Initial matrix:\n";
    PrintMatrix(matrix, rows, cols);

    // Обчислення кількості та суми елементів, які задовольняють критерію
    int count = 0, sum = 0;
    CalcRecursive(matrix, rows, cols, 0, 0, count, sum);

    // Виведення результатів
    cout << "Count of elements: " << count << endl;
    cout << "Sum of elements: " << sum << endl;

    // Виведення модифікованої матриці
    cout << "Modified matrix:\n";
    PrintMatrix(matrix, rows, cols);

    // Сортування матриці
    SortMatrixRecursive(matrix, rows, cols);

    // Виведення відсортованої матриці
    cout << "Sorted matrix:\n";
    PrintMatrix(matrix, rows, cols);

    // Звільнення пам'яті
    for (int i = 0; i < rows; i++) {
        delete[] matrix[i];
    }
    delete[] matrix;

    return 0;
}
