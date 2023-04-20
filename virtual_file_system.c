#include<stdio.h>
#include<unistd.h>
#include<fcntl.h>
#include<stdlib.h>
#include<stdio_ext.h> // for __fpurge
#include<string.h>
#include<errno.h>
#include<sys/stat.h>
#include<ds.h>
#include<dirent.h>
#include<string.h>

// utility function starts
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
// utility functions ends

// global variables and structure declaration starts
char FILE_NAME[10]="tmfs.fs";
int permission_mode=S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP | S_IROTH;
int global_file_descriptor;
typedef struct __$__path_log_DS
{
char current_working_directory[1001];
char absolute_path[4096];
char path_log[1001];
}PATH_DS;
PATH_DS path;
AVLTree *avlTree;
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
typedef struct __$__META_DATA_FOR_DS
{
char file_name[101];
int file_size;
unsigned long long int starting_byte_information;
unsigned long long int end_information;
char parent_directory[1001];
}META_DATA_FOR_DS;
int comparator(void *left,void *right)
{
META_DATA_FOR_DS *i,*j;
i=(META_DATA_FOR_DS *)left;
j=(META_DATA_FOR_DS *)right;
if(strcmp(i->file_name,j->file_name)==0) // file or directory file already exists then it check in same directory or not
{
return strcmp(i->parent_directory,j->parent_directory);
}
else
{
return strcmp(i->file_name,j->file_name);
}
}
// global variables declaration ends

// forward declaration of function starts
void releasingTheMemory();
void register_this_directory_into_our_datastructure(Input *);
int populateDataStructure();
void extracting_data(char *,Input *);
void copy_data(Input *,char);
void show_current_working_directory();
void makeDirectory(Input *);
void changeDirectory(Input *);
void list_of_content();
int create_file_and_prepare_database();
void displayFileContent(Input *);

// forward declaration of function ends

void releasingTheMemory()
{
OperationDetail success;
AVLTreeInOrderIterator inorderIterator;
META_DATA_FOR_DS *meta=NULL;
inorderIterator=getAVLTreeInOrderIterator(avlTree,&success);
if(success.succ==true)
{
while(hasNextInOrderElementInAVLTree(&inorderIterator))
{
meta=(META_DATA_FOR_DS *)getNextInOrderElementFromAVLTree(&inorderIterator,&success);
if(success.succ==true) free(meta);
}
}
clearAVLTree(avlTree);
destroyAVLTree(avlTree);
} // function ends

void register_this_directory_into_our_datastructure(Input *input)
{
int result;
OperationDetail success;
Header header;
META_DATA_FOR_DS *meta,*vMeta;
long long int wb;
meta=(META_DATA_FOR_DS *)malloc(sizeof(META_DATA_FOR_DS));
if(meta==NULL || input->argc < 2)
{
printf("unable to register directory into our system because low memory Issue\n");
return;
}
strcpy(meta->file_name,input->argument1);
strcpy(meta->parent_directory,path.current_working_directory);
vMeta=(META_DATA_FOR_DS *)getFromAVLTree(avlTree,(void *)meta,&success);
if(success.succ==true)
{
free(meta);
return;
}
else
{
meta->file_size=-1;
meta->starting_byte_information=-1;
meta->end_information=-1;
result=lseek(global_file_descriptor,0,SEEK_SET);
if(result<0)
{
printf("Some internal problem, directory not registered\n");
free(meta);
return;
}
result=read(global_file_descriptor,&header,sizeof(Header));
if(result<0)
{
printf("Some internal problem, directory not registered\n");
free(meta);
return;
}
header.number_of_files_directories++;
wb=header.new_record_for_ds_byte;
header.new_record_for_ds_byte=header.new_record_for_ds_byte+sizeof(META_DATA_FOR_DS);
result=lseek(global_file_descriptor,wb,SEEK_SET);
if(result<0)
{
printf("Some internal problem, directory not registered\n");
free(meta);
return;
}
result=write(global_file_descriptor,meta,sizeof(META_DATA_FOR_DS));
if(result<0)
{
printf("Some internal problem, directory not registered\n");
free(meta);
return;
}
result=lseek(global_file_descriptor,0,SEEK_SET);
if(result<0)
{
printf("Some internal problem, directory not registered\n");
free(meta);
return;
}
result=write(global_file_descriptor,&header,sizeof(Header));
if(result<0)
{
printf("Some internal problem, directory not registered\n");
free(meta);
return;
}
addToAVLTree(avlTree,(void *)meta,&success);
if(success.succ==false)
{
printf("Directory registered into our system but because of low memory issue you cannot see effect on this time please restart application to see changes\n");
free(meta);
}
}
}// function ends

int create_file_and_prepare_database()
{
Header header;
int result,current_offset,size_of_data_written,number_of_bytes_extracted;
char hole_start_from_this_location='|';
char hole_end_flag='&';
OperationDetail success;
global_file_descriptor=open(FILE_NAME,O_RDWR | O_CREAT,permission_mode);
if(global_file_descriptor==-1) return 0; // unable to create file
header.number_of_files_directories=0;
header.new_record_for_ds_byte=sizeof(Header);
header.new_record_for_acutal_data_byte=1048579; // it needs attention
result=write(global_file_descriptor,&header,sizeof(Header));
if(result==-1)
{
remove(FILE_NAME);
return 0; // unable to write header
}
current_offset=lseek(global_file_descriptor,999976,SEEK_SET);
if(current_offset==-1)
{
remove(FILE_NAME);
printf("Error No: %d\n",errno);
return 0; // unable to create space for data structure in file
}
result=write(global_file_descriptor,&hole_start_from_this_location,1);
if(result==-1)
{
remove(FILE_NAME);
printf("Error No: %d\n",errno);
return 0; // unable to create space for data structure in file
}
current_offset=lseek(global_file_descriptor,2000000,SEEK_SET);
if(current_offset==-1)
{
remove(FILE_NAME);
printf("Error No: %d\n",errno);
return 0; // unable to create space for acutal data in file
}
result=write(global_file_descriptor,&hole_end_flag,1);
if(result==-1)
{
remove(FILE_NAME);
printf("Error No: %d\n",errno);
return 0; // unable to create space for acutal in file
}
current_offset=lseek(global_file_descriptor,0,SEEK_SET);
if(current_offset==-1)
{
remove(FILE_NAME);
printf("Error No: %d\n",errno);
return 0; // unable to set internal pointer to begning location
}
avlTree=createAVLTree(&success,comparator);
if(success.succ==false) return 0; // unable to create AVLTree
return 1;
}

int populateDataStructure()
{
Header header;
int result,current_offset,size_of_data_written,number_of_bytes_extracted;
char hole_start_from_this_location='|';
char hole_end_flag='&';
OperationDetail success;
int i,permission_mode;
char c;
char *cwd_ptr;
DIR *directory;
struct stat entry_info;
struct dirent *entry;
char _path[4096];
Input input;
META_DATA_FOR_DS *meta;
strcpy(path.current_working_directory,"/");
cwd_ptr=getcwd(path.absolute_path,4096);
if(cwd_ptr==NULL) return 1;
input.argc=3;
strcpy(path.path_log,"tmfs");
global_file_descriptor=open(FILE_NAME,O_RDWR,permission_mode);
if(global_file_descriptor<0)
{
if(create_file_and_prepare_database()==0) return 0;
}
else
{
avlTree=createAVLTree(&success,comparator);
if(success.succ==false) return 0; // unable to create AVLTree
result=read(global_file_descriptor,&header,sizeof(Header));
if(result==-1)
{
destroyAVLTree(avlTree);
return 0; // unable to read header or meta data in file.
}
i=0;
while(i<header.number_of_files_directories)
{
meta=(META_DATA_FOR_DS *)malloc(sizeof(META_DATA_FOR_DS));
if(meta!=NULL)
{
result=read(global_file_descriptor,meta,sizeof(META_DATA_FOR_DS));
if(result==-1)
{
releasingTheMemory(avlTree);
return 0; // because of read api fails
}
else
{
addToAVLTree(avlTree,(void *)meta,&success);
if(success.succ==false)
{
releasingTheMemory(avlTree);
return 0; // because of low Memory Issue.
}
}
}
else
{
releasingTheMemory(avlTree);
return 0; // because of Low Memory Issue
}
i++;
} // while ends
// return 1;
}
directory=opendir(path.absolute_path);
if(directory==NULL)
{
printf("Some internal problem thats why current files and directory in your %s directory are not loaded into virtual file system\n",path.absolute_path);
return 1;
}
while(1)
{
entry=readdir(directory);
if(entry==NULL) break;
if(entry->d_name[0]=='.') continue;
strcpy(_path,path.absolute_path);
if(strlen(_path)>0 && _path[strlen(_path)-1]!='/')
{
strcat(_path,"/");
}
strcat(_path,entry->d_name);
result=stat(_path,&entry_info);
if(result==0)
{
if(S_ISDIR(entry_info.st_mode))
{
i=strlen(_path);
while(_path[i]!='/') i--;
strcpy(input.argument1,_path+i+1);
register_this_directory_into_our_datastructure(&input);
}
else if(S_ISREG(entry_info.st_mode))
{
strcpy(input.argument1,"x:");
strcat(input.argument1,_path);
strcpy(input.argument2,".");
copy_data(&input,'Y');
}
}
else
{
printf("Unable to determine type of [%s]\n",_path);
}
} // while ends
result=closedir(directory);
return 1;
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
} // function ends

void copy_data(Input *input,char registering_data)
{
int local_global_file_descriptor,result,permission_mode,wb1,wb2,i;
Header header;
char new_file_name[101];
char file_path[4028];
char *buffer;
OperationDetail success;
META_DATA_FOR_DS *meta=NULL;
META_DATA_FOR_DS *vMeta;

if(input->argc<3)
{
printf("invalid argument\n");
return;
}

if(input->argument2[0]=='/')
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
if(strcmp(new_file_name,"tmfs.fs")==0 || strcmp(new_file_name,"file_system")==0) return;
strcpy(file_path,input->argument1+2);
local_global_file_descriptor=open(file_path,O_RDONLY,permission_mode);
if(local_global_file_descriptor<0)
{
printf("%s is not exists, invalid path or some internal problem\n",file_path);
return;
}
meta=(META_DATA_FOR_DS *)malloc(sizeof(META_DATA_FOR_DS));
if(meta==NULL)
{
close(local_global_file_descriptor);
printf("Low memory Issue\n");
return;
}
strcpy(meta->file_name,new_file_name);
meta->file_size=lseek(local_global_file_descriptor,0,SEEK_END);
if(meta->file_size<0)
{
printf("Your File is corrupt\n");
free(meta);
close(local_global_file_descriptor);
return;
}
strcpy(meta->parent_directory,path.current_working_directory);
buffer=(char *)malloc(sizeof(char)*meta->file_size);
if(buffer==NULL)
{
printf("Low memory Issue\n");
close(local_global_file_descriptor);
free(meta);
return;
}

result=lseek(local_global_file_descriptor,0,SEEK_SET);
if(result<0)
{
printf("Some internal problem\n");
close(local_global_file_descriptor);
free(meta);
free(buffer);
return;
}

result=read(local_global_file_descriptor,buffer,meta->file_size);
if(result<0)
{
printf("Some internal problem\n");
close(local_global_file_descriptor);
free(meta);
free(buffer);
}
close(local_global_file_descriptor);

vMeta=(META_DATA_FOR_DS *)getFromAVLTree(avlTree,(void *)meta,&success);
if(success.succ==true)
{
if(strcmp(vMeta->parent_directory,path.current_working_directory)==0)
{
if(registering_data=='N') printf("%s is already exist duplicates not allowed\n",vMeta->file_name);
free(meta);
free(buffer);
return;
}
}

result=lseek(global_file_descriptor,0,SEEK_SET);
if(result<0)
{
printf("Some internal problem\n");
free(meta);
free(buffer);
return;
}

result=read(global_file_descriptor,&header,sizeof(Header));
if(result<0)
{
printf("Some internal problem\n");
free(meta);
free(buffer);
return;
}

header.number_of_files_directories++;
wb1=header.new_record_for_ds_byte;
wb2=header.new_record_for_acutal_data_byte;
header.new_record_for_ds_byte=header.new_record_for_ds_byte+sizeof(META_DATA_FOR_DS);
header.new_record_for_acutal_data_byte=header.new_record_for_acutal_data_byte+meta->file_size;
meta->starting_byte_information=wb2;
meta->end_information=wb2+meta->file_size;

result=lseek(global_file_descriptor,wb2,SEEK_SET);
if(result<0)
{
printf("Some internal problem\n");
free(meta);
free(buffer);
return;
}
result=write(global_file_descriptor,buffer,meta->file_size);
if(result<0)
{
printf("Some internal problem\n");
free(meta);
free(buffer);
return;
}

result=lseek(global_file_descriptor,wb1,SEEK_SET);
if(result<0)
{
printf("Some internal problem\n");
free(meta);
free(buffer);
return;
}

result=write(global_file_descriptor,meta,sizeof(META_DATA_FOR_DS));
if(result<0)
{
printf("Some internal problem\n");
free(meta);
free(buffer);
return;
}

result=lseek(global_file_descriptor,0,SEEK_SET);
if(result<0)
{
printf("Some internal problem\n");
free(meta);
free(buffer);
return;
}

result=write(global_file_descriptor,&header,sizeof(Header));
if(result<0)
{
printf("Some internal problem\n");
free(meta);
free(buffer);
return;
}
addToAVLTree(avlTree,(void *)meta,&success);
if(success.succ==false)
{
printf("Data is permantly stored but due to low memory Issue please restart the tmfs application for see changes\n");
free(meta);
}
free(buffer);
} // function ends

void show_current_working_directory()
{
printf("%s\n",path.current_working_directory);
}


void makeDirectory(Input *input)
{
META_DATA_FOR_DS *vMeta,*meta=NULL;
Header header;
int result,wb,permission_mode;
OperationDetail success;
int number_of_bytes_extracted,current_offset;
char read_and_write_data_buffer[2048];
int number_of_bytes_written;
meta=(META_DATA_FOR_DS *)malloc(sizeof(META_DATA_FOR_DS));
if(meta==NULL || input->argc < 2)
{
printf("unable to create directory\n");
return;
}
strcpy(meta->file_name,input->argument1);
strcpy(meta->parent_directory,path.current_working_directory);

vMeta=(META_DATA_FOR_DS *)getFromAVLTree(avlTree,(void *)meta,&success);
if(success.succ==true)
{
printf("it already exists\n");
free(meta);
return;
}
else
{
meta->file_size=-1;
meta->starting_byte_information=-1;
meta->end_information=-1;

result=lseek(global_file_descriptor,0,SEEK_SET);
if(result<0)
{
printf("1 Some internal problem, directory not created\n");
free(meta);
return;
}

result=read(global_file_descriptor,&header,sizeof(Header));
if(result<0)
{
printf("2 Some internal problem, directory not created\n");
free(meta);
return;
}

header.number_of_files_directories++;
wb=header.new_record_for_ds_byte;
header.new_record_for_ds_byte=header.new_record_for_ds_byte+sizeof(META_DATA_FOR_DS);

result=lseek(global_file_descriptor,wb,SEEK_SET);
if(result<0)
{
printf("3 Some internal problem, directory not created\n");
free(meta);
return;
}
result=write(global_file_descriptor,meta,sizeof(META_DATA_FOR_DS));
if(result<0)
{
printf("4 Some internal problem, directory not created\n");
free(meta);
return;
}
permission_mode=S_IXUSR | S_IRUSR | S_IWUSR | S_IXGRP | S_IRGRP | S_IWGRP | S_IXOTH | S_IROTH;

result=mkdir(meta->file_name,permission_mode);
if(result<0)
{
printf("5 Some internal problem, directory not created\n");
free(meta);
return;
}
else
{
result=lseek(global_file_descriptor,0,SEEK_SET);
if(result<0)
{
printf("Some internal problem, directory not created\n");
rmdir(meta->file_name);
free(meta);
return;
}
result=write(global_file_descriptor,&header,sizeof(Header));
if(result<0)
{
printf("Some internal problem, directory not created\n");
rmdir(meta->file_name);
free(meta);
return;
}
addToAVLTree(avlTree,(void *)meta,&success);
if(success.succ==false)
{
printf("Directory created but because of low memory issue you cannot see effect on this time please restart application to see changes\n");
free(meta);
}
} // directory successfully created else part end
} // else ends
} // function ends


void changeDirectory(Input *input)
{
META_DATA_FOR_DS *vMeta,*meta=NULL;
int result,i,j,k;
char path_name[4096],_cwd[4096],_absolute_path[4096],_path_log[4096];
OperationDetail success;
if(input->argument1[0]=='/')
{
printf("No absolute Path Allowed\n");
return;
}
if(input->argc < 2)
{
printf("please Provide a valid directory name\n");
return;
}

if(strcmp(input->argument1,"..")==0)
{
if(strcmp(path.current_working_directory,"/")==0)
{
printf("We are already on root directory\n");
}
else
{
strcpy(_cwd,path.current_working_directory);
strcpy(_absolute_path,path.absolute_path);
strcpy(_path_log,path.path_log);
i=strlen(_cwd)-2;
j=strlen(_absolute_path)-1;
k=strlen(_path_log)-1;
while(_cwd[i]!='/') i--;
while(_absolute_path[j]!='/') j--;
while(_path_log[k]!='/') k--;
_cwd[i+1]='\0';
_absolute_path[j+1]='\0';
_path_log[k]='\0';
result=chdir(_absolute_path);
if(result==-1)
{
printf("Some internal problem,directory not changed\n");
}
else
{
strcpy(path.current_working_directory,_cwd);
strcpy(path.absolute_path,_absolute_path);
strcpy(path.path_log,_path_log);
}
}
return;
} // change to previous directory if part ends
meta=(META_DATA_FOR_DS *)malloc(sizeof(META_DATA_FOR_DS));
if(meta==NULL)
{
printf("Low memory issue\n");
return;
}
strcpy(meta->file_name,input->argument1);
strcpy(meta->parent_directory,path.current_working_directory);
vMeta=(META_DATA_FOR_DS *)getFromAVLTree(avlTree,meta,&success); // it is because our desgin depends upon the data of tmfs.fs
if(success.succ==false)
{
printf("Directory not exist\n");
free(meta);
return;
}
strcpy(path_name,path.absolute_path);
strcat(path_name,"/");
strcat(path_name,input->argument1);
result=chdir(path_name);
if(result==-1)
{
printf("please Provide a valid directory name\n");
return;
}
else
{
strcat(path.current_working_directory,input->argument1);
strcat(path.current_working_directory,"/");
strcpy(path.absolute_path,path_name);
strcat(path.path_log,"/");
strcat(path.path_log,input->argument1);
}
}

void list_of_content()
{
OperationDetail success;
AVLTreeInOrderIterator inorderIterator;
META_DATA_FOR_DS *meta=NULL;
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
meta=(META_DATA_FOR_DS *)getNextInOrderElementFromAVLTree(&inorderIterator,&success);
if(success.succ==false)
{
printf("Some Internal Problem\n");
return;
}
else
{
if(strcmp(meta->parent_directory,path.current_working_directory)==0)
{
if(meta->file_size==-1) printf("Directory: %s\n",meta->file_name);
else printf("File: %s Size: %d\n",meta->file_name,meta->file_size);
}
}
}
}
else
{
printf("Some Internal Problem\n");
}
} // function ends


void displayFileContent(Input *input)
{
int result;
int i;
OperationDetail success;
char *data;
META_DATA_FOR_DS *vMeta,*meta=NULL;
if(input->argc<2)
{
printf("please provide file name\n");
return;
}
meta=(META_DATA_FOR_DS *)malloc(sizeof(META_DATA_FOR_DS));
if(meta==NULL)
{
printf("low memory can't display\n");
return;
}
strcpy(meta->file_name,input->argument1);
strcpy(meta->parent_directory,path.current_working_directory);
vMeta=(META_DATA_FOR_DS *)getFromAVLTree(avlTree,meta,&success);
if(success.succ==false)
{
printf("file not exist in current directory\n");
free(meta);
return;
}
free(meta);
data=(char *)malloc(sizeof(char)*vMeta->file_size+1);
if(data==NULL)
{
printf("low memory can't display\n");
return;
}
result=lseek(global_file_descriptor,vMeta->starting_byte_information,SEEK_SET);
if(result<0)
{
printf("Some internal problem\n");
free(data);
return;
}
result=read(global_file_descriptor,data,vMeta->file_size);
if(result<0)
{
printf("Some internal problem\n");
free(data);
return;
}
data[vMeta->file_size]='\0';
printf("%s\n",data);
free(data);
} // function ends

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
printf("%s>",path.path_log);
scanf("%[^\n]",cmd);
__fpurge(stdin);
extracting_data(cmd,&input);
if(input.argc==0)
{
printf("Unable to execute your command due to low memory Issue\n");
continue;
}
if(strcmp(input.command,"pwd")==0) show_current_working_directory();
else if(strcmp(input.command,"xcp")==0) copy_data(&input,'N');
else if(strcmp(input.command,"ls")==0) list_of_content();
else if(strcmp(input.command,"mkdir")==0) makeDirectory(&input);
else if(strcmp(input.command,"cd")==0) changeDirectory(&input);
else if(strcmp(input.command,"xcat")==0) displayFileContent(&input);
else printf("Invalid command\n");
}
releasingTheMemory(avlTree);
return 0;
}
