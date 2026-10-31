/* 2.1  First n decimal numbers of a file -> 16-bit binary using recursion
   Usage: ./a.out n inDec.dat outBin.dat */
#include <stdio.h>
#include <stdlib.h>

void toBin(int n, int pos, char *s) {         /* fills s[pos]..s[0] recursively */
    if (pos < 0) return;
    s[pos] = (n % 2) + '0';
    toBin(n / 2, pos - 1, s);
}

int main(int argc, char *argv[]) {
    if (argc != 4) { printf("Usage: %s n srcfile destfile\n", argv[0]); return 1; }
    int n = atoi(argv[1]), x, cnt = 0; char s[17]; s[16] = '\0';
    FILE *in = fopen(argv[2], "r"), *out = fopen(argv[3], "w");
    if (!in || !out) { perror("fopen"); return 1; }
    while (cnt < n && fscanf(in, "%d", &x) == 1) {
        toBin(x, 15, s);
        fprintf(out, "The binary equivalent of %d is %s\n", x, s);
        cnt++;
    }
    fclose(in); fclose(out);

    char line[200];
    out = fopen(argv[3], "r");
    while (fgets(line, sizeof line, out)) printf("%s", line);
    fclose(out);
    return 0;
}
