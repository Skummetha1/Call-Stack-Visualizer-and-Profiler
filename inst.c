#include <execinfo.h>
#include <stdio.h>
#include <time.h>
#include <string.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <unistd.h>

//global variables 
  void* function;
  void* caller;
  void* framePointer;
  void* beginning_address;
  void* ending_address;
  void* initial;
  void* final;
  struct timespec start_time;
  struct timespec end_time;
  pid_t staPareId;
  pid_t staProcId;
  pid_t endPareId;
  pid_t endProcId;
  register void *sp asm ("sp");
  FILE *write_ptr;

//Node structure with required data values 
  struct Node {
  void* function;
  void* caller;
  void* framePointer;
  struct timespec start_time;
  struct timespec end_time;
  void* beginning_address;
  void* ending_address;
  void* initial;
  void* final;
  pid_t staProcId ;
  pid_t staPareId;
  pid_t endPareId;
  pid_t endProcId;
};
 struct Node *Node;
/*
* function is called just after the function enter. It allocates for the struct and captures, start 
* time, function, caller, begenning adress, frame pointer and initial contents, and parent process id  and process id
* It assigns the coorecponding values to the values in struct Node
* @param this_fn: this is the pointer of the start of the current function
* @param 2nd-param: call_site: this is the pointer of the function that is calling this_fn 
* @void function: no return value.
*/
void __cyg_profile_func_enter(void *this_fn, void *call_site) {

   function = this_fn;
   caller = call_site;
   //open file in main function eneter 
   if(function == caller){
   write_ptr = fopen("stack.bin","wb");
   }

  //append to file 
   else {
   write_ptr = fopen("stack.bin","ab");
   }

  //allocating memory for node structure 
  Node = (struct Node *) malloc(sizeof(struct Node));
  //capturing values and assigning them to struct data variables 
  clock_gettime(CLOCK_MONOTONIC, &start_time);
  Node-> start_time = start_time;
  //function = this_fn;
  Node-> function = function;
  //caller = call_site;
  Node-> caller = caller;
  beginning_address = __builtin_frame_address(1) + 2 * sizeof(void *);
  Node-> beginning_address = beginning_address;
  framePointer =  __builtin_frame_address(1);
  Node-> framePointer = framePointer;
  Node-> initial = (sp-1);
  Node-> staProcId = getpid();
  Node-> staPareId = getppid();
  
}

/*
* function is called just before function exit. This function captures the 
* end clock time, ending adress, and calcultes the running time of the function, and final contents, process id and 
* parent process Id
* we assign these values to the cooresponding vlaues in our Node struct
* This function writes the nodes to a binary stack file
* @param this_fn: this is the pointer of the start of the current function
* @param 2nd-param: call_site: this is the pointer of the function that is calling this_fn 
* @void function: no return value.
*/
void __cyg_profile_func_exit(void *this_fn, void *call_site) {
  //capturing values and assigning them to struct data variables
   clock_gettime(CLOCK_MONOTONIC, &end_time);
   Node-> end_time = end_time;
   ending_address = __builtin_frame_address(0) + 4 * sizeof(void *);
   Node-> ending_address = ending_address;
   Node-> endProcId = getpid();
   Node-> endPareId = getppid();
   Node-> final = (sp-4);

  //writes the struct to the file and then closed the file 
  fwrite(Node,sizeof(struct Node),1,write_ptr);

  //close the binary file at the end of the main function 
  if(this_fn == call_site){
    fclose(write_ptr);
   }
 
}
