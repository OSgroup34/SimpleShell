#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <signal.h>
#include <sys/time.h>
#include <time.h>

#define MAX 1000
char** historyArray; //declaring global variable to access in different functions 
int num=0;   

char* readInput() {
    char* buffer=(char*)malloc(MAX*sizeof(char*));
    printf("OSAssignment2@shell:~$ ");
    if (buffer==NULL){             
        printf("Memory allocation failed\n");
        exit(1);
    }

    if (fgets(buffer,MAX,stdin)==NULL){   
        printf("Could not read input\n");
        exit(1);
    }
    buffer[strcspn(buffer,"\n")]='\0';
    return buffer;
}
int parse(char* cmd,char** arr,char* delim){
    char* word=strtok(cmd,delim);
    int size=0;
    while (word!=NULL){
        arr[size++]=word;
        word=strtok(NULL,delim);}
    arr[size]=NULL;
    return size;}

void createProcess(char* command){
    historyArray[num++] = strdup(command);
    char** arr = (char**)malloc(MAX * sizeof(char*));
    if (arr == NULL) {
        printf("Memory allocation failed\n");
        exit(1);
    }
    int arrsize=parse(command,arr,"|");
    if (arrsize==1){
        //no pipe
    }
    else{
        int pipes[arg_size][2];
        if (pipe(pipes[i])==-1){
            prerror("Error: pipeline\n");
            exit(1);
        }
        int stat=fork();
        if (i>0){
            close(pipes[i-1][1];
            dup2(pipes[i-1][0], STDIN_FILENO);
            close(pipes[i-1][0];
            
    }
    
    
}

void mainloop(){
    int repeat=1;
    while (repeat){
        char* cmd=read_user_input();
        createProcess(cmd);
    }
}

int main(){

}

