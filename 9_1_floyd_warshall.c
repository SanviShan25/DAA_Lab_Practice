/* 9.1  Floyd-Warshall all-pairs shortest paths. Reads matrix from inDiAdjMat2.dat (0 off-diagonal = no edge) */
#include <stdio.h>
#define MAX 30
#define INF 1000000000

int main(void) {
    int n, d[MAX][MAX], nxt[MAX][MAX], w, u, v;
    printf("Number of Vertices: "); scanf("%d", &n);
    FILE *f = fopen("inDiAdjMat2.dat", "r");
    if (!f) { perror("inDiAdjMat2.dat"); return 1; }
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++) {
            fscanf(f, "%d", &w);
            if (i == j)      { d[i][j] = 0;   nxt[i][j] = i; }
            else if (w == 0) { d[i][j] = INF; nxt[i][j] = -1; }
            else             { d[i][j] = w;   nxt[i][j] = j; }
        }
    fclose(f);
    for (int k = 0; k < n; k++)
        for (int i = 0; i < n; i++)
            for (int j = 0; j < n; j++)
                if (d[i][k] != INF && d[k][j] != INF && d[i][k] + d[k][j] < d[i][j]) {
                    d[i][j] = d[i][k] + d[k][j];
                    nxt[i][j] = nxt[i][k];
                }
    for (int i = 0; i < n; i++) {
        if (d[i][i] < 0) { printf("Negative weight cycle detected\n"); return 1; }
    }
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) { if (d[i][j] == INF) printf("INF\t"); else printf("%d\t", d[i][j]); }
        printf("\n");
    }
    printf("Enter the source and destination vertex: "); scanf("%d %d", &u, &v); u--; v--;
    if (d[u][v] == INF) { printf("No path\n"); return 0; }
    printf("Shortest Path from vertex %d to vertex %d: %d", u + 1, v + 1, u + 1);
    for (int x = u; x != v; ) { x = nxt[x][v]; printf("-->%d", x + 1); }
    printf("\nPath weight: %d\n", d[u][v]);
    return 0;
}
