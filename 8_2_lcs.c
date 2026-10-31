/* 8.2  Longest Common Subsequence */
#include <stdio.h>
#include <string.h>
#define MAX 101

int main(void) {
    char X[MAX], Y[MAX], L[MAX]; int c[MAX][MAX] = {{0}};
    printf("Enter the first string into an array: ");  scanf("%100s", X);
    printf("Enter the second string into an array: "); scanf("%100s", Y);
    int m = strlen(X), n = strlen(Y);
    for (int i = 1; i <= m; i++)
        for (int j = 1; j <= n; j++)
            if (X[i-1] == Y[j-1]) c[i][j] = c[i-1][j-1] + 1;
            else c[i][j] = c[i-1][j] >= c[i][j-1] ? c[i-1][j] : c[i][j-1];
    int len = c[m][n], k = len, i = m, j = n;
    L[len] = '\0';
    while (i > 0 && j > 0) {
        if (X[i-1] == Y[j-1]) { L[--k] = X[i-1]; i--; j--; }
        else if (c[i-1][j] >= c[i][j-1]) i--;
        else j--;
    }
    printf("LCS: %s\nLCS Length: %d\n", L, len);
    return 0;
}
