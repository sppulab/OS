#include <stdio.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

void BubbleSort(int arr[], int n)
{
    for (int i = 0; i < n - 1; i++)
    {
        for (int j = 0; j < n - i - 1; j++)
        {
            if (arr[j] > arr[j + 1])
            {
                int temp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = temp;
            }
        }
    }
    printf("\nSorted Array by Bubble Sort in Child Process is:\n");
    for (int i = 0; i < n; i++)
    {
        printf("%d ", arr[i]);
    }
    printf("\n");
}

void SelectionSort(int arr[], int n)
{
    int ind;
    for (int i = 0; i < n - 1; i++)
    {
        ind = i;
        for (int j = i + 1; j < n; j++)
        {
            if (arr[j] < arr[ind])
                ind = j;
            if (ind != i)
            {
                int temp = arr[ind];
                arr[ind] = arr[i];
                arr[i] = temp;
            }
        }
    }
    printf("\nSorted Array by Selection Sort in Parent Process is:\n");
    for (int i = 0; i < n; i++)
    {
        printf("%d ", arr[i]);
    }
    printf("\n");
}

int main()
{
    pid_t pid;

    int n;
    printf("\nEnter the number of Elements:");
    scanf("%d", &n);
    int arr[n];

    printf("\nEnter the Array Elements:");
    for (int i = 0; i < n; i++)
    {
        scanf("%d", &arr[i]);
    }

    pid = fork();
    if (pid == 0)
    {
        printf("\n------Child Process------\n");
        printf("\nThis is Child Process with pid = %d and ppid = %d \n", getpid(), getppid());
        BubbleSort(arr, n);
        printf("\n------Child Process Terminated------\n");
    }
    else
    {
        sleep(2);
        wait(NULL);
        printf("\n------Parent Process------\n");
        printf("\nThis is Parent Process with pid = %d and ppid = %d \n", getpid(), getppid());
        SelectionSort(arr, n);
        printf("\n------Parent Process Terminated------\n");
    }
}