/**
 * file: prime_factorization.cpp
 * type: C++ (source file)
 * date: 25_SEPTEMBER_2024
 * author: karbytes
 * license: PUBLIC_DOMAIN 
 */

// below is ChatGPT-4o output. karbyes is in the process of modifying it to fit karbytes' style and comprehension.

#include <iostream>
#include <vector>
#include <iomanip>  // For setting spaces using setw

using namespace std;

// Function to generate Pascal's Triangle up to a given number of rows
vector<vector<int>> generatePascalsTriangle(int rows) {
    vector<vector<int>> triangle(rows);

    for (int i = 0; i < rows; ++i) {
        triangle[i].resize(i + 1);
        triangle[i][0] = triangle[i][i] = 1;  // First and last elements are 1

        for (int j = 1; j < i; ++j) {
            triangle[i][j] = triangle[i - 1][j - 1] + triangle[i - 1][j];
        }
    }
    return triangle;
}

// Function to print Pascal's Triangle in equilateral triangle form
void printPascalsTriangle(const vector<vector<int>>& triangle) {
    int rows = triangle.size();
    int max_width = to_string(triangle[rows - 1][rows / 2]).length();  // Get width of the largest number

    for (int i = 0; i < rows; ++i) {
        // Print leading spaces to center the numbers
        cout << setw((rows - i) * (max_width + 1) / 2) << "";

        for (int j = 0; j <= i; ++j) {
            cout << setw(max_width) << triangle[i][j] << " ";
        }
        cout << endl;
    }
}

int main() {
    int numRows;
    cout << "Enter the number of rows for Pascal's Triangle: ";
    cin >> numRows;

    vector<vector<int>> triangle = generatePascalsTriangle(numRows);
    printPascalsTriangle(triangle);

    return 0;
}
