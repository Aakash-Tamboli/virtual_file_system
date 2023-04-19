## Generic Stack   
### Description of Main functions :

* To `create` Stack
   ```c
   Stack * createStack(int,OperationDetail *);
   ```
   `int sizeOfOneElement;`  
   `OperationDetail err;`  
    `Stack *stack;`  
    sizeOfOneElement=sizeof(int);  
    `stack=createStack(sizeOfOneElement,&err);`  
    if(`err.succ==true`) stack is created.  
    if(`err.succ==false`) stack is not created.  
		

* To `Push` element in Stack
  ```c
  void pushOnStack(struct __Stack__ *,const void *,OperationDetail *);
  ```
  `OperationDetail err;`  
  `int i=100;`  
  `pushOnStack(stack,(const void *)&i,&err);`  
   if(`err.succ==true`) element is pushed.   
   if(`err.succ==false`) element is not pushed.  
    

* To `Pop` element from Stack
  ```c
  void popFromStack(struct __Stack__ *,void *,OperationDetail *);
  ```
  `OperationDetail err;`  
  `int Element;`  
  `popFromStack(stack,(void *)&Element,&err);`  
  if(`err.succ==true`) element is poped.  
  if(`err.succ==false`) element is not poped.  

* To `clear` the Stack  
  ```c
	void clearStack(struct __Stack__ *);
  ```
  `clearStack(stack);`  
* To `delete/destroy` the Stack    
  ```c
	void destroyStack(struct __Stack__ *);
  ```
  use to delete the Stack.  
  `destroyStack(stack);`  
  ***  

* To `check Element At Top Of Stack` in Stack
  ```c
  void elementAtTopOfStack(struct __Stack__ *,void *,OperationDetail *);
  ```
  `int Element`   
  `OperationDetail err;`   
  `getElementAtTopOfStack(stack,(void *)&Element,&err);`   
  if(`err.succ==true`) data is received in Element Variable.  
  if(`err.succ==false`) data is not received  
  
  ***
### Use Of Stack :
  ```c
  #include<ds.h>
  #include<stdio.h>
  int main()
  {
  int i1,i2,i3;
  int y,Element;
  OperationDetail err;
  Stack *stack;
  stack=createStack(sizeof(int),&err);
  if(err.succ==false)
  {
  printf("Unable to create stack");
  return 0;
  }
  printf("stack Created\n");
  i1=100;
  i2=200;
  i3=300;

  //pushing data
  pushOnStack(stack,(void *)&i1,&err);
  if(err.succ) printf("%d added to stack\n",i1);
  else printf("Unable to add %d to stack\n",i1);
  //pushing data
  pushOnStack(stack,(void *)&i2,&err);
  if(err.succ) printf("%d added to stack\n",i2);
  else printf("Unable to add %d to stack\n",i2);
  //pushing data
  pushOnStack(stack,(void *)&i3,&err);
  if(err.succ) printf("%d added to stack\n",i3);
  else printf("Unable to add %d to stack\n",i3);
  //removing data of 0 index
  popFromStack(stack,(void *)&Element,&err);
  if(err.succ) printf("%d poped stack\n",Element);
  else printf("Unable to pop");
   //clearing stack
  clearStack(stack);
  //destroying stack
  destroyStack(stack);
  return 0;
  }
  ```
