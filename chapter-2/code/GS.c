#include <stdio.h>
#include <stdlib.h>
#define N 100
struct node
{
    int val;
    struct node *next;
    struct node *prev;
};

struct node *insert(int val, struct node *first);
struct node *delete_head(struct node *first);

int main(int argc, char *argv[])
{
    int n;
    int ManPref[N][N], WomanPref[N][N], Next[N], Current[N], Ranking[N][N];
    struct node *first;
    FILE *file;
    char *file_name;

    /*
    inputの例:
    5
    1 4 5 2 3
    5 1 2 3 4
    1 2 4 3 5
    5 2 1 3 4
    4 2 1 5 3
    4 5 3 1 2
    3 1 4 5 2
    5 3 1 2 4
    2 1 3 5 4
    3 1 2 4 5
    */
    file_name = argc == 1 ? "input" : argv[1];
    file = fopen(file_name, "r");
    fscanf(file, "%d", &n);
    printf("n = %d\n", n);
    if (n > N)
    {
        printf("Error: n is larger than Max size %d\n", N);
        exit(1);
    }

    // 好意順リストを読み込む
    for (int i = 1; i <= n; i++)
    {
        for (int j = 1; j <= n; j++)
        {
            fscanf(file, "%d", &ManPref[i][j]);
        }
    }
    for (int i = 1; i <= n; i++)
    {
        for (int j = 1; j <= n; j++)
        {
            fscanf(file, "%d", &WomanPref[i][j]);
        }
    }

    // Nextを初期化
    for (int i = 1; i <= n; i++)
    {
        Next[i] = 1;
    }

    // Currentを初期化
    for (int i = 1; i <= n; i++)
    {
        // 0はwが自由の身であることを表す
        Current[i] = 0;
    }

    // Rankingを初期化
    for (int i = 1; i <= n; i++)
    {
        for (int j = 1; j <= n; j++)
        {
            Ranking[i][WomanPref[i][j]] = j;
        }
    }

    // 自由の身の男性をリストで管理
    for (int i = 1; i <= n; i++)
    {
        first = insert(i, first);
    }

    while (first != NULL)
    {
        int m = first->val;
        int w = ManPref[m][Next[m]];
        if (Current[w] == 0)
        {
            Current[w] = m;
            first = delete_head(first);
        }
        else if (Ranking[w][m] < Ranking[w][Current[w]])
        {
            first = delete_head(first);
            first = insert(Current[w], first);
            Current[w] = m;
        }

        Next[m]++;
    }

    for (int i = 1; i <= n; i++)
    {
        printf("m_%d w_%d\n", Current[i], i);
    }
}

struct node *insert(int val, struct node *first)
{
    struct node *new_node = (struct node *)malloc(sizeof(struct node));
    new_node->val = val;
    new_node->next = first;
    new_node->prev = NULL;
    if (first != NULL)
        first->prev = new_node;

    return new_node;
}

struct node *delete_head(struct node *first)
{
    if (first == NULL)
        return NULL;

    struct node *temp = first->next;
    free(first);
    if (temp != NULL)
        temp->prev = NULL;

    return temp;
}
