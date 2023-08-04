#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#define MAX 100
#define MIN 2

void shuffle(int *arr, int n);
bool fileExists(const char *filename);

int main()
{
    int n;
    bool isValidInput;

    do
    {
        printf("人数(ペアの数)を入力してください(2 <= n <= 100): ");
        isValidInput = scanf("%d", &n) == 1 && (n >= MIN && n <= MAX);

        if (!isValidInput)
        {
            printf("入力が不正です\n");
            // エラーハンドリング: 入力バッファをクリアする
            int c;
            while ((c = getchar()) != '\n' && c != EOF)
            {
            };
        }
        else
        {
            printf("男女%dずつ人の好意順リストを作成します\n", n);
        }
    } while (!isValidInput);

    char *fileName;
    const char *prefix = "input";
    int suffixNum = 0;
    do
    {
        sprintf(fileName, "%s_%d", prefix, suffixNum);
        suffixNum++;
    } while (fileExists(fileName));

    int pref_list[2 * n][n];
    for (int i = 0; i < 2 * n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            pref_list[i][j] = j;
        }
        shuffle(pref_list[i], n);
    }

    printf("-----------------------------------------------------\n");
    printf("%d\n", n);
    for (int i = 0; i < 2 * n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            printf("%d ", pref_list[i][j]);
        }
        printf("\n");
    }
    printf("-----------------------------------------------------\n");

    FILE *file = fopen(fileName, "w");

    if (file == NULL)
    {
        printf("ファイルのオープンに失敗しました\n");
        return 1; // 異常終了
    }

    fprintf(file, "%d\n", n);
    for (int i = 0; i < 2 * n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            fprintf(file, "%d ", pref_list[i][j]);
        }
        fprintf(file, "\n");
    }

    printf("%sに書き込みました\n", fileName);

    // ファイルを閉じる
    fclose(file);

    return 0;
}

void shuffle(int *arr, int n)
{
    for (int i = n - 1; i > 0; i--)
    {
        // ランダムなインデックスを生成
        int j = rand() % (i + 1);

        // ランダムに入れ替える
        int temp = arr[i];
        arr[i] = arr[j];
        arr[j] = temp;
    }
}

bool fileExists(const char *filename)
{
    FILE *file = fopen(filename, "r");
    if (file)
    {
        fclose(file);
        return true;
    }
    return false;
}
