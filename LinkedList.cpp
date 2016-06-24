#include "LinkedList.h"


void LN_InsertNode(LinkedNode **pHead, void* pData){
    //새로운 노드를 추가한다.
    LinkedNode* pNewNode = (LinkedNode*)malloc(sizeof(LinkedNode));
    pNewNode->pData = pData;
    pNewNode->pNext = NULL;
    
    //만약 헤드가 없으면 새로운 노드를 헤드로 만든다.
    if(*pHead == NULL)
        *pHead = pNewNode;
    else{
        LinkedNode *pCurrentNode = *pHead;
        
        while(pCurrentNode->pNext != NULL)
            pCurrentNode = pCurrentNode->pNext;
        
        pCurrentNode->pNext = pNewNode;
    }
};

void LN_DeleteNode(LinkedNode **pHead,LinkedNode* pNode){
    
    if(*pHead == NULL || pNode == NULL){
        return;
    }
    
    LinkedNode *pCurrentNode = (*pHead);
    LinkedNode* pDeleted;
    
    //만약 지우려는 노드와 헤드와 같다면
    if(pCurrentNode == pNode){
        pDeleted = (*pHead);
        
        *pHead = (*pHead)->pNext;
    }else{
        while(pCurrentNode->pNext != NULL){
            if(pCurrentNode->pNext == pNode){
                pDeleted = pCurrentNode->pNext;
                
                pCurrentNode->pNext = pCurrentNode->pNext->pNext;
                
                break;
            }
            
            pCurrentNode = pCurrentNode->pNext;
        }
    }
    
    free(pDeleted);
}