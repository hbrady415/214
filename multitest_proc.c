#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <pthread.h>
#include <unistd.h>
#include "multitest.h"

int found=0;

void searchProcs(int numArrays,int arraySize,int key,int**masterList) 
{
struct timeval start;
struct timeval end;
int totalTimeProc = 0;
gettimeofday(&start, 0);
printf("doin proc\n");
int i=0;
int k=0;
int q=0;
int yuh=0;
for (i=0;i<numArrays;i++){
	if(fork()==0){
	//printf("child: %d\n",i);
	for (k=0;k<arraySize;k++){
	if (masterList[i][k]==key){
	//printf("found the bih\n");
	//printf("i:%d k:%d\n\n",i,k);	
	q=(i+1)*(k+1);
	q--;
	exit(k);	
	}
	}
	exit(0);
	}
}
int stat;
int bih=-1;
int exit_status=-1;
for(i=0;i<numArrays;i++){
wait(&stat);
if (WIFEXITED(stat)){
	exit_status=WEXITSTATUS(stat);
}

//printf("exitStatus:%d\n",exit_status);

if (exit_status!=0){
bih=(i*arraySize)+(exit_status);
yuh=1;
printf("found at: %d\n",bih);
}
} 
if (yuh==0){printf("not found.\n");}
gettimeofday(&end, 0);
totalTimeProc = totalTimeProc + ((end.tv_sec-start.tv_sec)*1000000 + (end.tv_usec-start.tv_usec));
printf("\nproc runtime: %d microseconds\n", (totalTimeProc));

}
