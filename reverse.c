#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdlib.h>
#define MAX 20
int a[MAX];
int main(int argc, char *argv[])
{
    int i;
    for (i = 0; i < argc; i++)
    {
        a[i] = atoi(argv[i]);
    }
    printf("Reversed Array:");
    for (int i = argc - 1; i >= 0; i--)
    {
        printf("%d ", a[i]);
    }
    printf("\nEXECVE() called");
    return 0;
}