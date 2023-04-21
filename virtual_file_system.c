#include<stdio.h>
#include<stdio_ext.h> // for __fpurge
#include<stdlib.h>
#include<string.h>
#include<fcntl.h>
#include<unistd.h>
#include<errno.h>
#include<ds.h>


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

int create_file_and_prepare_database();
int populateDataStructure();
void releasingTheMemory();
void extracting_data(char *,Input *);







// utility functions ends

// global variables declarations starts
char FILE_NAME[10]="tmfs.fs";
int permission_mode=S_IXUSR | S_IRUSR | S_IWUSR | S_IXGRP | S_IRGRP | S_IWGRP | S_IXOTH | S_IROTH;
int global_file_descriptor;
// global variables declarations ends


// forward declaration of function starts
void show_current_working_directory();
void copy_data(Input *,char);
void list_of_content();
void makeDirectory(Input *);
void changeDirectory(Input *);
void displayFileContent(Input *);
// forward declaration of function ends


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