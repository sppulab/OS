#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>

void bankers(int n, int r, int alloc[][r], int need[][r], int avail[]) {
    int count = 0, safeSeq[n];
    bool vis[n];

    while(count != n) {
        for(int i=0 ; i<n ; i++) {
            if(!vis[i]) {
                int satisfied = 0;
                for(int j=0 ; j<r ; j++) {
                    if(avail[j] >= need[i][j]) {
                        satisfied++;
                    }
                }
                if(satisfied == r) {
                    vis[i] = true;
                    for(int j=0 ; j<r ; j++) {
                        avail[j] += alloc[i][j];
                    }
                    safeSeq[count] = i+1;
                    count++;
                }
            }
        }
    }

    printf("<--Safe Sequence-->");
    for(int i=0 ; i<n ; i++) {
        printf("%d ", safeSeq[i]);
    }
}

int main() {
    int n, r;
    printf("Enter the number of processes : ");
    scanf("%d", &n);
    printf("Enter the number of resources : ");
    scanf("%d", &r);

    int alloc[n][r], required[n][r], need[n][r], avail[r];

    printf("Enter total resources : ");
    for(int i=0 ; i<r ; i++) {
        scanf("%d", &avail[i]);
    }
    
    printf("\n<--Enter allocated Resources-->\n");
    for(int i=0 ; i<n ; i++) {
        printf("for process P%d : ", i+1);
        for(int j=0 ; j<r ; j++) {
            scanf("%d", &alloc[i][j]);
            avail[j] -= alloc[i][j];
        }
    }

    printf("\n<--Enter Required Resources-->\n");
    for(int i=0 ; i<n ; i++) {
        printf("for process P%d : ", i+1);
        for(int j=0 ; j<r ; j++) {
            scanf("%d", &required[i][j]);
            need[i][j] = required[i][j] - alloc[i][j];
        }
    }

    bankers(n, r, alloc, need, avail);
}