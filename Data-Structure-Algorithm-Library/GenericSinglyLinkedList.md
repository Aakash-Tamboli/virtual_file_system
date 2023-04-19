## Generic Singly Linked List  
### Description of Main functions :

* To `create` SinglyLinkedList
   ```c
   SinglyLinkedList * createSinglyLinkedList(int,OperationDetail *)
   ```
   `int sizeOfOneElement;`  
   `OperationDetail err;`  
    `SinglyLinkedList *list;`  
    sizeOfOneElement=sizeof(int);  
    `list=createSinglyLinkedList(sizeOfOneElement,&err);`  
    if(`err.succ==true`) list is created.  
    if(`err.succ==false`) list is not created.  
		

* To `add` element in Singly Linked List
  ```c
  void addToSinglyLinkedList(SinglyLinkedList *,void *,OperationDetail *);
  ```
  `OperationDetail err;`  
  `int i=100;`  
  `addToSinglyLinkedList(list,(void *)&i,&err);`  
   if(`err.succ==true`) element is added.   
   if(`err.succ==false`) element is not added.  
    
* To `insert` element in Singly Linked List
   ```c
   void insertIntoSinglyLinkedList(SinglyLinkedList *,int,void *,OperationDetail *);
   ```
   `OperationDetail err;`  
  `int i=100;`  
  `int index;` (position to insert element in list)  
  `insertIntoSinglyLinkedList(list,index,(void *)&i,&err);`  
   if(`err.succ==true`) element is inserted.  
   if(`err.succ==false`) element is not   inserted.  
   
* To `remove` element from Singly Linked List
  ```c
  void removeFromSinglyLinkedList(SinglyLinkedList *,void *,int,OperationDetail *);
  ```
  `OperationDetail err;`  
  `int Element;`  
  `int index;` (position to remove element in list)  
  `removeFromSinglyLinkedList(list,&Element,index,&err);`  
  if(`err.succ==true`) element is removed.  
  if(`err.succ==false`) element is not removed.  

* To `get size` of Singly Linked List
  ```c
  int getSizeOfSinglyLinkedList(SinglyLinkedList *);
  ```
  `int size;`  
  `size=getSizeOfSinglyLinkedList(list);`  
* To `get an element` from Singly Linked List  
  ```c
  void getFromSinglyLinkedList(SinglyLinkedList *,void *,int,OperationDetail *);
  ```
  `OperationDetail err;`  
  `int Element;`  
  `int index;`  
  `getFromSinglyLinkedList(list,(void *)&Element,index,&err);`   
  if(`err.succ==true`) data is received in Element variable.  
  if(`err.succ==false`) data is not received in Element variable.  
  
* To `merge one list into another list` of Singly Linked List  
  ```c
	void appendToSinglyLinkedList(SinglyLinkedList *,SinglyLinkedList *,OperationDetail *);
  ```
  we have `list_1` and `list_2` of SinglyLinkedList.  
  for merging `list_1` into `list_2`.  
	`OperationDetail err;`   
  `appendToSinglyLinkedList(list_1,list_2,&err);`  
	if(`err.succ==true`) lists are merged.  
  if(`err.succ==false`) lists are not merged.  

* To `clear` the Singly Linked List  
  ```c
	void clearSinglyLinkedList(SinglyLinkedList *);
  ```
  use to free (remove) nodes of list (size of list is zero).  
  `clearSinglyLinkedList(list);`  
* To `delete/destroy` the Singly Linked List    
  ```c
	void destroySinglyLinkedList(SinglyLinkedList *);
  ```
  use to delete the list.  
  `destroySinglyLinkedList(list);`  
  ***  
### Description of Iterator functions of Singly Linked List:  

* To `create iterator` of Singly Linked List
  ```c
	SinglyLinkedListIterator getSinglyLinkedListIterator(SinglyLinkedList *,OperationDetail *);
  ```
  `SinglyLinkedListIterator it;`      
	`OperationDetail err;`   
  `it=getSinglyLinkedListIterator(list,&err);`  
	if(`err.succ==true`) iterator (it) is created.  	
  if(`err.succ==false`) iterator (it) is not created.  
  
* To `check iterator's position` in Singly Linked List
  ```c
	bool hasNextInSinglyLinkedList(SinglyLinkedListIterator *);
  ```
  `bool check;`  
  `check=hasNextInSinglyLinkedList(&it);`  
  if(`check==true`) next element is exist in the list.  
  if(`check==false`) iterator is at end of the list.  

* To `check iterator's position` in Singly Linked List  
  ```c
	void getNextElementFromSinglyLinkedList(SinglyLinkedListIterator *,void *,OperationDetail *);
  ```
  In this function iterator will return the current pointing element (address) and traverse one step forward.  
  `int Element`   
	`OperationDetail err;`   
  `getNextElementFromSinglyLinkedList(&it,(void *)&Element,&err);   
	if(`err.succ==true`) data is received in Element Variable.  
  if(`err.succ==false`) data is not received  
  
  ***
### Use Of Singly Linked List :
  ```c
  #include<ds.h>
  #include<stdio.h>
  int main()
  {
  int i1,i2,i3;
  int y,Element;
  OperationDetail err;
  SinglyLinkedList *list1;
  list1=createSinglyLinkedList(sizeof(int),&err);
  if(err.succ==false)
  {
  printf("Unable to create list");
  return 0;
  }
  printf("List Created\n");
  i1=100;
  i2=200;
  i3=300;

  //adding data
  addToSinglyLinkedList(list1,(void *)&i1,&err);
  if(err.succ) printf("%d added to list1\n",i1);
  else printf("Unable to add %d to list1\n",i1);
  //adding data
  addToSinglyLinkedList(list1,(void *)&i2,&err);
  if(err.succ) printf("%d added to list1\n",i2);
  else printf("Unable to add %d to list1\n",i2);
  //inserting data
  insertIntoSinglyLinkedList(list1,1,(void *)&i3,&err);
  if(err.succ) printf("%d inserted to list1\n",i3);
  else printf("Unable to insert %d to list1\n",i3);
  //size of list
  printf("Size of list1 is %d\n",getSizeOfSinglyLinkedList(list1));

  //use of iterator
  SinglyLinkedListIterator it;
  it=getSinglyLinkedListIterator(list1,&err);
  if(err.succ)
  {
  while(hasNextInSinglyLinkedList(&it))
  {
  getNextElementFromSinglyLinkedList(&it,(void *)&Element,&err);
  printf("%d\n",Element);
  }
  }
 
  //removing data of 0 index
  removeFromSinglyLinkedList(list1,(void *)&Element,0,&err);
  if(err.succ) printf("%d removed list1\n",Element);
  else printf("Unable to remove");
 
  //clearing list
  clearSinglyLinkedList(list1);

  //destroying list
  destroySinglyLinkedList(list1);
  return 0;
  }
  ```
