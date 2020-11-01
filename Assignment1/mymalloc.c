#include <stdio.h>
#include <stdlib.h>
#include "mymalloc.h"


void* mymalloc(size_t size,char* FILE,int line){
printf("\n%d\n", size);
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
if (mem[j]!=0){
	small=mem[j];
	if ((char)small<0){
		small=small+256;
	}
	large=mem[j+1];
	large=large<<8;
	calcSize=small+large;

	j=j+2+calcSize;
	continue;
}

	if (mem[j]==0){
	//lookForSpace
		count=0;
		start=j;
		while(count<(sizeT+2)){
			if (j>=4096){
				printf("cool");
				break;
			}	
			if(mem[j]!=0){
				gate=0;			
				small=mem[j];
				large=mem[j+1];
				large=large<<8;
				calcSize=small+large;
				j=j+2+calcSize;
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
	if (count==(sizeT+2)){
	//store data in order to rewrite over data that was shifted if these positions changed
		if(mem[start+8]!=0 || mem[start+9]!=0 || mem[start+10]!=0){
			l1=mem[start+8];
			o2=mem[start+9];
			l2=mem[start+10];
		}
		large=sizeT>>8;
		small=sizeT<<8;
		small=small>>8;
	mem[start]=small;
	mem[start+1]=large;
	
	//THE KEY; use LL to hold data 
	safe=start+1;
	Node small1={small};
	*(Node*)(mem+start)=small1;
	Node* smallPtr=(Node*)(mem+start);

	Node large1={large};
	*(Node*)(mem+safe)=large1;
	Node* largePtr=(Node*)(mem+safe);
	smallPtr->next=largePtr;
	//return to old data after shift
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
//only reach here if not enough space
printf("\nerror:(NotEnoughSpace)\nin %s at line%d",FILE,line);

return NULL;
}


void myfree(void* p,char* file,int line){
printf("\n\nfree start");


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
		//findSize
		small=mem[i];
		large=mem[i+1];
		if ((char) small< 0){
			small=small+256;
		}
		large=large<<8;
		sizeT=small+large;
		temp=sizeT+2;
		q=i;
		count2=0;
			while (temp>0){
				mem[i]=0;
				i=i+1;
				temp=temp-1;	\
				count2=count2+1;
			}
			break;
		}


		if (mem[i]!=0){
		//find Size and skip
			small=mem[i];
			large=mem[i+1];
			large=large<<8;
			sizeT=small+large;
			i=i+sizeT;
			continue;	
		}
		if (mem[i]==0){
			i=i+1;		
		}
}

return;
}

