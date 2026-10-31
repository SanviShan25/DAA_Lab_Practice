/* 10.3  Binary counter with INCREMENT and RESET in O(n) total for n operations.
   Keep 'high' = index of the highest 1. INCREMENT works as usual (and updates high).
   RESET only clears bits 0..high (cost high+1 <= number of bits ever set).
   Aggregate: every bit set by an INCREMENT is cleared at most once (by carry or by RESET),
   so total cost <= 2 * (#INCREMENTs) = O(n). */
#include <stdio.h>
#define K 16

int A[K], high = -1; long long total = 0;

int increment(void) {
    int i = 0, cost = 0;
    while (i < K && A[i] == 1) { A[i] = 0; cost++; i++; }
    if (i < K) { A[i] = 1; cost++; if (i > high) high = i; } else high = -1;
    return cost;
}
int reset(void) {
    int cost = 0;
    for (int i = 0; i <= high; i++) { A[i] = 0; cost++; }
    high = -1; return cost;
}
void show(void) { for (int i = 4; i >= 0; i--) printf("%d ", A[i]); }

int main(void) {
    int ch, c;
    printf("Bit4 Bit3 Bit2 Bit1 Bit0  Operation  Cost(total)\n");
    for (;;) {
        printf("\n1. Increment  2. Reset  3. Exit : "); if (scanf("%d", &ch) != 1 || ch == 3) break;
        c = (ch == 1) ? increment() : reset();
        total += c; show(); printf(" %s  cost=%d  total=%lld\n", ch == 1 ? "Increment" : "Reset", c, total);
    }
    return 0;
}
