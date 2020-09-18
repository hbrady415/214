#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include <pthread.h>
#include <time.h>
#include "multitest.h"
#include "multitest_thread.c"
#include "multitest_proc.c"
int main(int argc, char**argv){
int arraySize=250;
//changeable^^^^^^ (range: 1-->256)
struct timeval start;
struct timeval end;
int totalTimeProc = 0;
int totalTimeThread = 0;
char * name=MYSTRING;
int upper=strtol(argv[1],NULL,10);
int lower=0;
int i=0;
int numbers [upper];
int num=0;
int k=0;
int temp=0;
int needArrays=1;
for (i=0; i<upper; i++){
	if ((i!=0) && (i%arraySize) == 0){ 
	needArrays++;
	}
}
//printf("need: %d\n",needArrays);

i=0;
while (i<upper){
numbers[i]=i;
i++;
}


srand(time(0));
for (i=0; i<upper; i++) {
	num= rand() % 
		((upper-1) - lower + 1) +lower;	
	//printf("randomIndex: %d\n",num);
		if (num==i){
		//printf("noswap: %d\n",numbers[i]);
		continue;
		}
	temp=numbers[i];
	numbers[i]=numbers[num];
	numbers[num]=temp;
	//printf("numbers[i] after switch: %d\n",numbers[i]);
}
int** masterList=malloc(sizeof(int)*needArrays*arraySize);
for (i=0;i<needArrays;i++){
masterList[i]=malloc(arraySize*sizeof(int));
}
int cur=0;
i=0;
while (cur<needArrays){
for (k=0; k<arraySize; k++){
	if (i>=upper){
		masterList[cur][k]=(int)(-1);
	//printf("check %d\n",masterList[cur][k]);
		continue;
	}masterList[cur][k]=numbers[i];
	//printf("check %d\n",masterList[cur][k]);
	i=i+1;
}cur++;
//printf("nextArray\n");
}

if (strcmp(name,"thread")==0){
gettimeofday(&start, 0);
searchThread2(needArrays,arraySize,7,masterList);
gettimeofday(&end, 0);
totalTimeThread = totalTimeThread + ((end.tv_sec-start.tv_sec)*1000000 + (end.tv_usec-start.tv_usec));
printf("\nthread runtime: %d microseconds\n", totalTimeThread);
}
if (strcmp(name,"proc")==0){
gettimeofday(&start, 0);
searchProc2(needArrays,arraySize,7,masterList);
gettimeofday(&end, 0);
totalTimeProc = totalTimeProc + ((end.tv_sec-start.tv_sec)*1000000 + (end.tv_usec-start.tv_usec));
printf("\nproc runtime: %d microseconds\n", totalTimeProc);
}
//free(masterList);

return 0;
}

