#include "p1-support.h"
#include <stdio.h>
#include <string.h>

////////////////////////////////////////////////////////////////////////
//
// File           : p1support.c
// Description    : Set of general-purpose utility functions for project1 
// Author         : ***Abhinav Prathipati***
// Date           : ***3/1/2024***
// Notes          : ***Type bug fixes/other with dates for your records 


////////////////////////////////////////////////////////////////////////
// Function Definitions
////////////////////////////////////////////////////////////////////////

//Function definitions as decribed in the project manual 

//This function prints out the array of integer values
void display_array(unsigned int* arr, int size){
  int i;
  printf("{");
  for(i = 0;i<size;i++){
    printf("%4d%s",arr[i],(i==9)?"":",");
  }
  printf("}\n");
  
}


//Additional function definitions for helper functions
//Shortly describe each function above the function definition.

// Adds two integers using only bitwise operations and loop
int bitwise_add(int num1, int num2) {
  while (num2 != 0) {
    int carry = num1 & num2;
    num1 = num1 ^ num2;
    num2 = carry << 1;
  }
  return num1;
}

// Shifts the first parameter to the left by the amount of the second parameter
int bitwise_shift_left(int num1, int num2) {
  return num1 << num2;
}

// Returns count of 1s in the bitwise representation of a number
int count_set_bits(int num) {
  int count = 0;
  while (num) {
    count += num & 1;
    num >>= 1;
  }
  return count;
}

// Fills the text string with a binary representation of the number
void binary_string(unsigned int num, char* str) {
  str[0] = '0';
  str[1] = 'b';
  int i;
  for (i = 0; i < 32; i++) {
    str[2 + i] = ((num >> (31 - i)) & 1) ? '1' : '0';
  }
  str[34] = '\0'; // null termination
}

// Returns mod 32 of a number using bitwise AND operation
int bitwise_mod32(int num) {
  return num & 0b11111; // 0b11111 represents 5 least significant bits of 1s
}

// Returns the absolute value of the input integer
int bitwise_abs(int num) {
  if (num < 0)
    return bitwise_add(~num, 1);
  return num;
}

// Extracts the specified bit from a given number
int bit_get(int num, int offset) {
  return (num >> offset) & 1;
}

// Returns 1 if the unsigned integer input is odd, 0 if even
int odd_or_even(unsigned int num) {
  return bit_get(num, 0);
}

// Swaps the inputs without using a temporary variable
void swap_ints(int *a, int *b) {
  *a = *a ^ *b;
  *b = *a ^ *b;
  *a = *a ^ *b;
}


