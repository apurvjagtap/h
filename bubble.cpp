#include <iostream>
#include <omp.h>
using namespace std;

void bubbleSort(int arr[], int n) {
    #pragma omp parallel for
    for (int i = 0; i < n-1; i++) {
        // Last i elements are already in place
        for (int j = 0; j < n-i-1; j++) {
            if (arr[j] > arr[j+1]) {
                // Swap arr[j] and arr[j+1]
                int temp = arr[j];
                arr[j] = arr[j+1];
                arr[j+1] = temp;
            }
        }
    }
}

int main() {
    int arr[] = {64, 34, 25, 12, 22, 11};
    int n = sizeof(arr)/sizeof(arr[0]);

    cout << "Array before sorting:\n";
    for (int i = 0; i < n; i++)
        cout << arr[i] << " ";
        cout << endl;

    bubbleSort(arr, n);

    cout << "Array after sorting:\n";
    for (int i = 0; i < n; i++)
        cout << arr[i] << " ";
    cout << endl;
    return 0;
}
