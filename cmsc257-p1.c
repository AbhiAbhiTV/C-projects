////////////////////////////////////////////////////////////////////////
//
//  File           : cmsc257-p1.c
//  Description    : This is the main source code for for the first 
//                   project of CMSC257.  
//                   See the related assignment page for details.
//
//  Author         : 
//  Last Modified  :
//

// System Includes
#include <stdio.h>
#include <stdlib.h>

// Project Includes
#include "p1-support.h"


// Functions
///////////////////////////////////////////////////////////////////////
//
// Function     : main
// Description  : The main function for the CMSC257 project #1
// 
// Inputs       : argc - the number of command line parameters
//                argv - the parameters
// Output       : 0 if successful test, -1 if failure

int main(int argc, char *argv[]) {

  // Local variables
  int int_array1[10];
  unsigned int uint_array1[10], uint_array2[10];
  int i;
  int option = 0;
  int offset = 0;
  //Add more local variables here as needed
    
  if (argc < 11)
  {   
  //Exit if there are less than 10 inputs
    printf("Exiting the program, missing input");
    return 0;	
  }

  // Step a - Read in the integer numbers input at 
  // the time of execution and save them into int_array1
  for (i=1; i<11; i++) {
    int_array1[i-1] = atoi(argv[i]);//converting input to integer
  }
  //You don't need to modify the code above for testing
  //Modify/uncomment the code below for testing as needed
  display_array(int_array1, 10);//display the input array
  // Step b - Reverse the order of array elements in int_array1 
  //           using swap function. 
    
  
  int i = 0;
  for(i = 0;i<5;i++){
    swap_ints(int_array1+i,int_array1arr+9-i);
  }
  
	
  //Add index values of each array element on the array elements
  //test entering different offsets, maybe get input using scanf
  
  for (i=0; i<10; i++){
    int_array1[i] = bitwise_add(int_array1[i], offset);
  }
  
	
  // Step c - Convert numbers in int into positive values by taking their 
  // absolute values and save them in uint_array1. 
  // Print all numbers in a single line using display_array function
  	
  for(i=0;i<10;i++){
    uint_array1[i] = bitwise_abs(int_array1[i]);
  }
	
  display_array(uint_array1, 10);
  

  // Step d - Convert these positive integers to numbers 
  // in the range 0,…,32 by implementing the  mod operation
  // save them into uint_array2. 
  // Print all numbers in a single line using display_array function
  
  
  for(i=0;i<10;i++){
    uint_array2[i] = bitwise_mod32(uint_array1[i]);
  }
	
  display_array(uint_array2, 10);
  
	
  // Return successfully
  return(0);
}
