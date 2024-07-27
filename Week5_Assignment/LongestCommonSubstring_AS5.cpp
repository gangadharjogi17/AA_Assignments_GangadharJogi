#include <iostream>
#include <cstring>
#include <cstdlib>

using namespace std;


struct Node {
    int value;
    Node* next;
};


struct LinkedList {
    Node* head;
    LinkedList() : head(nullptr) {}

    
    void append(int value) {
        Node* newNode = new Node;
        newNode->value = value;
        newNode->next = nullptr;

        if (head == nullptr) {
            head = newNode;
        }
        else {
            Node* temp = head;
            while (temp->next != nullptr) {
                temp = temp->next;
            }
            temp->next = newNode;
        }
    }

    // Function to get the last node value
    int getLastValue() {
        if (head == nullptr) {
            return 0;
        }
        Node* temp = head;
        while (temp->next != nullptr) {
            temp = temp->next;
        }
        return temp->value;
    }
};

int main() {
    string X, Y;
    cout << "Enter first string: ";
    cin >> X;
    cout << "Enter second string: ";
    cin >> Y;

    int m = X.length();
    int n = Y.length();

    // Creating a 2D array of linked lists
    LinkedList** dp = new LinkedList * [m + 1];  //dynamic values
    for (int i = 0; i <= m; ++i) {
        dp[i] = new LinkedList[n + 1];
    }

    int maxLength = 0;
    int endIndex = 0;

    // Filling the table according to the longest common substring algorithm
    for (int i = 1; i <= m; ++i) {
        for (int j = 1; j <= n; ++j) {
            if (X[i - 1] == Y[j - 1]) {
                int value = dp[i - 1][j - 1].getLastValue() + 1;
                dp[i][j].append(value);
                if (value > maxLength) {
                    maxLength = value;
                    endIndex = i - 1;
                }
            }
            else {
                dp[i][j].append(0);
            }
        }
    }

    // Print the table
    cout << "DP Table:" << endl;
    for (int i = 0; i <= m; ++i) {
        for (int j = 0; j <= n; ++j) {
            cout << dp[i][j].getLastValue() << " ";
        }
        cout << endl;
    }

    if (maxLength > 0) {
        // Extract the longest common substring
        string longestCommonSubstr = X.substr(endIndex - maxLength + 1, maxLength);
        cout << "The longest common substring is: " << longestCommonSubstr << endl;
        cout << "The length of the longest common substring is: " << maxLength << endl;
    }
    else {
        cout << "No common substring found." << endl;
    }

    // delete/free the allocated memory
    for (int i = 0; i <= m; ++i) {
        delete[] dp[i];
    }
    delete[] dp;

    return 0;
}
