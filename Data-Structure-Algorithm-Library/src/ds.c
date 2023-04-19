#ifndef DS_C
#define DS_C 1245
#include<common.h>
#include<ds.h>
#include<stdlib.h>
#include<string.h>
// just for testing
#include<stdio.h>
Stack * createStack(int sizeOfOneElement,OperationDetail *error)
{
Stack *stack;
if(error) error->succ=false;
if(sizeOfOneElement<=0)
{
if(error) error->code=7;
return NULL;
}
stack=(Stack *)malloc(sizeof(Stack));
if(stack==NULL)
{
if(error) error->code=2;
return NULL;
}
stack->node=NULL;
stack->size=0;
stack->sizeOfOneElement=sizeOfOneElement;
if(error)
{
error->succ=true;
error->code=0;
}
return stack;
}
void pushOnStack(struct __Stack__ *stack,const void *data,OperationDetail *error)
{
StackNode *node;
if(error) error->succ=false;
if(stack==NULL)
{
if(error) error->code=3;
return;
}
if(data==NULL)
{
if(error) error->code=4;
return;
}
node=(StackNode *)malloc(sizeof(StackNode));
if(node==NULL)
{
if(error) error->code=2;
return;
}
node->ptr=(void *)malloc(sizeof(stack->sizeOfOneElement));
if(node->ptr==NULL)
{
if(error) error->code=2;
free(node);
return;
}
memcpy(node->ptr,(const void *)data,stack->sizeOfOneElement);
node->next=stack->node;
stack->node=node;
stack->size++;
if(error)
{
error->code=0;
error->succ=true;
}
}
void popFromStack(struct __Stack__ *stack,void *data,OperationDetail *error)
{
StackNode *j;
if(error) error->succ=false;
if(stack==NULL)
{
if(error) error->code=3;
return;
}
if(data==NULL)
{
if(error) error->code=4;
return;
}
if(stack->node==NULL)
{
if(error) error->code=5;
return;
}
memcpy(data,(const void *)stack->node->ptr,stack->sizeOfOneElement);
free(stack->node->ptr);
j=stack->node;
stack->node=stack->node->next;
free(j);
stack->size--;
if(error)
{
error->code=0;
error->succ=true;
}
}
int isStackEmpty(struct __Stack__ *stack)
{
if(stack==NULL) return 0;
return stack->node==NULL;
}
void clearStack(struct __Stack__ *stack)
{
StackNode *j;
if(stack==NULL || stack->node==NULL) return;
while(stack->node!=NULL)
{
free(stack->node->ptr);
j=stack->node;
stack->node=stack->node->next;
free(j);
}
stack->size=0;
}

void destroyStack(struct __Stack__ *stack)
{
if(stack==NULL) return;
clearStack(stack);
free(stack);
}

void elementAtTopOfStack(struct __Stack__ *stack,void *ptr,OperationDetail *error)
{
if(error) error->succ=false;
if(isStackEmpty(stack))
{
ptr=NULL;
if(error)
{
error->succ=true;
error->code=0;
}
return;
}
memcpy(ptr,(const void *)stack->node->ptr,stack->sizeOfOneElement);
} // function ends

Queue * createQueue(int sizeOfOneElement,OperationDetail *error)
{
Queue *queue=NULL;
if(error) error->succ=false;
if(sizeOfOneElement<=0)
{
if(error) error->code=7;
return NULL;
}
queue=(Queue *)malloc(sizeof(Queue));
if(queue==NULL)
{
if(error) error->code=2;
return NULL;
}
queue->front=NULL;
queue->rear=NULL;
queue->size=0;
queue->sizeOfOneElement=sizeOfOneElement;
if(error)
{
error->succ=true;
error->code=0;
}
return queue;
}
void addToQueue(struct __Queue__ *queue,const void *data,OperationDetail *error)
{
QueueNode *node;
if(error) error->succ=false;
if(queue==NULL)
{
if(error) error->code=3;
return;
}
if(data==NULL)
{
if(error) error->code=4;
return;
}
node=(QueueNode *)malloc(sizeof(QueueNode));
if(node==NULL)
{
if(error) error->code=2;
return;
}
node->ptr=(void *)malloc(sizeof(queue->sizeOfOneElement));
if(node->ptr==NULL)
{
if(error) error->code=2;
free(node);
return;
}
memcpy(node->ptr,(const void *)data,queue->sizeOfOneElement);
if(queue->rear==NULL && queue->front==NULL)
{
queue->rear=node;
queue->front=node;
node->next=NULL;
queue->size++;
if(error)
{
error->code=0;
error->succ=true;
}
return;
}
queue->rear->next=node;
node->next=NULL;
queue->rear=node;
queue->size++;
if(error)
{
error->code=0;
error->succ=true;
}
}
void removeFromQueue(struct __Queue__ *queue,void *data,OperationDetail *error)
{
QueueNode *j;
if(error) error->succ=false;
if(queue==NULL)
{
if(error) error->code=3;
return;
}
if(data==NULL)
{
if(error) error->code=4;
return;
}
memcpy(data,(const void *)queue->front->ptr,queue->sizeOfOneElement);
free(queue->front->ptr);
j=queue->front;
queue->front=queue->front->next;
if(queue->front==NULL)
{
queue->rear=NULL;
queue->front=NULL;
}
free(j);
queue->size--;
if(error)
{
error->code=0;
error->succ=true;
}
}
int isQueueEmpty(struct __Queue__ *queue)
{
if(queue==NULL) return 0;
return queue->front==NULL;
}
void clearQueue(struct __Queue__ *queue)
{
QueueNode *j;
if(queue==NULL || queue->front!=NULL) return;
while(!isQueueEmpty(queue))
{
free(queue->front->ptr);
j=queue->front;
queue->front=queue->front->next;
free(j);
}
queue->size=0;
queue->front=NULL;
queue->rear=NULL;
}
void destroyQueue(struct __Queue__ *queue)
{
if(queue==NULL) return;
clearQueue(queue);
free(queue);
}
// implementation of singlyLinkedList
SinglyLinkedList * createSinglyLinkedList(int sizeOfOneElement,OperationDetail *error)
{
SinglyLinkedList *singlyLinkedList;
if(error) error->succ=false;
singlyLinkedList=(SinglyLinkedList *)malloc(sizeof(SinglyLinkedList));
if(singlyLinkedList==NULL)
{
if(error) error->code=2;
return NULL;
}
singlyLinkedList->start=NULL;
singlyLinkedList->end=NULL;
singlyLinkedList->size=0;
singlyLinkedList->sizeOfOneElement=sizeOfOneElement;
if(error)
{
error->succ=true;
error->code=0;
}
return singlyLinkedList;
} // function ends

void destroySinglyLinkedList(SinglyLinkedList *singlyLinkedList)
{
if(singlyLinkedList==NULL) return;
clearSinglyLinkedList(singlyLinkedList);
free(singlyLinkedList);
}

void clearSinglyLinkedList(SinglyLinkedList *singlyLinkedList)
{
SinglyLinkedListNode *node;
if(singlyLinkedList==NULL) return;
node=singlyLinkedList->start;
while(singlyLinkedList->start!=NULL)
{
node=singlyLinkedList->start;
singlyLinkedList->start=singlyLinkedList->start->next;
free(node->ptr);
free(node);
}
singlyLinkedList->end=NULL;
singlyLinkedList->size=0;
} // function ends

int getSizeOfSinglyLinkedList(SinglyLinkedList *singlyLinkedList)
{
if(singlyLinkedList==NULL) return 0;
return singlyLinkedList->size;
} // function ends

void addToSinglyLinkedList(SinglyLinkedList *singlyLinkedList,void *ptr,OperationDetail *error)
{
SinglyLinkedListNode *node;
if(error) error->succ=false;
if(singlyLinkedList==NULL)
{
if(error) error->code=3;
return;
}
node=(SinglyLinkedListNode *)malloc(sizeof(SinglyLinkedListNode));
if(node==NULL)
{
if(error) error->code=2;
return;
}
node->ptr=(void *)malloc(singlyLinkedList->sizeOfOneElement);
if(node->ptr==NULL)
{
if(error) error->code=2;
free(node);
return;
}
memcpy(node->ptr,(const void *)ptr,singlyLinkedList->sizeOfOneElement);
node->next=NULL;
if(singlyLinkedList->start==NULL)
{
singlyLinkedList->start=node;
singlyLinkedList->end=node;
}
else
{
singlyLinkedList->end->next=node;
singlyLinkedList->end=node;
}
singlyLinkedList->size++;;
if(error)
{
error->succ=true;
error->code=0;
}
} // function ends

void insertIntoSinglyLinkedList(SinglyLinkedList *singlyLinkedList,int index,void *ptr,OperationDetail *error)
{
SinglyLinkedListNode *node,*p1,*p2;
int x;
if(error) error->succ=false;
if(singlyLinkedList==NULL)
{
if(error) error->code=3;
return;
}
if(index<0 || index>singlyLinkedList->size)
{
if(error) error->code=9;
return;
}
if(index==singlyLinkedList->size)
{
addToSinglyLinkedList(singlyLinkedList,ptr,error);
return;
}
node=(SinglyLinkedListNode *)malloc(sizeof(SinglyLinkedListNode));
if(node==NULL)
{
if(error) error->code=2;
return;
}
node->ptr=(void *)malloc(singlyLinkedList->sizeOfOneElement);
if(node->ptr==NULL)
{
if(error) error->code=2;
free(node);
return;
}
memcpy(node->ptr,(const void *)ptr,singlyLinkedList->sizeOfOneElement);
node->next=NULL;
if(index==0)
{
node->next=singlyLinkedList->start;
singlyLinkedList->start=node;
singlyLinkedList->size++;
if(error)
{
error->succ=true;
error->code=0;
}
return;
}
p1=singlyLinkedList->start;
x=0;
while(x<index)
{
p2=p1;
p1=p1->next;
x++;
}
node->next=p1;
p2->next=node;
singlyLinkedList->size++;
if(error)
{
error->succ=true;
error->code=0;
}
} // function ends

void removeFromSinglyLinkedList(SinglyLinkedList *singlyLinkedList,void *ptr,int index,OperationDetail *error)
{
SinglyLinkedListNode *p1,*p2;
int x;
if(error) error->succ=false;
if(singlyLinkedList==NULL)
{
if(error) error->code=3;
return;
}
if(index<0 || index>=singlyLinkedList->size)
{
if(error) error->code=9;
return;
}
p1=singlyLinkedList->start;
x=0;
while(x<index)
{
p2=p1;
p1=p1->next;
x++;
}
memcpy(ptr,(const void *)p1->ptr,singlyLinkedList->sizeOfOneElement);
if(singlyLinkedList->start==p1 && singlyLinkedList->end==p1)
{
singlyLinkedList->start=NULL;
singlyLinkedList->end=NULL;
}
else if(singlyLinkedList->start==p1)
{
singlyLinkedList->start=singlyLinkedList->start->next;
}else if(singlyLinkedList->end==p1)
{
singlyLinkedList->end=p2;
singlyLinkedList->end->next=NULL;
}else
{
p2->next=p1->next;
}
free(p1->ptr);
free(p1);
singlyLinkedList->size--;
if(error)
{
error->succ=true;
error->code=0;
}
} // function ends

void appendToSinglyLinkedList(SinglyLinkedList *targetSinglyLinkedList,SinglyLinkedList *sourceSinglyLinkedList,OperationDetail *error)
{
SinglyLinkedListNode *s,*e,*t,*node;
bool done;
if(error) error->succ=false;
if(targetSinglyLinkedList==NULL)
{
if(error) error->code=3;
return;
}
if(sourceSinglyLinkedList->sizeOfOneElement!=targetSinglyLinkedList->sizeOfOneElement)
{
if(error) error->code=10;
return;
}
if(sourceSinglyLinkedList==NULL || sourceSinglyLinkedList->size==0)
{
if(error)
{
error->succ=true;
error->code=0;
}
return;
}
s=NULL;
e=NULL;
done=true;
t=sourceSinglyLinkedList->start;
while(t!=NULL)
{
node=(SinglyLinkedListNode *)malloc(sizeof(SinglyLinkedListNode));
if(node==NULL)
{
done=false;
break;
}
node->ptr=(void *)malloc(sourceSinglyLinkedList->sizeOfOneElement);
if(node->ptr==NULL)
{
free(node);
done=false;
break;
}
memcpy(node->ptr,(const void *)t->ptr,sourceSinglyLinkedList->sizeOfOneElement);
node->next=NULL;
if(s==NULL)
{
s=node;
e=node;
}
else
{
e->next=node;
e=node;
}
t=t->next;
}
if(done==false)
{
while(s!=NULL)
{
node=s;
s=s->next;
free(node->ptr);
free(node);
}
if(error) error->code=2;
return;
}
if(targetSinglyLinkedList->start==NULL)
{
targetSinglyLinkedList->start=s;
targetSinglyLinkedList->end=e;
targetSinglyLinkedList->size=sourceSinglyLinkedList->size;
targetSinglyLinkedList->sizeOfOneElement=sourceSinglyLinkedList->sizeOfOneElement;
}
else
{
targetSinglyLinkedList->end->next=s;
targetSinglyLinkedList->end=e;
targetSinglyLinkedList->size+=sourceSinglyLinkedList->size;
}
if(error)
{
error->succ=true;
error->code=0;
}
} // function ends

void getFromSinglyLinkedList(SinglyLinkedList *singlyLinkedList,void *ptr,int index,OperationDetail *error)
{
SinglyLinkedListNode *node;
int x;
if(error) error->succ=false;
if(singlyLinkedList==NULL)
{
if(error) error->code=3;
return;
}
if(index<0 || index>=singlyLinkedList->size)
{
if(error) error->code=9;
return;
}
node=singlyLinkedList->start;
x=0;
while(x<index)
{
node=node->next;
x++;
}
memcpy(ptr,(const void *)node->ptr,singlyLinkedList->sizeOfOneElement);
if(error)
{
error->succ=true;
error->code=0;
}
} // function ends

SinglyLinkedListIterator getSinglyLinkedListIterator(SinglyLinkedList *singlyLinkedList,OperationDetail *error)
{
SinglyLinkedListIterator singlyLinkedListIterator;
singlyLinkedListIterator.node=NULL;
if(error) error->succ=false;
if(singlyLinkedList==NULL)
{
if(error) error->code=3;
return singlyLinkedListIterator;
}
if(singlyLinkedList->start==NULL) 
{
if(error)
{
error->succ=true;
error->code=0;
}
return singlyLinkedListIterator;
}
if(error)
{
error->succ=true;
error->code=0;
}
singlyLinkedListIterator.node=singlyLinkedList->start;
singlyLinkedListIterator.sizeOfOneElement=singlyLinkedList->sizeOfOneElement;
return singlyLinkedListIterator;  
} // function ends

bool hasNextInSinglyLinkedList(SinglyLinkedListIterator *singlyLinkedListIterator)
{
if(singlyLinkedListIterator==NULL) return false;
if(singlyLinkedListIterator->node==NULL) return false;
return true;
} // function ends

void getNextElementFromSinglyLinkedList(SinglyLinkedListIterator *singlyLinkedListIterator,void *ptr,OperationDetail *error)
{
if(error) error->succ=false;
if(singlyLinkedListIterator==NULL || singlyLinkedListIterator->node==NULL)
{
if(error) error->code=3;
return;
}
memcpy(ptr,(const void *)singlyLinkedListIterator->node->ptr,singlyLinkedListIterator->sizeOfOneElement);
singlyLinkedListIterator->node=singlyLinkedListIterator->node->next;
if(error)
{
error->code=0;
error->succ=true;
}
} // function ends

// implementation of Doubly Linked List
DoublyLinkedList * createDoublyLinkedList(int sizeOfOneElement,OperationDetail *error)
{
DoublyLinkedList *doublyLinkedList;
if(error) error->succ=false;
doublyLinkedList=(DoublyLinkedList *)malloc(sizeof(DoublyLinkedList));
if(doublyLinkedList==NULL)
{
if(error) error->code=2;
return NULL;
}
doublyLinkedList->start=NULL;
doublyLinkedList->end=NULL;
doublyLinkedList->size=0;
doublyLinkedList->sizeOfOneElement=sizeOfOneElement;
if(error)
{
error->succ=true;
error->code=0;
}
return doublyLinkedList;
}
int getSizeOfDoublyLinkedList(DoublyLinkedList *doublyLinkedList)
{
if(doublyLinkedList==NULL) return 0;
return doublyLinkedList->size;
}

void clearDoublyLinkedList(DoublyLinkedList *doublyLinkedList)
{
DoublyLinkedListNode *node;
if(doublyLinkedList==NULL) return;
node=doublyLinkedList->start;
while(doublyLinkedList->start!=NULL)
{
node=doublyLinkedList->start;
doublyLinkedList->start=doublyLinkedList->start->next;
free(node->ptr);
free(node);
}
doublyLinkedList->end=NULL;
doublyLinkedList->size=0;
}

void destroyDoublyLinkedList(DoublyLinkedList *doublyLinkedList)
{
if(doublyLinkedList==NULL) return;
clearDoublyLinkedList(doublyLinkedList);
free(doublyLinkedList);
}

void addToDoublyLinkedList(DoublyLinkedList *doublyLinkedList,const void *ptr,OperationDetail *error)
{
DoublyLinkedListNode *node;
if(error) error->succ=false;
if(doublyLinkedList==NULL) return;
node=(DoublyLinkedListNode *)malloc(sizeof(DoublyLinkedListNode));
if(node==NULL)
{
if(error) error->code=2;
return;
}
node->ptr=(void *)malloc(doublyLinkedList->sizeOfOneElement);
if(node->ptr==NULL)
{
free(node);
if(error) error->code=2;
return;
}
memcpy(node->ptr,(const void *)ptr,doublyLinkedList->sizeOfOneElement);
node->next=NULL;
node->previous=NULL;
if(doublyLinkedList->start==NULL)
{
doublyLinkedList->start=node;
doublyLinkedList->end=node;
}
else
{
doublyLinkedList->end->next=node;
node->previous=doublyLinkedList->end;
doublyLinkedList->end=node;
}
doublyLinkedList->size++;;
if(error)
{
error->succ=true;
error->code=0;
}
}

void insertIntoDoublyLinkedList(DoublyLinkedList *doublyLinkedList,int index,const void *ptr,OperationDetail *error)
{
DoublyLinkedListNode *node,*p1;
int x;
if(error) error->succ=false;
if(doublyLinkedList==NULL)
{
if(error) error->code=3;
return;
}
if(index<0 || index>doublyLinkedList->size)
{
if(error) error->code=9;
return;
}
if(index==doublyLinkedList->size)
{
addToDoublyLinkedList(doublyLinkedList,ptr,error);
return;
}
node=(DoublyLinkedListNode *)malloc(sizeof(DoublyLinkedListNode));
if(node==NULL)
{
if(error) error->code=2;
return;
}
node->ptr=(void *)malloc(doublyLinkedList->sizeOfOneElement);
if(node->ptr==NULL)
{
free(node);
if(error) error->code=2;
return;
}
memcpy(node->ptr,(const void *)ptr,doublyLinkedList->sizeOfOneElement);
node->next=NULL;
node->previous=NULL;
if(index==0)
{
node->next=doublyLinkedList->start;
doublyLinkedList->start->previous=node;
doublyLinkedList->start=node;
doublyLinkedList->size++;
if(error)
{
error->succ=true;
error->code=0;
}
return;
}
p1=doublyLinkedList->start;
x=0;
while(x<index)
{
p1=p1->next;
x++;
}
node->next=p1;
node->previous=p1->previous;
p1->previous->next=node;
p1->previous=node;
doublyLinkedList->size++;
if(error)
{
error->succ=true;
error->code=0;
}
}

void removeFromDoublyLinkedList(DoublyLinkedList *doublyLinkedList,void *ptr,int index,OperationDetail *error)
{
DoublyLinkedListNode *p1;
int x;
if(error) error->succ=false;
if(doublyLinkedList==NULL)
{
if(error) error->code=3;
return;
}
if(index<0 || index>doublyLinkedList->size)
{
if(error) error->code=9;
return;
}
p1=doublyLinkedList->start;
x=0;
while(x<index)
{
p1=p1->next;
x++;
}
memcpy(ptr,(const void *)p1->ptr,doublyLinkedList->sizeOfOneElement);
free(p1->ptr);
if(doublyLinkedList->start==p1 && doublyLinkedList->end==p1)
{
doublyLinkedList->start=NULL;
doublyLinkedList->end=NULL;
}
else if(doublyLinkedList->start==p1)
{
doublyLinkedList->start=doublyLinkedList->start->next;
doublyLinkedList->start->previous=NULL;
}else if(doublyLinkedList->end==p1)
{
doublyLinkedList->end=doublyLinkedList->end->previous;
doublyLinkedList->end->next=NULL;
}else
{
p1->previous->next=p1->next;
p1->next->previous=p1->previous;
}
free(p1);
doublyLinkedList->size--;
if(error) error->code=0;
} // function ends

void appendToDoublyLinkedList(DoublyLinkedList *targetDoublyLinkedList,DoublyLinkedList * sourceDoublyLinkedList,OperationDetail *error)
{
DoublyLinkedListNode *s,*e,*t,*node;
bool done;
if(error) error->succ=false;
if(targetDoublyLinkedList==NULL)
{
if(error) error->code=3;
return;
}
if(sourceDoublyLinkedList==NULL || sourceDoublyLinkedList->size==0)
{
if(error) error->code=3;
return;
}
if(sourceDoublyLinkedList->sizeOfOneElement!=targetDoublyLinkedList->sizeOfOneElement)
{
if(error) error->code=10;
return;
}
s=NULL;
e=NULL;
done=true;
t=sourceDoublyLinkedList->start;
while(t!=NULL)
{
node=(DoublyLinkedListNode *)malloc(sizeof(DoublyLinkedListNode));
if(node==NULL)
{
done=false;
break;
}
node->ptr=(void *)malloc(sourceDoublyLinkedList->sizeOfOneElement);
if(node->ptr==NULL)
{
free(node);
done=false;
break;
}
memcpy(node->ptr,(const void *)t->ptr,sourceDoublyLinkedList->sizeOfOneElement);
node->next=NULL;
node->previous=NULL;
if(s==NULL)
{
s=node;
e=node;
}
else
{
e->next=node;
node->previous=e;
e=node;
}
t=t->next;
}

if(done==false)
{
while(s!=NULL)
{
node=s;
s=s->next;
free(node->ptr);
free(node);
}
return;
}
if(targetDoublyLinkedList->start==NULL)
{
targetDoublyLinkedList->start=s;
targetDoublyLinkedList->end=e;
targetDoublyLinkedList->size=sourceDoublyLinkedList->size;
targetDoublyLinkedList->sizeOfOneElement=sourceDoublyLinkedList->sizeOfOneElement;
}
else
{
targetDoublyLinkedList->end->next=s;
s->previous=targetDoublyLinkedList->end;
targetDoublyLinkedList->end=e;
targetDoublyLinkedList->size+=sourceDoublyLinkedList->size;
}
if(error) error->succ=true;
}

void getFromDoublyLinkedList(DoublyLinkedList *doublyLinkedList,void *ptr,int index,OperationDetail *error)
{
DoublyLinkedListNode *node;
int x;
if(error) error->succ=false;
if(doublyLinkedList==NULL)
{
if(error) error->code=3;
return;
}
if(index<0 || index>=doublyLinkedList->size)
{
if(error) error->code=9;
return;
}
node=doublyLinkedList->start;
x=0;
while(x<index)
{
node=node->next;
x++;
}
memcpy(ptr,(const void *)node->ptr,doublyLinkedList->sizeOfOneElement);
if(error)
{
error->succ=true;
error->code=0;
}
}
DoublyLinkedListIterator getDoublyLinkedListIterator(DoublyLinkedList *doublyLinkedList,OperationDetail *error)
{
DoublyLinkedListIterator doublyLinkedListIterator;
doublyLinkedListIterator.node=NULL;
if(error) error->succ=false;
if(doublyLinkedList==NULL)
{
if(error) error->code=3;
return doublyLinkedListIterator;
}
if(doublyLinkedList->start==NULL) 
{
if(error)
{
error->succ=true;
error->code=0;
}
return doublyLinkedListIterator;
}
if(error) error->succ=true;
doublyLinkedListIterator.node=doublyLinkedList->start;
doublyLinkedListIterator.sizeOfOneElement=doublyLinkedList->sizeOfOneElement;
return doublyLinkedListIterator;  
}
bool hasNextInDoublyLinkedList(DoublyLinkedListIterator *doublyLinkedListIterator)
{
if(doublyLinkedListIterator==NULL) return false;
if(doublyLinkedListIterator->node==NULL) return false;
return true;
}
void getNextElementFromDoublyLinkedList(DoublyLinkedListIterator *doublyLinkedListIterator,void *ptr,OperationDetail *error)
{
if(error) error->succ=false;
if(doublyLinkedListIterator==NULL || doublyLinkedListIterator->node==NULL)
{
if(error) error->code=3;
return;
}
memcpy(ptr,(const void *)doublyLinkedListIterator->node->ptr,doublyLinkedListIterator->sizeOfOneElement);
doublyLinkedListIterator->node=doublyLinkedListIterator->node->next;
if(error)
{
error->succ=true;
error->code=0;
}
}

DoublyLinkedListReverseIterator getDoublyLinkedListReverseIterator(DoublyLinkedList *doublyLinkedList,OperationDetail *error)
{
DoublyLinkedListReverseIterator doublyLinkedListReverseIterator;
doublyLinkedListReverseIterator.node=NULL;
if(error) error->succ=false;
if(doublyLinkedList==NULL)
{
if(error) error->code=3;
return doublyLinkedListReverseIterator;
}
if(doublyLinkedList->start==NULL) 
{
if(error)
{
error->succ=true;
error->code=0;
}
return doublyLinkedListReverseIterator;
}
if(error) error->succ=true;
doublyLinkedListReverseIterator.node=doublyLinkedList->end;
doublyLinkedListReverseIterator.sizeOfOneElement=doublyLinkedList->sizeOfOneElement;
return doublyLinkedListReverseIterator;  
}
bool hasPreviousInDoublyLinkedList(DoublyLinkedListReverseIterator *doublyLinkedListReverseIterator)
{
if(doublyLinkedListReverseIterator==NULL) return false;
if(doublyLinkedListReverseIterator->node==NULL) return false;
return true;
}
void getPreviousElementFromDoublyLinkedList(DoublyLinkedListReverseIterator *doublyLinkedListReverseIterator,void *ptr,OperationDetail *error)
{
if(error) error->succ=false;
if(doublyLinkedListReverseIterator==NULL || doublyLinkedListReverseIterator->node==NULL)
{
if(error) error->code=3;
return;
}
memcpy(ptr,(const void *)doublyLinkedListReverseIterator->node->ptr,doublyLinkedListReverseIterator->sizeOfOneElement);
doublyLinkedListReverseIterator->node=doublyLinkedListReverseIterator->node->previous;
if(error)
{
error->succ=true;
error->code=0;
}
}

// AVLTree implementation starts here

AVLTree * createAVLTree(OperationDetail *operationDetail,int (*predicate)(void *,void *))
{
if(operationDetail) operationDetail->succ=false;
AVLTree *avlTree;
avlTree=(AVLTree *)malloc(sizeof(AVLTree));
if(avlTree==NULL)
{
if(operationDetail) operationDetail->code=2;
return NULL;
}
if(predicate==NULL)
{
if(operationDetail) operationDetail->code=6;
return NULL;
}
avlTree->start=NULL;
avlTree->size=0;
avlTree->predicate=predicate;
if(operationDetail)
{
operationDetail->succ=true;
operationDetail->code=0;
}
return avlTree;
}

void balanceAVLTree(AVLTree *avlTree,Stack *stack)
{
AVLTreeNode *lc,*rc,*root,*lcrc,*rclc,*parent;
AVLTreeNode **p2p;
OperationDetail oper;
int lh,rh,diff;
bool succ;
if(stack==NULL) return;
if(isStackEmpty(stack)) return;
while(!isStackEmpty(stack)) 
{
popFromStack(stack,(void *)&root,&oper);
lh=getHeightOfAVLTree(root->left);
rh=getHeightOfAVLTree(root->right);
diff=lh-rh;
if(diff>=-1 && diff<=1) continue;
if(isStackEmpty(stack))
{
p2p=&(avlTree->start);
}
else
{
elementAtTopOfStack(stack,(void *)&parent,&oper);
if(parent->left==root)
{
p2p=&(parent->left);
}
else
{
p2p=&(parent->right);
}
}
if(rh>lh)
{
rc=root->right;
if(getHeightOfAVLTree(rc->left)>getHeightOfAVLTree(rc->right))
{
rclc=rc->left;
rc->left=rclc->right;
rclc->right=rc;
root->right=rclc;
rc=root->right;
}
root->right=rc->left;
rc->left=root;
*p2p=rc;
}
else
{
lc=root->left;
if(getHeightOfAVLTree(lc->right)>getHeightOfAVLTree(lc->left))
{
lcrc=lc->right;
lc->right=lcrc->left;
lcrc->left=lc;
root->left=lcrc;
lc=root->left;
}
root->left=lc->right;
lc->right=root;
*p2p=lc;
}
}
}//function ends

void destroyAVLTree(AVLTree *avlTree)
{
if(avlTree==NULL) return;
clearAVLTree(avlTree);
free(avlTree);
}

int getSizeOfAVLTree(AVLTree *avlTree)
{
if(avlTree==NULL) return 0;
return avlTree->size;
}

void addToAVLTree(AVLTree *avlTree,void *ptr,OperationDetail *operationDetail)
{
OperationDetail oper;
Stack *stack;
AVLTreeNode *j,*t;
int weight;
if(operationDetail) operationDetail->succ=false;
if(avlTree==NULL)
{
if(operationDetail) operationDetail->code=3;
return;
}
if(avlTree->start==NULL) 
{
t=(AVLTreeNode *)malloc(sizeof(AVLTreeNode));
if(t==NULL)
{
if(operationDetail) operationDetail->code=2;
return;
}
t->ptr=ptr;
t->left=NULL;
t->right=NULL;
avlTree->start=t;
avlTree->size++;
if(operationDetail)
{
operationDetail->succ=true;
operationDetail->code=0;
}
return;
}
stack=createStack(sizeof(AVLTreeNode **),&oper);
if(oper.succ==false)
{
if(operationDetail) operationDetail->code=oper.code;
return;
}
j=avlTree->start;
while(1)
{
weight=avlTree->predicate(ptr,j->ptr);
if(weight==0)
{
if(operationDetail) operationDetail->code=10;
destroyStack(stack);
return;
}
pushOnStack(stack,(void *)&j,&oper);
if(oper.succ==false)
{
destroyStack(stack);
if(operationDetail) operationDetail->code=oper.code;
return;
}
if(weight<0)
{
if(j->left==NULL)
{
t=(AVLTreeNode *)malloc(sizeof(AVLTreeNode));
if(t==NULL)
{
if(operationDetail) operationDetail->code=2;
destroyStack(stack);
return;
}
t->ptr=ptr;
t->left=NULL;
t->right=NULL;
j->left=t;
break;
}
else
{
j=j->left;
}
}
else
{
if(j->right==NULL)
{
t=(AVLTreeNode *)malloc(sizeof(AVLTreeNode));
if(t==NULL)
{
if(operationDetail) operationDetail->code=2;
destroyStack(stack);
return;
}
t->ptr=ptr;
t->left=NULL;
t->right=NULL;
j->right=t;
break;
}
else
{
j=j->right;
}
}
}
avlTree->size++;
balanceAVLTree(avlTree,stack);
destroyStack(stack);
if(operationDetail)
{
operationDetail->succ=true;
operationDetail->code=0;
}
}

void insertIntoAVLTree(AVLTree *avlTree,void *ptr,OperationDetail *operationDetail)
{
OperationDetail oper;
Stack *stack;
AVLTreeNode *j,*t;
int weight;
if(operationDetail) operationDetail->succ=false;
if(avlTree==NULL)
{
if(operationDetail) operationDetail->code=3;
return;
}
if(avlTree->start==NULL) 
{
t=(AVLTreeNode *)malloc(sizeof(AVLTreeNode));
if(t==NULL)
{
if(operationDetail) operationDetail->code=2;
return;
}
t->ptr=ptr;
t->left=NULL;
t->right=NULL;
avlTree->start=t;
avlTree->size++;
if(operationDetail)
{
operationDetail->succ=true;
operationDetail->code=0;
}
return;
}
stack=createStack(sizeof(AVLTreeNode **),&oper);
if(oper.succ==false)
{
if(operationDetail) operationDetail->code=oper.code;
return;
}
j=avlTree->start;
while(1)
{
weight=avlTree->predicate(ptr,j->ptr);
if(weight==0)
{
if(operationDetail) operationDetail->code=10;
destroyStack(stack);
return;
}
pushOnStack(stack,(void *)&j,&oper);
if(oper.succ==false)
{
if(operationDetail) operationDetail->code=oper.code;
destroyStack(stack);
return;
}
if(weight<0)
{
if(j->left==NULL)
{
t=(AVLTreeNode *)malloc(sizeof(AVLTreeNode));
if(t==NULL)
{
if(operationDetail) operationDetail->code=2;
destroyStack(stack);
return;
}
t->ptr=ptr;
t->left=NULL;
t->right=NULL;
j->left=t;
break;
}
else
{
j=j->left;
}
}
else
{
if(j->right==NULL)
{
t=(AVLTreeNode *)malloc(sizeof(AVLTreeNode));
if(t==NULL)
{
if(operationDetail) operationDetail->code=2;
destroyStack(stack);
return;
}
t->ptr=ptr;
t->left=NULL;
t->right=NULL;
j->right=t;
break;
}
else
{
j=j->right;
}
}
}
avlTree->size++;
balanceAVLTree(avlTree,stack);
destroyStack(stack);
if(operationDetail)
{
operationDetail->succ=true;
operationDetail->code=0;
}
}

void * removeFromAVLTree(AVLTree *avlTree,void *ptr,OperationDetail *operationDetail)
{
AVLTreeNode *t,*j,*e,*f;
AVLTreeNode **p2p;
void *removedPtr;
int weight;
if(operationDetail) operationDetail->succ=false;
if(avlTree==NULL || avlTree->start==NULL)
{
if(operationDetail) operationDetail->code=3;
return NULL;
}
t=avlTree->start;
while(t!=NULL)
{
weight=avlTree->predicate(ptr,t->ptr);
if(weight==0) break;
j=t;
if(weight<0) t=t->left;
else t=t->right;
}
if(t==NULL)
{
if(operationDetail) operationDetail->code=9;
return NULL;
}
removedPtr=t->ptr;
if(t==avlTree->start) p2p=&(avlTree->start);
else if(j->left==t) p2p=&(j->left);
else p2p=&(j->right); 
if(t->left==t->right) //both are NULL leaf node
{
*p2p=NULL;
}
else
{
if(t->right!=NULL)  //successor part start
{
for(e=t->right;e->left!=NULL;e=e->left) f=e;
if(t->right==e)
{
e->left=t->left;
}
else
{
f->left=e->right;
e->right=t->right;
e->left=t->left; 
}
*p2p=e;
} //successor part ends
else //predecessor part start
{
for(e=t->left;e->right!=NULL;e=e->right) f=e;
if(t->left==e)
{
e->right=t->right;
}
else
{
f->right=e->left;
e->right=t->right;
e->left=t->left; 
}
*p2p=e; 
} //predecessor part ends
}
free(t);
avlTree->size--;
if(operationDetail)
{
operationDetail->succ=true;
operationDetail->code=0;
}
return removedPtr; 
}

void clearAVLTree(AVLTree *avlTree)
{
AVLTreeNode *t,*j,*free_fire,*element_at_top_of_stack;
Stack *stack;
OperationDetail oper;
if(avlTree==NULL) return;
if(avlTree->start==NULL) return;
stack=createStack(sizeof(AVLTreeNode **),&oper);
t=avlTree->start;
while(1)
{
while(t!=NULL)
{
if(t->right!=NULL) pushOnStack(stack,(void *)&(t->right),&oper);
pushOnStack(stack,(void *)&t,&oper);
t=t->left;
}
popFromStack(stack,&t,&oper);
elementAtTopOfStack(stack,&element_at_top_of_stack,&oper);
if(!isStackEmpty(stack) && t->right!=NULL && t->right==element_at_top_of_stack)
{
popFromStack(stack,&free_fire,&oper);
pushOnStack(stack,(void *)&t,&oper);
t=t->right;
}
else
{
j=t;
t=NULL;
free(j);
}
if(isStackEmpty(stack)) break;
}
avlTree->size=0;
avlTree->start=NULL;
destroyStack(stack);
}

int getHeightOfAVLTree(AVLTreeNode *root)
{
int leftTreeHeight,rightTreeHeight;
if(root==NULL) return 0;
leftTreeHeight=getHeightOfAVLTree(root->left);
rightTreeHeight=getHeightOfAVLTree(root->right);
if(leftTreeHeight>rightTreeHeight)
{
return leftTreeHeight+1;
}
else
{
return rightTreeHeight+1;
}
}


void * getFromAVLTree(AVLTree *avlTree,void *ptr,OperationDetail *operationDetail)
{
AVLTreeNode *t;
int weight;
if(operationDetail) operationDetail->succ=false;
if(avlTree==NULL || avlTree->start==NULL)
{
if(operationDetail) operationDetail->code=3;
return NULL;
}
t=avlTree->start;
while(t!=NULL)
{
weight=avlTree->predicate(ptr,t->ptr);
if(weight==0)
{
if(operationDetail)
{
operationDetail->code=0;
operationDetail->succ=true;
}
return t->ptr;
}
if(weight<0) t=t->left;
else t=t->right;
}
return NULL;
}

AVLTreeInOrderIterator getAVLTreeInOrderIterator(AVLTree *avlTree,OperationDetail *operationDetail)
{
OperationDetail oper;
AVLTreeNode *t;
AVLTreeInOrderIterator avlTreeInOrderIterator;
avlTreeInOrderIterator.node=NULL;
avlTreeInOrderIterator.stack=NULL;
if(operationDetail) operationDetail->succ=false;
if(avlTree==NULL)
{
if(operationDetail) operationDetail->code=3;
return avlTreeInOrderIterator;
}
if(avlTree->start==NULL)
{
if(operationDetail)
{
operationDetail->code=0;
operationDetail->succ=true;
}
return avlTreeInOrderIterator;  
}
avlTreeInOrderIterator.stack=createStack(sizeof(AVLTree **),&oper);
if(oper.succ==false)
{
if(operationDetail) operationDetail->code=oper.code;
return avlTreeInOrderIterator;
}
t=avlTree->start;
while(t!=NULL)
{
pushOnStack(avlTreeInOrderIterator.stack,(void *)&t,&oper);
if(oper.succ==false)
{
if(operationDetail) operationDetail->code=oper.code;
destroyStack(avlTreeInOrderIterator.stack);
avlTreeInOrderIterator.stack=NULL;
return avlTreeInOrderIterator;
}
t=t->left;
}
popFromStack(avlTreeInOrderIterator.stack,&(avlTreeInOrderIterator.node),&oper);
if(operationDetail)
{
operationDetail->succ=true;
operationDetail->code=0;
}
return avlTreeInOrderIterator;
}

bool hasNextInOrderElementInAVLTree(AVLTreeInOrderIterator *avlTreeInOrderIterator)
{
if(avlTreeInOrderIterator==NULL || avlTreeInOrderIterator->node==NULL) return false;
return true;
}


void * getNextInOrderElementFromAVLTree(AVLTreeInOrderIterator *avlTreeInOrderIterator,OperationDetail *operationDetail)
{
OperationDetail oper;
AVLTreeNode *j,*t;
if(operationDetail) operationDetail->succ=false;
if(avlTreeInOrderIterator==NULL || avlTreeInOrderIterator->node==NULL)
{
if(operationDetail) operationDetail->code=3;
return NULL;
}
j=avlTreeInOrderIterator->node;
t=j->right;
while(t!=NULL)
{
pushOnStack(avlTreeInOrderIterator->stack,&t,&oper);
if(oper.succ==false)
{
if(operationDetail) operationDetail->code=oper.code;
destroyStack(avlTreeInOrderIterator->stack);
avlTreeInOrderIterator->stack=NULL;
avlTreeInOrderIterator->node=NULL;
return t->ptr;
}
t=t->left;
}
if(isStackEmpty(avlTreeInOrderIterator->stack))
{
destroyStack(avlTreeInOrderIterator->stack);
avlTreeInOrderIterator->node=NULL;
avlTreeInOrderIterator->stack=NULL;
}
else
{
popFromStack(avlTreeInOrderIterator->stack,&(avlTreeInOrderIterator->node),&oper);
}
if(operationDetail)
{
operationDetail->succ=true;
operationDetail->code=0;
}
return j->ptr;
}

AVLTreePreOrderIterator getAVLTreePreOrderIterator(AVLTree *avlTree,OperationDetail *operationDetail)
{
OperationDetail oper;
AVLTreePreOrderIterator avlTreePreOrderIterator;
avlTreePreOrderIterator.node=NULL;
avlTreePreOrderIterator.stack=NULL;
if(operationDetail) operationDetail->succ=false;
if(avlTree==NULL)
{
if(operationDetail) operationDetail->code=3;
return avlTreePreOrderIterator;
}
if(avlTree->start==NULL)
{
if(operationDetail)
{
operationDetail->succ=true;
operationDetail->code=0;
}
return avlTreePreOrderIterator;  
}
avlTreePreOrderIterator.stack=createStack(sizeof(AVLTreeNode **),&oper);
if(oper.succ==false)
{
if(operationDetail) operationDetail->code=oper.code;
return avlTreePreOrderIterator; 
}
avlTreePreOrderIterator.node=avlTree->start;
if(operationDetail)
{
operationDetail->succ=true;
operationDetail->code=0;
}
return avlTreePreOrderIterator;
}

bool hasNextPreOrderElementInAVLTree(AVLTreePreOrderIterator *avlTreePreOrderIterator)
{
if(avlTreePreOrderIterator==NULL || avlTreePreOrderIterator->node==NULL) return false;
return true;
}

void * getNextPreOrderElementFromAVLTree(AVLTreePreOrderIterator *avlTreePreOrderIterator,OperationDetail *operationDetail)
{
OperationDetail oper;
AVLTreeNode *j,*t;
if(operationDetail) operationDetail->succ=false;
if(avlTreePreOrderIterator==NULL || avlTreePreOrderIterator->node==NULL)
{
if(operationDetail) operationDetail->code=3;
return NULL;
}
j=avlTreePreOrderIterator->node;
if(j->right!=NULL)
{
pushOnStack(avlTreePreOrderIterator->stack,(void **)&(j->right),&oper);
if(oper.succ==false)
{
if(operationDetail) operationDetail->code=oper.code;
destroyStack(avlTreePreOrderIterator->stack);
avlTreePreOrderIterator->stack=NULL;
avlTreePreOrderIterator->node=NULL;
return j->ptr;
}
}
if(j->left!=NULL)
{
pushOnStack(avlTreePreOrderIterator->stack,(void **)&(j->left),&oper);
if(oper.succ==false)
{
if(operationDetail) operationDetail->code=oper.code;
destroyStack(avlTreePreOrderIterator->stack);
avlTreePreOrderIterator->stack=NULL;
avlTreePreOrderIterator->node=NULL;
return j->ptr;
}
}
if(isStackEmpty(avlTreePreOrderIterator->stack))
{
destroyStack(avlTreePreOrderIterator->stack);
avlTreePreOrderIterator->node=NULL;
avlTreePreOrderIterator->stack=NULL;
}
else
{
popFromStack(avlTreePreOrderIterator->stack,&(avlTreePreOrderIterator->node),&oper);
}
if(operationDetail)
{
operationDetail->succ=true;
operationDetail->code=0;
}
return j->ptr;
}

AVLTreePostOrderIterator getAVLTreePostOrderIterator(AVLTree *avlTree,OperationDetail *operationDetail)
{
OperationDetail oper;
AVLTreeNode *t,*element_at_top_of_stack,*free_fire;
AVLTreePostOrderIterator avlTreePostOrderIterator;
avlTreePostOrderIterator.node=NULL;
avlTreePostOrderIterator.stack=NULL;
if(operationDetail) operationDetail->succ=false;
if(avlTree==NULL)
{
if(operationDetail) operationDetail->code=3;
return avlTreePostOrderIterator;
}
if(avlTree->start==NULL)
{
if(operationDetail)
{
operationDetail->succ=true;
operationDetail->code=0;
}
return avlTreePostOrderIterator;  
}
avlTreePostOrderIterator.stack=createStack(sizeof(AVLTreeNode **),&oper);
if(oper.succ==false)
{
if(operationDetail) operationDetail->code=oper.code;
return avlTreePostOrderIterator; 
}
t=avlTree->start;
while(1)
{
while(t!=NULL)
{
if(t->right!=NULL)
{
pushOnStack(avlTreePostOrderIterator.stack,(void *)&(t->right),&oper);
}
pushOnStack(avlTreePostOrderIterator.stack,(void *)&t,&oper);
t=t->left;
}
popFromStack(avlTreePostOrderIterator.stack,(void *)&t,&oper);
elementAtTopOfStack(avlTreePostOrderIterator.stack,(void *)&element_at_top_of_stack,&oper);
if(!isStackEmpty(avlTreePostOrderIterator.stack) && t->right!=NULL && t->right==element_at_top_of_stack)
{
popFromStack(avlTreePostOrderIterator.stack,(void *)&free_fire,&oper);
pushOnStack(avlTreePostOrderIterator.stack,(void *)&t,&oper); 
t=t->right;
}
else
{
break;
}
}
avlTreePostOrderIterator.node=t;
if(operationDetail)
{
operationDetail->succ=true;
operationDetail->code=0;
}
return avlTreePostOrderIterator;
}

bool hasNextPostOrderElementInAVLTree(AVLTreePostOrderIterator *avlTreePostOrderIterator)
{
if(avlTreePostOrderIterator==NULL || avlTreePostOrderIterator->node==NULL) return false;
return true;
}

void * getNextPostOrderElementFromAVLTree(AVLTreePostOrderIterator *avlTreePostOrderIterator,OperationDetail *operationDetail)
{
OperationDetail oper;
AVLTreeNode *j,*t,*element_at_top_of_stack,*free_fire;
if(operationDetail) operationDetail->succ=false;
if(avlTreePostOrderIterator==NULL || avlTreePostOrderIterator->node==NULL)
{
if(operationDetail) operationDetail->code=3;
return NULL;
}
j=avlTreePostOrderIterator->node;
if(isStackEmpty(avlTreePostOrderIterator->stack))
{
avlTreePostOrderIterator->node=NULL;
destroyStack(avlTreePostOrderIterator->stack);
if(operationDetail)
{
operationDetail->succ=true;
operationDetail->code=0;
}
return j->ptr;
}
t=NULL;
while(1)
{
while(t!=NULL)
{
if(t->right!=NULL)
{
pushOnStack(avlTreePostOrderIterator->stack,(void *)&(t->right),&oper);
}
pushOnStack(avlTreePostOrderIterator->stack,(void *)&t,&oper);
t=t->left;
}
popFromStack(avlTreePostOrderIterator->stack,(void *)&t,&oper);
elementAtTopOfStack(avlTreePostOrderIterator->stack,(void *)&(element_at_top_of_stack),&oper);
if(!isStackEmpty(avlTreePostOrderIterator->stack) && t->right!=NULL && t->right==element_at_top_of_stack)
{
popFromStack(avlTreePostOrderIterator->stack,(void *)&free_fire,&oper);
pushOnStack(avlTreePostOrderIterator->stack,(void *)&t,&oper); 
t=t->right;
}
else
{
break;
}
}
avlTreePostOrderIterator->node=t;
if(operationDetail)
{
operationDetail->succ=true;
operationDetail->code=0;
}
return j->ptr;
}
// AVLTree implementation ends here
#endif
