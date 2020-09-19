#include <stdio.h>
#include <stdlib.h>
#include "mymalloc.h"


void* mymalloc(size_t size,char* FILE,int line){
printf("\n%d\n", size);
//printf("\nPUTERRORHERE->FILE: %s ->LINE:%d",FILE,line);
if (size<1){
printf("\nerror:(need size>=1)\nin %s at line%d",FILE,line);
return NULL;
}

if (size>4094){
printf("\nerror:(need size<=4094)\nin %s at line%d",FILE,line);
return NULL;
}
/*
//print graph
printf("\n\n");
int k=0;
char yup='0';
while (k<100){
yup=mem[k];
printf(".%d",yup);
k=k+1;
}
*/


//printf("\n\nEntered MyMalloc");
//printf("%d",mem[268]);
//printf("%d",mem[7]);
//mem[0]=size;
unsigned short sizeT=(unsigned short) size; 
int j=0;
int gate=1;
int count=-1;
int start=-1;
int end=-1;
int safe=0;
unsigned short calcSize=0;
unsigned short small=0;
unsigned short large=0;
char l1=0;
char o2=0;
char l2=0;

while (j<4096){
gate=1;
small=0;
large=0;
calcSize=0;
	if (j>=4096){
	printf("cool");
	break;
	}
//printf("\n\n\nnextMemCheck:%d",mem[j+1]);

//printf("\nj:%d{}memJ:%d\n",j,mem[j]);
if (mem[j]!=0){
small=mem[j];
//printf("\nsaml2:%d",small);
if ((char)small<0){
small=small+256;
//printf("\nsaml:%d",small);
}
large=mem[j+1];
large=large<<8;
calcSize=small+large;
//printf("\nsmall:%d\nlarge:%d\ncalcSize:%d\nj:%d", small, large, calcSize, j);
j=j+2+calcSize;
//printf("jJumpFront:%d",j);
//possible>4096?
continue;
}

	if (mem[j]==0){
	//lookForSpace
	count=0;
	start=j;
	//printf("size?%d",sizeT);
	//printf("\n\nstart:%d",start);
	while(count<(sizeT+2)){
		//printf("\ncount:%d",count);
		if (j>=4096){
		printf("cool");
		break;
		}	
	//printf("%dsozeT:%d",count,sizeT+2);

	//printf("\nmemj:%d",mem[j]);

	//MIGHT NEVER REACH?
			if(mem[j]!=0){
			gate=0;			
	//printf("\n\nj:%d\nchecker:%d\n\n",j,mem[j]);
			small=mem[j];
			large=mem[j+1];
	//printf("\n\nlarge:%d",large);
			large=large<<8;
			calcSize=small+large;
			//printf("\nsmall:%d\nlarge:%d\ncalcSize:%d\nj:%d", small, large, calcSize, j);
			j=j+2+calcSize;
			//printf("jJump?:%d",j);
			break;
			}
		j=j+1;
		count=count+1;	
		}
	if (gate==0){
	continue;
	}
	}
	if(j>4096){
	break;	
	}

	//printf("\ncount:%d sizeT:%d",count,sizeT);
	if (count==(sizeT+2)){

	//soft as a shell
	if(mem[start+8]!=0 || mem[start+9]!=0 || mem[start+10]!=0){
	l1=mem[start+8];
	o2=mem[start+9];
	l2=mem[start+10];
	}
	large=sizeT>>8;
	small=sizeT<<8;
	small=small>>8;


	//printf("\nsmall:%d\nlarge:%d",small,large);
	//printf("\nfoundBlock!");
	mem[start]=small;
	mem[start+1]=large;
	//printf("\n\nsmallInMem:%d",mem[start]);
	//printf("\nlargeInMem:%d",mem[start+1]);
	
	//THE KEY
	safe=start+1;
	//printf("\nsmalllargestartsafe%d,%d,%d,%d",small,large,start,safe);
	Node small1={small};
	*(Node*)(mem+start)=small1;
	Node* smallPtr=(Node*)(mem+start);

	Node large1={large};
	*(Node*)(mem+safe)=large1;
	Node* largePtr=(Node*)(mem+safe);
	smallPtr->next=largePtr;

	//printf("\n%p;;\n%p",smallPtr,largePtr);
	
	//HARD AS A ROCK
	if(l1==0 && l2==0 && o2==0){
	mem[start+8]=0;
	mem[start+9]=0;
	mem[start+10]=0;
	}
	if(l1!=0 || l2!=0 || o2!=0){
		mem[start+8]=l1;
		mem[start+9]=o2;
		mem[start+10]=l2;
	}
	return smallPtr;
	}
}

printf("\nerror:(NotEnoughSpace)\nin %s at line%d",FILE,line);
//maybe add helpul print statement about 
//space left

return NULL;
}


void myfree(void* p,char* file,int line){
//printf("\n\nEnetered MyFree");
//printf("memoryCheck:%p",mem[0]);
//printf("\n%d",mem[0]);
printf("\n\nfree start");
/*
int k=0;
char yup='0';
while (k<100){
yup=mem[k];
printf(".%d",yup);
k=k+1;
}
*/


if (p==NULL){
printf("\nerror:(Not Sending In An Allocated Ptr)\nin %s at line%d",file,line);
return;
}




//PreErrorChecksHere
int found=0;
int i=0;
int temp=-1;
int q=0;
int count2=0;
unsigned short sizeT=0;
unsigned short small=0;
unsigned short large=0;
while (i<4096){
	if (p==&mem[i]){
	//FREE!!!
	if (mem[i]==0){
	printf("\nerror:(Trying to free something we've freed before)\nin %s at line%d",file,line);
	return;
	}
	//printf("FreeThisBitch");
	//printf("\n%d",mem[i]);
	//findSize
	small=mem[i];
	large=mem[i+1];
	if ((char) small< 0){
	small=small+256;
	//printf("\n\nsmallRN:%d",small);
	}
	//printf("\nlargeInMemFree:%d",mem[i+1]);
	//printf("\nlargeFree:%d",large);
	large=large<<8;
	sizeT=small+large;
	//printf("\nsmall:%d\nlarge:%d\nsizeT:%d",small,large,sizeT);
	temp=sizeT+2;
	q=i;
	count2=0;
		while (temp>0){
		mem[i]=0;
		i=i+1;
		temp=temp-1;	\
		count2=count2+1;
		}
//printf("\n\nFREEDCOUNT:%d\n\n",count2);
	//printf("\nfreed:%d\n%d",i,mem[q]);
	break;
	}


		if (mem[i]!=0){
		//find Size and skip
		small=mem[i];
		large=mem[i+1];
		large=large<<8;
		sizeT=small+large;
		i=i+sizeT;
		//printf("\nfreeJump-i:%d\nsizeT:%d",i,sizeT);	
		continue;	
		}
		if (mem[i]==0){
		i=i+1;		
		}
}
//print what we change

//ErrorChecks

return;
}

