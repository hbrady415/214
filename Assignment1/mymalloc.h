#ifndef _mymalloc_h

#define _mymalloc_h

 

#define malloc(x) mymalloc(x, __FILE__,  __LINE__)

#define free(x) myfree(x, __FILE__, __LINE__)

#define MSIZE 4096


static char mem[MSIZE];



typedef struct Node{ 

unsigned short data;
struct Node* next;
 

}Node;

 

void* mymalloc(size_t size, char* file, int line);

 

void myfree(void* ptr, char *file,int line);

 

void data();

 

#endif
