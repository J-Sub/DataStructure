#ifndef Heap_h
#define Heap_h

#include <stdio.h>
#include <stdlib.h>
#include "RBTree.h"

#define TRUE	1
#define FALSE	0

#define HEAP_LEN	100

typedef int PriorityComp(void* left, void* right);

typedef struct _Heap
{
    PriorityComp * comp;
    int numOfData;
    void** pHeapArr;
} Heap;

void HeapInit(Heap * ph, int size, PriorityComp pc);
int HIsEmpty(Heap * ph);

void HInsert(Heap * ph, void* data);
void* HDelete(Heap * ph);

void HeapDestroy(Heap * ph);

#endif