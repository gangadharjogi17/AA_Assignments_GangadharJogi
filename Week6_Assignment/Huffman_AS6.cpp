#include <iostream>
#include <string>

using namespace std;

// Node structure for the Huffman tree
struct Node {
    char data;
    int freq;
    Node* left;
    Node* right;

    Node(char data, int freq) {
        this->data = data;
        this->freq = freq;
        left = right = nullptr;
    }
};


struct NodeList {
    Node* node;
    NodeList* next;

    NodeList(Node* n) : node(n), next(nullptr) {}
};

// Priority queue implementation using linked list
struct PriorityQueue {
    NodeList* head;

    PriorityQueue() : head(nullptr) {}

    void push(Node* n) {
        NodeList* newNode = new NodeList(n);
        if (!head || head->node->freq > n->freq) {
            newNode->next = head;
            head = newNode;
        }
        else {
            NodeList* current = head;
            while (current->next && current->next->node->freq <= n->freq) {
                current = current->next;
            }
            newNode->next = current->next;
            current->next = newNode;
        }
    }

    Node* pop() {
        if (!head) return nullptr;
        NodeList* temp = head;
        head = head->next;
        Node* node = temp->node;
        delete temp;
        return node;
    }

    bool isEmpty() {
        return head == nullptr;
    }
};

// Function to print the Huffman codes in preorder traversal
void printCodes(Node* root, string str) {
    if (!root) return;

    // If this is a leaf node, then it's a character with its Huffman code
    if (!root->left && !root->right) {
        cout << root->data << ": " << str << "\n";
    }

    printCodes(root->left, str + "0");
    printCodes(root->right, str + "1");
}

// Main function to build the Huffman tree and generate codes
void HuffmanCodes(char data[], int freq[], int size) {
    PriorityQueue minHeap;

    // Create a leaf node for each character and add it to the min heap
    for (int i = 0; i < size; ++i) {
        minHeap.push(new Node(data[i], freq[i]));
    }

    // Iterate until the size of heap becomes 1
    while (minHeap.head->next != nullptr) {
        // Extract the two nodes with the lowest frequency
        Node* left = minHeap.pop();
        Node* right = minHeap.pop();

        // Create a new internal node with frequency equal to the sum of the two nodes' frequencies
        Node* top = new Node('$', left->freq + right->freq);

        
        top->left = left;
        top->right = right;

        // Add this node to the min heap
        minHeap.push(top);
    }

    // The remaining node is the root of the Huffman tree
    printCodes(minHeap.pop(), "");
}

int main() {
    string S;
    cout << "Enter the characters: ";
    cin >> S;
    
    // Validate that the string contains only alphabetic characters
    for (char c : S) {
        if (!isalpha(c)) {
            cerr << "Invalid Format.Only alphabetic characters are allowed.\n";
            return 1;
        }
    }
    int n = S.length();
    int* freq = new int[n];

    cout << "Enter the frequencies: ";
    for (int i = 0; i < n; ++i) {
        while (true) {
            cout << "Enter frequency for '" << S[i] << "': ";
            cin >> freq[i];

            if (cin.fail() || freq[i] <= 0) {
                cerr << "Invalid input.. Please enter a positive numeric value(>0) for the frequency....\n";
                cin.clear(); // Clear the error flag on cin
                cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Ignore the invalid input
            }
            else {
                break;
            }
        }

    }

    // Print the String and their frequencies
    cout << "\nEntered String: " << S << "\nFrequencies: ";
    for (int i = 0; i < n; ++i) {
        cout << freq[i];
        if (i < n - 1) {
            cout << ", ";
        }
    }
    cout << endl;

    HuffmanCodes(&S[0], freq, n);

    delete[] freq;
    return 0;
}
