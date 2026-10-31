/* 3.2  Menu driven Quick Sort: comparisons + best/worst case partitioning */
#include <stdio.h>
#include <stdlib.h>
#define MAX 1000

long long cmp; int unbalanced, total;   /* partition statistics (sub-arrays of size >= 3) */

void swap(int *a, int *b) { int t = *a; *a = *b; *b = t; }

int partition(int a[], int lo, int hi) {          /* Lomuto, pivot = last element */
    int pivot = a[hi], i = lo - 1;
    for (int j = lo; j < hi; j++) {
        cmp++;
        if (a[j] <= pivot) { i++; swap(&a[i], &a[j]); }
    }
    swap(&a[i + 1], &a[hi]);
    return i + 1;
}
void quickSort(int a[], int lo, int hi) {
    if (lo < hi) {
        int p = partition(a, lo, hi);
        int left = p - lo, right = hi - p, size = hi - lo + 1;
        if (size >= 3) {
            total++;
            if (left == 0 || right == 0) unbalanced++;   /* n-1 and 0 split => worst */
        }
        quickSort(a, lo, p - 1);
        quickSort(a, p + 1, hi);
    }
}
int readFile(const char *fn, int a[]) {
    FILE *f = fopen(fn, "r"); int n = 0;
    if (!f) { perror(fn); return 0; }
    while (n < MAX && fscanf(f, "%d", &a[n]) == 1) n++;
    fclose(f); return n;
}
void show(int a[], int n) { for (int i = 0; i < n; i++) printf("%d ", a[i]); printf("\n"); }

int main(void) {
    int a[MAX], n, ch;
    const char *in[]  = {"", "inAsce.dat", "inDesc.dat", "inRand.dat"};
    const char *out[] = {"", "outQuickAsce.dat", "outQuickDesc.dat", "outQuickRand.dat"};
    while (1) {
        printf("\nMAIN MENU (QUICK SORT)\n1. Ascending Data\n2. Descending Data\n3. Random Data\n4. ERROR (EXIT)\nEnter option: ");
        if (scanf("%d", &ch) != 1 || ch == 4) break;
        if (ch < 1 || ch > 3) { printf("Invalid option\n"); continue; }
        n = readFile(in[ch], a); if (!n) continue;
        printf("Before Sorting:\n"); show(a, n);
        cmp = unbalanced = total = 0;
        quickSort(a, 0, n - 1);
        FILE *fo = fopen(out[ch], "w");
        for (int i = 0; i < n; i++) fprintf(fo, "%d ", a[i]);
        fclose(fo);
        printf("After Sorting (content of %s):\n", out[ch]); show(a, n);
        printf("Number of Comparisons: %lld\n", cmp);
        printf("Scenario: %s\n", (total > 0 && unbalanced == total) ? "Worst-case (n-1 : 0 splits)"
                                                                      : "Best/Average-case (balanced splits)");
    }
    return 0;
}
