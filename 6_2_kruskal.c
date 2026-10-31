/* 6.2  Kruskal's MST (sort edges + union-find). Input: n m, then m lines  u v w */
#include <stdio.h>
#include <stdlib.h>

typedef struct { int u, v, w; } Edge;
int parent[1000];

int find(int x) { return parent[x] == x ? x : (parent[x] = find(parent[x])); }
int cmpEdge(const void *a, const void *b) { return ((Edge*)a)->w - ((Edge*)b)->w; }

int main(void) {
    int n, m, total = 0, cnt = 0;
    scanf("%d %d", &n, &m);
    Edge *e = malloc(m * sizeof(Edge));
    for (int i = 0; i < m; i++) scanf("%d %d %d", &e[i].u, &e[i].v, &e[i].w);
    qsort(e, m, sizeof(Edge), cmpEdge);
    for (int i = 1; i <= n; i++) parent[i] = i;
    printf("Edge\tCost\n");
    for (int i = 0; i < m && cnt < n - 1; i++) {
        int a = find(e[i].u), b = find(e[i].v);
        if (a != b) {
            parent[a] = b; total += e[i].w; cnt++;
            printf("%d--%d\t%d\n", e[i].u, e[i].v, e[i].w);
        }
    }
    printf("Total Weight of the Spanning Tree: %d\n", total);
    return 0;
}
