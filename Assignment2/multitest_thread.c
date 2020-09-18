#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
#include <time.h>
#include "multitest.h"

int arraySizeG=-1;
int keyG=-1;
int foundG=0;
int** masterListG;
int indexG=0;

void *threadSearch(void* arg){
	
	int k=(int)arg;
	//printf("\nARGk:%d\n",k);
	//printf("threadSearch\n");
	//printf("arraySize:%d\nkey:%d\n",arraySizeG,keyG);
	int i=0;
	for(i=0;i<arraySizeG;i++){
	//printf("k::%d::i:%d::%d\n",k,i,masterListG[k][i]);
	if (keyG==masterListG[k][i]){
	//printf("FOUND HER:%d\n",keyG);
	//printf("k::%d::i:%d::%d\n",k,i,masterListG[k][i]);
	indexG=(k*arraySizeG)+(i);
	foundG=1;
	}
	}
	//free(real_args);
	//return NULL;
}


void searchThreads(int numArrays,int arraySize, int key,int **masterList) 
{ 	//printf("in searchThreads\n");
	//printf("numArrays:%d\n",numArrays);
	//printf("key:%d\n",key);i
	struct timeval start;
	struct timeval end;
	int totalTimeThread = 0;
	gettimeofday(&start, 0);
printf("doin thread\n");

pthread_t thread_id;
int i=0;
arraySizeG=arraySize;
keyG=key;
//int* rArray=malloc(sizeof(int)*arraySizeG);
//printf("GarrayS:%d\nGkey:%d\n",arraySizeG,keyG);
masterListG=malloc(sizeof(int)*numArrays*arraySize);
for (i=0;i<numArrays;i++){
masterListG[i]=malloc(sizeof(int)*arraySizeG);
}
masterListG=masterList;
for (i=0;i<numArrays;i++){
//int* rArray=malloc(sizeof(int)*arraySizeG);
//rArray=malloc(sizeof(int)*arraySizeG);
//rArray=masterList[i];
//printf("GbeforeTSearch:%d\n",masterListG[i][0]);	

pthread_create(&thread_id,NULL,threadSearch,(int*)i);

//pthread_join(thread_id,NULL);
//free(rArray);
//printf("\nhi  ");
//printf("i:%d",i);
}
//for(i=0;i<numArrays;i+
sleep(1);
if (foundG==1){
printf("found at: %d\n",indexG);
}
//printf("Average runtime: %d milliseconds\n", totaltime);
if (foundG==0){
printf("not found.");
}
gettimeofday(&end, 0);
totalTimeThread = totalTimeThread + ((end.tv_sec-start.tv_sec)*1000000 + (end.tv_usec-start.tv_usec));
printf("\nthread runtime: %d microseconds\n", (totalTimeThread-1000000)); 

pthread_exit(NULL);





	printf("DONE THREADS");
return;
} 

