/* 2.3  GCD using recursion.  Usage: ./a.out inGcd.dat outGcd.dat */
#include <stdio.h>

int gcd(int a, int b) { return b == 0 ? a : gcd(b, a % b); }

int main(int argc, char *argv[]) {
    if (argc != 3) { printf("Usage: %s src dest\n", argv[0]); return 1; }
    FILE *in = fopen(argv[1], "r"), *out = fopen(argv[2], "w");
    if (!in || !out) { perror("fopen"); return 1; }
    int a, b;
    while (fscanf(in, "%d %d", &a, &b) == 2)
        fprintf(out, "The GCD of %d and %d is %d\n", a, b, gcd(a, b));
    fclose(in); fclose(out);

    char line[200]; out = fopen(argv[2], "r");
    while (fgets(line, sizeof line, out)) printf("%s", line);
    fclose(out);
    return 0;
}
