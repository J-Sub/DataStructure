#include "RBTree.h"

extern Node *Nil;

void RBT_DestroyTree(Node *pTree){
    if(pTree == NULL)
        return;
    
    if( pTree->pRight != Nil )
        RBT_DestroyTree( pTree->pRight );
    
    if( pTree->pLeft != Nil )
        RBT_DestroyTree( pTree->pLeft );
    
    pTree->pLeft = Nil;
    pTree->pRight = Nil;
    
    RBT_DestroyNode( pTree );
}

Node* RBT_CreateNode(int iID, void *pData){
    Node *pNewNode = (Node*)malloc(sizeof(Node));
    pNewNode->pParent = NULL;
    pNewNode->pLeft = NULL;
    pNewNode->pRight = NULL;
    pNewNode->iID = iID;
    pNewNode->pData = pData;
    pNewNode->Color = _Node::Black;
    
    return pNewNode;
}


void RBT_DestroyNode(Node *pNode){
    free(pNode);
}

Node* RBT_SearchNode(Node *pTree, int iTargetID){
    if(pTree == Nil)
        return NULL;
    
    //데이터 정렬 방식
    if( pTree->iID > iTargetID )
        return RBT_SearchNode(pTree->pLeft, iTargetID);
    else if(pTree->iID < iTargetID)
        return RBT_SearchNode(pTree->pRight, iTargetID);
    else
        return pTree;
    
}

Node* RBT_SearchMinNode(Node *pTree){
    if(pTree == Nil)
        return Nil;
    
    if(pTree->pLeft == Nil)
        return pTree;
    else
        return RBT_SearchMinNode(pTree->pLeft);
}

void RBT_InsertNode(Node **pTree, Node *pNewNode){
    RBT_InsertNodeHelper(pTree, pNewNode);
    
    pNewNode->Color = _Node::Red;
    pNewNode->pLeft = Nil;
    pNewNode->pRight = Nil;
    
    RBT_RebuildAfterInsert(pTree, pNewNode);
}

void RBT_InsertNodeHelper(Node **pTree,Node *pNewNode){
    if( (*pTree) == NULL )
        (*pTree) = pNewNode;
    
    //데이터 정렬 방식
    if( (*pTree)->iID < pNewNode->iID ){
        if( (*pTree)->pRight == Nil ){
            (*pTree)->pRight = pNewNode;
            pNewNode->pParent = (*pTree);
        }else
            RBT_InsertNodeHelper( &(*pTree)->pRight, pNewNode );
    }else if( (*pTree)->iID > pNewNode->iID ){
        if( (*pTree)->pLeft == Nil ){
            (*pTree)->pLeft = pNewNode;
            pNewNode->pParent = (*pTree);
        }else
            RBT_InsertNodeHelper( &(*pTree)->pLeft, pNewNode );
    }
}

Node* RBT_RemoveNode(Node **pRoot, int iID){
    Node *pRemoved = NULL;
    Node *pSuccessor = NULL;
    Node *pTarget = RBT_SearchNode( (*pRoot), iID );
    
    if( pTarget == NULL )
        return NULL;
    
    if( pTarget->pLeft == Nil || pTarget->pRight == Nil )
        pRemoved = pTarget;
    else{
        pRemoved = RBT_SearchMinNode( pTarget->pRight );
        pTarget->pData = pRemoved->pData;
        pTarget->iID = pRemoved->iID;
    }
    
    if( pRemoved->pLeft != Nil )
        pSuccessor = pRemoved->pLeft;
    else
        pSuccessor = pRemoved->pRight;
    
    pSuccessor->pParent = pRemoved->pParent;
    
    if(pRemoved->pParent == NULL){
        (*pRoot) = pSuccessor;
    }else{
        if( pRemoved == pRemoved->pParent->pLeft )
            pRemoved->pParent->pLeft = pSuccessor;
        else
            pRemoved->pParent->pRight = pSuccessor;
    }
    
    if(pRemoved->Color == _Node::Black)
        RBT_RebuildAfterRemove( pRoot, pSuccessor );
    
    
    return pRemoved;
}

void RBT_RebuildAfterInsert(Node **pTree, Node *pNewNode){
    while( pNewNode != (*pTree) && pNewNode->pParent->Color == _Node::Red){
        if(pNewNode->pParent == pNewNode->pParent->pParent->pLeft){
            Node* pUncle = pNewNode->pParent->pParent->pRight;
            
            if(pUncle->Color == _Node::Red){
                pNewNode->pParent->Color = _Node::Black;
                pUncle->Color = _Node::Black;
                pNewNode->pParent->pParent->Color = _Node::Red;
                
                pNewNode = pNewNode->pParent->pParent;
            }else{
                if(pNewNode == pNewNode->pParent->pRight){
                    pNewNode = pNewNode->pParent;
                    RBT_RotateLeft( pTree, pNewNode );
                }
                
                pNewNode->pParent->Color = _Node::Black;
                pNewNode->pParent->pParent->Color = _Node::Red;
                
                RBT_RotateRight( pTree , pNewNode->pParent->pParent );
            }
        }else{
            Node *pUncle = pNewNode->pParent->pParent->pLeft;
            
            if(pUncle->Color == _Node::Red){
                pNewNode->pParent->Color = _Node::Black;
                pUncle->Color = _Node::Black;
                pNewNode->pParent->pParent->Color = _Node::Red;
                
                pNewNode = pNewNode->pParent->pParent;
            }else{
                if( pNewNode == pNewNode->pParent->pLeft ){
                    pNewNode = pNewNode->pParent;
                    RBT_RotateRight( pTree , pNewNode );
                }
                
                pNewNode->pParent->Color = _Node::Black;
                pNewNode->pParent->pParent->Color = _Node::Red;
                RBT_RotateLeft( pTree, pNewNode->pParent->pParent );
            }
        }
    }
    
    (*pTree)->Color = _Node::Black;
}

void RBT_RebuildAfterRemove(Node **pRoot, Node *pSuccessor){
    Node *pSibling = NULL;
    
    while( pSuccessor->pParent != NULL && pSuccessor->Color == _Node::Black){
        if(pSuccessor == pSuccessor->pParent->pLeft){
            pSibling = pSuccessor->pParent->pRight;
            
            if(pSibling->Color == _Node::Red){
                pSibling->Color = _Node::Black;
                pSuccessor->pParent->Color = _Node::Red;
                RBT_RotateLeft(pRoot, pSuccessor->pParent);
                //pSibling = pSuccessor->pParent->pRight;
            }else{
                if(pSibling->pLeft->Color == _Node::Black && pSibling->pRight->Color == _Node::Black){
                    pSibling->Color = _Node::Red;
                    pSuccessor = pSuccessor->pParent;
                }else{
                    if(pSibling->pLeft->Color == _Node::Red){
                        pSibling->pLeft->Color = _Node::Black;
                        pSibling->Color = _Node::Red;
                        
                        RBT_RotateRight(pRoot, pSibling);
                        pSibling = pSuccessor->pParent->pRight;
                    }
                    
                    pSibling->Color = pSuccessor->pParent->Color;
                    pSuccessor->pParent->Color = _Node::Black;
                    pSibling->pRight->Color = _Node::Black;
                    RBT_RotateLeft(pRoot, pSuccessor->pParent);
                    pSuccessor = (*pRoot);
                }
            }
        }else{
            pSibling = pSuccessor->pParent->pLeft;
            
            if(pSibling->Color == _Node::Red){
                pSibling->Color = _Node::Black;
                pSuccessor->pParent->Color = _Node::Red;
                RBT_RotateRight(pRoot, pSuccessor->pParent);
                //pSibling = pSuccessor->pParent->pLeft;
            }else{
                if( pSibling->pRight->Color == _Node::Black && pSibling->pLeft->Color == _Node::Black){
                    pSibling->Color = _Node::Red;
                    pSuccessor = pSuccessor->pParent;
                }else{
                    if(pSibling->pRight->Color == _Node::Red){
                        pSibling->pRight->Color = _Node::Black;
                        pSibling->Color = _Node::Red;
                        
                        RBT_RotateLeft(pRoot, pSibling);
                        pSibling = pSuccessor->pParent->pLeft;
                    }
                    
                    pSibling->Color = pSuccessor->pParent->Color;
                    pSuccessor->pParent->Color = _Node::Black;
                    pSibling->pLeft->Color = _Node::Black;
                    RBT_RotateRight(pRoot, pSuccessor->pParent);
                    pSuccessor = (*pRoot);
                }
            }
        }
    }
    
    pSuccessor->Color = _Node::Black;
}




void RBT_RotateLeft(Node **pRoot, Node *pParent){
    Node *pRightChild = pParent->pRight;
    
    pParent->pRight = pRightChild->pLeft;
    
    if(pRightChild->pLeft != Nil)
        pRightChild->pLeft->pParent = pParent;
    
    pRightChild->pParent = pParent->pParent;
    
    if(pParent->pParent == NULL)
        (*pRoot) = pRightChild;
    else{
        if(pParent == pParent->pParent->pLeft)
            pParent->pParent->pLeft = pRightChild;
        else
            pParent->pParent->pRight = pRightChild;
    }
    pRightChild->pLeft = pParent;
    pParent->pParent = pRightChild;
}

void RBT_RotateRight(Node **pRoot, Node *pParent){
    Node *pLeftChild = pParent->pLeft;
    
    pParent->pLeft = pLeftChild->pRight;
    
    if(pLeftChild->pRight != Nil)
        pLeftChild->pRight->pParent = pParent;
    
    pLeftChild->pParent = pParent->pParent;
    
    if(pParent->pParent == NULL)
        (*pRoot) = pLeftChild;
    else{
        if(pParent == pParent->pParent->pLeft)
            pParent->pParent->pLeft = pLeftChild;
        else
            pParent->pParent->pRight = pLeftChild;
    }
    pLeftChild->pRight = pParent;
    pParent->pParent = pLeftChild;
}

void RBT_PrintTree(Node *pNode, int iDepth, int iBlackCount){
    int i=0;
    char c = 'X';
    int v = -1;
    char cnt[100];
    
    if(pNode == NULL || pNode == Nil)
        return;
    
    if(pNode->Color == _Node::Black)
        iBlackCount++;
    
    if(pNode->pParent != NULL){
        v = pNode->pParent->iID;
        
        if(pNode->pParent->pLeft == pNode)
            c = 'L';
        else
            c = 'R';
    }
    
    if(pNode->pLeft == Nil && pNode->pRight == Nil)
        sprintf(cnt,"--------- %d",iBlackCount);
    else
        sprintf(cnt,"");
    
    for(i=0;i<iDepth;i++)
        printf("   ");
    
    printf("%d %s [%c, %d] %s\n", pNode->iID,
           (pNode->Color == _Node::Red)?"Red":"Black",c,v,cnt);
    
    RBT_PrintTree( pNode->pLeft, iDepth+1, iBlackCount);
    RBT_PrintTree( pNode->pRight, iDepth+1, iBlackCount);
    
}

void RBT_Inorder( Node *pNode, void *pData, void (*fnConduct)(Node *pNode,void *pData) ){
    if(pNode == NULL || pNode == Nil)
        return;
    
    RBT_Inorder(pNode->pLeft, pData, fnConduct);
    
    fnConduct(pNode, pData);
    
    RBT_Inorder(pNode->pRight, pData, fnConduct);
}