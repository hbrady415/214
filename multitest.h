#ifndef _multitest_h
#define _multitest_h


//#define search(x,y) searchTingThread(x,y)
#define searchThread2(x,y,z,q) searchThreads(x,y,z,q)
#define searchProc2(x,y,z,q) searchProcs(x,y,z,q)
void searchThreads(int numArrays,int arraySize,int key,int**masterList);
void searchProcs(int numArrays,int arraySize,int key,int** masterList);



//void searchTing(int numArrays,int key);



#endif
