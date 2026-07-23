//  TIME & SPACE COMPLEXITY SUMMARY
//  Algorithm         Best        Average     Worst       Space     Stable
//  Bubble Sort       O(n)        O(n^2)      O(n^2)      O(1)      Yes
//  Selection Sort    O(n^2)      O(n^2)      O(n^2)      O(1)      No
//  Insertion Sort    O(n)        O(n^2)      O(n^2)      O(1)      Yes
//  Merge Sort        O(n log n)  O(n log n)  O(n log n)  O(n)      Yes
//  Quick Sort        O(n log n)  O(n log n)  O(n^2)      O(log n)  No

#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <chrono>
using namespace std;
using namespace std::chrono;

// Bubble Sort
void bubbleSort(vector<int> &arr)
{
    int n = arr.size();
    for (int i = 0; i < n - 1; i++)
    {
        bool swapped = false;
        for (int j = 0; j < n - i - 1; j++)
        {
            if (arr[j] > arr[j + 1])
            {
                swap(arr[j], arr[j + 1]);
                swapped = true;
            }
        }
        if (!swapped)
            break;
    }
}

// Selection Sort
void selectionSort(vector<int> &arr)
{
    int n = arr.size();
    for (int i = 0; i < n - 1; i++)
    {
        int minIdx = i;
        for (int j = i + 1; j < n; j++)
            if (arr[j] < arr[minIdx])
                minIdx = j;
        if (minIdx != i)
            swap(arr[i], arr[minIdx]);
    }
}

// Insertion Sort
void insertionSort(vector<int> &arr)
{
    int n = arr.size();
    for (int i = 1; i < n; i++)
    {
        int key = arr[i];
        int j = i - 1;
        while (j >= 0 && arr[j] > key)
        {
            arr[j + 1] = arr[j];
            j--;
        }
        arr[j + 1] = key;
    }
}

// Merge Sort
void merge(vector<int> &arr, vector<int> &buffer, int l, int m, int r)
{
    int i = l, j = m + 1, k = l;
    while (i <= m && j <= r)
        buffer[k++] = (arr[i] <= arr[j]) ? arr[i++] : arr[j++];
    while (i <= m)
        buffer[k++] = arr[i++];
    while (j <= r)
        buffer[k++] = arr[j++];
    for (int x = l; x <= r; x++)
        arr[x] = buffer[x];
}

void mergeSortHelper(vector<int> &arr, vector<int> &buffer, int l, int r)
{
    if (l < r)
    {
        int m = l + (r - l) / 2;
        mergeSortHelper(arr, buffer, l, m);
        mergeSortHelper(arr, buffer, m + 1, r);
        merge(arr, buffer, l, m, r);
    }
}

void mergeSort(vector<int> &arr, int l, int r)
{
    vector<int> buffer(arr.size());
    mergeSortHelper(arr, buffer, l, r);
}

// Quick Sort
int partition(vector<int> &arr, int low, int high)
{
    int pivot = arr[high];
    int i = low - 1;
    for (int j = low; j < high; j++)
    {
        if (arr[j] < pivot)
        {
            i++;
            swap(arr[i], arr[j]);
        }
    }
    swap(arr[i + 1], arr[high]);
    return i + 1;
}

void quickSort(vector<int> &arr, int low, int high)
{
    vector<pair<int, int> > stack;
    stack.reserve(64);
    stack.push_back(make_pair(low, high));
    while (!stack.empty())
    {
        pair<int, int> range = stack.back();
        stack.pop_back();
        int l = range.first;
        int h = range.second;
        if (l < h)
        {
            int pi = partition(arr, l, h);
            stack.push_back(make_pair(l, pi - 1));
            stack.push_back(make_pair(pi + 1, h));
        }
    }
}

int main()
{
    const int n = 100;
    vector<int> arr(n), temp;
    arr.reserve(n);
    srand(time(0));

    for (int i = 0; i < n; i++)
        arr[i] = rand() % 1000;

    cout << "Number of Elements = " << n << "\n\n";

    auto start = high_resolution_clock::now();
    temp = arr;
    bubbleSort(temp);
    auto stop = high_resolution_clock::now();
    cout << "Bubble Sort Time    : " << duration_cast<microseconds>(stop - start).count() << " microseconds\n";

    start = high_resolution_clock::now();
    temp = arr;
    selectionSort(temp);
    stop = high_resolution_clock::now();
    cout << "Selection Sort Time : " << duration_cast<microseconds>(stop - start).count() << " microseconds\n";

    start = high_resolution_clock::now();
    temp = arr;
    insertionSort(temp);
    stop = high_resolution_clock::now();
    cout << "Insertion Sort Time : " << duration_cast<microseconds>(stop - start).count() << " microseconds\n";

    start = high_resolution_clock::now();
    temp = arr;
    mergeSort(temp, 0, n - 1);
    stop = high_resolution_clock::now();
    cout << "Merge Sort Time     : " << duration_cast<microseconds>(stop - start).count() << " microseconds\n";

    start = high_resolution_clock::now();
    temp = arr;
    quickSort(temp, 0, n - 1);
    stop = high_resolution_clock::now();
    cout << "Quick Sort Time     : " << duration_cast<microseconds>(stop - start).count() << " microseconds\n";

    return 0;
}