#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include "mymalloc.h"
#include "mymalloc.c"


int main(int argc,char ** argv){


void*ptrHolder[2000]= {NULL};
struct timeval start;
struct timeval end;
size_t* ptr= NULL;
int totalTimeA=0;
int totalTimeB=0;
int totalTimeC=0;
int totalTimeD=0;
int totalTimeE=0;
int totalTimeF=0;
int testA=0;
//WorkLoad A
printf("\nworkLoadA");
int i=0;
while(testA<100){
gettimeofday(&start, 0);

while (i<150){
ptr=malloc(1);
free(ptr);
i=i+1;
}
gettimeofday(&end, 0);
totalTimeA = totalTimeA + ((end.tv_sec-start.tv_sec)*1000000 + (end.tv_usec-start.tv_usec));
testA++;

}
int q =1;
int testB =0;
//WorkLoad B
printf("\nworkLoadB");
//ptrHolder[0]=ptr;
while(testB<100){
gettimeofday(&start, 0);
ptrHolder[0]=ptr;
q=1;
while (q<150){
ptr=malloc(1);
ptrHolder[q]=ptr;
q=q+1;
}

q=0;

while(q<150){
printf("\nptrHoldb4free:%p",ptrHolder[2]);
printf("\nptr b4 free:%p",ptr);
free(ptrHolder[q]);
printf("\nptrHolder2 after free:%p",ptrHolder[2]);
printf("\nptrafterfree:%p",ptr);
q=q+1;
}
gettimeofday(&end, 0);
totalTimeB = totalTimeB + ((end.tv_sec-start.tv_sec)*1000000 + (end.tv_usec-start.tv_usec));
testB++;

}

int testC=0;
//WorkLoad C
int countMalloc=0;
int k =0;
int randomTemp=0;
size_t* ptrTemp=NULL;
printf("\nworkLoadC");
while(testC<100){
gettimeofday(&start, 0);

countMalloc=0;
k=0;
randomTemp=0;
ptrTemp=NULL;
while (countMalloc<50){
randomTemp=rand() % 2;
	if (randomTemp==0){
	ptrTemp=malloc(1);
	ptrHolder[k]=ptrTemp;
	k=k+1;
	countMalloc=countMalloc+1;
	continue;
	}
	if (randomTemp==1){
	free(ptrHolder[k]);
	k=k=1;
	continue;
	}
}
gettimeofday(&end, 0);
totalTimeC = totalTimeC + ((end.tv_sec-start.tv_sec)*1000000 + (end.tv_usec-start.tv_usec));
testC++;

}


int testD=0;
//WorkLoad D
int randomTemp2=0;
printf("\nworkLoadD");
while(testD<100){
gettimeofday(&start, 0);

countMalloc=0;
k=0;
randomTemp=0;
randomTemp2=0;
ptrTemp=NULL;
while (countMalloc<50){
randomTemp=rand() % 2;
randomTemp2=(rand() % 64)+1;
	if (randomTemp==0){
	ptrTemp=malloc(randomTemp2);
	ptrHolder[k]=ptrTemp;
	k=k+1;
	countMalloc=countMalloc+1;
	continue;
	}
	if (randomTemp==1){
	free(ptrHolder[k]);
	k=k=1;
	continue;
	}
}
gettimeofday(&end, 0);
totalTimeD = totalTimeD + ((end.tv_sec-start.tv_sec)*1000000 + (end.tv_usec-start.tv_usec));
testD++;

}


int testE=0;
//WorkLoad E (ErrorChecks)
printf("\nworkLoadE");
while(testE<100){
gettimeofday(&start, 0);

size_t* ptrE1=malloc(10);
size_t* ptrE2=malloc(4097);
free(ptrE2);
ptrE2=malloc(4030);
free(ptrE1);
free(ptrE1);
ptrE1=malloc(10);
size_t* ptrE3=malloc(100);
size_t* ptrE4=malloc(0);
free(ptrE4);
ptrE4=malloc(0);
free(ptrE4);
free((int*)4);
free(ptrE3);
free(ptrE2);
free(ptrE1);
gettimeofday(&end, 0);
testE++;
totalTimeE = totalTimeE + ((end.tv_sec-start.tv_sec)*1000000 + (end.tv_usec-start.tv_usec));
}





//WorkLoad F (Free Refills!)
printf("\nworkLoadF");
int testF=0;
while(testF<100){
gettimeofday(&start, 0);

size_t* ptrF1=malloc(1);
size_t* ptrF2=malloc(6);
size_t* ptrF3=malloc(20);
size_t* ptrF4=malloc(10);
size_t* ptrF5=malloc(20);
free(ptrF1);
ptrF1=malloc(1);
free(ptrF2);
free(ptrF3);
ptrF2=malloc(6);
size_t* ptrF6=malloc(21);
free(ptrF6);
free(ptrF5);
free(ptrF4);
free(ptrF3);
free(ptrF2);
free(ptrF1);
gettimeofday(&end, 0);
testF++;
totalTimeF = totalTimeF + ((end.tv_sec-start.tv_sec)*1000000 + (end.tv_usec-start.tv_usec));
}


	printf("Average runtime for workload A %d milliseconds\n", totalTimeA/100);
        printf("Average runtime for workload B %d milliseconds\n", totalTimeB/100);
        printf("Average runtime for workload C %d milliseconds\n", totalTimeC/100);
        printf("Average runtime for workload D %d milliseconds\n", totalTimeD/100);
        printf("Average runtime for workload E %d milliseconds\n", totalTimeE/100);
        printf("Average runtime for workload F %d milliseconds\n", totalTimeF/100);



//printf("DONE Testing!");

return 0;
}
