/* 8.1  Matrix chain multiplication with M-table and S-table */
#include <stdio.h>
#include <limits.h>
#define MAX 20

int m[MAX][MAX], s[MAX][MAX], p[MAX];

void printOpt(int i, int j) {
    if (i == j) { printf("A%d", i); return; }
    printf("("); printOpt(i, s[i][j]); printf(" "); printOpt(s[i][j] + 1, j); printf(")");
}

int main(void) {
    int n, r, c, prevc = -1;
    printf("Enter number of matrices: "); scanf("%d", &n);
    for (int i = 1; i <= n; i++) {
        printf("Enter row and col size of A%d: ", i); scanf("%d %d", &r, &c);
        if (i > 1 && prevc != r) { printf("Dimension mismatch: A%d cols (%d) != A%d rows (%d)\n", i-1, prevc, i, r); return 1; }
        if (i == 1) p[0] = r;
        p[i] = c; prevc = c;
    }
    for (int len = 2; len <= n; len++)
        for (int i = 1; i <= n - len + 1; i++) {
            int j = i + len - 1; m[i][j] = INT_MAX;
            for (int k = i; k < j; k++) {
                int q = m[i][k] + m[k+1][j] + p[i-1] * p[k] * p[j];
                if (q < m[i][j]) { m[i][j] = q; s[i][j] = k; }
            }
        }
    printf("M Table:\n");
    for (int i = 1; i <= n; i++) { for (int j = 1; j <= n; j++) printf("%d\t", m[i][j]); printf("\n"); }
    printf("S Table:\n");
    for (int i = 1; i <= n; i++) { for (int j = 1; j <= n; j++) printf("%d\t", s[i][j]); printf("\n"); }
    printf("Optimal parenthesization: "); printOpt(1, n); printf("\n");
    printf("The optimal ordering of the given matrices requires %d scalar multiplications.\n", m[1][n]);
    return 0;
}
