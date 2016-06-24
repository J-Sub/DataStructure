#include "Heap.h"

void HeapInit(Heap * ph, int size, PriorityComp pc)
{
    ph->numOfData = 0;
    ph->comp = pc;
    ph->pHeapArr = (void**)malloc(sizeof(void*) * size);
}

int HIsEmpty(Heap * ph)
{
    if(ph->numOfData == 0)
        return TRUE;
    else
        return FALSE;
}

int GetParentIDX(int idx)
{
    return idx/2;
}

int GetLChildIDX(int idx)
{
    return idx*2;
}

int GetRChildIDX(int idx)
{
    return GetLChildIDX(idx)+1;
}

int GetHiPriChildIDX(Heap * ph, int idx)
{
    if(GetLChildIDX(idx) > ph->numOfData)
        return 0;
    
    else if(GetLChildIDX(idx) == ph->numOfData)
        return GetLChildIDX(idx);
    
    else
    {
        
        if(ph->comp(ph->pHeapArr[GetLChildIDX(idx)],
                    ph->pHeapArr[GetRChildIDX(idx)]) < 0)
            return GetRChildIDX(idx);
        else
            return GetLChildIDX(idx);
    }
}

void HInsert(Heap * ph, void* pData)
{
    int idx = ph->numOfData+1;
    
    while(idx != 1)
    {
    
        if(ph->comp(pData, ph->pHeapArr[GetParentIDX(idx)]) > 0)
        {
            ph->pHeapArr[idx] = ph->pHeapArr[GetParentIDX(idx)];
            idx = GetParentIDX(idx);
        }
        else
        {
            break;
        }
    }
    
    ph->pHeapArr[idx] = pData;
    ph->numOfData += 1;
}

void* HDelete(Heap * ph)
{
    void* retData = ph->pHeapArr[1];
    void* lastElem = ph->pHeapArr[ph->numOfData];
    
    int parentIdx = 1;
    int childIdx;
    
    while((childIdx = GetHiPriChildIDX(ph, parentIdx)))
    {
        if(ph->comp(lastElem, ph->pHeapArr[childIdx]) >= 0)
            break;
        
        ph->pHeapArr[parentIdx] = ph->pHeapArr[childIdx];
        parentIdx = childIdx;
    }
    
    ph->pHeapArr[parentIdx] = lastElem;
    ph->numOfData -= 1;
    return retData;
}

void HeapDestroy(Heap* ph){
    free(ph->pHeapArr);
}