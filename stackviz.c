#include <stdio.h>
#include <stdlib.h>
#include "inst.c"

/*
* The main function takes command line arguments. It them opens the file and reads the
* nodes one by one. This function allocates memory and prints the values of each stack frame. It 
* prints the inital values/final vlaues, function, caller, frame pointer, parent procefss adress and process adress, 
stack frame, and time
* @param: int argc, char **argv-- these parameters are for command line input 
* @return o at the end of the function
*/
void insertion_sort(struct Node *data, int count);
void insertion_sort2(struct Node *data, int count);
void insertion_sort3(struct Node *data, int count);

//main method taking command line arguments 
int main(int argc, char** argv){

    FILE *ptr = NULL;
    //if -s, -p, -f options on command line 
    if (argc == 3){
    //call method to sort nodes by start time and open stack.bin file 
    if (strcmp(argv[1], "-s") == 0){
        printf("\nSorting by start time\n");
        ptr = fopen(argv[2], "rb"); // r for read, b for binary 
        //insertion_sort(&data, count);
    }
    //call method to sort nodes by finish time and open stack.bin file 
    else if (strcmp(argv[1], "-f") == 0){
        //insertion_sort2(&data, count);
         printf("\nSorting by finish time\n");
         ptr = fopen(argv[2], "rb"); // r for read, b for binary 
    }
    //call method to sort nodes by PID and open stack.bin file 
    else if (strcmp(argv[1], "-p") == 0){
         printf("\nSorting by finish PID\n");
         ptr = fopen(argv[2], "rb"); // r for read, b for binary 
        //insertion_sort3(&data, count);
    }
    else {
        fprintf(stderr,"Option not allowed. Please enter valid option.\n");
        return 1;
    }
    }
    //if only fileName is provided on commandline open the file 
    else if (argc == 2){
    ptr = fopen(argv[1], "rb"); // r for read, b for binary 
    }

    //if the file didn't open then exit and print to stderr
    if(!ptr){
    fprintf(stderr,"There was an error opening the file. Please enter valid filename as command line argument.\n");
    return 1;
    }

    else{
	//Allocate memory to retrieve stack contents
	struct Node *data = (struct Node *) malloc(sizeof(struct Node)*20); 
    //int variable stores how many nodes were read, then prints to user 
    int count = (fread(data, sizeof(struct Node), 20, ptr));
    //diplays the number of functions called 
    
    // closes file and frees data
    if (fclose(ptr) == EOF){
        free(data);
    }

    printf("\nNumber of functions called: %i\n", count);

    //loop to print contents of every function
    for(int i = 0; i < count; i++)
    {
    //retrieves stack contents and prints them in the specified pormat
    printf("\n(%d)", i + 1);
    printf("\nstart process: %d,  start parent process: %d", data[i].staProcId, data[i].staPareId);
    printf("\nfinish process: %d,  finish parent process: %d", data[i].endProcId, data[i].endPareId);
    printf("\nfunction: %p,  caller: %p,  frame pointer: %p\n", data[i].function, data[i].caller, data[i].framePointer);
    printf("stack frame: %p-%p, time:(%ld.%.9ld - %ld.%.9ld)\n", data[i].beginning_address, data[i].ending_address, data[i].start_time.tv_sec, data[i].start_time.tv_nsec,data[i].end_time.tv_sec, data[i].end_time.tv_nsec);
    printf("adress range                 initial      final\n");

    //getting the adress ranges 
    int i; 
    void* ini;
    void* end;
    //loop to print at 4 byte intervals 
    for(i = 32; i <= 32; i--)
    {
    ini = (data -> initial) + i;
    unsigned long ul = (unsigned long)(ini);
    end = (data -> final) + i;
    unsigned long ul2 = (unsigned long)(end);
    printf("%p-%p      %08lu | %08lu\n", ini, end, ul,ul2);
    i = i-3;

    if (i < 2){
       break;
    }
    }
        }
    
return 0;
}

}

//method to sort nodes by the start time 
void insertion_sort(struct Node *data, int count)
{
    //loop through all nodes 
        for(int i = 1; i < count; i++){

         long key = data[i].start_time.tv_nsec;
         long j = data[i-1].start_time.tv_nsec;

         while(j >= 0 && data[j].start_time.tv_nsec > key)
         {
            //sorting data from low to high 
            data[j+1] = data[j];
            data[j] = data[j - 1];
         }

         data[j+1].start_time.tv_nsec = key;
        }
    }

//method to sort data by finish time 
void insertion_sort2(struct Node *data, int count)
{
    //loop through all nodes 
        for(int i = 1; i < count; i++){
         long key = data[i].end_time.tv_nsec;
         long j = data[i-1].end_time.tv_nsec;

         while(j >= 0 && data[j].end_time.tv_nsec > key)
         {
            //sorting data from low to high 
            data[j+1] = data[j];
            data[j] = data[j - 1];
         }
         data[j+1].end_time.tv_nsec = key;
        }
    }

//method to sort data by PID 
void insertion_sort3(struct Node *data, int count)
{
    //loop through all nodes 
        for(int i = 1; i < count; i++){
         long key = data[i].endProcId;
         long j = data[i-1].endProcId;

         while(j >= 0 && data[j].endProcId > key)
         {
            //sorting data from low to high 
            data[j+1] = data[j];
            data[j] = data[j - 1];
         }
         data[j+1].endProcId = key;
        }
    }
