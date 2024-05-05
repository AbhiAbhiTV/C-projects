////////////////////////////////////////////////////////////////////////
//
// File           : p2-support.h
// Description    : Header file for project2 
// Author         : ***Abhinav Prathipati ***
// Date           : ***3/31/2024***
// Notes          : ***added multiple new functions updated struct Database and struct Employee

#ifndef P2Header //To prevent double inclusion of header
#define P2Header //To prevent double inclusion of header

#include <stdio.h>
#define byID 1
#define byNAME 2
#define dbSIZE 100
#define idSIZE 6
#define nameSIZE 10
#define emailSIZE 20


typedef struct date// do not modify
{
  int day; 
  int month;
  int year;
}date;

typedef struct Employee
{
  char ID[idSIZE];
  char first_name[nameSIZE];
  char last_name[nameSIZE];
  char email[emailSIZE];
  double salary;
  date hire_date;
}employee, *employee_ptr;

typedef struct DataBase
{
  employee *emp; // Pointer to the dynamic array of employees
  int total; // Number of current employees in the database
}*dataBase_ptr;
// Functional Prototypes

// Function     : initialize
// Description  : This function creates an array in the database
//                then initalializes each array elemet with the data 
//                in the given file
// Inputs       : a pointer to DataBase struct
// Output       : none
void initialize (dataBase_ptr);

// Function     : create_record
// Description  : This function creates a new employee record with the provided information
//                and adds it to the database.
// Inputs       : ID - The ID of the employee.
//                first_name - The first name of the employee.
//                last_name - The last name of the employee.
//                email - The email of the employee.
//                salary - The salary of the employee.
//                hire_date - The hire date of the employee.
//                db - A pointer to a DataBase struct.
// Output       : None
void create_record (const char *ID, const char *first_name, const char *last_name, const char *email, double salary, date hire_date, dataBase_ptr db);

// Function     : print_title
// Description  : This function prints the title of the employee database.
// Inputs       : None
// Output       : Prints the title of the employee database.
void print_title();

// Function     : display_menu
// Description  : This function displays the menu options for interacting with the employee database.
// Inputs       : db - A pointer to a DataBase struct.
// Output       : Displays the menu options for interacting with the employee database.
void display_menu(dataBase_ptr db);

// Function     : sort_by_id
// Description  : This function sorts the employees in the database by their ID in ascending order.
// Inputs       : db - A pointer to a DataBase struct.
// Output       : Sorts the employees in the database by their ID in ascending order.
void sort_by_id(dataBase_ptr db);

// Function     : sort_by_hire_date
// Description  : This function sorts the employees in the database by their hire date in ascending order.
// Inputs       : db - A pointer to a DataBase struct.
// Output       : Sorts the employees in the database by their hire date in ascending order.
void sort_by_hire_date(dataBase_ptr db);

// Function     : display_all_employees
// Description  : This function displays all the employees in the database.
// Inputs       : db - A pointer to a DataBase struct.
// Output       : Displays all the employees in the database.
void display_all_employees(dataBase_ptr db);

// Function     : search_by_id
// Description  : This function searches for an employee in the database by their ID and displays their information.
// Inputs       : db - A pointer to a DataBase struct.
//                search_id - The ID of the employee to search for.
// Output       : Displays the information of the employee with the specified ID.
void search_by_id(dataBase_ptr db, const char *search_id);

// Function     : search_by_last_name
// Description  : This function searches for employees in the database by their last name (partial or complete) and displays their information.
// Inputs       : db - A pointer to a DataBase struct.
//                last_name - The last name (partial or complete) of the employee(s) to search for.
// Output       : Displays the information of the employee(s) with the specified last name.
void search_by_last_name(dataBase_ptr db, const char *last_name);

// Function     : delete_by_id
// Description  : This function deletes an employee from the database by their ID.
// Inputs       : db - A pointer to a DataBase struct.
//                delete_id - The ID of the employee to delete.
// Output       : Deletes the employee with the specified ID from the database.
void delete_by_id(dataBase_ptr db, const char *delete_id);

// Function     : save
// Description  : This function saves the current state of the employee database to a file.
// Inputs       : db - A pointer to a DataBase struct.
// Output       : Saves the updated databse 
void save(dataBase_ptr);


#endif //To prevent double inclusion of header
