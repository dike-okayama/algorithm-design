#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#define N 100
typedef struct man
{
    int name;
    struct woman *partner;
} man;
typedef struct woman
{
    int name;
    struct man *partner;
} woman;

bool existSingle(man **M, int length);
bool preferMeToPartner(woman *w, man *m, man **prefs);

int main()
{
    int n;
    man *M[N], *menPrefs[N][N];
    woman *W[N], *womenPrefs[N][N];
    int proposedRank[N];
    FILE *file;

    file = fopen("input", "r");
    fscanf(file, "%d", &n);
    printf("n = %d\n", n);
    if (n > N)
    {
        printf("Error: n is larger than Max size %d\n", N);
        exit(1);
    }
    // 初期化
    for (int i = 0; i < n; i++)
    {
        man *m;
        woman *w;
        m = (struct man *)malloc(sizeof(man));
        m->name = i;
        m->partner = NULL;
        M[i] = m;
        w = (struct woman *)malloc(sizeof(woman));
        w->name = i;
        w->partner = NULL;
        W[i] = w;
    }

    for (int i = 0; i < n; i++)
    {
        int a[n];
        for (int j = 0; j < n; j++)
        {
            fscanf(file, "%d", &a[j]);
        }
        printf("preference list of m_%d: ", i);
        for (int j = 0; j < n; j++)
        {
            womenPrefs[i][j] = W[a[j]];
            printf("%d ", a[j]);
        }
        printf("\n");
    }
    for (int i = 0; i < n; i++)
    {
        int a[n];
        for (int j = 0; j < n; j++)
        {
            fscanf(file, "%d", &a[j]);
        }
        printf("preference list of w_%d: ", i);
        for (int j = 0; j < n; j++)
        {
            menPrefs[i][j] = M[a[j]];
            printf("%d ", a[j]);
        }
        printf("\n");
    }
    fclose(file);
    printf("----------------------------------------------------------------------\n");
    while (existSingle(M, n))
    {
        for (int i = 0; i < n; i++)
        {
            man *m = M[i];
            woman *w = womenPrefs[i][proposedRank[i]];
            // mは婚約済み
            if (m->partner != NULL)
                continue;
            proposedRank[i]++;

            // wが独身のため婚約
            if (w->partner == NULL)
            {
                w->partner = m;
                m->partner = w;
                continue;
            }

            // 略奪成功
            if (preferMeToPartner(w, m, menPrefs[w->name]))
            {
                w->partner->partner = NULL;
                w->partner = m;
                m->partner = w;
                continue;
            }
        }
    }
    printf("(m, w)\n");
    for (int i = 0; i < n; i++)
    {
        if (M[i]->partner == NULL)
        {
            printf("%d is single\n", M[i]->name);
            continue;
        }
        printf("(%d, %d)\n", M[i]->name, M[i]->partner->name);
    }
    return 0;
}

bool existSingle(man **M, int length)
{
    for (int i = 0; i < length; i++)
    {
        if (M[i]->partner == NULL)
            return true;
    }
    return false;
}

bool preferMeToPartner(woman *w, man *m, man **prefs)
{
    if (w->partner == NULL)
        return true;
    for (int i = 0; i < N; i++)
    {
        if (prefs[i] == m)
            return true;
        if (prefs[i] == w->partner)
            return false;
    }
    return false;
}
