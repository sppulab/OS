#include<stdio.h>
#include<sys/types.h>
#include<unistd.h>
#include<sys/wait.h>

void BubbleSort(int arr[],int n){
	for(int i =0;i<n-1;i++){
		for(int j =0;j<n-i-1;j++){
			if(arr[j] > arr[j+1]){
				int temp = arr[j];
				arr[j] = arr[j+1];
				arr[j+1] = temp;
			}
		}
	}
	printf("After Sorting using BubbleSort:\n");
	for(int i =0;i<n;i++){
		printf("%d ",arr[i]);
	}
	printf("\n");
}

void SelectionSort(int arr[],int n){
	int min_ind;
	for(int i =0;i<n-1;i++){
		min_ind = i;
		for(int j = i+1;j<n;j++){
			if(arr[j]<arr[min_ind]){
				min_ind = j;
			}
		}
		if(min_ind != i ){
			int temp = arr[min_ind];
			arr[min_ind] = arr[i];
			arr[i] = temp;
		}
	}
	printf("After Sorting using SelectionSort:\n");
	for(int i =0;i<n;i++){
		printf("%d ",arr[i]);
	}
	printf("\n");
}

int main(){
	int n;
	pid_t pid;

    printf("\nEnter the number of Elements:");
    scanf("%d", &n);
    int arr[n];

    printf("\nEnter the Array Elements:");
    for (int i = 0; i < n; i++)
    {
        scanf("%d", &arr[i]);
    }

	pid = fork();
	if(pid<0){
		printf("\nError while creating a new process!\n");
	}else if(pid == 0){
		sleep(2);
		wait(NULL);
		printf("\n----Child Process----\n");
        printf("\nThis is Child Process with pid = %d and ppid = %d \n", getpid(), getppid());
        BubbleSort(arr, n);
        printf("\n------Child Process Terminated------\n");
	}else{
		printf("\n----Parent Process----\n");
        printf("\nThis is Parent Process with pid = %d and ppid = %d \n", getpid(), getppid());
        SelectionSort(arr, n);
        printf("\n------Parent Process Terminated------\n");
	}
	return 0;
}
