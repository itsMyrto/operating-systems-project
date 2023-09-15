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

	int *process_is_finished;
    process_is_finished = calloc( n, sizeof(int));
    int finished_processes = 0;
    int running_process = 0;
    int time = 0;

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

    // This loop ends when all processes are finished
    while(1){
        // Executing the chosen process until it is finished
        for(int i=0; i<arr[running_process].burst_time;i++){
            printf("%d\n",arr[running_process].pid);
            time++;
        }
        finished_processes++;
        process_is_finished[running_process] = 1;

        // Finding the process with the minimum burst time - choosing only between the processes that have arrived at this time or before
        int minimum_burst_time;
        for(int i=0; i<n; i++){
            if(process_is_finished[i] == 0 && arr[i].arrival_time <= time){
                minimum_burst_time = arr[i].burst_time;
                running_process = i;
                break;
            }
        }
        for(int i=0; i<n; i++){
            if(process_is_finished[i] == 0 && arr[i].arrival_time <= time && arr[i].burst_time < minimum_burst_time){
                minimum_burst_time = arr[i].burst_time;
                running_process = i;
            }
        }

        // If all processes are finished then it exits the while loop
        if(finished_processes == n){
            break;
        }
    }


	return 0; /* DO NOT EDIT THIS LINE */
}
