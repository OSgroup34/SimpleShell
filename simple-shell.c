#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <signal.h>
#include <sys/time.h>
#include <time.h>

#define MAX 1000
char* historyArray[MAX];  
int historyCount=0;
double runtimeArray[MAX];
struct timeval startTime;
struct timeval endTime;
time_t timeArray[MAX];
time_t* currtime;
int pidArray[MAX];

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

void runningProcess(char* command){
    char** arr = (char**)malloc(MAX * sizeof(char*));
    if (arr == NULL) {
        perror("Memory allocation failed");
        exit(1);
    }
    int arrsize=parse(command,arr,"|");
    if (arrsize==1){
        int check=fork();
        if (check == 0){
            char** cmdLst=(char**)malloc(MAX * sizeof(char*));
            if (cmdLst==NULL) {
                perror("Memory allocation failed");
                free(cmdLst);
                exit(1);
            }
            parse(arr[0],cmdLst," ");
            if (historyCount<MAX){
                historyArray[historyCount]=strdup(command);
            }
            else{
                perror("Command Limit Exceeded");
                free(cmdLst);
                exit(1);
            }
            gettimeofday(&startTime, NULL);
            currtime=time(NULL);
            timeArray[historyCount]=strdup(ctime(currtime));
            execvp(cmdLst[0], cmdLst);
            perror("execvp failed");
            free(cmdLst);
            exit(1);
        } 
        else if (check>0) {
            pidArray[historyCount]=wait(NULL);
            gettimeofday(&endTime, NULL);
            runtimeArray[historyCount]=(endTime.tv_sec-startTime.tv_sec)+(endTime.tv_usec-startTime.tv_usec)/1000000.0;
            historyCount++;
            
        } 
        else {
            perror("Forking error\n");
            exit(1);
    }}
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
    
    
}}

void mainloop(){
    int repeat=1;
    while (repeat){
        char* cmd=read_user_input();
        createProcess(cmd);
    }
}

int main(){

}

