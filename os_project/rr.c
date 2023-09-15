#include <stdio.h>
#include <stdlib.h>

typedef struct {
	int pid;
	int arrival_time;
	int burst_time;
} process;

typedef struct {
    int pid;
    int remaining_time;
} process_round_robin;

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

	int time=0;
    process_round_robin *queue;
    int first_element_in_queue=0;
    int last_element_in_queue=0;
    int finished_processes=0;
    int modulo_remain=0;
    queue = malloc( n * sizeof(process_round_robin));


    // Adding in the queue only the processes that arrive in time equal to zero
    for(int i=0; i<n; i++){
        if(arr[i].arrival_time == 0){
            process_round_robin new_process;
            new_process.pid = arr[i].pid;
            new_process.remaining_time = arr[i].burst_time;
            queue[last_element_in_queue]=new_process;
            last_element_in_queue++;
        }
    }


    while(1) {
        // Executing the first process in the queue and decrease by one its remaining time
        queue[first_element_in_queue].remaining_time = queue[first_element_in_queue].remaining_time - 1;
        printf("%d\n",queue[first_element_in_queue].pid);

        // Increase time by one - next CPU cycle
        time++;

        // This loop checks whether if there are any new processes with arrival time equal to the current time that need to be added in the queue
        for(int i=0;i<n;i++){
            if(arr[i].arrival_time == time){
                process_round_robin new_process;
                new_process.pid = arr[i].pid;
                new_process.remaining_time = arr[i].burst_time;
                queue[last_element_in_queue]=new_process;
                last_element_in_queue++;
            }
        }

        // This statement checks:
        // [1] if the process that was just executed is finished - if so then it is removed from the queue
        // [2] if the executing process should change based on the quantum number - if so the queue changes cyclically.
        if(queue[first_element_in_queue].remaining_time == 0){
            for(int i=1;i<last_element_in_queue;i++){
                queue[i-1]=queue[i];
            }
            last_element_in_queue--;
            modulo_remain=time % quantum;
            finished_processes++;
        }
        else if(time % quantum == modulo_remain){
            process_round_robin temp_process = queue[first_element_in_queue];
            for(int i=1;i<last_element_in_queue;i++){
                queue[i-1]=queue[i];
            }
            queue[last_element_in_queue-1]=temp_process;
        }

        // If all the processes are finished then the loop ends
        if(finished_processes == n){
            break;
        }

    }



	return 0; /* DO NOT EDIT THIS LINE */
}
