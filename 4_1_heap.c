/* 4.1  Min-heap (age) / Max-heap (weight) on dynamically allocated struct person
   Input file line format:  id  full name  age  height  weight      e.g.  0 Adarsh Hota 39 77 231 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct person { int id; char *name; int age, height, weight; } Person;

Person *data, *minh, *maxh; int n, minN, maxN, minCap;

void swp(Person *a, Person *b) { Person t = *a; *a = *b; *b = t; }

void minDown(Person h[], int sz, int i) {
    for (;;) {
        int l = 2*i+1, r = l+1, s = i;
        if (l < sz && h[l].age < h[s].age) s = l;
        if (r < sz && h[r].age < h[s].age) s = r;
        if (s == i) break;
        swp(&h[i], &h[s]); i = s;
    }
}
void minUp(Person h[], int i) {
    while (i > 0 && h[(i-1)/2].age > h[i].age) { swp(&h[i], &h[(i-1)/2]); i = (i-1)/2; }
}
void maxDown(Person h[], int sz, int i) {
    for (;;) {
        int l = 2*i+1, r = l+1, s = i;
        if (l < sz && h[l].weight > h[s].weight) s = l;
        if (r < sz && h[r].weight > h[s].weight) s = r;
        if (s == i) break;
        swp(&h[i], &h[s]); i = s;
    }
}
void show(Person p[], int sz) {
    printf("%-4s %-20s %-4s %-7s %s\n", "Id", "Name", "Age", "Height", "Weight(pound)");
    for (int i = 0; i < sz; i++)
        printf("%-4d %-20s %-4d %-7d %d\n", p[i].id, p[i].name, p[i].age, p[i].height, p[i].weight);
}
int readData(const char *fn) {
    FILE *f = fopen(fn, "r"); char line[256]; int cap = 16;
    if (!f) { perror(fn); return 0; }
    data = malloc(cap * sizeof(Person)); n = 0;
    while (fgets(line, sizeof line, f)) {
        int id, off; char *rest, *p;
        if (sscanf(line, "%d %n", &id, &off) < 1) continue;
        rest = line + off; rest[strcspn(rest, "\r\n")] = 0;
        p = strrchr(rest, ' '); if (!p) continue; int w = atoi(p+1); *p = 0;
        p = strrchr(rest, ' '); if (!p) continue; int h = atoi(p+1); *p = 0;
        p = strrchr(rest, ' '); if (!p) continue; int a = atoi(p+1); *p = 0;
        if (n == cap) { cap *= 2; data = realloc(data, cap * sizeof(Person)); }
        data[n].id = id; data[n].name = strdup(rest);
        data[n].age = a; data[n].height = h; data[n].weight = w; n++;
    }
    fclose(f); return 1;
}

int main(void) {
    int ch; char fn[100];
    while (1) {
        printf("\nMAIN MENU (HEAP)\n1. Read Data\n2. Create a Min-heap based on the age\n"
               "3. Create a Max-heap based on the weight\n4. Display weight of the youngest person\n"
               "5. Insert a new person into the Min-heap\n6. Delete the oldest person\n7. Exit\nEnter option: ");
        if (scanf("%d", &ch) != 1 || ch == 7) break;
        switch (ch) {
        case 1:
            printf("Enter file name: "); scanf("%99s", fn);
            if (readData(fn)) show(data, n);
            break;
        case 2:
            if (!n) { printf("Read data first\n"); break; }
            minCap = n + 16; minh = malloc(minCap * sizeof(Person)); minN = n;
            memcpy(minh, data, n * sizeof(Person));
            for (int i = minN/2 - 1; i >= 0; i--) minDown(minh, minN, i);
            printf("Min-heap (by age) array order:\n"); show(minh, minN);
            break;
        case 3:
            if (!n) { printf("Read data first\n"); break; }
            maxh = malloc(n * sizeof(Person)); maxN = n;
            memcpy(maxh, data, n * sizeof(Person));
            for (int i = maxN/2 - 1; i >= 0; i--) maxDown(maxh, maxN, i);
            printf("Max-heap (by weight) array order:\n"); show(maxh, maxN);
            break;
        case 4:
            if (!minN) { printf("Create the min-heap first\n"); break; }
            printf("Weight of youngest student: %.2f kg\n", minh[0].weight * 0.45359237);
            break;
        case 5: {
            if (!minN) { printf("Create the min-heap first\n"); break; }
            Person p; char nm[100];
            printf("Enter id: ");     scanf("%d", &p.id);
            printf("Enter name: ");   scanf(" %99[^\n]", nm); p.name = strdup(nm);
            printf("Enter age height weight: "); scanf("%d %d %d", &p.age, &p.height, &p.weight);
            if (minN == minCap) { minCap *= 2; minh = realloc(minh, minCap * sizeof(Person)); }
            minh[minN] = p; minUp(minh, minN); minN++;
            printf("Inserted. Heap now:\n"); show(minh, minN);
            break; }
        case 6: {
            if (!minN) { printf("Create the min-heap first\n"); break; }
            int idx = 0;                              /* oldest is always a leaf; linear scan */
            for (int i = 1; i < minN; i++) if (minh[i].age > minh[idx].age) idx = i;
            printf("Deleted oldest person: %s (age %d)\n", minh[idx].name, minh[idx].age);
            minh[idx] = minh[--minN];
            if (idx < minN) { minUp(minh, idx); minDown(minh, minN, idx); }
            show(minh, minN);
            break; }
        default: printf("Invalid option\n");
        }
    }
    return 0;
}
