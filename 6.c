#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>

void fifo(int n, int m, int refStr[], int frames[]) {
    int pageFaults = 0, pageHits = 0;
    
    // Initializing frames with -1 to denote empty frame
    for(int i=0 ; i<m ; i++) {
        frames[i] = -1;
    }

    printf("Page\t\tframe1\t\tframe2\t\tframe3\t\tFault/Hit");

    for (int i=0 ; i<n ; i++) {
        int exists = 0;

        // Page already exists in the frame.
        for(int j=0 ; j<m ; j++) {
            if (refStr[i] == frames[j]) {
                exists = 1;
                pageHits++;
                break;
            }
        }

        // Page doesnt exist in the frame.
        if(exists == 0) {
            frames[pageFaults % m] = refStr[i];
            pageFaults++;
        }

        printf("\n%d\t\t", refStr[i]);
        for(int k=0 ; k<m ; k++) {
            printf("%d\t\t", frames[k]);
        }
        if(exists == 0) {
            printf("F");
        } else {
            printf("H");
        }
    }
    printf("\nTotal Page Faults : %d", pageFaults);
    printf("\nTotal Page hits : %d", pageHits); 
}

void lru(int n, int m, int refStr[], int frames[]) {
    int pageFaults = 0;
    int counter[m];

    for(int i=0 ; i<m ; i++) {
        frames[i] = -1;
        counter[i] = 0;
    }

    printf("Page\t\tframe1\t\tframe2\t\tframe3\t\tFault/Hit");
    for(int i=0 ; i<n ; i++) {
        int currentPage = refStr[i];

        // Check if current page exists in the frame;
        int pageIdx = -1;
        for(int j=0 ; j<m ; j++) {
            if(frames[j] == currentPage) {
                pageIdx = j;
                break;
            }
        }

        // If page not found
        if (pageIdx == -1) {
            int replaceIdx = 0;
            int minCounter = counter[0];

            // Get the page which is least recently used.
            for(int j=1 ; j<m ; j++) {
                if(counter[j] < minCounter) {
                    minCounter = counter[j];
                    replaceIdx = j;
                }
            }

            frames[replaceIdx] = currentPage;
            counter[replaceIdx] = i+1;
            pageFaults++;
        } else {
            counter[pageIdx] = i+1;
        }

        printf("\n%d\t\t", refStr[i]);
        for(int k=0 ; k<m ; k++) {
            printf("%d\t\t", frames[k]);
        }
        if(pageIdx == -1) {
            printf("F");
        } else {
            printf("H");
        }
    }

    printf("\nTotal Page Faults : %d", pageFaults);
    printf("\nTotal Page hits : %d", (n-pageFaults));
}

void optimal(int n, int m, int refStr[], int frames[]) {
    int pageFaults = 0;

    // Initialize empty frames
    for(int i=0 ; i<m ; i++) {
        frames[i] = -1;
    }

    printf("Page\t\tframe1\t\tframe2\t\tframe3\t\tframe4\t\tFault/Hit");
    bool exists;
    for (int i=0 ; i<n ; i++) {
        exists = false;
        // Check if the page already exists in frame
        for(int j=0 ; j<m ; j++) {
            if(frames[j] == refStr[i]) {
                exists = true;
                break;
            }
        }

        if(!exists) {
            int replaceIdx = 0;
            int farthest = i;
            for(int j=0 ; j<m ; j++) {
                int k;
                for(k=i ; k<n ; k++) {
                    if (frames[j] == refStr[k]) {
                        if (k > farthest){
                            replaceIdx = j;
                            farthest = k;                            
                        }
                        break;
                    }
                }

                if (k == n) {
                    replaceIdx = j;
                    break;
                }
            }

            frames[replaceIdx] = refStr[i];
            pageFaults++;
        }

        printf("\n%d\t\t", refStr[i]);
        for(int k=0 ; k<m ; k++) {
            printf("%d\t\t", frames[k]);
        }
        if(!exists) {
            printf("F");
        } else {
            printf("H");
        }
    }

    printf("\nTotal Page Faults : %d", pageFaults);
    printf("\nTotal Page hits : %d", (n-pageFaults));
}

int main() {
    int n, m, refStr[100], frames[10];
    printf("Enter the number of pages : ");
    scanf("%d", &n);
    printf("Enter the Reference String : ");
    for (int i=0 ; i<n ; i++) {
        scanf("%d", &refStr[i]);
    }
    printf("Enter the number of frames : ");
    scanf("%d", &m);

    fifo(n, m, refStr, frames);
    // lru(n, m, refStr, frames);
    // optimal(n, m, refStr, frames);
}