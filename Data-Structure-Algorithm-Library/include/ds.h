#ifndef DS_H
#define DS_H 1234
#include<common.h>
// structure definations of stack and stackNode
typedef struct __stackNode__
{
void *ptr;
struct __stackNode__ *next;
}StackNode;
typedef struct __Stack__
{
StackNode *node;
int size;
int sizeOfOneElement;
}Stack;

// stack related functionality
Stack * createStack(int,OperationDetail *);
void pushOnStack(struct __Stack__ *,const void *,OperationDetail *);
void popFromStack(struct __Stack__ *,void *,OperationDetail *);
int isStackEmpty(struct __Stack__ *);
void clearStack(struct __Stack__ *);
void destroyStack(struct __Stack__ *);
void elementAtTopOfStack(struct __Stack__ *,void *,OperationDetail *);
// structure definations of queue and queueNode

typedef struct __Queue_Node__
{
void *ptr;
struct __Queue_Node__ *next;
}QueueNode;
typedef struct __Queue__
{
QueueNode *front;
QueueNode *rear;
int size;
int sizeOfOneElement;
}Queue;
// queue related functionality
Queue * createQueue(int,OperationDetail *);
void addToQueue(struct __Queue__ *,const void *,OperationDetail *);
void removeFromQueue(struct __Queue__ *,void *,OperationDetail *);
int isQueueEmpty(struct __Queue__ *);
void clearQueue(struct __Queue__ *);
void destroyQueue(struct __Queue__ *);

// structure definations of SinglyLinkedListNode, SinglyLinkedList, and SinglyLinkedListIterator

typedef struct __$__sll_node
{
void *ptr;
struct __$__sll_node *next;
}SinglyLinkedListNode;

typedef struct __$__sll
{
struct __$__sll_node *start;
struct __$__sll_node *end;
int sizeOfOneElement;
int size;
}SinglyLinkedList;

typedef struct __$__sll_iterator
{
SinglyLinkedListNode *node;
int sizeOfOneElement;
}SinglyLinkedListIterator;

// SinglyLinkedList related functionality

SinglyLinkedList * createSinglyLinkedList(int,OperationDetail *);
void clearSinglyLinkedList(SinglyLinkedList *);
void destroySinglyLinkedList(SinglyLinkedList *);
int getSizeOfSinglyLinkedList(SinglyLinkedList *);
void addToSinglyLinkedList(SinglyLinkedList *,void *,OperationDetail *);
void insertIntoSinglyLinkedList(SinglyLinkedList *,int,void *,OperationDetail *);
void removeFromSinglyLinkedList(SinglyLinkedList *,void *,int,OperationDetail *);
void appendToSinglyLinkedList(SinglyLinkedList *,SinglyLinkedList *,OperationDetail *);
void getFromSinglyLinkedList(SinglyLinkedList *,void *,int,OperationDetail *);
SinglyLinkedListIterator getSinglyLinkedListIterator(SinglyLinkedList *,OperationDetail *);
bool hasNextInSinglyLinkedList(SinglyLinkedListIterator *);
void getNextElementFromSinglyLinkedList(SinglyLinkedListIterator *,void *,OperationDetail *);


// structure definations of DoublyLinkedList, DoublyLinkedListNode, DoublyLinkedListIterator and DoublyLinkedListReverseIterator.

typedef struct __$__DoublyLinkedListNode
{
void *ptr;
struct __$__DoublyLinkedListNode *next;
struct __$__DoublyLinkedListNode *previous;
}DoublyLinkedListNode;

typedef struct __$__DoublyLinkedList
{
DoublyLinkedListNode *start;
DoublyLinkedListNode *end;
int size;
int sizeOfOneElement;
}DoublyLinkedList;

typedef struct __$__DoublyLinkedListIterator
{
DoublyLinkedListNode *node;
int sizeOfOneElement;
}DoublyLinkedListIterator;

typedef struct __$__DoublyLinkedListReverseIterator
{
DoublyLinkedListNode *node;
int sizeOfOneElement;
}DoublyLinkedListReverseIterator;

// DoublyLinkedList related functionality
DoublyLinkedList * createDoublyLinkedList(int,OperationDetail *);
int getSizeOfDoublyLinkedList(DoublyLinkedList *);
void clearDoublyLinkedList(DoublyLinkedList *);
void destroyDoublyLinkedList(DoublyLinkedList *);
void addToDoublyLinkedList(DoublyLinkedList *,const void *,OperationDetail *);
void insertIntoDoublyLinkedList(DoublyLinkedList *,int,const void *,OperationDetail *);
void removeFromDoublyLinkedList(DoublyLinkedList *,void *,int,OperationDetail *);
void appendToDoublyLinkedList(DoublyLinkedList *,DoublyLinkedList *,OperationDetail *);
void getFromDoublyLinkedList(DoublyLinkedList *,void *,int,OperationDetail *);
DoublyLinkedListIterator getDoublyLinkedListIterator(DoublyLinkedList *,OperationDetail *);
bool hasNextInDoublyLinkedList(DoublyLinkedListIterator *); 
void getNextElementFromDoublyLinkedList(DoublyLinkedListIterator *,void *,OperationDetail *);
DoublyLinkedListReverseIterator getDoublyLinkedListReverseIterator(DoublyLinkedList *,OperationDetail *);
bool hasPreviousInDoublyLinkedList(DoublyLinkedListReverseIterator *); 
void getPreviousElementFromDoublyLinkedList(DoublyLinkedListReverseIterator *,void *,OperationDetail *);

// structure defination of AVLTree

typedef struct __$_my_avl_tree_node
{
void *ptr;
struct __$_my_avl_tree_node *left;
struct __$_my_avl_tree_node *right;
}AVLTreeNode;
typedef struct __$_my_avl_tree
{
struct __$_my_avl_tree_node *start;
int (*predicate)(void *,void *);
int size;
}AVLTree;

typedef struct __$__my_avl_tree_in_order_iterator
{
AVLTreeNode *node;
Stack *stack;
}AVLTreeInOrderIterator;

typedef struct __$__my_avl_tree_pre_order_iterator
{
AVLTreeNode *node;
Stack *stack;
}AVLTreePreOrderIterator;

typedef struct __$__my_avl_tree_post_order_iterator
{
AVLTreeNode *node;
Stack *stack;
}AVLTreePostOrderIterator;
// structure defination of AVLTree ends

// function declaration of AVLTree starts
AVLTree * createAVLTree(OperationDetail *,int (*)(void *,void *));
void destroyAVLTree(AVLTree *);
int getSizeOfAVLTree(AVLTree *);
void addToAVLTree(AVLTree *,void *,OperationDetail *);
void insertIntoAVLTree(AVLTree *,void *,OperationDetail *);
void * removeFromAVLTree(AVLTree *,void *,OperationDetail *);
void clearAVLTree(AVLTree *);
void * getFromAVLTree(AVLTree *,void *,OperationDetail *);
AVLTreeInOrderIterator getAVLTreeInOrderIterator(AVLTree *,OperationDetail *);
bool hasNextInOrderElementInAVLTree(AVLTreeInOrderIterator *); 
void * getNextInOrderElementFromAVLTree(AVLTreeInOrderIterator *,OperationDetail *);
AVLTreePreOrderIterator getAVLTreePreOrderIterator(AVLTree *,OperationDetail *);
bool hasNextPreOrderElementInAVLTree(AVLTreePreOrderIterator *); 
void * getNextPreOrderElementFromAVLTree(AVLTreePreOrderIterator *,OperationDetail *);
AVLTreePostOrderIterator getAVLTreePostOrderIterator(AVLTree *,OperationDetail *);
bool hasNextPostOrderElementInAVLTree(AVLTreePostOrderIterator *); 
void * getNextPostOrderElementFromAVLTree(AVLTreePostOrderIterator *,OperationDetail *);
int getHeightOfAVLTree(AVLTreeNode *);
void balanceAVLTree(AVLTree *,Stack *);
// function declaration of AVLTree ends
#endif
