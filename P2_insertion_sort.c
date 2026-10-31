/* Practice 2: Menu driven Insertion Sort, comparisons, best/worst-case scenario */
#include <stdio.h>
#define MAX 1000

int readFile(const char *fn, int a[]) {
    FILE *f = fopen(fn, "r"); int n = 0;
    if (!f) { perror(fn); return 0; }
    while (n < MAX && fscanf(f, "%d", &a[n]) == 1) n++;
    fclose(f); return n;
}
int main(void) {
    int a[MAX], n, ch;
    const char *in[]  = {"", "inAsce.dat", "inDesc.dat", "inRand.dat"};
    const char *out[] = {"", "outInsAsce.dat", "outInsDesc.dat", "outInsRand.dat"};
    for (;;) {
        printf("\nMAIN MENU (INSERTION SORT)\n1. Ascending Data\n2. Descending Data\n3. Random Data\n4. ERROR (EXIT)\nEnter option: ");
        if (scanf("%d", &ch) != 1 || ch == 4) break;
        if (ch < 1 || ch > 3) { printf("Invalid option\n"); continue; }
        n = readFile(in[ch], a); if (!n) continue;
        printf("Before Sorting:\n"); for (int i = 0; i < n; i++) printf("%d ", a[i]);
        long long cmp = 0;
        for (int i = 1; i < n; i++) {
            int key = a[i], j = i - 1;
            while (j >= 0) {
                cmp++;
                if (a[j] > key) { a[j + 1] = a[j]; j--; } else break;
            }
            a[j + 1] = key;
        }
        FILE *fo = fopen(out[ch], "w"); for (int i = 0; i < n; i++) fprintf(fo, "%d ", a[i]); fclose(fo);
        printf("\nAfter Sorting (content of %s):\n", out[ch]); for (int i = 0; i < n; i++) printf("%d ", a[i]);
        printf("\nNumber of Comparisons: %lld\n", cmp);
        long long nn = n;
        printf("Scenario: %s\n", cmp == nn - 1 ? "Best-case (n-1 comparisons)"
                              : cmp == nn * (nn - 1) / 2 ? "Worst-case (n(n-1)/2 comparisons)" : "Average-case");
    }
    return 0;
}
