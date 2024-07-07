#include <iostream>
using namespace std;

struct Node {
    int row;
    int col;
    int value;
    Node* next;

    Node(int r, int c, int v) : row(r), col(c), value(v), next(nullptr) {}
};

class SparseMatrix {
private:
    Node* head;
    int rows, cols;

public:
    SparseMatrix(int r, int c) : rows(r), cols(c), head(nullptr) {}

    ~SparseMatrix() {
        Node* current = head;
        while (current != nullptr) {
            Node* next = current->next;
            delete current;
            current = next;
        }
    }

    void addValue(int r, int c, int value) {
        if (value != 0) {
            Node* newNode = new Node(r, c, value);
            if (head == nullptr) {
                head = newNode;
            }
            else {
                Node* current = head;
                while (current->next != nullptr) {
                    current = current->next;
                }
                current->next = newNode;
            }
        }
    }

    void printMatrix() {
        if (head == nullptr) {
            cout << "No Non zero elements found in the Matrix";
            
        }
        else
        {
             Node* current = head;
        cout << "Row: ";
        while (current != nullptr) {
            cout << current->row << " ";
            current = current->next;
        }
        cout << "\nColumn: ";
        current = head;
        while (current != nullptr) {
            cout << current->col << " ";
            current = current->next;
        }
        cout << "\nValue: ";
        current = head;
        while (current != nullptr) {
            cout << current->value << " ";
            current = current->next;
        }
        cout << "\nNext Node (Address): ";
        current = head;
        while (current != nullptr) {
            cout << current->next << " ";
            current = current->next;
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
