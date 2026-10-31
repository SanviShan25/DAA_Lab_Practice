/* 5.2  Huffman tree using a Min-Priority Queue keyed on frequency */
#include <stdio.h>
#include <stdlib.h>

typedef struct { char alphabet; int frequency; } SYMBOL;
typedef struct Node { SYMBOL s; struct Node *l, *r; } Node;

Node *pq[256]; int pqn = 0;

void push(Node *x) {
    int i = pqn++; pq[i] = x;
    while (i > 0 && pq[(i-1)/2]->s.frequency > pq[i]->s.frequency) {
        Node *t = pq[i]; pq[i] = pq[(i-1)/2]; pq[(i-1)/2] = t; i = (i-1)/2;
    }
}
Node *pop(void) {                                    /* EXTRACT-MIN */
    Node *top = pq[0]; pq[0] = pq[--pqn]; int i = 0;
    for (;;) {
        int l = 2*i+1, r = l+1, s = i;
        if (l < pqn && pq[l]->s.frequency < pq[s]->s.frequency) s = l;
        if (r < pqn && pq[r]->s.frequency < pq[s]->s.frequency) s = r;
        if (s == i) break;
        Node *t = pq[i]; pq[i] = pq[s]; pq[s] = t; i = s;
    }
    return top;
}
void inorder(Node *t) {                              /* prints only leaf symbols */
    if (!t) return;
    inorder(t->l);
    if (!t->l && !t->r) printf("%c ", t->s.alphabet);
    inorder(t->r);
}
void codes(Node *t, char *buf, int d) {
    if (!t) return;
    if (!t->l && !t->r) { buf[d] = 0; printf("%c : %s\n", t->s.alphabet, d ? buf : "0"); return; }
    buf[d] = '0'; codes(t->l, buf, d + 1);
    buf[d] = '1'; codes(t->r, buf, d + 1);
}

int main(void) {
    int n; SYMBOL sym[100];
    printf("Enter the number of distinct alphabets: "); scanf("%d", &n);
    printf("Enter the alphabets: ");
    for (int i = 0; i < n; i++) scanf(" %c", &sym[i].alphabet);
    printf("Enter its frequencies: ");
    for (int i = 0; i < n; i++) scanf("%d", &sym[i].frequency);

    for (int i = 0; i < n; i++) {
        Node *x = calloc(1, sizeof(Node)); x->s = sym[i]; push(x);
    }
    for (int i = 0; i < n - 1; i++) {
        Node *x = pop(), *y = pop();
        Node *z = calloc(1, sizeof(Node));
        z->l = x; z->r = y; z->s.frequency = x->s.frequency + y->s.frequency; z->s.alphabet = '*';
        push(z);
    }
    Node *root = pop();
    printf("In-order traversal of the tree (Huffman): "); inorder(root); printf("\n");
    char buf[100]; printf("Huffman codes:\n"); codes(root, buf, 0);
    return 0;
}
