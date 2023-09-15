#include <stdio.h>
#include <stdlib.h>

typedef struct {
	int pid;
	int arrival_time;
	int burst_time;
} process;


int main() {

	/* read in data - DO NOT EDIT (START) */
	int n;
	int quantum;
	scanf("%d", &n);
	scanf("%d", &quantum);
	process *arr;
	arr = malloc(n * sizeof(process));
	for (int i = 0; i < n ; ++i) {
		scanf("%d", &arr[i].pid);
		scanf("%d", &arr[i].arrival_time);
		scanf("%d", &arr[i].burst_time);
	}
	/* read in data - DO NOT EDIT (END) */

	int finished_processes = 0;
    int running_process = 0;
    int time = 0;
    int *remaining_time;
    remaining_time = malloc( n * sizeof(int));

    // Creating a new array that is parallel with the array that contains the processes. This new array is for keeping the remaining time of each process
    for(int i=0;i<n;i++){
        remaining_time[i] = arr[i].burst_time;
    }

    // This block of code searches for the process that arrived first (when time is equal to zero)
    // if there are more processes that arrive this time then it chooses the process with the lowest burst time
    int min = -1;
    for(int i=0;i<n;i++){
        if(arr[i].arrival_time == 0){
            if (min == -1){
                min = arr[i].burst_time;
                running_process = i;
            }
            else if (arr[i].burst_time < min) {
                min = arr[i].burst_time;
                running_process = i;
            }
        }
    }

    while(1){
        remaining_time[running_process]--;
        printf("%d\n",arr[running_process].pid);
        time++;

        // This statement checks:
        // [1] If the process that is currently executing is finished then it searches for the next process with the minimum burst time
        // [2] If there is a process with less burst time, it interrupts the current process and takes the CPU
        if(remaining_time[running_process] == 0){
            finished_processes++;
            int minimum_remaining_time = -1;
            for(int j=0; j<n; j++) {
                if (remaining_time[j] > 0 && arr[j].arrival_time <= time) {
                    if(minimum_remaining_time != -1 && remaining_time[j] >= minimum_remaining_time){
                        continue;
                    }
                    running_process = j;
                    minimum_remaining_time = remaining_time[j];
                }
            }
        }
        else{
            for(int j=0; j<n; j++) {
                if (remaining_time[j] > 0 && remaining_time[j] < remaining_time[running_process] && arr[j].arrival_time <= time) {
                    running_process = j;
                }
            }
        }

        if(finished_processes == n){
            break;
        }
    }




	return 0; /* DO NOT EDIT THIS LINE */
}
