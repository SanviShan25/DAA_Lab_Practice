/* 10.2  Fibonacci-sum counter ("fitstring"), F1=F2=1, F3=2, F4=3 ...
   Keeps the fitstring in the form with NO two adjacent 1s (bit 1 unused).
   INCREMENT : +1 = F2. Flip bit2 (if bit2 already 1: 2 = F3, so clear bit2, set bit3), then repeatedly
               merge adjacent 1s  F_i + F_{i+1} = F_{i+2}  (011 -> 100). Each merge removes one '1',
               so with potential = (#ones) the amortised cost of INCREMENT is O(1).
   DECREMENT : find lowest 1 at k; F_k - 1 = F_{k-1} + F_{k-3} + ... (down to bit 2 or 3).
   NOTE: this simple version has O(1) amortised INCREMENT; the full "inc+dec both O(1) amortised"
   proof uses a lazy / redundant representation (the hint). Check this part with your faculty. */
#include <stdio.h>
#define M 60

int fit[M + 5]; long long F[M + 5]; int cost;

void flip(int i, int v) { fit[i] = v; cost++; }

void increment(void) {
    int i;
    cost = 0;
    if (fit[2]) { flip(2, 0); flip(3, 1); i = 3; } else { flip(2, 1); i = 2; }
    while (fit[i] && fit[i + 1]) { flip(i, 0); flip(i + 1, 0); flip(i + 2, 1); i += 2; }
}
void decrement(void) {
    int k = 2; cost = 0;
    while (k < M && !fit[k]) k++;
    if (k >= M) { printf("Counter already 0\n"); return; }
    flip(k, 0);
    for (int j = k - 1; j >= 2; j -= 2) flip(j, 1);
}
long long value(void) { long long v = 0; for (int i = 2; i < M; i++) if (fit[i]) v += F[i]; return v; }
void show(void) {
    int top = M - 1; while (top > 2 && !fit[top]) top--;
    printf("fitstring: "); for (int i = top; i >= 2; i--) printf("%d", fit[i]);
    printf("  value = %lld  (cost of last op = %d)\n", value(), cost);
}
int main(void) {
    F[1] = F[2] = 1; for (int i = 3; i < M + 5; i++) F[i] = F[i-1] + F[i-2];
    int ch;
    for (;;) {
        printf("\n1. Increment  2. Decrement  3. Exit : "); if (scanf("%d", &ch) != 1 || ch == 3) break;
        if (ch == 1) increment(); else if (ch == 2) decrement();
        show();
    }
    return 0;
}
