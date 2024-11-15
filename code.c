#include <stdio.h>
#include <stdlib.h>
#include <time.h>

typedef struct Node 
{
    int key;
    struct Node* left;
    struct Node* right;
} Node;

Node* createNode(int key) 
{
    Node* newNode = (Node*)malloc(sizeof(Node));
    newNode->key = key;
    newNode->left = NULL;
    newNode->right = NULL;
    return newNode;
}

Node* insertIterative(Node* root, int key) 
{
    Node* newNode = createNode(key);
    if (root == NULL) 
    {
        return newNode;
    }

    Node* current = root;
    Node* parent = NULL;

    while (current != NULL) 
    {
        parent = current;
        if (key < current->key) 
        {
            current = current->left;
        } 
        else 
        {
            current = current->right;
        }
    }

    if (key < parent->key) 
    {
        parent->left = newNode;
    }
    else 
    {
        parent->right = newNode;
    }

    return root;
}

Node* insertRecursive(Node* root, int key) 
{
    if (root == NULL) 
    {
        return createNode(key);
    }

    if (key < root->key) 
    {
        root->left = insertRecursive(root->left, key);
    } 
    else 
    {
        root->right = insertRecursive(root->right, key);
    }

    return root;
}

void generateData(int* arr, int size, int seed) 
{
    srand(seed);
    for (int i = 0; i < size; i++) 
    {
        arr[i] = rand() % 100000 + 1;
    }
}

void measurePerformance(int* data, int size) 
{
    Node* rootIterative = NULL;
    Node* rootRecursive = NULL;
    clock_t start, end;

    start = clock();
    for (int i = 0; i < size; i++) 
    {
        rootIterative = insertIterative(rootIterative, data[i]);
    }
    end = clock();
    double iterativeTime = ((double)(end - start)) / CLOCKS_PER_SEC;

    start = clock();
    for (int i = 0; i < size; i++) 
    {
        rootRecursive = insertRecursive(rootRecursive, data[i]);
    }
    end = clock();
    double recursiveTime = ((double)(end - start)) / CLOCKS_PER_SEC;

    printf("Data Size: %d\n", size);
    printf("  Iterative Time: %.6f seconds\n", iterativeTime);
    printf("  Recursive Time: %.6f seconds\n", recursiveTime);
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
