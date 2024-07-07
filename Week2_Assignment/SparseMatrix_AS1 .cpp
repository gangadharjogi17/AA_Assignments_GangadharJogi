#include <iostream>
using namespace std;

#define MAX 100 // Default max non-zero values

class SparseMatrix {
private:
    int* row_indices;
    int* col_indices;
    int* values;
    int count;  // Number of non-zero elements
    int maxNonZero; // Maximum number of non-zero elements allowed
    int rows, cols;

public:
    SparseMatrix(int r, int c, int maxNonZero = MAX) : rows(r), cols(c), count(0), maxNonZero(maxNonZero) {
        row_indices = new int[maxNonZero];
        col_indices = new int[maxNonZero];
        values = new int[maxNonZero];
    }

    ~SparseMatrix() {
        delete[] row_indices;
        delete[] col_indices;
        delete[] values;
    }

    void addValue(int r, int c, int value) {
        if (value != 0) {
            if (count < maxNonZero) {
                row_indices[count] = r;
                col_indices[count] = c;
                values[count] = value;
                count++;
            }
            else {
                cout << "Exceeded maximum number of non-zero elements. Ignoring additional elements." << endl;
            }
        }
    }

    void printMatrix() {
        if (count == 0)
        {
            cout << "No Non zero elements found in the Matrix";
        }
        else
        {
            cout << "Row: ";
            for (int i = 0; i < count; ++i) {
                cout << row_indices[i] << " ";
            }
            cout << "\nColumn: ";
            for (int i = 0; i < count; ++i) {
                cout << col_indices[i] << " ";
            }
            cout << "\nValue: ";
            for (int i = 0; i < count; ++i) {
                cout << values[i] << " ";
            }
            cout << endl;
        }
        
    }
};

int main() {
    int rows, cols;

    cout << "Enter the number of rows: ";
    cin >> rows;
    cout << "Enter the number of columns: ";
    cin >> cols;

    SparseMatrix sm(rows, cols);

    cout << "Enter the elements of the matrix (row by row):\n";
    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
            int value;
            cin >> value;
            sm.addValue(i, j, value);
        }
    }

    sm.printMatrix();

    return 0;
}
