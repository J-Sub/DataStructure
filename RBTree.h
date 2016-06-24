#ifndef RBT_H
#define RBT_H

#include <stdio.h>
#include <stdlib.h>

typedef struct _Node{
    struct _Node *pParent;
    struct _Node *pLeft;
    struct _Node *pRight;
    
    enum {Red,Black} Color;
    
    //노드 식별코드와 추가 데이터
    int iID;
    void *pData;
} Node;

//레드블랙트리 관련 함수
void RBT_DestroyTree(Node *pTree);

Node* RBT_CreateNode(int iID,void *pData);

void RBT_DestroyNode(Node *pNode);

Node* RBT_SearchNode(Node *pTree, int iTargetID);

Node* RBT_SearchMinNode(Node *pTree);

void RBT_InsertNode(Node **pTree, Node *pNewNode);

void RBT_InsertNodeHelper(Node **pTree,Node *pNewNode);

Node* RBT_RemoveNode(Node **pRoot, int iID);

void RBT_RebuildAfterInsert(Node **pTree, Node *pNewNode);

void RBT_RebuildAfterRemove(Node **pRoot, Node *pSuccessor);


void RBT_PrintTree(Node *pNode, int iDepth, int iBlackCount);

void RBT_RotateLeft(Node **Root, Node *pParent);

void RBT_RotateRight(Node **pRoot, Node *pParent);

void RBT_Inorder( Node *pNode, void *pData, void (*fnConduct)(Node *pNode,void *pData) );


#endif