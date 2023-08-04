#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#define N 100
typedef struct man_t
{
    int name;
    struct woman_t *partner;
} man_t;
typedef struct woman_t
{
    int name;
    struct man_t *partner;
} woman_t;

bool existSingle(man_t **M, int length);
bool preferMeToPartner(woman_t *w, man_t *m, man_t **prefs);

int main()
{
    int n;
    man_t *M[N], *menPrefs[N][N];
    woman_t *W[N], *womenPrefs[N][N];
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
        man_t *m;
        woman_t *w;
        m = (struct man_t *)malloc(sizeof(man_t));
        m->name = i;
        m->partner = NULL;
        M[i] = m;
        w = (struct woman_t *)malloc(sizeof(woman_t));
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
            man_t *m = M[i];
            woman_t *w = womenPrefs[i][proposedRank[i]];
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

bool existSingle(man_t **M, int length)
{
    for (int i = 0; i < length; i++)
    {
        if (M[i]->partner == NULL)
            return true;
    }
    return false;
}

bool preferMeToPartner(woman_t *w, man_t *m, man_t **prefs)
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
