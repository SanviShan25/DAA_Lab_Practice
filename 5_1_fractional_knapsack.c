/* 5.1  Fractional knapsack; items sorted by profit/weight (non-increasing) using heap sort */
#include <stdio.h>

typedef struct { int item_id; double item_profit, item_weight, profit_weight_ratio; } ITEM;

void swp(ITEM *a, ITEM *b) { ITEM t = *a; *a = *b; *b = t; }

/* min-heapify on ratio: repeatedly moving the min to the end gives NON-INCREASING order */
void minHeapify(ITEM a[], int n, int i) {
    for (;;) {
        int l = 2*i+1, r = l+1, s = i;
        if (l < n && a[l].profit_weight_ratio < a[s].profit_weight_ratio) s = l;
        if (r < n && a[r].profit_weight_ratio < a[s].profit_weight_ratio) s = r;
        if (s == i) break;
        swp(&a[i], &a[s]); i = s;
    }
}
void heapSort(ITEM a[], int n) {
    for (int i = n/2 - 1; i >= 0; i--) minHeapify(a, n, i);
    for (int i = n - 1; i > 0; i--) { swp(&a[0], &a[i]); minHeapify(a, i, 0); }
}

int main(void) {
    int n; ITEM it[100]; double cap, profit = 0, frac[100];
    printf("Enter the number of items: "); scanf("%d", &n);
    for (int i = 0; i < n; i++) {
        it[i].item_id = i + 1;
        printf("Enter the profit and weight of item no %d: ", i + 1);
        scanf("%lf %lf", &it[i].item_profit, &it[i].item_weight);
        it[i].profit_weight_ratio = it[i].item_profit / it[i].item_weight;
    }
    printf("Enter the capacity of knapsack: "); scanf("%lf", &cap);
    heapSort(it, n);
    double rem = cap;
    for (int i = 0; i < n; i++) {
        if (rem >= it[i].item_weight) { frac[i] = 1.0; rem -= it[i].item_weight; profit += it[i].item_profit; }
        else { frac[i] = rem / it[i].item_weight; profit += it[i].item_profit * frac[i]; rem = 0; }
    }
    printf("Item No profit Weight Amount to be taken\n");
    for (int i = 0; i < n; i++)
        printf("%d %f %f %f\n", it[i].item_id, it[i].item_profit, it[i].item_weight, frac[i]);
    printf("Maximum profit: %f\n", profit);
    return 0;
}
