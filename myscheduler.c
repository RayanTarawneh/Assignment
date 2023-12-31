#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

//  you may need other standard header files


//  CITS2002 Project 1 2023
//  Student1:   STUDENT-NUMBER1   NAME-1
//  Student2:   23807678    Milan Scekic


//  myscheduler (v1.0)
//  Compile with:  cc -std=c11 -Wall -Werror -o myscheduler myscheduler.c


//  THESE CONSTANTS DEFINE THE MAXIMUM SIZE OF sysconfig AND command DETAILS
//  THAT YOUR PROGRAM NEEDS TO SUPPORT.  YOU'LL REQUIRE THESE //  CONSTANTS
//  WHEN DEFINING THE MAXIMUM SIZES OF ANY REQUIRED DATA STRUCTURES.

#define MAX_DEVICES                     4
#define MAX_DEVICE_NAME                 20
#define MAX_COMMANDS                    10
#define MAX_COMMAND_NAME                20
#define MAX_SYSCALLS_PER_PROCESS        40
#define MAX_RUNNING_PROCESSES           50

//  NOTE THAT DEVICE DATA-TRANSFER-RATES ARE MEASURED IN BYTES/SECOND,
//  THAT ALL TIMES ARE MEASURED IN MICROSECONDS (usecs),
//  AND THAT THE TOTAL-PROCESS-COMPLETION-TIME WILL NOT EXCEED 2000 SECONDS
//  (SO YOU CAN SAFELY USE 'STANDARD' 32-BIT ints TO STORE TIMES).

#define DEFAULT_TIME_QUANTUM            100

#define TIME_CONTEXT_SWITCH             5
#define TIME_CORE_STATE_TRANSITIONS     10
#define TIME_ACQUIRE_BUS                20

//variables
//  ----------------------------------------------------------------------

#define CHAR_COMMENT                    '#'

struct {
    char devicename[MAX_DEVICE_NAME + 1];
    int readspeed;
    int writespeed;
    
        
} Devices[MAX_DEVICES];

// Declaring the inner struct
struct Inner_Status_Info;

struct Outer_Command_Info{
    char commandname[MAX_COMMAND_NAME + 1];
    struct Inner_Status_Info *inner;
    


};

struct Inner_Status_Info{
    
    int usecduration;
    char status[5];
    char devicename[MAX_DEVICE_NAME + 1];
    int sleeplength;
    int readwritespeed;

};

int read_sysconfig(char argv0[], char filename[])
{


    FILE *sysconfigfile = fopen(filename, "r");
    if(sysconfigfile == NULL){
        return(EXIT_FAILURE);
    }

    char line[1000];
    int device = 0;

    


    while(fgets(line, sizeof(line), sysconfigfile) != NULL && (device < MAX_DEVICES)) {

        if(line[0] == CHAR_COMMENT || line[0] == '\n'){
            continue;
        }

        sscanf(line, "device %s %dBps %dBps", 
            Devices[device].devicename, 
            &Devices[device].readspeed,
            &Devices[device].writespeed);

            // printf("%s %d %d \n" , Devices[device].devicename, Devices[device].readspeed, Devices[device].writespeed);
            // printf("%d \n",device);
        device++;
        //int timequantum = DEFAULT_TIME_QUANTUM;

        }
    return 0;
}


int read_commands(char argv0[], char filename[])
{
    // int readyqueue[];
    // int running;
    // int blockedqueue[];
    // int waiting[];

    FILE *commandsfile = fopen(filename, "r");
    if(commandsfile == NULL){
        return(EXIT_FAILURE);
    }
    
    char line[1000];
    int command = -1;
    int time = 0;
    int leave = 0;
    int bytes = 0;
    char devicetype[MAX_DEVICE_NAME +1];
    char status[50];

    while(fgets(line, sizeof(line), commandsfile) != NULL && (command < MAX_COMMANDS)) {

        if(line[0] == CHAR_COMMENT){
            continue;
        }
        
        if(line[0] == CHAR_COMMENT || leave == 0){
            
            leave = 1;
            command++;
            printf("%d \n", command);
            sscanf(line, "%s", Commands[command].commandname);  
            printf("%s \n", Commands[command].commandname);
        }
        

        while(fgets(line, sizeof(line), commandsfile) != NULL && leave == 1){
            sscanf(line, "%dusecs %s \n", &time, status );
            
            if(strcmp(status, "sleep") == 0){
                printf("sleep \n");
                continue;
            }

            if(strcmp(status, "read") == 0){
                sscanf(line, "%dusecs %s %s %dB \n", &time, status, devicetype, &bytes);
                printf("read \n");
            }

            if(strcmp(status, "write") == 0){
                sscanf(line, "%dusecs %s %s %dB \n", &time, status, devicetype, &bytes);
                printf("write \n");
            }

            if(strcmp(status, "wait") == 0){
                printf("wait \n");
                continue;
            }

            if(strcmp(status, "spawn") == 0){
                printf("spawn \n");
                continue;
            }

            if(strcmp(status, "exit") == 0){
                printf("exit \n");
                leave = 0;
                continue;
            }

            // printf("this is the value of leave %d \n", leave);

            sscanf(line, "%dusecs %s \n", &time, status );
            continue;
        }
        // printf("this is the number of command %d \n", command);
    }
    return 0;
}

//  ----------------------------------------------------------------------

void execute_commands(void)
{
    
}

//  ----------------------------------------------------------------------

int main(int argc, char *argv[])
{

//  ENSURE THAT WE HAVE THE CORRECT NUMBER OF COMMAND-LINE ARGUMENTS
    if(argc != 3) {
        printf("Usage: %s sysconfig-file command-file\n", argv[0]);
        exit(EXIT_FAILURE);
    }

//  READ THE SYSTEM CONFIGURATION FILE
    read_sysconfig(argv[0], argv[1]);

//  READ THE COMMAND FILE
    read_commands(argv[0], argv[2]);

//  EXECUTE COMMANDS, STARTING AT FIRST IN command-file, UNTIL NONE REMAIN
    execute_commands();

//  PRINT THE PROGRAM'S RESULTS
    printf("measurements  %i  %i\n", 0, 0);
    
    exit(EXIT_SUCCESS);
}

//  vim: ts=8 sw=4

