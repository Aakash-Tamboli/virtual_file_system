#include<stdio.h>
#include<stdio_ext.h> // for __fpurge
#include<stdlib.h>
#include<string.h>
#include<fcntl.h>
#include<unistd.h>
#include<errno.h>
#include<ds.h>

// global variables and structure declaration starts
typedef struct __$__path_log_DS
{
char current_working_directory[1001];
char path_log[1001];
}PATH_DS;

typedef struct __$__Input
{
int argc;
char command[11];
char argument1[101];
char argument2[101];
}Input;

typedef struct __header
{
int number_of_files_directories;
unsigned long long int new_record_for_ds_byte;
unsigned long long int new_record_for_acutal_data_byte;
}Header;

typedef struct __$__DATA_STRUCTURE
{
int file_size;
char file_name[101];
char parent_directory[1001];
unsigned long long int starting_byte_information;
unsigned long long int end_information;
}DATA_STRUCTURE;

int comparator(void *left,void *right)
{
DATA_STRUCTURE *i,*j;
i=(DATA_STRUCTURE *)left;
j=(DATA_STRUCTURE *)right;
if(strcmp(i->file_name,j->file_name)==0)
{
return strcmp(i->parent_directory,j->parent_directory);
}
else
{
return strcmp(i->file_name,j->file_name);
}
}

PATH_DS global_path;
char FILE_NAME[10]="tmfs.fs";
int permission_mode=S_IXUSR | S_IRUSR | S_IWUSR | S_IXGRP | S_IRGRP | S_IWGRP | S_IXOTH | S_IROTH;
int global_file_descriptor;
AVLTree *avlTree;

// global variables declaration ends


// forward declaration of function starts
int populateDataStructure();
void show_current_working_directory();
void copy_data(Input *);
void list_of_content();
void makeDirectory(Input *);
void changeDirectory(Input *);
void displayFileContent(Input *);
// forward declaration of function ends

// utility functions for populateDataStructure starts
int create_file_and_prepare_database()
{
Header header;
int api_result;
char character='|';
OperationDetail success;

global_file_descriptor=open(FILE_NAME,O_RDWR | O_CREAT,permission_mode);
if(global_file_descriptor==-1) return 0;
header.number_of_files_directories=0;
header.new_record_for_ds_byte=sizeof(Header);
header.new_record_for_acutal_data_byte=1048579;
api_result=write(global_file_descriptor,&header,sizeof(Header));
if(api_result==-1)
{
remove(FILE_NAME);
return 0;
}
api_result=lseek(global_file_descriptor,999976,SEEK_SET);
if(api_result==-1)
{
remove(FILE_NAME);
printf("Error No: %d\n",errno);
return 0;
}
api_result=write(global_file_descriptor,&character,1);
if(api_result==-1)
{
remove(FILE_NAME);
printf("Error No: %d\n",errno);
return 0;
}
api_result=lseek(global_file_descriptor,2000000,SEEK_SET);
if(api_result==-1)
{
remove(FILE_NAME);
printf("Error No: %d\n",errno);
return 0;
}
api_result=write(global_file_descriptor,&character,1);
if(api_result==-1)
{
remove(FILE_NAME);
printf("Error No: %d\n",errno);
return 0;
}
avlTree=createAVLTree(&success,comparator);
if(success.succ==false)
{
printf("Unable to load data structure\n");
return 0;
}
return 1;
}

void releasingTheMemory()
{
OperationDetail success;
AVLTreeInOrderIterator inorderIterator;
DATA_STRUCTURE *ds=NULL;
inorderIterator=getAVLTreeInOrderIterator(avlTree,&success);
if(success.succ==true)
{
while(hasNextInOrderElementInAVLTree(&inorderIterator))
{
ds=(DATA_STRUCTURE *)getNextInOrderElementFromAVLTree(&inorderIterator,&success);
if(success.succ==true) free(ds);
}
}
clearAVLTree(avlTree);
destroyAVLTree(avlTree);
}

int load_data_structure_into_our_tree()
{
Header header;
OperationDetail success;
int i,api_result;
DATA_STRUCTURE *ds;
api_result=lseek(global_file_descriptor,0,SEEK_SET);
if(api_result==-1) return 0;
avlTree=createAVLTree(&success,comparator);
if(success.succ==false) return 0;
api_result=read(global_file_descriptor,&header,sizeof(Header));
if(api_result==-1)
{
destroyAVLTree(avlTree);
return 0;
}
i=0;
while(i<header.number_of_files_directories)
{
ds=(DATA_STRUCTURE *)malloc(sizeof(DATA_STRUCTURE));
if(ds!=NULL)
{
api_result=read(global_file_descriptor,ds,sizeof(DATA_STRUCTURE));
if(api_result==-1)
{
releasingTheMemory(avlTree);
return 0;
}
else
{
addToAVLTree(avlTree,(void *)ds,&success);
if(success.succ==false)
{
releasingTheMemory(avlTree);
return 0;
}
}
}
else
{
releasingTheMemory(avlTree);
return 0;
}
i++;
} // while ends
return 1;
}
// utility functions for populateDataStructure ends

int populateDataStructure()
{
global_file_descriptor=open(FILE_NAME,O_RDWR,permission_mode);
if(global_file_descriptor<0)
{
if(create_file_and_prepare_database()==0) return 0;
}
else
{
if(load_data_structure_into_our_tree()==0) return 0;
}
strcpy(global_path.current_working_directory,"/");
strcpy(global_path.path_log,"tmfs");
return 1;
}

void show_current_working_directory()
{
printf("%s\n",global_path.current_working_directory);
}

void copy_data(Input *input)
{
int local_file_descriptor,api_result,permission_mode,wb1,wb2,i;
Header header;
char new_file_name[101];
char file_path[4028];
char *buffer;
OperationDetail success;
DATA_STRUCTURE *ds=NULL;
DATA_STRUCTURE *vDs;

if(input->argc<3)
{
printf("invalid argument\n");
return;
}

if(input->argument1[0]=='/')
{
printf("Currently No support for absoulte path\n");
return;
}

if(strcmp(input->argument2,".")==0)
{
i=strlen(input->argument1)-1;
while(i>=0 && input->argument1[i]!=':' && input->argument1[i]!='/') i--;
if(i<0 || input->argument1[i]==':')
{
printf("Invalid Path (%s)\n",input->argument1);
return;
}
i++;
strcpy(new_file_name,input->argument1+i);
}
else
{
strcpy(new_file_name,input->argument2);
}

strcpy(file_path,input->argument1+2);

local_file_descriptor=open(file_path,O_RDONLY,permission_mode);

if(local_file_descriptor<0)
{
printf("%s is not exists, invalid path or some internal problem\n",file_path);
return;
}

ds=(DATA_STRUCTURE *)malloc(sizeof(DATA_STRUCTURE));
if(ds==NULL)
{
close(local_file_descriptor);
printf("Low memory Issue\n");
return;
}

strcpy(ds->file_name,new_file_name);
ds->file_size=lseek(local_file_descriptor,0,SEEK_END);
if(ds->file_size<0)
{
printf("Your File is corrupt\n");
free(ds);
close(local_file_descriptor);
return;
}

strcpy(ds->parent_directory,global_path.current_working_directory);

vDs=(DATA_STRUCTURE *)getFromAVLTree(avlTree,(void *)ds,&success);
if(success.succ==true)
{
if(strcmp(vDs->parent_directory,global_path.current_working_directory)==0)
{
printf("%s is already exist duplicates not allowed right now\n",vDs->file_name);
free(ds);
close(local_file_descriptor);
return;
}
}

buffer=(char *)malloc(sizeof(char)*ds->file_size);
if(buffer==NULL)
{
printf("Low memory Issue\n");
close(local_file_descriptor);
free(ds);
return;
}

api_result=lseek(local_file_descriptor,0,SEEK_SET);
if(api_result<0)
{
printf("Some internal problem\n");
close(local_file_descriptor);
free(ds);
free(buffer);
return;
}

api_result=read(local_file_descriptor,buffer,ds->file_size);
if(api_result<0)
{
printf("Some internal problem\n");
close(local_file_descriptor);
free(ds);
free(buffer);
}
close(local_file_descriptor);

api_result=lseek(global_file_descriptor,0,SEEK_SET);
if(api_result<0)
{
printf("Some internal problem\n");
free(ds);
free(buffer);
return;
}

api_result=read(global_file_descriptor,&header,sizeof(Header));
if(api_result<0)
{
printf("Some internal problem\n");
free(ds);
free(buffer);
return;
}

header.number_of_files_directories++;
wb1=header.new_record_for_ds_byte;
wb2=header.new_record_for_acutal_data_byte;
header.new_record_for_ds_byte=header.new_record_for_ds_byte+sizeof(DATA_STRUCTURE);
header.new_record_for_acutal_data_byte=header.new_record_for_acutal_data_byte+ds->file_size;
ds->starting_byte_information=wb2;
ds->end_information=wb2+ds->file_size;

api_result=lseek(global_file_descriptor,wb2,SEEK_SET);
if(api_result<0)
{
printf("Some internal problem\n");
free(ds);
free(buffer);
return;
}
api_result=write(global_file_descriptor,buffer,ds->file_size);
if(api_result<0)
{
printf("Some internal problem\n");
free(ds);
free(buffer);
return;
}

api_result=lseek(global_file_descriptor,wb1,SEEK_SET);
if(api_result<0)
{
printf("Some internal problem\n");
free(ds);
free(buffer);
return;
}

api_result=write(global_file_descriptor,ds,sizeof(DATA_STRUCTURE));
if(api_result<0)
{
printf("Some internal problem\n");
free(ds);
free(buffer);
return;
}

api_result=lseek(global_file_descriptor,0,SEEK_SET);
if(api_result<0)
{
printf("Some internal problem\n");
free(ds);
free(buffer);
return;
}

api_result=write(global_file_descriptor,&header,sizeof(Header));
if(api_result<0)
{
printf("Some internal problem\n");
free(ds);
free(buffer);
return;
}
addToAVLTree(avlTree,(void *)ds,&success);
if(success.succ==false)
{
printf("Data is permantly stored but due to low memory Issue please restart the tmfs application for see changes\n");
free(ds);
}
free(buffer);
}


void list_of_content()
{
OperationDetail success;
AVLTreeInOrderIterator inorderIterator;
DATA_STRUCTURE *ds=NULL;
if(getSizeOfAVLTree(avlTree)<=0)
{
printf("\n");
return;
}
inorderIterator=getAVLTreeInOrderIterator(avlTree,&success);
if(success.succ==true)
{
while(hasNextInOrderElementInAVLTree(&inorderIterator))
{
ds=(DATA_STRUCTURE *)getNextInOrderElementFromAVLTree(&inorderIterator,&success);
if(success.succ==false)
{
printf("Some Internal Problem\n");
return;
}
else
{
if(strcmp(ds->parent_directory,global_path.current_working_directory)==0)
{
if(ds->file_size==-1) printf("Directory: %s\n",ds->file_name);
else printf("File: %s Size: %d\n",ds->file_name,ds->file_size);
}
}
}
}
else
{
printf("Some Internal Problem\n");
}
}



char * trimmed(const char *data)
{
int i,j,size;
char *new_string=NULL;
i=0;
j=strlen(data)-1;
while(data[i]==' ') i++;
while(data[j]==' ') j--;
size=(j-i)+2;
new_string=(char *)malloc(sizeof(char)*size);
if(new_string==NULL) return NULL;
strncpy(new_string,data+i,size);
new_string[size-1]='\0';
return new_string;
} // function ends


void extracting_data(char *cmd,Input *input)
{
int i,j,count;
char *vCmd=trimmed(cmd);
if(vCmd==NULL)
{
input->argc=0;
return;
}
if(!strlen(vCmd))
{
input->argc=0;
free(vCmd);
return;
}
count=0;
i=0;
input->argc=0;
while(1)
{
j=0;
while(vCmd[i]!=' ' && vCmd[i]!='\0')
{
if(count==0)
{
input->command[i]=vCmd[i];
}
else if(count==1)
{
input->argument1[j]=vCmd[i];
j++;
}
else
{
input->argument2[j]=vCmd[i];
j++;
}
i++;
} // inner while ends
if(count==0) input->command[i]='\0';
else if(count==1) input->argument1[j]='\0';
else input->argument2[j]='\0';
input->argc++;
count++;
if(vCmd[i]=='\0' || count > 2) break;
i++;
}
free(vCmd);
}

// function defination starts
void makeDirectory(Input *)
{

}
void changeDirectory(Input *)
{

}
void displayFileContent(Input *)
{

}
// function defination ends
int main()
{
Input input;
char cmd[101];
if(!populateDataStructure())
{
printf("Unable to load Data, Application Forcefully terminated\n");
return 0;
}
while(1)
{
printf("%s>",global_path.path_log);
scanf("%[^\n]",cmd);
__fpurge(stdin);
extracting_data(cmd,&input);
if(input.argc==0)
{
printf("Invalid Command Or unable to execute your command due to low memory Issue\n");
continue;
}
if(strcmp(input.command,"pwd")==0) show_current_working_directory();
else if(strcmp(input.command,"xcp")==0) copy_data(&input);
else if(strcmp(input.command,"ls")==0) list_of_content();
else if(strcmp(input.command,"mkdir")==0) makeDirectory(&input);
else if(strcmp(input.command,"cd")==0) changeDirectory(&input);
else if(strcmp(input.command,"xcat")==0) displayFileContent(&input);
else printf("Invalid command\n");
}
releasingTheMemory(avlTree);
return 0;
}