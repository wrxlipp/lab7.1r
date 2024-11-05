#include <iostream>
#include <iomanip>
#include <ctime>
#include <vector>
#include <algorithm>

using namespace std;

// ������� ��� ��������� ������� ���������� ����� � �������� �������
void CreateMatrix(int** matrix, int rows, int cols, int Low, int High) {
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            matrix[i][j] = Low + rand() % (High - Low + 1);
        }
    }
}

// ������� ��� ��������� �������
void PrintMatrix(int** matrix, int rows, int cols) {
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            cout << setw(4) << matrix[i][j];
        }
        cout << endl;
    }
}

// ���������� ������� ��� ���������� ���� �� ������� ��������, �� ������������� �������
void CalcRecursive(int** matrix, int rows, int cols, int row, int col, int& count, int& sum) {
    // ������� �������: ���� �� �������� ���������
    if (row == rows) return;

    // ��������, �� ������� ������� �� ���������� �����
    if (col == cols) {
        CalcRecursive(matrix, rows, cols, row + 1, 0, count, sum); // ������� �� ���������� �����
        return;
    }

    // �������� �������
    if (!(matrix[row][col] > 0 && matrix[row][col] % 2 == 0)) {
        sum += matrix[row][col];
        count++;
        matrix[row][col] = 0; // ����� �������� �� 0
    }

    // ������� �� ���������� ��������
    CalcRecursive(matrix, rows, cols, row, col + 1, count, sum);
}

// ���������� ������� ��� ���������� �������
void SortMatrixRecursive(int** matrix, int rows, int cols, int i = 0) {
    if (i >= rows - 1) return; // ������� �������

    // ���������� �����
    sort(matrix, matrix + rows, [cols](int* row1, int* row2) {
        if (row1[0] != row2[0]) return row1[0] > row2[0]; // ���������� �� ������ ���������� � �������� �������
        if (row1[1] != row2[1]) return row1[1] < row2[1]; // ���� ������ �������� ���������, ������� �� ������ � ����������� �������
        return row1[3] > row2[3]; // ���� ������ � ������ �������, ������� �� ��������� � �������� �������
        });

    SortMatrixRecursive(matrix, rows, cols, i + 1); // ������� �� ���������� �����
}

// ������� �������
int main() {
    srand(static_cast<unsigned>(time(0))); // ����������� ���������� ���������� �����

    const int rows = 8;
    const int cols = 6;
    const int Low = -26;
    const int High = 23;

    // ��������� �������� �������
    int** matrix = new int* [rows];
    for (int i = 0; i < rows; i++) {
        matrix[i] = new int[cols];
    }

    // ��������� �������
    CreateMatrix(matrix, rows, cols, Low, High);

    // ��������� ��������� �������
    cout << "Initial matrix:\n";
    PrintMatrix(matrix, rows, cols);

    // ���������� ������� �� ���� ��������, �� ������������� �������
    int count = 0, sum = 0;
    CalcRecursive(matrix, rows, cols, 0, 0, count, sum);

    // ��������� ����������
    cout << "Count of elements: " << count << endl;
    cout << "Sum of elements: " << sum << endl;

    // ��������� ������������ �������
    cout << "Modified matrix:\n";
    PrintMatrix(matrix, rows, cols);

    // ���������� �������
    SortMatrixRecursive(matrix, rows, cols);

    // ��������� ����������� �������
    cout << "Sorted matrix:\n";
    PrintMatrix(matrix, rows, cols);

    // ��������� ���'��
    for (int i = 0; i < rows; i++) {
        delete[] matrix[i];
    }
    delete[] matrix;

    return 0;
}
