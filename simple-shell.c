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
time_t* timeArray[MAX];
time_t currtime;
int pidArray[MAX];
void showHistory(){
    for(int i=0;i<historyCount;i++){
        printf("%s\n",historyArray[i]);
    }
}
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
            if (historyCount<MAX){
                historyArray[historyCount]=strdup(command);
                printf(command);
                printf(historyArray[historyCount]);
            }
            else{
                perror("Command Limit Exceeded");
                free(cmdLst);
                exit(1);
            }
            gettimeofday(&startTime, NULL);
            currtime=time(NULL);
            timeArray[historyCount]=&currtime;
            if (strcmp("history",arr[0])==0){
                showHistory();
            }
            else{
            parse(arr[0],cmdLst," ");
            execvp(cmdLst[0],cmdLst);
            perror("execvp failed");
            free(cmdLst);
            exit(1);}
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
    else{ //with pipeline
        int pipelines[arg_size][2];
        int i=0;
        while(i<arrSize){
            if(pipe(pipelines[i])==-1){
            perror("Error creating pipeline\n");
            exit(1);
            }        
    
            int check=fork();
            if(check==0){
                char** cmdLst=(char**)malloc(MAX*sizeof(char*));
                if(cmdLst==NULL){
                    perror("Memory allocation failed");
                    exit(1);
                }
                parse(arr[i],cmdLst," ");

                if(i>0){
                    close(pipelines[i-1][1]);
                    dup2(pipelines[i-1][0],STDIN_FILENO);
                    close(pipelines[i-1][0]);
                }
                if(i<arrsize-1){
                    dup2(pipelines[i][1],STDOUT_FILENO);
                    close(pipelines[i][0]);
                    close(pipelines[i][1]);
                }

                execvp(cmdLst[0],cmdLst);
                perror("execvp failed");
                free(cmdLst);
                exit(1);
            }
            else if(check>0){
                if(i>0){
                    close(pipelines[i-1][0]);
                    close(pipelines[i-1][1]);
                }

                if(i==arrSize-1){
                    pidArray[historyCount]=wait(NULL);
                    gettimeofday(&endTime,NULL);
                    runtimeArray[historyCount]=(endTime.tv_sec-startTime.tv_sec)+(endTime.tv_usec-startTime.tv_usec)/1000000.0;
                    historyCount++;
                }
                else{wait(NULL)}
            }
            else{
                printf("Forking error\n");
                exit(1);    
            }
            i++;
        }
}}
   
void mainloop(){
    int repeat=1;
    while (repeat!=0){
        char* cmd=readInput();
/*        if (strcmp("history",cmd)==0){
            int check=fork();
            if (check==0){
            showHistory();
            continue;}*/
        runningProcess(cmd);
        free (cmd);
    }
            }
    

int main(){
    mainloop();
}

