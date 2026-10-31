/* 10.1  Randomized Quick Sort
   Expected time: O(n log n) for EVERY input. The pivot is uniformly random, so each element is equally
   likely to be the pivot. Any two elements z_i<z_j are compared at most once, and exactly when one of
   them is the first pivot chosen from {z_i..z_j}, probability 2/(j-i+1).
   E[comparisons] = sum_{i<j} 2/(j-i+1) = O(n log n).  Worst case O(n^2) is possible but has
   probability ~ 1/n! style tiny; no particular input can force it (unlike pivot = last element). */
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

long long cmp;
void swap(int *a, int *b) { int t = *a; *a = *b; *b = t; }

int randPartition(int a[], int lo, int hi) {
    int r = lo + rand() % (hi - lo + 1);
    swap(&a[r], &a[hi]);                         /* random pivot moved to end */
    int pivot = a[hi], i = lo - 1;
    for (int j = lo; j < hi; j++) { cmp++; if (a[j] <= pivot) swap(&a[++i], &a[j]); }
    swap(&a[i + 1], &a[hi]);
    return i + 1;
}
void rquick(int a[], int lo, int hi) {
    if (lo < hi) { int p = randPartition(a, lo, hi); rquick(a, lo, p - 1); rquick(a, p + 1, hi); }
}
int main(void) {
    int n, a[10000];
    srand((unsigned)time(NULL));
    printf("Enter n: "); scanf("%d", &n);
    printf("Enter %d elements: ", n);
    for (int i = 0; i < n; i++) scanf("%d", &a[i]);
    rquick(a, 0, n - 1);
    printf("Sorted: "); for (int i = 0; i < n; i++) printf("%d ", a[i]);
    printf("\nComparisons: %lld (expected ~ 2 n ln n = %.0f)\n", cmp, 2.0 * n * __builtin_log(n > 1 ? n : 2));
    return 0;
}
