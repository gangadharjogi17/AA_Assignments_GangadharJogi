#include <iostream>
#include <unordered_map>

using namespace std;

typedef int* IntArrayPtr;
void fill_array(int a[], int size);
bool twoSum(int nums[], int size, int target, int result[]);

int main() {
    // Ask the user to enter the number of elements or length of the array
    int array_size;
    cout << "Enter the number of elements/length of the array (between 2 and 104): ";
    cin >> array_size;

    // Validate Constraint - array_size
    while (array_size < 2 || array_size > 104) {
        cout << "Invalid input. Enter a number between 2 and 104: ";
        cin.clear(); // Clear error flags
        cin >> array_size;
    }

    // Allocate memory for the array based on user input
    IntArrayPtr nums;
    nums = new int[array_size];
    fill_array(nums, array_size);

    // Prompt the user to enter the target sum
    int target;
    cout << "Enter the target sum (between -109 and 109): ";
    cin >> target;

    // Validate Constraints for the target
    while (target < -109 || target > 109) {
        cout << "Invalid input. Enter a number between -109 and 109: ";
        cin.clear(); // Clear error flags
        cin >> target;
    }

    // Array to store the indices of the two numbers
    int result[2];

    // Function to find the indices of the two numbers that add up to the target
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

void fill_array(int a[], int size) {
    cout << "Enter " << size << " integers.\n";
    for (int index = 0; index < size; index++) {
        cin >> a[index];
        // Validate Constraint - input number to ensure it is within the range [-109, 109]
        while (a[index] < -109 || a[index] > 109) {
            cout << "Invalid input. Enter an integer between -109 and 109: ";
            cin.clear(); // Clear error flags
            cin >> a[index];
        }
    }
}

bool twoSum(int nums[], int size, int target, int result[]) {
    unordered_map<int, int> num_map;

    for (int i = 0; i < size; ++i) {
        int complement = target - nums[i];

        // Check if the complement (needed to reach the target) exists in the map
        if (num_map.find(complement) != num_map.end()) {
            // Found the pair that adds up to the target
            result[0] = num_map[complement];
            result[1] = i;
            return true;
        }

        num_map[nums[i]] = i;
    }

    return false; // No valid pair found
}
