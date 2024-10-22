#include <iostream>

using namespace std;

class Matrix {
private:
    int rows;
    int cols;
    int** data;

public:
    Matrix(int r, int c) {  // constructor
        rows = r;
        cols = c;

        // Allocating memory for the 2D array
        data = new int*[rows];
        for (int i = 0; i < rows; ++i) {
            data[i] = new int[cols](); // Initialize to zero
        }
    }

    // Destructor to free allocated memory
    ~Matrix() {
        for (int i = 0; i < rows; ++i) {
            delete[] data[i];
        }
        delete[] data;
    }

    // Method to input matrix values
    void input() {
        cout << "Enter elements of the matrix (" << rows << "x" << cols << "):\n";
        for (int i = 0; i < rows; i++) {
            for (int j = 0; j < cols; j++) {
                cin >> data[i][j];
            }
        }
    }

    // Method to display the matrix
    void display() const {
        cout << "Matrix:\n";
        for (int i = 0; i < rows; i++) {
            for (int j = 0; j < cols; j++) {
                cout << data[i][j] << " ";
            }
            cout << endl;
        }
    }

    // Method to check if the matrix is empty
    bool isEmpty() const {
        return rows == 0 || cols == 0;
    }

    // Method to add another matrix
    Matrix add(const Matrix& other) {
        if (rows != other.rows || cols != other.cols) {
            cout << "Matrix dimensions do not match for addition." << endl;
            return Matrix(0, 0); // Return an empty matrix
        }
        Matrix result(rows, cols);
        for (int i = 0; i < rows; i++) {
            for (int j = 0; j < cols; j++) {
                result.data[i][j] = data[i][j] + other.data[i][j];
            }
        }
        return result;
    }

    // Method to subtract another matrix
    Matrix subtract(const Matrix& other) {
        if (rows != other.rows || cols != other.cols) {
            cout << "Matrix dimensions do not match for subtraction." << endl;
            return Matrix(0, 0); // Return an empty matrix
        }
        Matrix result(rows, cols);
        for (int i = 0; i < rows; i++) {
            for (int j = 0; j < cols; j++) {
                result.data[i][j] = data[i][j] - other.data[i][j];
            }
        }
        return result;
    }

    // Method to multiply with another matrix
    Matrix multiply(const Matrix& other) {
        if (cols != other.rows) {
            cout << "Matrix dimensions do not match for multiplication." << endl;
            return Matrix(0, 0); // Return an empty matrix
        }
        Matrix result(rows, other.cols);
        for (int i = 0; i < rows; i++) {
            for (int j = 0; j < other.cols; j++) {
                for (int k = 0; k < cols; k++) {
                    result.data[i][j] += data[i][k] * other.data[k][j];
                }
            }
        }
        return result;
    }

    // Method to calculate the trace of the matrix
    int trace() const {
        if (rows != cols) {
            cout << "Trace can only be calculated for square matrices." << endl;
            return 0; // Return 0 if not a square matrix
        }
        int traceValue = 0;
        for (int i = 0; i < rows; i++) {
            traceValue += data[i][i]; // Summing the diagonal elements
        }
        return traceValue;
    }

    // Method to transpose the matrix
    Matrix transpose() const {
        Matrix transposed(cols, rows);
        for (int i = 0; i < rows; i++) {
            for (int j = 0; j < cols; j++) {
                transposed.data[j][i] = data[i][j];
            }
        }
        return transposed;
    }

    // Method to rotate the matrix 90 degrees clockwise
    Matrix rotateClockwise() const {
        Matrix rotated(cols, rows);
        for (int i = 0; i < rows; i++) {
            for (int j = 0; j < cols; j++) {
                rotated.data[j][rows - 1 - i] = data[i][j];
            }
        }
        return rotated