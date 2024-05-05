#define _GNU_SOURCE		//strcasestr is a nonstandard GNU extension, 
//we need this line while serching for matching last name
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "p2-support.h"
#include <ctype.h>



void create_record(const char *ID, const char *first_name, const char *last_name, const char *email, double salary, date hire_date, dataBase_ptr db) {
    if (db->total < dbSIZE) {
        strcpy(db->emp[db->total].ID, ID);
        strcpy(db->emp[db->total].first_name, first_name);
        strcpy(db->emp[db->total].last_name, last_name);
        strcpy(db->emp[db->total].email, email);
        db->emp[db->total].salary = salary;
        db->emp[db->total].hire_date = hire_date;
        db->total++;
    } else {
        printf("Database is full. Cannot add more records.\n");
    }
}


void print_title ()// you can keep this fuction or remove if needed
{
  printf ("No. ID    Name          Email        Salary     Hire Date\n");
  printf ("--- ----- ------------- ------------ ---------- --/--/----\n");

}


// Sort records with ID numbers from lowest to highest
void sort_by_id(dataBase_ptr db) {
    for (int i = 0; i < db->total - 1; i++) {
        for (int j = i + 1; j < db->total; j++) {
            if (strcmp(db->emp[i].ID, db->emp[j].ID) > 0) {
                employee temp = db->emp[i];
                db->emp[i] = db->emp[j];
                db->emp[j] = temp;
            }
        }
    }
}


// Sort records with hire date from earliest to most recent
void sort_by_hire_date(dataBase_ptr db) {
    for (int i = 0; i < db->total - 1; i++) {
        for (int j = i + 1; j < db->total; j++) {
            if (db->emp[i].hire_date.year > db->emp[j].hire_date.year ||
                (db->emp[i].hire_date.year == db->emp[j].hire_date.year &&
                 db->emp[i].hire_date.month > db->emp[j].hire_date.month) ||
                (db->emp[i].hire_date.year == db->emp[j].hire_date.year &&
                 db->emp[i].hire_date.month == db->emp[j].hire_date.month &&
                 db->emp[i].hire_date.day > db->emp[j].hire_date.day)) {
                employee temp = db->emp[i];
                db->emp[i] = db->emp[j];
                db->emp[j] = temp;
            }
        }
    }
}

void display_all_employees(dataBase_ptr db) {
    print_title();
    for (int i = 0; i < db->total; i++) {
        // Truncate first name and last name if they exceed 13 characters
        char truncated_name[14];
        snprintf(truncated_name, sizeof(truncated_name), "%.13s %.13s", db->emp[i].first_name, db->emp[i].last_name);
        
        // Truncate email if it exceeds 12 characters
        char truncated_email[13];
        snprintf(truncated_email, sizeof(truncated_email), "%.12s", db->emp[i].email);

        // Displaying employee information
        printf("%-3d %-5s %-13s %-12s $%9.2lf %02d/%02d/%04d\n",
               i,
               db->emp[i].ID,
               truncated_name,
               truncated_email,
               db->emp[i].salary,
               db->emp[i].hire_date.month,
               db->emp[i].hire_date.day,
               db->emp[i].hire_date.year);
    }
}



// Display the employee with the given ID
void search_by_id(dataBase_ptr db, const char *search_id) {
    int found = 0;
    print_title();
    for (int i = 0; i < db->total; i++) {
        const char *id1 = db->emp[i].ID;
        const char *id2 = search_id;

        // Skip leading zeros in both ID strings
        while (*id1 == '0') id1++;
        while (*id2 == '0') id2++;

        // Compare the remaining IDs
        if (strcmp(id1, id2) == 0) {
            found = 1;
            char truncated_name[14];
            snprintf(truncated_name, sizeof(truncated_name), "%.13s %.13s", db->emp[i].first_name, db->emp[i].last_name);
        
        // Truncate email if it exceeds 12 characters
            char truncated_email[13];
            snprintf(truncated_email, sizeof(truncated_email), "%.12s", db->emp[i].email);

        // Displaying employee information
            printf("%-3d %-5s %-13s %-12s $%9.2lf %02d/%02d/%04d\n",
               i,
               db->emp[i].ID,
               truncated_name,
               truncated_email,
               db->emp[i].salary,
               db->emp[i].hire_date.month,
               db->emp[i].hire_date.day,
               db->emp[i].hire_date.year);
            break;
        }
    }
    if (!found)
        printf("Employee with ID %s not found.\n", search_id);
}

// Search the database by last name and display employee(s) partially or completely matching with the given string
int matchLastName(const char* lastName1, const char* lastName2) {
    // Convert both last names to lowercase for case-insensitive comparison
    char lname1_lower[strlen(lastName1) + 1];
    char lname2_lower[strlen(lastName2) + 1];
    for (int i = 0; lastName1[i]; i++)
        lname1_lower[i] = tolower(lastName1[i]);
    lname1_lower[strlen(lastName1)] = '\0';
    for (int i = 0; lastName2[i]; i++)
        lname2_lower[i] = tolower(lastName2[i]);
    lname2_lower[strlen(lastName2)] = '\0';

    // Check if last names partially match
    if (strstr(lname1_lower, lname2_lower) != NULL || strstr(lname2_lower, lname1_lower) != NULL) {
        return 1; // Partial match
    }
    // Check if last names completely match
    if (strcmp(lname1_lower, lname2_lower) == 0) {
        return 2; // Complete match
    }
    return 0; // No match
}

// Function to search employee by last name
void search_by_last_name(dataBase_ptr db, const char *last_name) {
    int found = 0;
    print_title();
    for (int i = 0; i < db->total; i++) {
        // Check if last names partially or completely match
        if (matchLastName(last_name, db->emp[i].last_name) > 0) {
            found = 1;
            char truncated_name[14];
            snprintf(truncated_name, sizeof(truncated_name), "%.13s %.13s", db->emp[i].first_name, db->emp[i].last_name);
            
            // Truncate email if it exceeds 12 characters
            char truncated_email[13];
            snprintf(truncated_email, sizeof(truncated_email), "%.12s", db->emp[i].email);

            // Displaying employee information
            printf("%-3d %-5s %-13s %-12s $%9.2lf %02d/%02d/%04d\n",
                   i,
                   db->emp[i].ID,
                   truncated_name,
                   truncated_email,
                   db->emp[i].salary,
                   db->emp[i].hire_date.month,
                   db->emp[i].hire_date.day,
                   db->emp[i].hire_date.year);
        }
    }
    if (!found)
        printf("No employee with last name %s found.\n", last_name);
}




// Delete one record with the matching ID from the list
void delete_by_id(dataBase_ptr db, const char *delete_id) {
    int found = 0;
    for (int i = 0; i < db->total; i++) {
        const char *id1 = db->emp[i].ID;
        const char *id2 = delete_id;

        // Skip leading zeros in both ID strings
        while (*id1 == '0') id1++;
        while (*id2 == '0') id2++;

        if (strcmp(id1, id2) == 0) {
            found = 1;
           char truncated_name[14];
            snprintf(truncated_name, sizeof(truncated_name), "%.13s %.13s", db->emp[i].first_name, db->emp[i].last_name);
        
        // Truncate email if it exceeds 12 characters
            char truncated_email[13];
            snprintf(truncated_email, sizeof(truncated_email), "%.12s", db->emp[i].email);

        // Displaying employee information
            printf("Employee with ID %s deleted successfully.\n");
            print_title();
            printf("%-3d %-5s %-13s %-12s $%9.2lf %02d/%02d/%04d\n",
               i,
               db->emp[i].ID,
               truncated_name,
               truncated_email,
               db->emp[i].salary,
               db->emp[i].hire_date.month,
               db->emp[i].hire_date.day,
               db->emp[i].hire_date.year);
            for (int j = i; j < db->total - 1; j++) {
                db->emp[j] = db->emp[j + 1];
            }
            db->total--;
            break;
        }
    }
    if (!found)
        printf("Employee with ID %s not found.\n", delete_id);
}


//fix save function. Save array into file: database_updated in the same format with the 
//database file.
void save (dataBase_ptr db)// this function is for saving the database into a text file
{
  FILE *dbfu;
  dbfu = fopen ("database_updated", "w");//open an Std IO file to write into
  if (dbfu == NULL)
  {
    printf ("File cannot be created");
    return;
  }
  for (int i = 0; i < db->total; i++)
  {
      fprintf(dbfu, "%s %s %s %s %.2lf %d/%d/%d\n", db->emp[i].ID, db->emp[i].first_name, db->emp[i].last_name,
                db->emp[i].email, db->emp[i].salary, db->emp[i].hire_date.month, db->emp[i].hire_date.day,
                db->emp[i].hire_date.year);
  }

  fclose (dbfu);//close file after writing
  return;

}

void display_menu (struct DataBase *db)
{
  int input = 0;
  while (input != 8)
  {
    puts
      ("\n**************************************************************");
    printf
      (  "********** Employee Database - Total Employees: %03d **********\n",
db->total);
    puts
      ("**************************************************************\n");
    puts ("Choose one of the menu options below:");
    puts ("1. Sort by ID");
    puts ("2. Sort by Hire Date");
    puts ("3. Display all employees");
    puts ("4. Search employees by ID");
    puts ("5. Search employees by Last Name");
    puts ("6. Delete employee by ID");
    puts ("7. Save");
    puts ("8. Exit");

    scanf ("%d", &input);

    switch (input) {
            case 1:
                // Call the function for sorting by ID
                sort_by_id(db);
                break;
            case 2:
                // Call the function for sorting by Hire Date
                sort_by_hire_date(db);
                break;
            case 3:
                // Call the function for displaying all employees
                display_all_employees(db);
                break;
            case 4: {
                // Call the function for searching employees by ID
                char search_id[idSIZE];
                printf("Enter the ID to search: ");
                scanf("%s", search_id);
                search_by_id(db, search_id);
                break;
            }
            case 5: {
                // Call the function for searching employees by Last Name
                char search_lastname[nameSIZE];
                printf("Enter the Last Name to search: ");
                scanf("%s", search_lastname);
                search_by_last_name(db, search_lastname);
                break;
            }
            case 6: {
                // Call the function for deleting employee by ID
                char delete_id[idSIZE];
                printf("Enter the ID to delete: ");
                scanf("%s", delete_id);
                delete_by_id(db, delete_id);
                break;
            }
            case 7:
                save(db);
                break;
            case 8:
                // Free memory for the array of employee records
                free(db->emp);
                // Free memory for the database structure
                free(db);
                printf("Bye!\n");
                break;

    }
  }

}

