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
