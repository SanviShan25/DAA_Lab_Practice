/* Practice 4: One-way-connected check: for every pair (u,v): u reaches v OR v reaches u.
   Method: transitive closure (Warshall) then test all pairs.  Time O(V^3), space O(V^2).
   (Faster, O(V+E): find SCCs, build condensation DAG, topologically sort; graph is one-way
    connected iff every consecutive pair in the topological order is joined by an edge.) */
#include <stdio.h>
#define MAX 100

int main(void) {
    int n, R[MAX][MAX];
    printf("Enter number of vertices: "); scanf("%d", &n);
    printf("Enter adjacency matrix (%d x %d):\n", n, n);
    for (int i = 0; i < n; i++) for (int j = 0; j < n; j++) { scanf("%d", &R[i][j]); if (R[i][j]) R[i][j] = 1; }
    for (int i = 0; i < n; i++) R[i][i] = 1;
    for (int k = 0; k < n; k++)
        for (int i = 0; i < n; i++)
            for (int j = 0; j < n; j++)
                R[i][j] = R[i][j] || (R[i][k] && R[k][j]);
    for (int i = 0; i < n; i++)
        for (int j = i + 1; j < n; j++)
            if (!R[i][j] && !R[j][i]) {
                printf("The given graph is NOT one way connected (no path between %d and %d)\n", i + 1, j + 1);
                return 0;
            }
    printf("The given graph is one way connected\n");
    return 0;
}
