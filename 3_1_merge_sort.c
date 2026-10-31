/* 3.1  Menu driven Merge Sort: comparisons + execution time (ns) */
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#define MAX 1000

long long cmp;

void merge(int a[], int l, int m, int r) {
    int n1 = m - l + 1, n2 = r - m, i, j, k;
    int *L = malloc(n1 * sizeof(int)), *R = malloc(n2 * sizeof(int));
    for (i = 0; i < n1; i++) L[i] = a[l + i];
    for (j = 0; j < n2; j++) R[j] = a[m + 1 + j];
    i = j = 0; k = l;
    while (i < n1 && j < n2) {
        cmp++;
        if (L[i] <= R[j]) a[k++] = L[i++]; else a[k++] = R[j++];
    }
    while (i < n1) a[k++] = L[i++];
    while (j < n2) a[k++] = R[j++];
    free(L); free(R);
}
void mergeSort(int a[], int l, int r) {
    if (l < r) {
        int m = (l + r) / 2;
        mergeSort(a, l, m); mergeSort(a, m + 1, r);
        merge(a, l, m, r);
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
    const char *out[] = {"", "outMergeAsce.dat", "outMergeDesc.dat", "outMergeRand.dat"};
    while (1) {
        printf("\nMAIN MENU (MERGE SORT)\n1. Ascending Data\n2. Descending Data\n3. Random Data\n4. ERROR (EXIT)\nEnter option: ");
        if (scanf("%d", &ch) != 1 || ch == 4) break;
        if (ch < 1 || ch > 3) { printf("Invalid option\n"); continue; }
        n = readFile(in[ch], a); if (!n) continue;
        printf("Before Sorting:\n"); show(a, n);
        cmp = 0;
        struct timespec t1, t2;
        clock_gettime(CLOCK_MONOTONIC, &t1);
        mergeSort(a, 0, n - 1);
        clock_gettime(CLOCK_MONOTONIC, &t2);
        long long ns = (t2.tv_sec - t1.tv_sec) * 1000000000LL + (t2.tv_nsec - t1.tv_nsec);
        FILE *fo = fopen(out[ch], "w");
        for (int i = 0; i < n; i++) fprintf(fo, "%d ", a[i]);
        fclose(fo);
        printf("After Sorting (content of %s):\n", out[ch]); show(a, n);
        printf("Number of Comparisons: %lld\n", cmp);
        printf("Execution Time: %lld ns\n", ns);
    }
    return 0;
}
