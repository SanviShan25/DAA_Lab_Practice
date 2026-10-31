/* 1.1  Second smallest and second largest element (read n numbers from a disc file) */
#include <stdio.h>
#include <limits.h>

int main(void) {
    char fn[100]; int n, x, i;
    printf("Enter file name: "); scanf("%99s", fn);
    printf("Enter n: ");         scanf("%d", &n);
    FILE *fp = fopen(fn, "r");
    if (!fp) { perror("fopen"); return 1; }

    int s1 = INT_MAX, s2 = INT_MAX, l1 = INT_MIN, l2 = INT_MIN;
    for (i = 0; i < n && fscanf(fp, "%d", &x) == 1; i++) {   /* single pass, O(n) */
        if (x < s1)                { s2 = s1; s1 = x; }
        else if (x < s2 && x != s1) s2 = x;
        if (x > l1)                { l2 = l1; l1 = x; }
        else if (x > l2 && x != l1) l2 = x;
    }
    fclose(fp);
    if (s2 == INT_MAX || l2 == INT_MIN) printf("Not enough distinct elements\n");
    else printf("Second smallest = %d\nSecond largest  = %d\n", s2, l2);
    return 0;
}
