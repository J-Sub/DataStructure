#ifndef LinkedList_h
#define LinkedList_h

#include <stdio.h>
#include <stdlib.h>

//링크드리스트 노드
typedef struct _LinkedNode{
    void* pData;
    
    struct _LinkedNode* pNext;
} LinkedNode;

//링크드리스트에 새로운 노드를 추가한다.
void LN_InsertNode(LinkedNode **pHead, void* pData);

void LN_DeleteNode(LinkedNode **pHead,LinkedNode* pNode);


#endif