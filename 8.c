#include<stdio.h>
#include<stdlib.h>

int sstf(int n, int reqSeq[], int headPos) {
    int count = 0, min, diff, idx, totalMovement = 0;
    while(count != n) {
        min = __INT_MAX__;
        for (int i=0 ; i<n ; i++) {
            diff = abs(reqSeq[i]-headPos);
            if (diff < min) {
                min = diff;
                idx = i;
            }
        }
        totalMovement += min;
        printf("%d ", reqSeq[idx]);
        headPos = reqSeq[idx];
        reqSeq[idx] = __INT_MAX__;
        count++;
    }
    return totalMovement;
}

int scan(int n, int reqSeq[], int headPos, int dir) {
    int size;
    printf("Enter the Disk Size : ");
    scanf("%d", &size);

    int totalMovement = 0;

    for(int i=0 ; i<n ; i++) {
        for (int j=0 ; j<n-i-1 ; j++) {
            if(reqSeq[j] > reqSeq[j+1]) {
                int temp = reqSeq[j];
                reqSeq[j] = reqSeq[j+1];
                reqSeq[j+1] = temp;
            }
        }
    }
    for(int i=0 ; i<n ; i++) {
        printf("%d ", reqSeq[i]);
    }

    int bp = -1;
    for(int i=0 ; i<n ; i++) {
        if(reqSeq[i] > headPos) {
            bp = i;
            break;
        }
    }
    printf("\n%d", bp);

    if (dir == 1) {
        for(int i=bp ; i<n ; i++) {
            totalMovement = totalMovement + abs(reqSeq[i] - headPos);
            headPos = reqSeq[i];
        }
        totalMovement = totalMovement + (size - 1 - headPos);
        headPos = size - 1;
        for(int i=bp-1 ; i>=0 ; i--) {
            totalMovement = totalMovement + abs(headPos - reqSeq[i]);
            headPos = reqSeq[i];
        }
    }
    if (dir == 0) {
        for(int i=bp-1 ; i>=0 ; i--) {
            totalMovement = totalMovement + abs(headPos - reqSeq[i]);
            headPos = reqSeq[i];
        }
        totalMovement = totalMovement + headPos;
        headPos = 0;
        for(int i=bp ; i<n ; i++) {
            totalMovement = totalMovement + abs(reqSeq[i] - headPos);
            headPos = reqSeq[i];
        }
    }

    return totalMovement;
}

int clook(int n, int reqSeq[], int headPos, int dir) {
    int totalMovement = 0;

    for(int i=0 ; i<n ; i++) {
        for (int j=0 ; j<n-i-1 ; j++) {
            if(reqSeq[j] > reqSeq[j+1]) {
                int temp = reqSeq[j];
                reqSeq[j] = reqSeq[j+1];
                reqSeq[j+1] = temp;
            }
        }
    }
    
    int bp = -1;
    for(int i=0 ; i<n ; i++) {
        if(reqSeq[i] > headPos) {
            bp = i;
            break;
        }
    }

    for (int i=bp ; i<n ; i++) {
        totalMovement += abs(reqSeq[i] - headPos);
        headPos = reqSeq[i];
    }
    for (int i=0 ; i<bp ; i++) {
        totalMovement += abs(reqSeq[i] - headPos);
        headPos = reqSeq[i];
    }

    return totalMovement;
}

int main() {
    int n, reqSeq[100], headPos, totalHeadMovement;
    
    printf("Enter the number of requests : ");
    scanf("%d", &n);
    printf("Enter the request sequence : ");
    for(int i=0 ; i<n ; i++) {
        scanf("%d", &reqSeq[i]);
    }
    printf("Enter the initial R/W head Position : ");
    scanf("%d", &headPos);

    // totalHeadMovement = sstf(n, reqSeq, headPos);
    // totalHeadMovement = scan(n, reqSeq, headPos, 0);
    totalHeadMovement = clook(n, reqSeq, headPos, 0);

    printf("\nTotal Head Movement is %d", totalHeadMovement);
}