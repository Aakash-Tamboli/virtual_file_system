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
