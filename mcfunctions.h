// mcfunctions.h
//
// This header declares functions used by the main program and defines
// types and macros specific to the application's domain.
//
// It exposes domain-specific helper functions, custom data types, and
// symbolic macros that support the core functionality of the program.
//
// This header is intended for exclusive use within this application
// and is not designed as a general-purpose or reusable library.
//
// All functions declared here assume that their inputs are valid.
// Input validation and error checking must be performed by the
// calling code, typically in the main program.
//
// by HelderJLima


#ifndef MCFUNCTIONS_H
#define MCFUNCTIONS_H


// Calendar array dimensions
#define CAL_ROWS 12
#define CAL_COLUMNS 40

// Status codes
typedef enum { SUCCESS = 0,
               MEMORY_ERROR = -1,
               READ_ERROR = -2,
               RANGE_ERROR = -3,
               FORMAT_ERROR = -4,
               ENCODING_ERROR = -5,
               NULL_POINTER_ERROR = -6,
               INCOMPSIZE_ERROR = -7,
               FILE_ERROR = -8,
               WRITING_ERROR = -9,
               GETCWD_ERROR = -10
             } Status_t;


// FUNCTIONS


// Receive from the user a number between 1 and 12 representing a month.
//
int getmonth(void);


// Receive an alphabetic character from the user and return it.
//  In case of an error while reading, return EOF.
//
int getoption(void);


// Receive from the user a year after 1582.
//
int getyear(void);


// Build the calendar for a given month in a given year and save it to an
//  array.
//
void makecalendar(int year, int month, char output[CAL_ROWS][CAL_COLUMNS]);


// Print the calendar contents to stdout.
//
void printcalendar(const char calendar[CAL_ROWS][CAL_COLUMNS]);


// Reset the array to be used in a new calendar.
//
void resetcalendar(char calendar[CAL_ROWS][CAL_COLUMNS]);


// Save the calendar to a file with a name constructed from the year and
//  month.
//  Return zero if successful or an error code otherwise.
//
Status_t savecalendar(const char calendar[CAL_ROWS][CAL_COLUMNS],
                     int year, int month);


// Display the directory path where the calendar file was saved.
//  Return zero if successful or an error code otherwise.
//
Status_t showpath(void);


#endif  // !MCFUNCTIONS_H
