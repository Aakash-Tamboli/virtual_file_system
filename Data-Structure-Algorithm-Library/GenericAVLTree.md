## Generic Stack   
### Description of Main functions :

* To `create` AVL Tree  
  ```c
  AVLTree * createAVLTree(OperationDetail *,int (*)(void *,void *));
  ```
  here the predicate funtion is required to create AVLTree (comparator funtion).  
  `OperationDetail oper;`  
  `AVLTree *tree;`  
  `tree=createAVLTree(&oper,predicate);`  
  if(`oper.succ==true`) tree is created.  
  if(`oper.succ==false`) tree is not created.  
* To `add/insert` in AVL Tree
  ```c
  void addToAVLTree(AVLTree *,void *,OperationDetail *);  
  void insertIntoAVLTree(AVLTree *,void *,OperationDetail *);
  ```
  both the funtions are use for adding and inserting new data in AVL Tree.  
  `OperationDetail oper;`  
  `int i=100;`  
  `addToAVLTree(tree,(void *)&i,&oper);`  
   if(`oper.succ==true`) element is added.  
   if(`oper.succ==false`) element is not added.  
   similary we can use insertIntoAVLTree function.  
* To `get size` of AVL Tree
  ```c
  int getSizeOfAVLTree(AVLTree *);
  ```
  `int size;`  
  `size=getSizeOfAVLTree(tree);`  
* To `remove` element from AVL Tree
  ```c
  void * removeFromAVLTree(AVLTree *,void *,OperationDetail *);
  ```
  `OperationDetail oper;`  
  `int i=100;` (element to remove from tree)  
  `void *ptr;`  
  `ptr=removeFromAVLTree(avlTree,(void *)i,&oper);` (ptr will store the address of removed element, which is i)  
  if(`oper.succ==true`) element is removed.  
  if(`oper.succ==false`) element is not removed.  

* To `get an element` from AVL Tree  
  ```c
  void * getFromAVLTree(AVLTree *,void *,bool *);
  ```
  `OperationDetail oper;`  
  `int i=100;` (element to get from tree)  
  `void *ptr;`  
  `ptr=removeFromAVLTree(avlTree,(void *)i,&oper);` (ptr will store the address of element to get, which is i)  
  if(`oper.succ==true`) element is received in ptr.  
  if(`oper.succ==false`) element is not received int ptr.  
* To `get height` of AVL Tree
  ```c
  int getHeightOfAVLTree(AVLTreeNode *);
  ```
  `int height;`  
  `getHeightOfAVLTree(avlTree);`  
* To `clear` the AVL Tree  
  ```c
  void clearAVLTree(AVLTree *);
  ```
  use to free (remove) all nodes of tree (size of tree is zero).  
  `clearAVLTree(tree);`  
* To `delete/destroy` the AVL Tree  
  ```c
  void destroyAVLTree(AVLTree *);
  ```
  use to delete the tree.  
  `destroyAVLTree(tree);`  
  ***  
### Description of Iterator functions of AVL Tree:  

* To `create iterator` of AVLTree
  ```c
  AVLTreeInOrderIterator getAVLTreeInOrderIterator(AVLTree *,OperationDetail *);  
  AVLTreePreOrderIterator getAVLTreePreOrderIterator(AVLTree *,OperationDetail *);  
  AVLTreePostOrderIterator getAVLTreePostOrderIterator(AVLTree *,OperationDetail *);  
  ```
  `AVLTreeInOrderIterator it;`  
  `OperationDetail oper;`  
  `it=getAVLTreeInOrderIterator(tree,&oper);`  
  if(`oper.succ==true`) iterator (it) is created.  
  if(`oper.succ==false`) iterator (it) is not created.  
  similary we can create iterator for pre order and post order traversal.
  
* To `check iterator's position` in AVL Tree  
  ```c
  bool hasNextInOrderElementInAVLTree(AVLTreeInOrderIterator *);  
  
  bool hasNextPreOrderElementInAVLTree(AVLTreePreOrderIterator *);  
  bool hasNextPostOrderElementInAVLTree(AVLTreePostOrderIterator *);  
  ```
  `bool check;`  
  `check=hasNextInOrderElementInAVLTree(&it);`  
  if(`check==true`) next element is exist in the tree traversal.  
  if(`check==false`) iterator is at end of the tree traversal.  
  similary we can use pre order and post order function.  

* To `check iterator's position` in AVL Tree  
  ```c
  void * getNextInOrderElementFromAVLTree(AVLTreeInOrderIterator *,OperationDetail *);  
  void * getNextPreOrderElementFromAVLTree(AVLTreePreOrderIterator *,OperationDetail *);  
  void * getNextPostOrderElementFromAVLTree(AVLTreePostOrderIterator *,OperationDetail *);  
  ```
  In this function iterator will return the current pointing element (data of node) and traverse one step forward.  
  `void * ptr;`  
  `OperationDetail oper;`  
  `ptr=getNextInOrderElementFromAVLTree(&it,&oper);`  
  if(`oper.succ==true`) element is received in ptr.  
  if(`oper.succ==false`)  element is not received in ptr.  
  similary we can use pre order and post order function.  
  ***
### Use Of AVL Tree :
```c
#include<ds.h>
#include<stdio.h>
int comparator(void *left,void *right)
{
int *i,*j;
i=(int *)left;
j=(int *)right;
return (*i)-(*j);
}
int main()
{
OperationDetail oper;
AVLTree *avltree;
AVLTreeInOrderIterator avlTreeInOrderIterator;
AVLTreePreOrderIterator avlTreePreOrderIterator;
AVLTreePostOrderIterator avlTreePostOrderIterator;
int i,j,k;
int number[12];
int retriveNumber[10];
int *m,*a,*b,*c,*d,*e,*f,*g,*h;
number[0]=40;
number[1]=30;
number[2]=50;
number[3]=25;
number[4]=35;
number[5]=60;
number[6]=45;
number[7]=15;
number[8]=28;
number[9]=55;
number[10]=70;

avltree=createAVLTree(&oper,comparator);
if(oper.succ==true) printf("AVLTree Created\n");

for(i=0;i<11;i++)
{
insertIntoAVLTree(avltree,(void *)&number[i],&oper);
if(oper.succ==true) printf("%d is add into tree\n",number[i]);
else printf("some problem\n");
}
/*
Just to check functionality of removeAVLTree
a=removeFromAVLTree(avltree,(void *)&number[0],&succ);
printf("%d == %d\n",number[0],*a);
b=removeFromAVLTree(avltree,(void *)&number[1],&succ);
printf("%d == %d\n",number[1],*b);
c=removeFromAVLTree(avltree,(void *)&number[2],&succ);
printf("%d == %d\n",number[2],*c);
d=removeFromAVLTree(avltree,(void *)&number[3],&succ);
printf("%d == %d\n",number[3],*d);
e=removeFromAVLTree(avltree,(void *)&number[4],&succ);
printf("%d == %d\n",number[4],*e);
f=removeFromAVLTree(avltree,(void *)&number[5],&succ);
printf("%d == %d\n",number[5],*f);
g=removeFromAVLTree(avltree,(void *)&number[6],&succ);
printf("%d == %d\n",number[6],*g);
h=removeFromAVLTree(avltree,(void *)&number[7],&succ);
printf("%d == %d\n",number[7],*h);
m=removeFromAVLTree(avltree,(void *)&number[8],&succ);
printf("%d == %d\n",number[8],*m);
*/

// checking functionality related to InOrderIteratorOfAVLTree
printf("----------------------------- IN ORDER _-------------------------------\n");
avlTreeInOrderIterator=getAVLTreeInOrderIterator(avltree,&oper);
if(oper.succ==true)
{
while(hasNextInOrderElementInAVLTree(&avlTreeInOrderIterator))
{
a=getNextInOrderElementFromAVLTree(&avlTreeInOrderIterator,&oper);
if(oper.succ==true) printf("value of %d\n",*a);
else printf("something wrong\n");
}
}
else
{
printf("No Iterator Gets\n");
}

// checking functionality of PreOrderIteratorofAvl trr
printf("-----------------------------------PRE ORDER --------------------------------\n");
avlTreePreOrderIterator=getAVLTreePreOrderIterator(avltree,&oper);
if(oper.succ==true)
{
while(hasNextPreOrderElementInAVLTree(&avlTreePreOrderIterator))
{
a=getNextPreOrderElementFromAVLTree(&avlTreePreOrderIterator,&oper);
if(oper.succ==true) printf("value of %d\n",*a);
else printf("something wrong\n");
}
}
else
{
printf("No Iterator Gets\n");
}


// checking functionality of postOrder Iterator
printf("_----------------------------------------POST ORDER ----------------------------------\n");
avlTreePostOrderIterator=getAVLTreePostOrderIterator(avltree,&oper);
if(oper.succ==true)
{
while(hasNextPostOrderElementInAVLTree(&avlTreePostOrderIterator))
{
a=getNextPostOrderElementFromAVLTree(&avlTreePostOrderIterator,&oper);
if(oper.succ==true) printf("value of %d\n",*a);
else printf("something wrong\n");
}
}
else
{
printf("No Iterator Gets\n");
}
destroyAVLTree(avltree);
return 0;
}
```
