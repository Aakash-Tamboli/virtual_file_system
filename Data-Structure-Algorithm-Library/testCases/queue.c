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
