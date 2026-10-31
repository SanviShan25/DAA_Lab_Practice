/* 1.4  ROTATE_RIGHT(p1,p2) using EXCHANGE(p,q) */
#include <stdio.h>

void EXCHANGE(int *p, int *q) { int t = *p; *p = *q; *q = t; }

/* rotate first p2 elements of array starting at p1 right by 1 position */
void ROTATE_RIGHT(int *p1, int p2) {
    for (int i = p2 - 1; i > 0; i--)
        EXCHANGE(&p1[i], &p1[i-1]);
}

int main(void) {
    int n, i, A[100];
    printf("Enter an array A of size N: "); scanf("%d", &n);
    for (i = 0; i < n; i++) scanf("%d", &A[i]);
    printf("Before ROTATE: "); for (i = 0; i < n; i++) printf("%d ", A[i]);
    ROTATE_RIGHT(A, 5);
    printf("\nAfter ROTATE:  "); for (i = 0; i < n; i++) printf("%d ", A[i]);
    printf("\n");
    return 0;
}
