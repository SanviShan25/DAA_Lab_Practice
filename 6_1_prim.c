/* 6.1  Prim's MST with a min-priority queue (array based extract-min).
   Reads cost adjacency matrix from inUnAdjMat.dat */
#include <stdio.h>
#define MAX 50
#define INF 1000000000

int main(void) {
    int n, s, g[MAX][MAX], T[MAX][MAX] = {{0}}, key[MAX], par[MAX], inQ[MAX], total = 0;
    printf("Enter the Number of Vertices: "); scanf("%d", &n);
    printf("Enter the Starting Vertex: ");    scanf("%d", &s); s--;
    FILE *f = fopen("inUnAdjMat.dat", "r");
    if (!f) { perror("inUnAdjMat.dat"); return 1; }
    for (int i = 0; i < n; i++) for (int j = 0; j < n; j++) fscanf(f, "%d", &g[i][j]);
    fclose(f);

    for (int i = 0; i < n; i++) { key[i] = INF; par[i] = -1; inQ[i] = 1; }
    key[s] = 0;
    for (int c = 0; c < n; c++) {
        int u = -1;                                       /* EXTRACT-MIN from Q */
        for (int v = 0; v < n; v++) if (inQ[v] && (u == -1 || key[v] <= key[u])) u = v;
        if (key[u] == INF) break;                         /* graph not connected */
        inQ[u] = 0;
        if (par[u] != -1) { T[u][par[u]] = T[par[u]][u] = g[u][par[u]]; total += g[u][par[u]]; }
        for (int v = 0; v < n; v++)                       /* DECREASE-KEY */
            if (g[u][v] && inQ[v] && g[u][v] < key[v]) { key[v] = g[u][v]; par[v] = u; }
    }
    for (int i = 0; i < n; i++) { for (int j = 0; j < n; j++) printf("%d ", T[i][j]); printf("\n"); }
    printf("Total Weight of the Spanning Tree: %d\n", total);
    return 0;
}
