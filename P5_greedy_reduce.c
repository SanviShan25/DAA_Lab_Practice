/* Practice 5: reduce n to 1 using fewest steps (greedy1 and greedy2) */
#include <stdio.h>

int greedy1(long long n) {                /* ops: n-1, n/2 (only if even) */
    int steps = 0; printf("%lld", n);
    while (n > 1) {
        if (n % 2 == 0) n /= 2; else n -= 1;
        printf(" -> %lld", n); steps++;
    }
    printf("\n"); return steps;
}
int twos(long long x) { int c = 0; while (x % 2 == 0) { x /= 2; c++; } return c; }

int greedy2(long long n) {                /* ops: n-1, n+1, n/2 (only if even) */
    int steps = 0; printf("%lld", n);
    while (n > 1) {
        if (n % 2 == 0) n /= 2;
        else if (n == 3) n -= 1;                               /* the single exception */
        else n = (twos(n - 1) > twos(n + 1)) ? n - 1 : n + 1;  /* more factors of 2 wins */
        printf(" -> %lld", n); steps++;
    }
    printf("\n"); return steps;
}
int main(void) {
    long long n; printf("Enter n: "); scanf("%lld", &n);
    printf("greedy1: steps = %d\n", greedy1(n));
    printf("greedy2: steps = %d\n", greedy2(n));
    return 0;
}
