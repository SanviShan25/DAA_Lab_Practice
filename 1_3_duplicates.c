/* 1.3  Count duplicate values + most repeating element (data read from file) */
#include <stdio.h>

int main(void) {
    char fn[100]; int n, i, j, a[1000], x;
    printf("Enter file name: "); scanf("%99s", fn);
    printf("Enter how many numbers you want to read from file: "); scanf("%d", &n);
    FILE *fp = fopen(fn, "r");
    if (!fp) { perror("fopen"); return 1; }
    for (i = 0; i < n && fscanf(fp, "%d", &x) == 1; i++) a[i] = x;
    n = i; fclose(fp);

    printf("The content of the array: ");
    for (i = 0; i < n; i++) printf("%d ", a[i]);
    printf("\n");

    int dup = 0, maxc = 0, maxv = a[0];
    for (i = 0; i < n; i++) {
        int seen = 0, c = 1;
        for (j = 0; j < i; j++) if (a[j] == a[i]) { seen = 1; break; }
        if (seen) continue;                       /* value already counted */
        for (j = i + 1; j < n; j++) if (a[j] == a[i]) c++;
        if (c > 1) dup++;                         /* distinct values that repeat */
        if (c > maxc) { maxc = c; maxv = a[i]; }
    }
    printf("Total number of duplicate values = %d\n", dup);
    printf("The most repeating element in the array = %d\n", maxv);
    return 0;
}
