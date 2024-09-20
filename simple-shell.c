#include <stdio.h>


char* read_user_input() {
    char* buffer = (char*)malloc(8000);
    printf("OSAssignment2@shell:~$ ");
    if (buffer==NULL){             
        printf("Memory allocation failed!\n");
        exit(1);
    }

    if (fgets(buffer, 1000, stdin)==NULL){   
        printf("Could not read input\n");
        exit(1);
    }
    buffer[strcspn(buffer, "\n")]='\0';
    return buffer;
}

