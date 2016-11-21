#include <sys/types.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
#include <string.h>


struct MyProcess {
   char p_name[50];
   int p_arrival;
   int p_bust_origin;
   int p_bust;
   int p_start_time;
   int p_finish_time;
};

struct MyProcess processList[n];


// -----------------------------------------------------------------------------------------------
// ----- REMAINING PROCESS COUNT -----
// -----------------------------------------------------------------------------------------------
int remainingProcessCount(struct MyProcess processList[] , int processCount){
	
	int remainProcess = 0;
	for(int i=0 ; i<processCount ; i++) {
		if(processList[i].p_bust>0){
			remainProcess += 1;	
		}
   	}
   	return remainProcess;
}


// -----------------------------------------------------------------------------------------------
// ----- PRINT PROCESS LIST -----
// -----------------------------------------------------------------------------------------------
void printScheduleResult(struct MyProcess processList[] , int processCount){
	
	int totalWaitingTime = 0;
	printf("ProcessName \t  ArrivalTime \t BurstTime \t WaitingTime");
	for(int i=0 ; i<processCount ; i++) {
		int waitingTime = (processList[i].p_start_time - processList[i].p_arrival) + (processList[i].p_finish_time - processList[i].p_start_time - processList[i].p_bust_origin);
		printf("\n%s \t\t  %d \t\t %d \t\t %d \t %d - %d" , processList[i].p_name, processList[i].p_arrival , processList[i].p_bust_origin , waitingTime , processList[i].p_start_time,processList[i].p_finish_time);
		//printf("\n%s \t\t  %d \t\t %d \t\t %d" , processList[i].p_name, processList[i].p_arrival , processList[i].p_bust_origin , waitingTime);
		totalWaitingTime += waitingTime;
   	}	

   	printf("\nTotal waiting time: %d\n", totalWaitingTime);
   	printf("Average waiting time: %f\n", ((float)totalWaitingTime/processCount));
}


// -----------------------------------------------------------------------------------------------
// ---- MAIN METHOD ---- 
// -----------------------------------------------------------------------------------------------
int main(){

	printf("Enter the total no of process: ");
	int processCount;
	scanf ("%d",&processCount);

	struct MyProcess processList[processCount];

	for(int i=0 ; i<processCount ; i++) {
		// creates process 
		struct MyProcess processTemp;
		
		// sets process values
		printf("Enter p_name: ");
		scanf("%s",processTemp.p_name);

		printf("Enter p_arrival: ");
		scanf ("%d",&processTemp.p_arrival);

		printf("Enter p_bust: ");
		scanf ("%d",&processTemp.p_bust);
		processTemp.p_bust_origin = processTemp.p_bust;
		processTemp.p_start_time = -1;
		processTemp.p_finish_time = -1;
		processList[i] = processTemp;

		printf("\n");
	}


	// -----------------------------------------------------------------------------------------------
	// -----------------------------------------------------------------------------------------------
	// 	PREEMPTIVE SHORTEST JOB FIRST SCHEDULING

   	int timer = 0;
    do{
       
    	int target = -1;
		for(int i=0 ; i<processCount; i++) {

    		if(processList[i].p_arrival<=timer && processList[i].p_arrival>0 && processList[i].p_bust>0){
				if(target==-1){
					target = i;
				}else{
					if(processList[i].p_bust<processList[target].p_bust){
						target = i;
					}else if(processList[i].p_bust==processList[target].p_bust){
						if(processList[i].p_finish_time==timer){
							target = i;
						}
					}
				}
    		}
	   	}

	   	if(target!=-1){

	   		processList[target].p_bust = processList[target].p_bust - 1 ;
   			processList[target].p_finish_time = timer+1;

	   		if(processList[target].p_start_time==-1){
	   			processList[target].p_start_time = timer;
	   		}

   			// printf("Timer -- %d -- %s -- Process bust %d -- Process start %d -- Process finish %d \n", timer ,processList[target].p_name , processList[target].p_bust, processList[target].p_start_time, processList[target].p_finish_time);

	   	}else{
	   		// process idle case
	   		// printf("Timer %d \n", timer );
	   	}

       
   		timer++;
    }while ( remainingProcessCount(processList , processCount)!=0 );


    // -----------------------------------------------------------------------------------------------
	// -----------------------------------------------------------------------------------------------
	// ----- PRINT RESULT ----- 
    printScheduleResult(processList,processCount);

	return 0;
}

