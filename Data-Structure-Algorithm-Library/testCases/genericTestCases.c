#include<stdio.h>
#include<stdlib.h>
#include<algo.h>

typedef struct student
{
int roll;
char name[32];
}Student;

int studentComparator(void *left,void *right) // (boolian predicate)
{
Student *s1,*s2;
s1=(Student *)left;
s2=(Student *)right;
return s1->roll-s2->roll;
}

int INTComparator(void *left,void *right)
{
int *i,*j;
i=(int *)left;
j=(int *)right;
return (*i)-(*j);
}
int main()
{
Student *s;
OperationDetail err;
int *x,req,i,lb,ub,intType,decision;
intType=0;
printf("What do you want to sort: 1) intType 2) studentType\n");
scanf("%d",&decision);
fflush(stdin);
if(decision==1) intType=1;
else if(decision==2) intType=0;
else
{
printf("You want to crash this application\n");
return 0;
}
if(intType)
{
printf("Enter your requirement: ");
scanf("%d",&req);
fflush(stdin);
if(req<=0) return 0;
x=(int *)malloc(sizeof(int)*req);
for(i=0;i<req;i++)
{
printf("Enter an Number: ");
scanf("%d",&x[i]);
fflush(stdin);
}
printf("Enter lb point: ");
scanf("%d",&lb);
fflush(stdin);
printf("Enter ub point: ");
scanf("%d",&ub);
fflush(stdin);
quickSort(x,lb,ub,sizeof(int),&err,INTComparator);
if(err.succ) printf("your collection is Sorted\n");
else printf("something wrong error code is: %d\n",err.code);
for(i=0;i<req;i++) printf("%d\n",x[i]);
free(x);
}
else
{
printf("Enter your requirement: ");
scanf("%d",&req);
fflush(stdin);
if(req<=0) return 0;
s=(Student *)malloc(sizeof(Student)*req);
for(i=0;i<req;i++)
{
printf("Enter an Student Roll-Number: ");
scanf("%d",&s[i].roll);
fflush(stdin);
printf("Enter an Student Name: ");
scanf("%s",&(s[i].name));
fflush(stdin);
}
printf("Enter lb point: ");
scanf("%d",&lb);
fflush(stdin);
printf("Enter ub point: ");
scanf("%d",&ub);
fflush(stdin);
quickSort(s,lb,ub,sizeof(Student),&err,studentComparator);
if(err.succ) printf("your collection is Sorted\n");
else printf("something wrong check error code\n");
for(i=0;i<req;i++)
{
printf("Student Name: %s,Roll Number: %d\n",s[i].name,s[i].roll);
}
free(s);
}
return 0;
}