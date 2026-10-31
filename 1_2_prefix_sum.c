/* 1.2  Prefix sum array */
#include <stdio.h>

int main(void) {
    int n, i, a[1000], p[1000];
    printf("Enter n: "); scanf("%d", &n);
    printf("Enter %d elements: ", n);
    for (i = 0; i < n; i++) scanf("%d", &a[i]);
    p[0] = a[0];
    for (i = 1; i < n; i++) p[i] = p[i-1] + a[i];
    printf("Prefix sum: ");
    for (i = 0; i < n; i++) printf("%d ", p[i]);
    printf("\n");
    return 0;
}
