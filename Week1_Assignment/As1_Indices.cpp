#include <iostream>

typedef int* IntArrayPtr;
void fill_array(int a[], int size);
bool twoSum(int nums[], int size, int target, int result[]);

int main() {
    using namespace std;

    // Ask the user to enter the number of elements in the array
    int array_size;
    cout << "Enter the number of elements in the array: ";
    cin >> array_size;

    // Allocate memory for the array based on user input
    IntArrayPtr nums;
    nums = new int[array_size];
    fill_array(nums, array_size);

    // Prompt the user to enter the target sum
    int target;
    cout << "Enter the target sum: ";
    cin >> target;

    // Array to store the indices of the two numbers
    int result[2];

    // Function which finds the indices of the two numbers that add up to the target
    bool found = twoSum(nums, array_size, target, result);

    if (found) {
        cout << "Indices of the two numbers that add up to the " << target << ": [" << result[0] << ", " << result[1] << "]\n";
    }
    else {
        cout << "No two numbers in the given array that add up to " << target << ".\n";
    }
    // Free dynamically allocated memory
    delete[] nums;

    return 0;
}

void fill_array(int a[], int size)
{
    using namespace std;
    cout << "Enter " << size << " integers.\n";
    for (int index = 0; index < size; index++)
        cin >> a[index];
}

bool twoSum(int nums[], int size, int target, int result[]) {
    
    for (int i = 0; i < size - 1; ++i) {
        for (int j = i + 1; j < size; ++j) {
            if (nums[i] + nums[j] == target) {
                result[0] = i;
                result[1] = j;
                return true;
            }
        }
    }
    return false;
}
