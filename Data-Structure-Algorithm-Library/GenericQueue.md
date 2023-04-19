## Generic Queue   
### Description of Main functions :

* To `create` Queue
   ```c
   Queue * createQueue(int,OperationDetail *);
   ```
   `int sizeOfOneElement;`  
   `OperationDetail err;`  
    `Queue *queue;`  
    sizeOfOneElement=sizeof(int);  
    `queue=createQueue(sizeOfOneElement,&err);`  
    if(`err.succ==true`) queue is created.  
    if(`err.succ==false`) queue is not created.  
		

* To `add` element in Queue
  ```c
  void addToQueue(struct __Queue__ *,const void *,OperationDetail *);
  ```
  `OperationDetail err;`  
  `int i=100;`  
  `addToQueue(queue,(const void *)&i,&err);`  
   if(`err.succ==true`) element is added.   
   if(`err.succ==false`) element is not added.  
    

* To `remove` element from Queue
  ```c
  void removeFromQueue(struct __Queue__ *,void *,OperationDetail *);
  ```
  `OperationDetail err;`  
  `int Element;`  
  `removeFromQueue(queue,(void *)&Element,&err);`  
  if(`err.succ==true`) element is removed.  
  if(`err.succ==false`) element is not removed.  


* To `remove` element from Queue
  ```c
  int isQueueEmpty(struct __Queue__ *queue)
  ```
  `int status`
  `status=isQueueEmpty(queue);`
  if(`status==true`) queue is empty
  if(`status==false`) queue is not empty


* To `clear` the Queue  
  ```c
	void clearQueue(struct __Queue__ *);
  ```
  `clearStack(queue);` 

* To `delete/destroy` the Queue    
  ```c
	void destroyQueue(struct __Queue__ *);
  ```
  It is use to delete the Queue.  
  `destroyStack(queue);`  
  ***  

### Use Of Queue :
  ```c
  #include<ds.h>
  #include<stdio.h>
  int main()
  {
  int i1,i2,i3;
  int y,Element;
  OperationDetail err;
  Queue *queue;
  queue=createQueue(sizeof(int),&err);
  if(err.succ==false)
  {
  printf("Unable to create queue");
  return 0;
  }
  printf("queue Created\n");
  i1=100;
  i2=200;
  i3=300;

  //pushing data
  addToQueue(queue,(void *)&i1,&err);
  if(err.succ) printf("%d added to queue\n",i1);
  else printf("Unable to add %d to queue\n",i1);
  //pushing data
  addToQueue(queue,(void *)&i2,&err);
  if(err.succ) printf("%d added to queue\n",i2);
  else printf("Unable to add %d to queue\n",i2);
  //pushing data
  addToQueue(queue,(void *)&i3,&err);
  if(err.succ) printf("%d added to queue\n",i3);
  else printf("Unable to add %d to queue\n",i3);
  //removing data of 0 index
  removeFromQueue(queue,(void *)&Element,&err);
  if(err.succ) printf("%d poped queue\n",Element);
  else printf("Unable to pop");
   //clearing queue
  clearQueue(queue);
  //destroying queue
  destroyQueue(queue);
  return 0;
  }
  ```
