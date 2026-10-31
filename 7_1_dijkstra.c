/* 7.1  Dijkstra single source shortest paths (directed). Reads matrix from inDiAdjMat1.dat; 0 = no edge */
#include <stdio.h>
#define MAX 50
#define INF 1000000000

int par[MAX];
void printPath(int s, int v) {
    if (v == s) { printf("%d", s + 1); return; }
    printPath(s, par[v]); printf("->%d", v + 1);
}

int main(void) {
    int n, s, g[MAX][MAX], dist[MAX], done[MAX] = {0};
    printf("Enter the Number of Vertices: "); scanf("%d", &n);
    printf("Enter the Source Vertex: ");      scanf("%d", &s); s--;
    FILE *f = fopen("inDiAdjMat1.dat", "r");
    if (!f) { perror("inDiAdjMat1.dat"); return 1; }
    for (int i = 0; i < n; i++) for (int j = 0; j < n; j++) fscanf(f, "%d", &g[i][j]);
    fclose(f);

    for (int i = 0; i < n; i++) { dist[i] = INF; par[i] = -1; }
    dist[s] = 0;
    for (int c = 0; c < n; c++) {
        int u = -1;
        for (int v = 0; v < n; v++) if (!done[v] && (u == -1 || dist[v] < dist[u])) u = v;
        if (dist[u] == INF) break;
        done[u] = 1;
        for (int v = 0; v < n; v++)                       /* RELAX(u,v) */
            if (g[u][v] && !done[v] && dist[u] + g[u][v] < dist[v]) { dist[v] = dist[u] + g[u][v]; par[v] = u; }
    }
    printf("Source\tDestination\tCost\tPath\n");
    for (int v = 0; v < n; v++) {
        printf("%d\t%d\t\t", s + 1, v + 1);
        if (dist[v] == INF) { printf("INF\tNo path\n"); continue; }
        printf("%d\t", dist[v]);
        if (v == s) printf("-"); else printPath(s, v);
        printf("\n");
    }
    return 0;
}
