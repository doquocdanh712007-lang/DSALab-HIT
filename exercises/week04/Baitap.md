#include <iostream>
#include <vector>

using namespace std;

void printArray(const vector<int>& arr) {
    for (size_t i = 0; i < arr.size(); i++) {
        cout << arr[i] << " ";
    }
    cout << endl;
}

void bubbleSortPrint(vector<int> arr) {
    cout << "\n--- BUBBLE SORT ---" << endl;
    cout << "Ban dau: "; printArray(arr);
    for (size_t i = 0; i < arr.size() - 1; i++) {
        bool swapped = false;
        for (size_t j = 0; j < arr.size() - i - 1; j++) {
            if (arr[j] > arr[j + 1]) {
                int temp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = temp;
                swapped = true;
            }
        }
        cout << "Buoc " << i + 1 << ": "; printArray(arr);
        if (!swapped) break;
    }
}

void selectionSortPrint(vector<int> arr) {
    cout << "\n--- SELECTION SORT ---" << endl;
    cout << "Ban dau: "; printArray(arr);
    for (size_t i = 0; i < arr.size() - 1; i++) {
        size_t min_idx = i;
        for (size_t j = i + 1; j < arr.size(); j++) {
            if (arr[j] < arr[min_idx]) min_idx = j;
        }
        int temp = arr[i];
        arr[i] = arr[min_idx];
        arr[min_idx] = temp;
        cout << "Buoc " << i + 1 << ": "; printArray(arr);
    }
}

void insertionSortPrint(vector<int> arr) {
    cout << "\n--- INSERTION SORT ---" << endl;
    cout << "Ban dau: "; printArray(arr);
    for (size_t i = 1; i < arr.size(); i++) {
        int key = arr[i];
        int j = i - 1;
        while (j >= 0 && arr[j] > key) {
            arr[j + 1] = arr[j];
            j--;
        }
        arr[j + 1] = key;
        cout << "Buoc " << i << ": "; printArray(arr);
    }
}

int main() {
    vector<int> data;
    data.push_back(5); data.push_back(2); data.push_back(9);
    data.push_back(1); data.push_back(5); data.push_back(6);

    bubbleSortPrint(data);
    selectionSortPrint(data);
    insertionSortPrint(data);
    return 0;
}
