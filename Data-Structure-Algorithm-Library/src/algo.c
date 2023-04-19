#ifndef ALGO_C
#define ALGO_C 123
#include<common.h>
#include<algo.h>
#include<stdlib.h>
#include<string.h>
#include<ds.h>
#include<stdio.h>
// common functions
int isInvalid(void *ptr,int *lb,int *ub,int *es,OperationDetail *error,int (*p2f) (void *,void *))
{
if(ptr==NULL)
{
error->code=3;
return 1;
}
if((*lb)<0 || (*ub)<(*lb) || *(lb)==*(ub))
{
error->code=1;
return 1;
}
if((*es)<=0)
{
error->code=7;
return 1;
}
if(p2f==NULL)
{
error->code=6;
return 1;
}
return 0;
}
void ifLowerBoundIsNotZero(void *ptr,int *lb,int *ub,int *es)
{
ptr=ptr+((*lb)*(*es));
*ub=(*ub)-(*lb);
*lb=0;
}
void findingTheHeaviestElement(void *ptr,int lb,int ub,int es,OperationDetail *error,void *heavestElement,int (*p2f) (void *,void *))
{
OperationDetail err;
int i;
if(error) error->succ=false;
if(error==NULL)
{
if(isInvalid(ptr,&lb,&ub,&es,&err,p2f)) return;
}
else{
if(isInvalid(ptr,&lb,&ub,&es,error,p2f)) return;
}
memcpy(heavestElement,(const void *)ptr+(lb*es),es);
for(i=lb+1;i<=ub;i++)
{
if(p2f(heavestElement,ptr+(i*es))<0) memcpy(heavestElement,(const void *)ptr+(i*es),es);
}
if(error)
{
error->code=0;
error->succ=true;
}
}

void findingTheHeaviestElementIndex(void *ptr,int lb,int ub,int es,OperationDetail *error,int *heaviestElementIndex,int (*p2f) (void *,void *))
{
int i;
OperationDetail err;
if(error) error->succ=false;
if(error==NULL)
{
if(isInvalid(ptr,&lb,&ub,&es,&err,p2f)) return;
}
else{
if(isInvalid(ptr,&lb,&ub,&es,error,p2f)) return;
}
*heaviestElementIndex=lb;
for(i=lb+1;i<=ub;i++)
{
if(p2f(ptr+((*heaviestElementIndex)*es),ptr+(i*es))<0) *heaviestElementIndex=i;
}
if(error)
{
error->code=0;
error->succ=true;
}
}
void findingTheLightestElement(void *ptr,int lb,int ub,int es,OperationDetail *error,void *lightestElement,int (*p2f) (void *,void *))
{
int i;
if(error) error->succ=false;
if(error==NULL)
{
OperationDetail err;
if(isInvalid(ptr,&lb,&ub,&es,&err,p2f)) return;
}
else{
if(isInvalid(ptr,&lb,&ub,&es,error,p2f)) return;
}
memcpy(lightestElement,(const void *)ptr,es);
for(i=lb+1;i<=ub;i++)
{
if(p2f(lightestElement,ptr+(i*es))>0) memcpy(lightestElement,(const void *)ptr+(i*es),es);
}
if(error)
{
error->code=0;
error->succ=true;
}
}
int INT_HEAVIEST_ELEMENT_COMPARATOR(void *left,void *right)
{
int *i,*j;
i=(int *)left;
j=(int *)right;
return (*i)-(*j);
}
int INT_LIGHTEST_ELEMENT_COMPARATOR(void *left,void *right)
{
int *i,*j;
i=(int *)left;
j=(int *)right;
return (*j)-(*i);
}

int HASH_FUNCTION_FOR_ADDRESS_CALCULATION_AKA_BUCKET_SORT(int elem,int largestDigit)
{
int i,key;
i=0;
key=0;
while(i<largestDigit)
{
key=elem%10;
elem=elem/10;
i++;
}
return key;
}
int dummy(void *left,void *right)
{
// do nothing 
}
// common function ends
void bubbleSort(void *ptr,int lb,int ub,int es,OperationDetail *error,int (*p2f)(void *,void *))
{
OperationDetail err;
int m,e,f,weight;
void *a,*b,*c;
if(error) error->succ=false;
if(error==NULL)
{
if(isInvalid(ptr,&lb,&ub,&es,&err,p2f)) return;
}
else{
if(isInvalid(ptr,&lb,&ub,&es,error,p2f)) return;
}
m=ub-1;
if(m<0) return;
c=(void *)malloc(es);
if(c==NULL)
{
if(error) error->code=2;
return;
}
while(m>=lb)
{
e=lb;
f=lb+1;
while(e<=m)
{
a=ptr+(f*es);
b=ptr+(e*es);
weight=p2f(a,b);
if(weight<0)
{
memcpy(c,(const void *)a,es);
memcpy(a,(const void *)b,es);
memcpy(b,(const void *)c,es);
}
e++;
f++;
}
m--;
}
free(c);
if(error)
{
error->code=0;
error->succ=true;
}
}

void onePassOfBubbleSort(void *ptr,int lb,int ub,int es,void *c,int (*p2f)(void *,void *))
{
if(lb<ub)
{
if(p2f((ptr+((lb+1)*es)),(ptr+(lb*es)))<0)
{
memcpy(c,(const void *)ptr+((lb)*(es)),(es));
memcpy(ptr+((lb)*(es)),(const void *)ptr+(((lb)+1)*(es)),(es));
memcpy(ptr+(((lb)+1)*(es)),(const void *)c,(es));
}
onePassOfBubbleSort(ptr,lb+1,ub,es,c,p2f);
}
}

void BSR(void *ptr,int lb,int ub,int es,void *c,int (*p2f)(void *,void *))
{
// BSR stands for Bubble Sort Recursive
if(lb<ub)
{
onePassOfBubbleSort(ptr,lb,ub,es,c,p2f);
BSR(ptr,lb,ub-1,es,c,p2f);
}
}
void bubbleSortRecursive(void *ptr,int lb,int ub,int es,OperationDetail *error,int (*p2f)(void *,void *))
{
void *c;
OperationDetail err;
if(error) error->succ=false;
if(error==NULL)
{
if(isInvalid(ptr,&lb,&ub,&es,&err,p2f)) return;
}
else{
if(isInvalid(ptr,&lb,&ub,&es,error,p2f)) return;
}
c=(void *)malloc(es);
if(c==NULL)
{
if(error) error->code=2;
return;
}
BSR(ptr,lb,ub,es,c,p2f);
free(c);
if(error)
{
error->succ=true;
error->code=0;
}
}

void linearSort(void *ptr,int lb,int ub,int es,OperationDetail *error,int (*p2f)(void *,void *))
{
int e,f,weight,oep,iep;
void *a,*b,*c;
OperationDetail err;
if(error) error->succ=false;
if(error==NULL)
{
if(isInvalid(ptr,&lb,&ub,&es,&err,p2f)) return;
}
else{
if(isInvalid(ptr,&lb,&ub,&es,error,p2f)) return;
}
c=(void *)malloc(es);
if(c==NULL)
{
if(error) error->code=2;
return;
}
e=lb;
oep=ub-1;
iep=ub;
while(e<=oep)
{
f=e+1;
while(f<=iep)
{
a=ptr+(f*es);
b=ptr+(e*es);
weight=p2f(a,b);
if(weight<0)
{
memcpy(c,(const void *)a,es);
memcpy(a,(const void *)b,es);
memcpy(b,(const void *)c,es);
}
f++;
}
e++;
}
free(c);
if(error)
{
error->succ=true;
error->code=0;
}
}

void onePassOfLinearSort(void *ptr,int e,int f,int ub,int es,void *c,int (*p2f)(void *,void *))
{
if((f)<=(ub))
{
if(p2f(ptr+((f)*(es)),ptr+((e)*(es)))<0)
{
memcpy(c,(const void *)ptr+((e)*(es)),(es));
memcpy(ptr+((e)*(es)),(const void *)ptr+((f)*(es)),(es));
memcpy(ptr+((f)*(es)),(const void *)c,(es));
}
onePassOfLinearSort(ptr,e,f+1,ub,es,c,p2f);
}
} // function ends

void LSR(void *ptr,int lb,int ub,int es,void *c,int (*p2f)(void *,void *))
{
if(lb<ub)
{
onePassOfLinearSort(ptr,lb,lb+1,ub,es,c,p2f);
LSR(ptr,lb+1,ub,es,c,p2f);
}
}

void linearSortRecursive(void *ptr,int lb,int ub,int es,OperationDetail *error,int (*p2f)(void *,void *))
{
void *c;
if(error) error->succ=false;
if(error==NULL)
{
OperationDetail err;
if(isInvalid(ptr,&lb,&ub,&es,&err,p2f)) return;
}
else{
if(isInvalid(ptr,&lb,&ub,&es,error,p2f)) return;
}
c=(void *)malloc(es);
if(c==NULL)
{
if(error) error->code=2;
return;
}
LSR(ptr,lb,ub,es,c,p2f);
free(c);
if(error)
{
error->succ=true;
error->code=0;
}
} // function ends

void selectionSort(void *ptr,int lb,int ub,int es,OperationDetail *error,int (*p2f) (void *,void *))
{
int e,f,si,weight;
void *a,*b,*c;
OperationDetail err;
if(error) error->succ=false;
if(error==NULL)
{
if(isInvalid(ptr,&lb,&ub,&es,&err,p2f)) return;
}
else{
if(isInvalid(ptr,&lb,&ub,&es,error,p2f)) return;
}
c=(void *)malloc(es);
if(c==NULL)
{
if(error) error->code=2;
return;
}
e=lb;
while(e<=ub-1)
{
si=e;
f=e+1;
while(f<=ub)
{
a=ptr+(f*es);
b=ptr+(si*es);
weight=p2f(a,b);
if(weight<0)
{
si=f;
}
f++;
}
a=ptr+(e*es);
b=ptr+(si*es);
memcpy(c,(const void *)a,es);
memcpy(a,(const void *)b,es);
memcpy(b,(const void *)c,es);
e++;
}
free(c);
if(error)
{
error->code=0;
error->succ=true;
}
}

void onePassOfSelectionSort(void *ptr,int e,int f,int ub,int es,int *si,int (*p2f)(void *,void *))
{
if((f)<=(ub))
{
if(p2f(ptr+((f)*(es)),ptr+((*si)*(es)))<0) *si=f;
onePassOfSelectionSort(ptr,e,f+1,ub,es,si,p2f);
}
}// function ends

void sSR(void *ptr,int lb,int ub,int es,void *c,int (*p2f)(void *,void *))
{
int si;
si=lb;
if(lb<ub)
{
onePassOfSelectionSort(ptr,lb,lb+1,ub,es,&si,p2f);
memcpy(c,(const void *)ptr+((lb)*(es)),(es));
memcpy(ptr+((lb)*(es)),(const void *)ptr+((si)*(es)),(es));
memcpy(ptr+((si)*(es)),(const void *)c,(es));
sSR(ptr,lb+1,ub,es,c,p2f);
}
}
void selectionSortRecursive(void *ptr,int lb,int ub,int es,OperationDetail *error,int (*p2f)(void *,void *))
{
void *c;
OperationDetail err;
if(error) error->succ=false;
if(error==NULL)
{
if(isInvalid(ptr,&lb,&ub,&es,&err,p2f)) return;
}
else{
if(isInvalid(ptr,&lb,&ub,&es,error,p2f)) return;
}
c=(void *)malloc(es);
if(c==NULL)
{
if(error) error->code=2;
return;
}
sSR(ptr,lb,ub,es,c,p2f);
free(c);
if(error)
{
error->succ=true;
error->code=0;
}
} // function ends

void insertionSort(void *ptr,int lb,int ub,int es,OperationDetail *error,int (*p2f)(void *,void *))
{
int y,leastLb;
void *c;
OperationDetail err;
if(error) error->succ=false;
if(error==NULL)
{
if(isInvalid(ptr,&lb,&ub,&es,&err,p2f)) return;
}
else{
if(isInvalid(ptr,&lb,&ub,&es,error,p2f)) return;
}
c=(void *)malloc(es);
if(c==NULL)
{
error->code=2;
return;
}
leastLb=lb;
lb++;
while(lb<=ub)
{
memcpy(c,(const void *)ptr+(lb*es),es);
y=lb-1;
while(y>=leastLb && p2f(c,ptr+(y*es))<0)
{
memcpy(ptr+((y+1)*es),(const void *)(ptr+(y*es)),es);
y--;
}
memcpy(ptr+((y+1)*es),(const void *)c,es);
lb++;
}
free(c);
if(error)
{
error->code=0;
error->succ=true;
}
}

void onePassOfInsertionSort(void *ptr,int *y,int olb,int diff,int es,void *c,int (*p2f)(void *,void *))
{
if((*y)>=(olb) && p2f(c,ptr+((*y)*(es)))<0)
{
memcpy(ptr+(((*y)+diff)*(es)),(const void *)ptr+((*y)*(es)),es);
*y=(*y)-diff;
onePassOfInsertionSort(ptr,y,olb,diff,es,c,p2f);
}
}

void ISR(void *ptr,int olb,int lb,int diff,int ub,int es,void *c,int (*p2f)(void *,void *))
{
int y;
if(lb<=ub)
{
memcpy(c,(const void *)ptr+(lb*es),es);
y=lb-diff;
onePassOfInsertionSort(ptr,&y,olb,diff,es,c,p2f);
memcpy(ptr+((y+diff)*es),(const void *)c,es);
ISR(ptr,olb,lb+diff,diff,ub,es,c,p2f);
}
}

void insertionSortRecursive(void *ptr,int lb,int ub,int es,OperationDetail *error,int (*p2f)(void *,void *))
{
int olb,diff;
void *c;
OperationDetail err;
if(error) error->succ=false;
if(error==NULL)
{
if(isInvalid(ptr,&lb,&ub,&es,&err,p2f)) return;
}
else{
if(isInvalid(ptr,&lb,&ub,&es,error,p2f)) return;
}
c=(void *)malloc(es);
if(c==NULL)
{
if(error) error->code=2;
return;
}
olb=lb;
diff=1;
ISR(ptr,olb,lb+diff,diff,ub,es,c,p2f);
free(c);
if(error)
{
error->succ=true;
error->code=0;
}
}
void insertionSortForDLL(DoublyLinkedList *doublyLinkedList,int lb,int ub,OperationDetail *error,int (*p2f) (void *,void *))
{
void *c;
int size,vEs=6;
DoublyLinkedListNode *lbNode,*y;
OperationDetail err;
if(error) error->succ=false;
size=doublyLinkedList->size-1;
if(error==NULL)
{
if(isInvalid((void *)doublyLinkedList,&lb,&size,&vEs,&err,dummy)) return;
}
else{
if(isInvalid((void *)doublyLinkedList,&lb,&ub,&vEs,error,dummy)) return;
}

if(doublyLinkedList==NULL)
{
if(error) error->code=3;
return;
}
if(doublyLinkedList->start==NULL)
{
if(error)
{
error->succ=true;
error->code=0;
}
return;
}

if(ub<size)
{
if(error) error->code=1;
return;
}
c=(void *)malloc(doublyLinkedList->sizeOfOneElement);
if(c==NULL)
{
if(error) error->code=2;
return;
}
lbNode=doublyLinkedList->start;
lbNode=lbNode->next;
while(lbNode!=NULL)
{
memcpy(c,(const void *)lbNode->ptr,doublyLinkedList->sizeOfOneElement);
y=lbNode->previous;
while(y!=NULL && p2f(c,y->ptr)<0)
{
memcpy(y->next->ptr,(const void *)y->ptr,doublyLinkedList->sizeOfOneElement);
y=y->previous;
}
if(y==NULL) memcpy(doublyLinkedList->start->ptr,(const void *)c,doublyLinkedList->sizeOfOneElement);
else memcpy(y->next->ptr,(const void *)c,doublyLinkedList->sizeOfOneElement);
lbNode=lbNode->next;
}
free(c);
if(error)
{
error->succ=true;
error->code=0;
}
}

int findPartionPoint(void *ptr,int e,int f,int es,int (*p2f)(void *,void *),OperationDetail *err)
{
int lb=e;
int ub=f;
void *a,*b,*c;
if(err) err->succ=false;
c=(void *)malloc(es);
if(c==NULL)
{
if(err) err->code=2;
return 0;
}
while(e<f)
{
while(e<ub && p2f(ptr+(e*es),ptr+(lb*es))<=0) e++;
while(p2f(ptr+(f*es),ptr+(lb*es))>0) f--;
if(e<f)
{
a=ptr+(e*es);
b=ptr+(f*es);
memcpy(c,(const void *)a,es);
memcpy(a,(const void *)b,es);
memcpy(b,(const void *)c,es);
}
else
{
a=ptr+(f*es);
b=ptr+(lb*es);
memcpy(c,(const void *)a,es);
memcpy(a,(const void *)b,es);
memcpy(b,(const void *)c,es);
}
}
free(c);
if(err)
{
err->succ=true;
err->code=0;
}
return f;
}
void quickSort(void *ptr,int lb,int ub,int es,OperationDetail *error,int (*p2f)(void *,void *))
{
typedef struct indexes
{
int lb;
int ub;
}Indexes;
int a,b;
Indexes *indexes;
Stack *stack;
int succ;
int pp,ppSucc;
OperationDetail err;
if(error) error->succ=false;
if(error==NULL)
{
if(isInvalid(ptr,&lb,&ub,&es,&err,p2f)) return;
}
else{
if(isInvalid(ptr,&lb,&ub,&es,error,p2f)) return;
}
stack=createStack(sizeof(Indexes),&err);
if(err.succ==false)
{
if(error) error->code=2;
return;
}
indexes=(Indexes *)malloc(sizeof(Indexes));
if(indexes==NULL)
{
if(error) error->code=2;
destroyStack(stack);
return;
}
indexes->lb=lb;
indexes->ub=ub;
pushOnStack(stack,(const void *)indexes,&err);
if(!err.succ)
{
if(error) error->code=err.code;
destroyStack(stack);
free(indexes);
return;
}
while(!isStackEmpty(stack))
{
popFromStack(stack,(void *)indexes,&err);
a=indexes->lb;
b=indexes->ub;
free(indexes);
pp=findPartionPoint(ptr,a,b,es,p2f,&err);
if(!err.succ)
{
destroyStack(stack);
if(error) error->code=err.code;
return;
}
if(pp+1<b)
{
indexes=(Indexes *)malloc(sizeof(Indexes));
if(indexes==NULL)
{
destroyStack(stack);
if(error) error->code=2;
return;
}
indexes->lb=pp+1;
indexes->ub=b;
pushOnStack(stack,(const void *)indexes,&err);
if(!err.succ)
{
destroyStack(stack);
free(indexes);
if(error) error->code=err.code;
return;
}
}
if(a<pp-1)
{
indexes=(Indexes *)malloc(sizeof(Indexes));
if(indexes==NULL)
{
destroyStack(stack);
if(error) error->code=err.code;
return;
}
indexes->lb=a;
indexes->ub=pp-1;
pushOnStack(stack,(const void *)indexes,&err);
if(!err.succ)
{
destroyStack(stack);
free(indexes);
if(error) error->code=err.code;
return;
}
}
}
destroyStack(stack);
if(error)
{
error->code=0;
error->succ=true;
}
} // function ends

void QSR(void *ptr,int lb,int ub,int es,OperationDetail *error,int (*p2f)(void *,void *))
{
int partitionPoint;
if(ub<=lb) return;
partitionPoint=findPartionPoint(ptr,lb,ub,es,p2f,error);
QSR(ptr,lb,partitionPoint-1,es,error,p2f);
QSR(ptr,partitionPoint+1,ub,es,error,p2f);
}

void quickSortRecursive(void *ptr,int lb,int ub,int es,OperationDetail *error,int (*p2f)(void *,void *))
{
OperationDetail err;
if(error) error->succ=false;
if(error==NULL)
{
if(isInvalid(ptr,&lb,&ub,&es,&err,p2f)) return;
}
else{
if(isInvalid(ptr,&lb,&ub,&es,error,p2f)) return;
}
QSR(ptr,lb,ub,es,error,p2f);
if(error)
{
error->succ=true;
error->code=0;
}
}

void merge(void *ptr,int low,int mid,int high,int es,int (*p2f) (void *,void *),int *succ)
{
if(succ) *succ=false;
int i1,i2,i3,lb1,lb2,lb3,ub1,ub2,ub3,size;
void *tmp;
size=(high-low)+1;
lb1=low;
ub1=mid;
lb2=mid+1;
ub2=high;
lb3=0;
ub3=size-1;
tmp=(void *)malloc(es*size);
if(tmp==NULL) return;
i1=lb1;
i2=lb2;
i3=lb3;
while(i1<=ub1 && i2<=ub2)
{
if(p2f(ptr+(i1*es),ptr+(i2*es))<0)
{
memcpy(tmp+(i3*es),(const void *)ptr+(i1*es),es);
i1++;
}
else
{
memcpy(tmp+(i3*es),(const void *)ptr+(i2*es),es);
i2++;
}
i3++;
}
while(i1<=ub1)
{
memcpy(tmp+(i3*es),(const void *)ptr+(i1*es),es);
i1++;
i3++;
}
while(i2<=ub2)
{
memcpy(tmp+(i3*es),(const void *)ptr+(i2*es),es);
i3++;
i2++;
}
i3=lb3;
i1=lb1;
while(i3<=ub3)
{
memcpy(ptr+(i1*es),(const void *)tmp+(i3*es),es);
i3++;
i1++;
}
free(tmp);
if(succ) *succ=true;
}
void mergeSort(void *ptr,int lb,int ub,int es,OperationDetail *error,int (*p2f)(void *,void *))
{
typedef struct __indexes__
{
int lb;
int ub;
}Indexes;
int succ;
int a,b,mid,lb1,ub1,ub2;
Stack *stack1;
Stack *stack2;
Indexes *indexes;
OperationDetail err;
if(error) error->succ=false;
if(error==NULL)
{
if(isInvalid(ptr,&lb,&ub,&es,&err,p2f)) return;
}
else{
if(isInvalid(ptr,&lb,&ub,&es,error,p2f)) return;
}
stack1=createStack(sizeof(Indexes),&err);
if(err.succ==false)
{
if(error) error->code=err.code;
return;
}
stack2=createStack(sizeof(Indexes),&err);
if(err.succ==false)
{
if(error) error->code=2;
destroyStack(stack1);
return;
}
indexes=(Indexes *)malloc(sizeof(Indexes));
if(indexes==NULL)
{
if(error) error->code=2;
destroyStack(stack1);
destroyStack(stack2);
return;
}
indexes->lb=lb;
indexes->ub=ub;
pushOnStack(stack1,(const void *)indexes,&err);
if(!err.succ)
{
if(error) error->code=err.code;
destroyStack(stack1);
destroyStack(stack2);
free(indexes);
return;
}
while(!isStackEmpty(stack1))
{
popFromStack(stack1,(void *)indexes,&err);
a=indexes->lb;
b=indexes->ub;
pushOnStack(stack2,(const void *)indexes,&err);
if(!err.succ)
{
if(error) error->code=err.code;
destroyStack(stack1);
destroyStack(stack2);
free(indexes);
return;
}
mid=(a+b)/2;
if(a<mid)
{
indexes=(Indexes *)malloc(sizeof(Indexes));
if(indexes==NULL)
{
if(error) error->code=2;
destroyStack(stack1);
destroyStack(stack2);
return;
}
indexes->lb=a;
indexes->ub=mid;
pushOnStack(stack1,(const void *)indexes,&err);
if(!err.succ)
{
if(error) error->code=err.code;
destroyStack(stack1);
destroyStack(stack2);
free(indexes);
return;
}
}
if(mid+1<b)
{
indexes=(Indexes *)malloc(sizeof(Indexes));
if(indexes==NULL)
{
if(error) error->code=2;
destroyStack(stack1);
destroyStack(stack2);
return;
}
indexes->lb=mid+1;
indexes->ub=b;
pushOnStack(stack1,(const void *)indexes,&err);
if(!err.succ)
{
if(error) error->code=err.code;
destroyStack(stack1);
destroyStack(stack2);
free(indexes);
return;
}
}
}
while(!isStackEmpty(stack2))
{
popFromStack(stack2,(void *)indexes,&err);
lb1=indexes->lb;
ub2=indexes->ub;
ub1=(lb1+ub2)/2;
merge(ptr,lb1,ub1,ub2,es,p2f,&succ);
if(succ==false)
{
destroyStack(stack2);
destroyStack(stack1);
free(indexes);
if(error)
{
error->code=2;
return;
}
}
}
destroyStack(stack1); // just for precaution
destroyStack(stack2); // just for precaution
free(indexes);
if(error)
{
error->code=0;
error->succ=true;
}
} // function ends

void MSR(void *ptr,int low,int high,int es,OperationDetail *error,int (*p2f)(void *,void *))
{
int mid,succ;
if(low<high)
{
mid=((low+high)/2);
MSR(ptr,low,mid,es,error,p2f);
MSR(ptr,mid+1,high,es,error,p2f);
merge(ptr,low,mid,high,es,p2f,&succ);
}
}

void mergeSortRecursive(void *ptr,int lb,int ub,int es,OperationDetail *error,int (*p2f)(void *,void *))
{
OperationDetail err;
if(error) error->succ=false;
if(error==NULL)
{
if(isInvalid(ptr,&lb,&ub,&es,&err,p2f)) return;
}
else{
if(isInvalid(ptr,&lb,&ub,&es,error,p2f)) return;
}
MSR(ptr,lb,ub,es,error,p2f);
if(error)
{
error->succ=true;
error->code=0;
}
}
void toConvertIntoHeap(void *ptr,int lb,int ub,int es,OperationDetail *error,int (*p2f)(void *,void *))
{
int y,ci,ri;
OperationDetail err;
void *c;
if(error) error->succ=false;
if(error==NULL)
{
if(isInvalid(ptr,&lb,&ub,&es,&err,p2f)) return;
}
else{
if(isInvalid(ptr,&lb,&ub,&es,error,p2f)) return;
}
c=(void *)malloc(es);
if(c==NULL)
{
if(error) error->code=2;
return;
}
if(lb!=0)
{
ptr=ptr+(lb*es);
ub=ub-lb;
lb=0;
}
y=lb+1;
while(y<=ub)
{
ci=y;
while(ci>lb)
{
ri=(ci-1)/2;
if(p2f(ptr+(ci*es),ptr+(ri*es))>0)
{
memcpy(c,(const void *)(ptr+(ci*es)),es);
memcpy((ptr+(ci*es)),(const void *)(ptr+(ri*es)),es);
memcpy((ptr+(ri*es)),(const void *)c,es);
ci=ri;
}
else
{
break;
}
}
y++;
}
if(error)
{
error->code=0;
error->succ=true;
}
free(c);
}


void heapSort(void *ptr,int lb,int ub,int es,OperationDetail *error,int (*p2f)(void *,void *))
{
int swi,y,lci,rci,ri;
OperationDetail err;
void *c;
if(error) error->succ=false;
if(error==NULL)
{
if(isInvalid(ptr,&lb,&ub,&es,&err,p2f)) return;
}
else{
if(isInvalid(ptr,&lb,&ub,&es,error,p2f)) return;
}
if(lb!=0)
{
ptr=ptr+(lb*es);
ub=ub-lb;
lb=0;
}
toConvertIntoHeap(ptr,lb,ub,es,&err,p2f);
if(err.succ==true)
{
c=(void *)malloc(es);
if(c==NULL)
{
if(error) error->code=2;
return;
}
y=ub;
while(y>lb)
{
memcpy(c,(const void *)ptr+(y*es),es);
memcpy(ptr+(y*es),(const void *)ptr+(lb*es),es);
memcpy(ptr+(lb*es),(const void *)c,es);
y--;
ri=lb;
while(ri<y)
{
lci=(ri*2)+1;
if(lci>y) break;
rci=lci+1;
if(rci>y) swi=lci;
else
{
if(p2f(ptr+(lci*es),ptr+(rci*es))>0) swi=lci;
else swi=rci;
}
if(p2f(ptr+(swi*es),ptr+(ri*es))>0)
{
memcpy(c,(const void *)ptr+(swi*es),es);
memcpy(ptr+(swi*es),(const void *)ptr+(ri*es),es);
memcpy(ptr+(ri*es),(const void *)c,es);
ri=swi;
}
else
{
break;
}
}
}
free(c);
if(error)
{
error->succ=true;
error->code=0;
}
}
else
{
if(error) error->code=err.code;
}
}

void anotherRecursiveCallForConvertingHeap(void *ptr,int lb,int ci,int es, void *c,int (*p2f) (void *,void *))
{
int ri;
if(ci>lb)
{
ri=(ci-1)/2;
if(p2f(ptr+(ci*es),ptr+(ri*es))>0)
{
memcpy(c,(const void *)ptr+(ci*es),es);
memcpy(ptr+(ci*es),(const void *)ptr+(ri*es),es);
memcpy(ptr+(ri*es),(const void *)c,es);
anotherRecursiveCallForConvertingHeap(ptr,lb,ri,es,c,p2f);
}
}
}

void convertingIntoHeapUsingRecursive(void *ptr,int y,int ub,int es,void *c,int (*p2f)(void *,void *))
{
int ci;
if(y<=ub)
{
ci=y;
anotherRecursiveCallForConvertingHeap(ptr,0,ci,es,c,p2f);
convertingIntoHeapUsingRecursive(ptr,y+1,ub,es,c,p2f);
}
} // function block ends

void toConvertIntoHeapUsingRecursive(void *ptr,int lb,int ub,int es,OperationDetail *error,int (*p2f)(void *,void *))
{
void *c;
OperationDetail err;
if(error) error->succ=false;
if(error==NULL)
{
if(isInvalid(ptr,&lb,&ub,&es,&err,p2f)) return;
}
else{
if(isInvalid(ptr,&lb,&ub,&es,error,p2f)) return;
}
c=(void *)malloc(es);
if(c==NULL)
{
if(error) error->code=2;
return;
}
if(lb!=0)
{
ptr=ptr+(lb*es);
ub=ub-lb;
lb=0;
}
convertingIntoHeapUsingRecursive(ptr,lb+1,ub,es,c,p2f);
free(c);
if(error)
{
error->succ=true;
error->code=0;
}
} // function block ends

void heapifyLogic(void *ptr,int ri,int y,int es,void *c,int (*p2f) (void *,void *))
{
int lci,rci,swi;
if(ri<y)
{
lci=(ri*2)+1;
if(lci>y) return;
rci=lci+1;
if(rci>y)
{
swi=lci;
}
else
{
if(p2f(ptr+(lci*es),ptr+(rci*es))>0) swi=lci;
else swi=rci;
}
if(p2f(ptr+(swi*es),ptr+(ri*es))>0)
{
memcpy(c,(const void *)ptr+(swi*es),es);
memcpy(ptr+(swi*es),(const void *)ptr+(ri*es),es);
memcpy(ptr+(ri*es),(const void *)c,es);
heapifyLogic(ptr,swi,y,es,c,p2f);
}
}
} // function block ends

void swappingAndHeapifyLogic(void *ptr,int lb,int ub,int es,void *c,int (*p2f) (void *,void *))
{
if(ub>lb)
{
memcpy(c,(const void *)ptr+(lb*es),es);
memcpy(ptr+(lb*es),(const void *)ptr+(ub*es),es);
memcpy(ptr+(ub*es),(const void *)c,es);
ub--;
heapifyLogic(ptr,lb,ub,es,c,p2f);
swappingAndHeapifyLogic(ptr,lb,ub,es,c,p2f);
}
} // function block ends


void heapSortRecursive(void *ptr,int lb,int ub,int es,OperationDetail *error,int (*p2f)(void *,void *))
{
void *c;
OperationDetail err;
if(error) error->succ=false;
if(error==NULL)
{
if(isInvalid(ptr,&lb,&ub,&es,&err,p2f)) return;
}
else{
if(isInvalid(ptr,&lb,&ub,&es,error,p2f)) return;
}
c=(void *)malloc(es);
if(c==NULL)
{
if(error) error->code=2;
return;
}
if(lb!=0)
{
ptr=ptr+(lb*es);
ub=ub-lb;
lb=0;
}
convertingIntoHeapUsingRecursive(ptr,lb+1,ub,es,c,p2f);
swappingAndHeapifyLogic(ptr,lb,ub,es,c,p2f);
free(c);
if(error)
{
error->succ=true;
error->code=0;
}
} // function block ends


// I use this dummy function for radix sort, count sort, insertionSortForDLL validation as predicate;
void radixSort(void *x,int lb,int ub,int es,OperationDetail *error,int decision)
{
int i;
Queue *negQueue,*posQueue;
int largestDigit;
int biggestNumber,biggestNumberDigit;
int smallestNumber,smallestNumberDigit;
int y;
int qIndex;
int index;
int e,f;
int elem;
OperationDetail err;
if(error) error->succ=false;
if(error==NULL)
{
if(isInvalid(x,&lb,&ub,&es,&err,dummy)) return;
}
else{
if(isInvalid(x,&lb,&ub,&es,error,dummy)) return;
}
if(sizeof(int)!=es)
{
if(error) error->code=8;
return;
}
negQueue=createQueue(es,&err);
if(err.succ==false) return;
posQueue=createQueue(es,&err);
if(err.succ==false)
{
destroyQueue(negQueue);
return;
}
memcpy(&biggestNumber,(const void *)x+(lb*es),es);
memcpy(&smallestNumber,(const void *)x+(lb*es),es);
for(y=lb+1;y<=ub;y++)
{
memcpy(&elem,(const void *)x+(y*es),es);
if(biggestNumber<elem) memcpy(&biggestNumber,(const void *)x+(y*es),es);
if(smallestNumber>elem) memcpy(&smallestNumber,(const void *)x+(y*es),es);
}
biggestNumberDigit=0;
while(biggestNumber>0)
{
biggestNumberDigit++;
biggestNumber=biggestNumber/10;
}
smallestNumberDigit=0;
while(smallestNumber<0)
{
smallestNumberDigit++;
smallestNumber=smallestNumber/10;
}
if(smallestNumberDigit>biggestNumberDigit) largestDigit=smallestNumberDigit;
else largestDigit=biggestNumberDigit;
e=1;
f=10;
while(largestDigit>0)
{
i=lb;
while(i<=ub)
{
memcpy(&elem,(const void *)x+(i*es),es);
qIndex=elem%f;
qIndex=qIndex/e;
if(qIndex<0)
{
qIndex=abs(qIndex);
addToQueue(&negQueue[qIndex],(void *)x+(i*es),&err);
if(err.succ==false)
{
for(i=0;i<=9;i++)
{
clearQueue(&negQueue[i]);
clearQueue(&posQueue[i]);
}
if(error) error->code=err.code;
return;
}
i++;
continue;
}
addToQueue(&posQueue[qIndex],(void *)x+(i*es),&err);
if(err.succ==false)
{
for(i=0;i<=9;i++)
{
clearQueue(&negQueue[i]);
clearQueue(&posQueue[i]);
}
if(error) error->code=err.code;
return;
}
i++;
}
if(decision>0)
{
// sorting in accending order
i=9;
index=lb;
while(i>=0)
{
while(!isQueueEmpty(&negQueue[i]))
{
removeFromQueue(&negQueue[i],(void *)x+(index*es),&err);
if(err.succ==false)
{
for(i=0;i<=9;i++)
{
clearQueue(&negQueue[i]);
clearQueue(&posQueue[i]);
}
if(error) error->code=err.code;
return;
}
index++;
}
i--;
}
i=0;
while(i<=9)
{
while(!isQueueEmpty(&posQueue[i]))
{
removeFromQueue(&posQueue[i],(void *)x+(index*es),&err);
if(err.succ==false)
{
for(i=0;i<=9;i++)
{
clearQueue(&negQueue[i]);
clearQueue(&posQueue[i]);
}
if(error) error->code=err.code;
return;
}
index++;
}
i++;
}
}
else
{
// case for decending order.
i=9;
index=lb;
while(i>=0)
{
while(!isQueueEmpty(&posQueue[i]))
{
removeFromQueue(&posQueue[i],(void *)x+(index*es),&err);
if(err.succ==false)
{
for(i=0;i<=9;i++)
{
clearQueue(&negQueue[i]);
clearQueue(&posQueue[i]);
}
if(error) error->code=err.code;
return;
}
index++;
}
i--;
}
i=0;
while(i<=9)
{
while(!isQueueEmpty(&negQueue[i]))
{
removeFromQueue(&negQueue[i],(void *)x+(index*es),&err);
if(err.succ==false)
{
for(i=0;i<=9;i++)
{
clearQueue(&negQueue[i]);
clearQueue(&posQueue[i]);
}
if(error) error->code=err.code;
return;
}
index++;
}
i++;
}
} // else block ends
largestDigit--;
e=e*10;
f=f*10;
}
for(i=0;i<=9;i++)
{
clearQueue(&negQueue[i]);
clearQueue(&posQueue[i]);
}
if(error)
{
error->succ=true;
error->code=0;
}
}
void shellSort(void *ptr,int lb,int ub,int es,OperationDetail *error,int (*p2f)(void *,void *))
{
int y,leastLb,diff;
void *c;
if(error) error->succ=false;
if(error==NULL)
{
OperationDetail err;
if(isInvalid(ptr,&lb,&ub,&es,&err,p2f)) return;
}
else{
if(isInvalid(ptr,&lb,&ub,&es,error,p2f)) return;
}
c=(void *)malloc(es);
if(c==NULL)
{
error->code=2;
return;
}
if(lb!=0)
{
ptr=ptr+(lb*es);
ub=ub-lb;
lb=0;
}
leastLb=lb;
diff=(ub-lb)+1;
diff=diff/2;
while(diff>0)
{
lb=diff;
while(lb<=ub)
{
memcpy(c,(const void *)ptr+(lb*es),es);
y=lb-diff;
while(y>=leastLb && p2f(c,ptr+(y*es))<0)
{
memcpy(ptr+((y+diff)*es),(const void *)(ptr+(y*es)),es);
y=y-diff;
}
memcpy(ptr+((y+diff)*es),(const void *)c,es);
lb=lb+diff;
}
diff=diff/2;
}
free(c);
if(error)
{
error->code=0;
error->succ=true;
}
}

void vShellSortRecursive(void *ptr,int olb,int diff,int ub,int es,void *c,int (*p2f)(void *,void *))
{
if(diff>0)
{
ISR(ptr,olb,diff,diff,ub,es,c,p2f);
vShellSortRecursive(ptr,olb,diff/2,ub,es,c,p2f);
}
}

void shellSortRecursive(void *ptr,int lb,int ub,int es,OperationDetail *error,int (*p2f)(void *,void *))
{
int olb,diff;
void *c;
OperationDetail err;
if(error) error->succ=false;
if(error==NULL)
{
if(isInvalid(ptr,&lb,&ub,&es,&err,p2f)) return;
}
else{
if(isInvalid(ptr,&lb,&ub,&es,error,p2f)) return;
}
c=(void *)malloc(es);
if(c==NULL)
{
if(error) error->code=2;
return;
}
olb=lb;
diff=(ub-lb)+1;
diff=diff/2;
vShellSortRecursive(ptr,olb,diff,ub,es,c,p2f);
free(c);
if(error)
{
error->succ=true;
error->code=0;
}
}

void countSort(void *ptr,int lb,int ub,int es,OperationDetail *error,int decision)
{
int heaviestElement,vHeaviestElement;
int lightestElement,vLightestElement;
int i,j,largestElement;
int *tmpPos,*tmpNeg;
int *x;
x=(int *)ptr;
if(error) error->succ=false;
if(error==NULL)
{
OperationDetail err;
if(isInvalid(ptr,&lb,&ub,&es,&err,dummy)) return;
}
else{
if(isInvalid(ptr,&lb,&ub,&es,error,dummy)) return;
}
if(sizeof(int)!=es)
{
if(error) error->code=8;
return;
}


int localPredicate(void *left,void *right)
{
int *leftOperand,*rightOperand;
leftOperand=(int *)left;
rightOperand=(int *)right;
return (*leftOperand)-(*rightOperand);
}
findingTheHeaviestElement(ptr,lb,ub,es,error,&heaviestElement,localPredicate);
findingTheLightestElement(ptr,lb,ub,es,error,&lightestElement,localPredicate);
vHeaviestElement=heaviestElement;
vLightestElement=lightestElement;
i=0;
while(vHeaviestElement>0)
{
vHeaviestElement/=10;
i++;
}
j=0;
while(vLightestElement<0)
{
vLightestElement/=10;
j++;
}
if(i<j) largestElement=lightestElement;
else largestElement=heaviestElement;
if(largestElement<0) largestElement=largestElement*-1; // now it becomes positive
tmpPos=(int *)malloc(es*(largestElement+1));
if(tmpPos==NULL)
{
if(error)
{
error->code=2;
error->succ=false;
}
return;
}
tmpNeg=(int *)malloc(es*(largestElement+1));
if(tmpNeg==NULL)
{
free(tmpPos);
if(error)
{
error->code=2;
error->succ=false;
}
return;
}
if(decision==ACC)
{
for(i=0;i<=largestElement;i++)
{
tmpPos[i]=0;
tmpNeg[i]=0;
}
j=0;
for(i=lb;i<=ub;i++)
{
if(x[i]<0)
{
j=x[i]*-1; // now it becomes  negative
tmpNeg[j]++;
}
else
{
tmpPos[x[i]]++;
}
}

for(i=largestElement;i>=0;i--)
{
while(tmpNeg[i]!=0)
{
x[lb]=(i*-1);
tmpNeg[i]--;
lb++;
}
}

for(i=0;i<=largestElement;i++)
{
while(tmpPos[i]!=0)
{
x[lb]=i;
tmpPos[i]--;
lb++;
}
}
}
else
{
for(i=0;i<=largestElement;i++)
{
tmpPos[i]=0;
tmpNeg[i]=0;
}
j=0;

for(i=lb;i<=ub;i++)
{
if(x[i]<0)
{
j=x[i]*-1; // now it becomes  negative
tmpNeg[j]++;
}
else
{
tmpPos[x[i]]++;
}
}
for(i=largestElement;i>=0;i--)
{
while(tmpPos[i]!=0)
{
x[lb]=i;
tmpPos[i]--;
lb++;
}
}
for(i=0;i<=largestElement;i++)
{
while(tmpNeg[i]!=0)
{
x[lb]=(i*-1);
tmpNeg[i]--;
lb++;
}
}
}
free(tmpPos);
free(tmpNeg);
if(error)
{
error->code=0;
error->succ=true;
}
}

void pancakeSort(void *ptr,int lb,int ub,int es,OperationDetail *error,int (*p2f) (void *,void *))
{
int iub,i,j;
void *c;
OperationDetail err;
if(error) error->succ=false;
if(error==NULL)
{
if(isInvalid(ptr,&lb,&ub,&es,&err,p2f)) return;
}
else
{
if(isInvalid(ptr,&lb,&ub,&es,error,p2f)) return;
}
c=(void *)malloc(es);
if(c==NULL)
{
if(error) error->code=2;
return;
}
iub=ub;
while(iub>lb)
{
findingTheHeaviestElementIndex(ptr,lb,iub,es,error,&j,p2f);
if(j==iub)
{
iub--;
continue;
}
while(j>lb)
{
memcpy(c,(const void *)ptr+(j*es),es);
memcpy(ptr+(j*es),(const void *)ptr+((j-1)*es),es);
memcpy(ptr+((j-1)*es),(const void *)c,es);
j--;
}
i=lb;
j=iub;
while(i<j)
{
memcpy(c,(const void *)ptr+(i*es),es);
memcpy(ptr+(i*es),(const void *)ptr+(j*es),es);
memcpy(ptr+(j*es),(const void *)c,es);
i++;
j--;
}
iub--;
}
free(c);
if(error)
{
error->code=0;
error->succ=true;
}
}

void flipTheWholeCake(void *ptr,int lb,int ub,int es,void *c)
{
if(lb<ub)
{
memcpy(c,(const void *)ptr+(lb*es),es);
memcpy(ptr+(lb*es),(const void *)ptr+(ub*es),es);
memcpy(ptr+(ub*es),(const void *)c,es);
flipTheWholeCake(ptr,++lb,--ub,es,c);
}
}

void flipTheBurntCake(void *ptr,int lb,int ub,int es,void *c)
{
if(ub>lb)
{
memcpy(c,(const void *)ptr+(ub*es),es);
memcpy(ptr+(ub*es),(const void *)ptr+((ub-1)*es),es);
memcpy(ptr+((ub-1)*es),(const void *)c,es);
flipTheBurntCake(ptr,lb,--ub,es,c);
}
}

void vPancakeSortRecursive(void *ptr,int lb,int ub,int es,void *c,int (*p2f) (void *,void *))
{
int j,iub=ub;
if(iub>lb)
{
findingTheHeaviestElementIndex(ptr,lb,iub,es,NULL,&j,p2f);
if(j==iub)
{
vPancakeSortRecursive(ptr,lb,--ub,es,c,p2f);
return;
}
flipTheBurntCake(ptr,lb,j,es,c);
flipTheWholeCake(ptr,lb,iub,es,c);
vPancakeSortRecursive(ptr,lb,--ub,es,c,p2f);
}
}

void pancakeSortRecursive(void *ptr,int lb,int ub,int es,OperationDetail *error,int (*p2f) (void *,void *))
{
void *c;
OperationDetail err;
if(error) error->succ=false;
if(error==NULL)
{
if(isInvalid(ptr,&lb,&ub,&es,&err,p2f)) return;
}
else
{
if(isInvalid(ptr,&lb,&ub,&es,error,p2f)) return;
}
c=(void *)malloc(es);
if(c==NULL)
{
if(error) error->code=2;
return;
}
vPancakeSortRecursive(ptr,lb,ub,es,c,p2f);
free(c);
if(error)
{
error->succ=true;
error->code=0;
}
}

void addressCalculationSort(void *ptr,int lb,int ub,int es,OperationDetail *error,int decision)
{
int largestDigit;
int biggestNumber,biggestNumberDigit;
int smallestNumber,smallestNumberDigit;
int i,j,index;
int key;
DoublyLinkedList **dll;
OperationDetail err;
if(error) error->succ=false;
if(error==NULL)
{
if(isInvalid(ptr,&lb,&ub,&es,&err,dummy)) return;
}
else{
if(isInvalid(ptr,&lb,&ub,&es,error,dummy)) return;
}
if(sizeof(int)!=es)
{
if(error) error->code=8;
return;
}
dll=(DoublyLinkedList **)malloc(sizeof(DoublyLinkedList *)*10);
for(i=0;i<=9;i++)
{
dll[i]=createDoublyLinkedList(sizeof(int),error);
if(error->succ==false)
{
for(j=i-1;j>=0;j--) destroyDoublyLinkedList(dll[j]);
free(dll);
return;
}
}
findingTheHeaviestElement(ptr,lb,ub,es,error,&biggestNumber,INT_HEAVIEST_ELEMENT_COMPARATOR);
findingTheHeaviestElement(ptr,lb,ub,es,error,&smallestNumber,INT_LIGHTEST_ELEMENT_COMPARATOR);
biggestNumberDigit=0;
while(biggestNumber!=0)
{
biggestNumber=biggestNumber/10;
biggestNumberDigit++;
}
smallestNumberDigit=0;
while(smallestNumber!=0)
{
smallestNumber=smallestNumber/10;
smallestNumberDigit++;
}
if(biggestNumberDigit<smallestNumberDigit) largestDigit=smallestNumberDigit;
else largestDigit=biggestNumberDigit;
for(i=lb;i<=ub;i++)
{
key=HASH_FUNCTION_FOR_ADDRESS_CALCULATION_AKA_BUCKET_SORT((*(int *)(ptr+(i*es))),largestDigit);
if(key<=0)
{
addToDoublyLinkedList(dll[0],(const void *)ptr+(i*es),error);
if(error->succ==false)
{
for(j=0;j<=9;j++) destroyDoublyLinkedList(dll[j]);
free(dll);
return;
}
}
else
{
addToDoublyLinkedList(dll[key],(const void *)ptr+(i*es),error);
if(error->succ==false)
{
for(j=0;j<=9;j++) destroyDoublyLinkedList(dll[j]);
free(dll);
return;
}
} // else block ends
}
for(i=0;i<=9;i++)
{
if(decision==ACC)
{
insertionSortForDLL(dll[i],0,getSizeOfDoublyLinkedList(dll[i])-1,error,INT_HEAVIEST_ELEMENT_COMPARATOR);
if(error->succ==false && error->code!=1)
{
for(j=0;j<=9;j++) destroyDoublyLinkedList(dll[j]);
free(dll);
return;
}
}
else
{
insertionSortForDLL(dll[i],0,getSizeOfDoublyLinkedList(dll[i])-1,error,INT_LIGHTEST_ELEMENT_COMPARATOR);
if(error->succ==false && error->code!=1)
{
for(j=0;j<=9;j++) destroyDoublyLinkedList(dll[j]);
free(dll);
return;
}
}
}
if(decision==ACC)
{
index=lb;
for(i=0;i<=9;i++)
{
while(getSizeOfDoublyLinkedList(dll[i])!=0)
{
removeFromDoublyLinkedList(dll[i],ptr+(index*es),0,error);
index++;
}
}
}
else
{
index=lb;
for(i=9;i>=0;i--)
{
while(getSizeOfDoublyLinkedList(dll[i])!=0)
{
removeFromDoublyLinkedList(dll[i],(void *)ptr+(index*es),0,error);
index++;
} // while loop ends
} // for loop ends
} // else block ends
for(j=0;j<=9;j++) destroyDoublyLinkedList(dll[j]);
free(dll);
if(error)
{
error->succ=true;
error->code=0;
}
} // function ends
#endif