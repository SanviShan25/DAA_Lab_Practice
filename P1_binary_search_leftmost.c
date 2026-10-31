/* Practice 1: Binary search returning the LEFTMOST occurrence + number of comparisons */
#include <stdio.h>

int main(void) {
    int n, a[1000], key;
    printf("Enter size of array: "); scanf("%d", &n);
    printf("Enter elements of the array: "); for (int i = 0; i < n; i++) scanf("%d", &a[i]);
    printf("Enter the key to be searched: "); scanf("%d", &key);

    int lo = 0, hi = n - 1, res = -1, cmp = 0;
    while (lo <= hi) {
        int mid = lo + (hi - lo) / 2;
        cmp++;                                   /* one 3-way comparison per iteration */
        if (a[mid] == key)     { res = mid; hi = mid - 1; }   /* keep looking to the left */
        else if (a[mid] < key) lo = mid + 1;
        else                   hi = mid - 1;
    }
    if (res >= 0) printf("%d found at index position %d\n", key, res);
    else          printf("%d not found\n", key);
    printf("Number of comparisons: %d\n", cmp);
    return 0;
}
