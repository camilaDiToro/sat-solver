// This is a personal academic project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com

/* Defines */
#define _GNU_SOURCE

/* Standard library */
#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/mman.h>
#include <stdlib.h>
#include <string.h>

/* Local headers */
#include "./include/posShmADT.h"
#include "./include/myerror.h"

// TO DO: remove this constant
#define SIZE 81920

int
main(int argc, char * argv[]){

    posShmADT shm;

    if(3 != argc){

        size_t lineCap = 0;
        char *shm_name = NULL;
        char *sem_name = NULL;

        if(getline(&shm_name, &lineCap, stdin) <= 0){
            perrorExit("Error in getline function");
        }

        if(getline(&sem_name, &lineCap, stdin) <= 0){
            free(shm_name);
            perrorExit("Error in getline function");
        }

        // https://stackoverflow.com/questions/2693776/removing-trailing-newline-character-from-fgets-input
        // Removes /n 
        shm_name[strcspn(shm_name,"\n")] = 0; 
        sem_name[strcspn(sem_name,"\n")] = 0;

        // TO DO: Check how to obtain size.
        shm = newPosShmADT(shm_name, sem_name, O_RDWR, 0, SIZE, PROT_READ); 

        free(shm_name);
        free(sem_name);

    } else {

        // TO DO: Check how to obtain size.
        shm = newPosShmADT(argv[1], argv[2], O_RDWR, 0, SIZE, PROT_READ);
    }

    char buffer[MAX_BUFFER];

    // TO DO: How do we obtain the total quantity of files we are going to process? 
    // Is there any way to avoid using stdin?

    // TO DO: remove i<20, its just for testing
    for(int i=0; i < 20; i++){
        shmRead(shm, buffer);
        printf("%s\n", buffer);
    }
    
    shmClose(shm);

    return 0;
}