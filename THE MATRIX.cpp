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
        return rotated;
    }

    // Method to rotate the matrix 90 degrees counterclockwise
    Matrix rotateCounterclockwise() const {
        Matrix rotated(cols, rows);
        for (int i = 0; i < rows; i++) {
            for (int j = 0; j < cols; j++) {
                rotated.data[cols - 1 - j][i] = data[i][j];
            }
        }
        return rotated;
    }

    // Method to calculate the determinant of a 2x2 matrix
    int determinant() const {
        if (rows != 2 || cols != 2) {
            cout << "Determinant can only be calculated for 2x2 matrices." << endl;
            return 0;
        }
        // Determinant formula for a 2x2 matrix: ad - bc
        return (data[0][0] * data[1][1]) - (data[0][1] * data[1][0]);
    }
};

// Function to display menu
void displayMenu() {
    cout << "\nMatrix Operations Menu:\n";
    cout << "1. Create Matrices\n";
    cout << "2. Add Matrices\n";
    cout << "3. Subtract Matrices\n"; // New option for subtraction
    cout << "4. Multiply Matrices\n";
    cout << "5. Transpose Matrix\n";
    cout << "6. Rotate Matrix Clockwise\n";
    cout << "7. Rotate Matrix Counterclockwise\n";
    cout << "8. Calculate Trace\n"; // New option for trace
    cout << "9. Calculate Determinant (2x2)\n"; // New option for determinant
    cout << "10. Exit\n";
    cout << "Choose an option: ";
}

int main() {
    Matrix* mat1 = NULL;
    Matrix* mat2 = NULL;
    int choice, rows, cols;

    while (true) {
        displayMenu();
        cin >> choice;

        switch (choice) {
            case 1: // Create matrices
                cout << "Enter rows and columns for the first matrix: ";
                cin >> rows >> cols;
                mat1 = new Matrix(rows, cols);
                mat1->input();
                mat1->display();

                cout << "Enter rows and columns for the second matrix: ";
                cin >> rows >> cols;
                mat2 = new Matrix(rows, cols);
                mat2->input();
                mat2->display();
                break;

            case 2: // Add matrices
                if (mat1 && mat2) {
                    Matrix sum = mat1->add(*mat2);
                    if (!sum.isEmpty()) { // Check if sum is valid
                        cout << "Sum of matrices:\n";
                        sum.display();
                    }
                } else {
                    cout << "Please create both matrices first.\n";
                }
                break;

            case 3: // Subtract matrices
                if (mat1 && mat2) {
                    Matrix difference = mat1->subtract(*mat2);
                    if (!difference.isEmpty()) { // Check if difference is valid
                        cout << "Difference of matrices:\n";
                        difference.display();
                    }
                } else {
                    cout << "Please create both matrices first.\n";
                }
                break;

            case 4: // Multiply matrices
                if (mat1 && mat2) {
                    Matrix product = mat1->multiply(*mat2);
                    if (!product.isEmpty()) { // Check if product is valid
                        cout << "Product of matrices:\n";
                        product.display();
                    }
                } else {
                    cout << "Please create both matrices first.\n";
                }
                break;

            case 5: // Transpose matrix
                if (mat1) {
                    Matrix transposed = mat1->transpose();
                    cout << "Transpose of 1st Matrix:\n";
                    transposed.display();
                } else {
                    cout << "Please create a matrix first.\n";
                }
                break;

            case 6: // Rotate matrix clockwise
                if (mat1) {
                    Matrix rotated = mat1->rotateClockwise();
                    cout << " Matrix 1 Rotated Clockwise:\n";
                    rotated.display();
                    delete mat1; // Free memory for the old matrix
                    mat1 = new Matrix(rotated); // Update mat1 to the rotated matrix
                } else {
                    cout << "Please create a matrix first.\n";
                }
                break;

            case 7: // Rotate matrix counterclockwise
                if (mat1) {
                    Matrix rotated = mat1->rotateCounterclockwise();
                    cout << "Matrix 1 Rotated Counterclockwise:\n";
                    rotated.display();
                    delete mat1; // Free memory for the old matrix
                    mat1 = new Matrix(rotated); // Update mat1 to the rotated matrix
                } else {
                    cout << "Please create a matrix first.\n";
                }
                break;

            case 8: // Calculate trace
                if (mat1) {
                    int traceValue = mat1->trace();
                    cout << "Trace of the matrix 1: " << traceValue << endl;
                } else {
                    cout << "Please create a matrix first.\n";
                }
                break;

            case 9: // Calculate determinant (for 2x2 matrices)
                if (mat1) {
                    int detValue = mat1->determinant();
                    if (detValue != 0) {
                        cout << "Determinant of 1st matrix: " << detValue << endl;
                    }
                } else {
                    cout << "Please create a matrix first.\n";
                }
                break;

            case 10: // Exit
                cout << "Exiting program...\n";
                return 0;

            default:
                cout << "Invalid option. Please choose again.\n";
        }
    }
}