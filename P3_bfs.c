/* Practice 3: BFS traversal + shortest distance (each edge = 2 units). Unreachable => -1 */
#include <stdio.h>
#define MAX 100

int main(void) {
    int n, m, g[MAX][MAX] = {{0}}, s, dist[MAX], vis[MAX] = {0}, q[MAX], f = 0, r = 0;
    scanf("%d %d", &n, &m);
    for (int i = 0; i < m; i++) { int u, v; scanf("%d %d", &u, &v); g[u][v] = g[v][u] = 1; }
    scanf("%d", &s);
    for (int i = 1; i <= n; i++) dist[i] = -1;
    printf("BFS Traversal: ");
    q[r++] = s; vis[s] = 1; dist[s] = 0;
    while (f < r) {
        int u = q[f++]; printf("%d ", u);
        for (int v = 1; v <= n; v++)
            if (g[u][v] && !vis[v]) { vis[v] = 1; dist[v] = dist[u] + 2; q[r++] = v; }
    }
    printf("\nDistance [");
    int first = 1;
    for (int i = 1; i <= n; i++) if (i != s) { printf(first ? "%d" : " %d", dist[i]); first = 0; }
    printf("]\n");
    return 0;
}
