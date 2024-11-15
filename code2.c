#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void swap(int* a, int* b) 
{
    int temp = *a;
    *a = *b;
    *b = temp;
}

int partition(int arr[], int low, int high) 
{
    int pivot = arr[high];
    int i = (low - 1);

    for (int j = low; j < high; j++) 
    {
        if (arr[j] <= pivot) 
        {
            i++;
            swap(&arr[i], &arr[j]);
        }
    }
    swap(&arr[i + 1], &arr[high]);
    return (i + 1);
}

void quickSort(int arr[], int low, int high) 
{
    if (low < high) 
    {
        int pi = partition(arr, low, high);
        quickSort(arr, low, pi - 1);
        quickSort(arr, pi + 1, high);
    }
}

void merge(int arr[], int left, int mid, int right) 
{
    int n1 = mid - left + 1;
    int n2 = right - mid;

    int* L = (int*)malloc(n1 * sizeof(int));
    int* R = (int*)malloc(n2 * sizeof(int));

    for (int i = 0; i < n1; i++) 
    {
        L[i] = arr[left + i];
    }
    for (int j = 0; j < n2; j++) 
    {
        R[j] = arr[mid + 1 + j];
    }

    int i = 0, j = 0, k = left;
    while (i < n1 && j < n2) 
    {
        if (L[i] <= R[j]) 
        {
            arr[k++] = L[i++];
        } 
        else 
        {
            arr[k++] = R[j++];
        }
    }

    while (i < n1) 
    {
        arr[k++] = L[i++];
    }

    while (j < n2) 
    {
        arr[k++] = R[j++];
    }

    free(L);
    free(R);
}

void mergeSort(int arr[], int left, int right) 
{
    if (left < right) 
    {
        int mid = left + (right - left) / 2;

        mergeSort(arr, left, mid);
        mergeSort(arr, mid + 1, right);

        merge(arr, left, mid, right);
    }
}

void generateData(int* arr, int size, int seed) 
{
    srand(seed);
    for (int i = 0; i < size; i++) {
        arr[i] = rand() % 100000 + 1;
    }
}

void copyArray(int* source, int* dest, int size) 
{
    for (int i = 0; i < size; i++) 
    {
        dest[i] = source[i];
    }
}

void measurePerformance(int* data, int size) 
{
    int* dataCopy = (int*)malloc(size * sizeof(int));

    copyArray(data, dataCopy, size);
    clock_t start = clock();
    mergeSort(dataCopy, 0, size - 1);
    clock_t end = clock();
    double mergeSortTime = ((double)(end - start)) / CLOCKS_PER_SEC;

    copyArray(data, dataCopy, size);
    start = clock();
    quickSort(dataCopy, 0, size - 1);
    end = clock();
    double quickSortTime = ((double)(end - start)) / CLOCKS_PER_SEC;

    printf("Data Size: %d\n", size);
    printf("  Merge Sort Time: %.6f seconds\n", mergeSortTime);
    printf("  Quick Sort Time: %.6f seconds\n", quickSortTime);

    free(dataCopy);
}

int main() 
{
    int sizes[] = {100, 1000, 5000, 10000};
    int numSizes = sizeof(sizes) / sizeof(sizes[0]);
    int seed = 42;

    for (int i = 0; i < numSizes; i++) 
    {
        int size = sizes[i];
        int* data = (int*)malloc(size * sizeof(int));
        generateData(data, size, seed);
        measurePerformance(data, size);
        free(data);
    }
    return 0;
}
