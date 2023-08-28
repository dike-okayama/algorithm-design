#include <stdio.h>
#include <stdlib.h>
#define N 100

void insert(int *H, int v, int *n);
int findMin(int *H);
void delete(int *H, int i, int *n);
int extractMin(int *H, int *n);
void heapifyUp(int *H, int i, int n);
void heapifyDown(int *H, int i, int n);
void swap(int *H, int i, int j);
void printBinaryTree(int tree[], int size, int index, int level);

int main()
{
    int A[N], H[N];
    int n, m;
    FILE *file;

    /*
    listdataの例:
    14
    17
    3
    15
    3
    1
    8
    16
    7
    11
    20
    2
    9
    10
    15
    */
    file = fopen("listdata", "r");
    fscanf(file, "%d", &n);
    if (n > N)
    {
        printf("Illegal array size n = %d for N = %d\n", n, N);
        exit(1);
    }
    for (int i = 0; i < n; i++)
        fscanf(file, "%d", &A[i]);
    fclose(file);

    printf("A: ");
    for (int i = 0; i < n; i++)
        printf("%d ", A[i]);
    printf("\n");

    m = 0;
    for (int i = 0; i < n; i++)
    {
        insert(H, A[i], &m);
    }

    printf("H: ");
    for (int i = 0; i < m; i++)
        printf("%d ", H[i]);
    printf("\n");

    printf("Binary Tree Representation:\n");
    printf("\n");
    printBinaryTree(H, m, 0, 0);
    printf("\n");

    printf("sorted: ");
    while (m > 0)
    {
        printf("%d ", extractMin(H, &m));
    }
    printf("\n");

    return 0;
}

void insert(int *H, int v, int *n)
{
    int n1;
    n1 = *n;
    if (n1 >= N)
    {
        printf("Error: Heap A is full.\n");
        exit(1);
    }
    H[n1] = v;
    heapifyUp(H, n1, n1 + 1);
    *n = n1 + 1;
    return;
}

int findMin(int *H)
{
    return H[0];
}

void delete(int *H, int i, int *n)
{
    int n1, j, k;
    n1 = *n;
    if (n1 < 1)
    {
        printf("Error: Heap is empty.\n");
        exit(1);
    }
    H[i] = H[n1 - 1];
    H[n1 - 1] = 0;
    j = (i + 1) / 2 - 1;
    k = 2 * i + 1;
    if (j >= 0 && H[j] > H[i])
    {
        heapifyUp(H, i, n1 - 1);
    }
    else if (k < n1 - 1 && H[k] < H[i])
        heapifyDown(H, 0, n1 - 1);
    *n = n1 - 1;
    return;
}

void heapifyUp(int *H, int i, int n)
{
    int j;
    j = (i + 1) / 2 - 1;
    if (i < 0 || i >= n)
    {
        printf("Illegal element i=%d for n=%d\n", i, n);
        exit(1);
    }
    if (j < 0)
    {
        return;
    }
    if (H[j] > H[i])
    {
        swap(H, i, j);
        heapifyUp(H, j, n);
    }
    return;
}

int extractMin(int *H, int *n)
{
    int min;
    min = findMin(H);
    delete (H, 0, n);
    return min;
}

void swap(int *H, int i, int j)
{
    int temp;
    temp = H[i];
    H[i] = H[j];
    H[j] = temp;
    return;
}

void heapifyDown(int *H, int i, int n)
{
    int j;
    j = 2 * i + 1;
    if (j >= n)
        return;
    if (j + 1 < n && H[j] > H[j + 1])
        j = j + 1;
    if (H[j] < H[i])
    {
        swap(H, i, j);
        heapifyDown(H, j, n);
    }
    return;
}

void printBinaryTree(int tree[], int size, int index, int level)
{
    if (index >= size)
    {
        return;
    }

    printBinaryTree(tree, size, 2 * index + 2, level + 1);

    for (int i = 0; i < level; i++)
    {
        printf("\t");
    }
    printf("%d\n", tree[index]);

    printBinaryTree(tree, size, 2 * index + 1, level + 1);
}
