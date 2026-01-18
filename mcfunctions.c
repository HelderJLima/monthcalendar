// Functions used in the 'monthcalendar' program
//
// by HelderJLima


#include "mcfunctions.h"

#include <ctype.h>
#include <direct.h>             // _getcwd
#include <limits.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define BASE        10          // Base used in strtoul function
#define DAY_LEN     3           // For a string with a day number
#define F_EXTENSION ".txt"      // File extension
#define FNAME_LEN   60          // Maximum length of the filename
#define GETDIR      _getcwd     // Function to get the directory name
#define INPUT_LIM   100         // Maximum size for getoption input
#define YEAR_LEN    40          // Long enough for any int value

// Calendar elements
#define CAL_DAY_LEN      7
#define CAL_DAYS_OF_WEEK "| S  | M  | T  | W  | T  | F  | S  |"
#define CAL_H_L_MARGIN   "|   "
#define CAL_H_R_MARGIN   "   |"
#define CAL_L_BLANK      "|    "
#define CAL_R_BLANK      "    |"
#define CAL_LINE         "------------------------------------"
#define CAL_PADDING      1
#define CAL_R_MARGIN     " |"


// Prototypes of auxiliary functions
int dayofweek(int, int, int);
Status_t daytostring(char*, int);
Status_t getfilename(int, int);
Status_t getheader(char*, int, int);
Status_t intfromstdin(int*);
Status_t strtolower(char*, const char*, int);

static char* months[] = { "", "JANUARY", "FEBRUARY", "MARCH", "APRIL", "MAY",
                          "JUNE", "JULY", "AUGUST", "SEPTEMBER", "OCTOBER",
                          "NOVEMBER", "DECEMBER" };

// Numbers of days in months
static int mlength[] = { 0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };

static char filename[FNAME_LEN] = "";


// MAIN FUNCTIONS


int getmonth(void)
{
    int month;
    Status_t status;

    do
    {
        status = intfromstdin(&month);          // Get value

        if (status < 0)
        {
            switch (status)
            {
            case MEMORY_ERROR:
            case READ_ERROR:

                printf("\nError reading month\n");

                break;

            case RANGE_ERROR:

                printf("\nThe number entered "
                       "is not consistent with a month's value\n");

                break;

            case FORMAT_ERROR:

                printf("\nNo numeric value was provided\n");

                break;
            }

            printf("\nEnter a valid month value: ");
        }
        else if(month < 1 || month > 12)
        {
            printf("\nThe number entered "
                   "is not consistent with a month's value\n");

            printf("\nEnter a valid month value: ");

            status = -1;
        }
    }
    while (status < 0);

    return month;
}


int getoption(void)
{
    char input[INPUT_LIM];
    char* status;
    int valid = 0;

    // Get an alphabetic character
    do
    {
        status = fgets(input, INPUT_LIM, stdin);

        if ( ferror(stdin) )
        {
            printf("\nerror: fgets could not read input\n");

            return EOF;
        }
        else if (status == NULL)
        {
            printf("\nInvalid character\n");

            printf("\nEnter a valid alphabetic character: ");
        }
        else if (strlen(input) > 2)                     // Character and '\n'
        {
            printf("\nMultiple characters\n");

            printf("\nEnter a single alphabetic character: ");
        }
        else
        {
            valid = isalpha(input[0]);

            if (!valid)
            {
                printf("\nInvalid character\n");

                printf("\nEnter a valid alphabetic character: ");
            }
        }
    }
    while (!valid);

    return tolower(input[0]);
}


int getyear(void)
{
    int year;
    Status_t status;

    do
    {
        status = intfromstdin(&year);           // Get value

        if (status < 0)
        {
            switch (status)
            {
            case MEMORY_ERROR:
            case READ_ERROR:

                printf("\nError reading year\n");

                break;

            case RANGE_ERROR:

                printf("\nThe number provided is too large\n");

                break;

            case FORMAT_ERROR:

                printf("\nNo numeric value was provided\n");

                break;
            }

            printf("\nEnter a valid year value: ");
        }
        else if (year < 1583)
        {
            printf("\nInvalid year\n");

            printf("\nEnter a year after 1582: ");

            status = -1;
        }
    }
    while (status < 0);

    return year;
}


void makecalendar(int year, int month, char output[CAL_ROWS][CAL_COLUMNS])
{
    int day;
    int ndays;
    int position;
    int row;
    int start;
    Status_t status;
    char daystring[CAL_DAY_LEN] = { 0 };

    // Place horizontal lines
    for (row = 0; row < 3; row++)
        strcat(&output[2 * row][0], CAL_LINE);

    // Put days of week in row 3
    strcat(&output[row][0], CAL_DAYS_OF_WEEK);

    // Place the name of the month and the year
    status = getheader(&output[1][0], year, month);

    // In case of encoding error
    if (status < 0)
    {
        output[1][0] = '\0';

        strcat(&output[1][0], "|...|");
    }
    
    // Day of the week on which the 1st of the month occurs
    start = dayofweek(year, month, 1);
    
    // Number of days in the month
    ndays = mlength[month];

    // February of a leap year
    if ( month == 2
         && (year % 4 == 0 && year % 100 != 0 || year % 400 == 0) )
        ndays++;

    // Place leading whitespaces
    row = 5;

    position = 0;

    while (position < start)
    {
        strcat(&output[row][0], CAL_L_BLANK);

        position++;
    }

    // Place the days of the month
    day = 1;

    while (ndays)
    {
        strcat(&output[row][0], "|");

        while (position < 7 && ndays)
        {
            status = daytostring(daystring, day);

            // In case of encoding error
            if (status < 0)
            {
                daystring[0] = '\0';

                strcat(daystring, " .. |");
            }

            strcat(&output[row][0], daystring);

            daystring[0] = '\0';

            day++;

            position++;

            ndays--;
        }

        row++;

        if(ndays)
            position = 0;
    }

    // Place trailing whitespaces
    row--;

    while (position++ < 7)
        strcat(&output[row][0], CAL_R_BLANK);
    
    // Place final horizontal line
    row++;

    strcat(&output[row][0], CAL_LINE);
}


void printcalendar(const char calendar[CAL_ROWS][CAL_COLUMNS])
{
    int row = 0;

    printf("\n\n");

    while (calendar[row][0] != '\0' && row < CAL_ROWS)
        printf("%s\n", &calendar[row++][0]);

    printf("\n");
}


void resetcalendar(char calendar[CAL_ROWS][CAL_COLUMNS])
{
    int row = 0;

    while (row < CAL_ROWS)
        calendar[row++][0] = '\0';
}


Status_t savecalendar(const char calendar[CAL_ROWS][CAL_COLUMNS],
                     int year, int month)
{
    int row = 0;
    Status_t status;
    FILE* file;

    status = getfilename(year, month);

    if (status < 0)
    {
        printf("\nError trying to save calendar\n");

        return status;
    }

    file = fopen(filename, "w");

    if (!file)
    {
        perror("\nfopen");

        return FILE_ERROR;
    }

    fprintf(file, "\n");

    // Write the strings from the array
    while (calendar[row][0] != '\0' && row < CAL_ROWS)
        fprintf(file, "%s\n", &calendar[row++][0]);

    if ( ferror(file) )
    {
        printf("\nfprintf: writing error\n");

        fclose(file);

        return WRITING_ERROR;
    }

    fclose(file);

    return SUCCESS;
}


Status_t showpath(void)
{
    char* dirname = NULL;
    
    // Get the name of the current directory
    dirname = GETDIR(NULL, _MAX_DIR);

    if (!dirname)
    {
        printf("\n_getcwd: error getting path\n");

        return GETCWD_ERROR;
    }

    // Display the path
    printf("%s\\%s\n\n\n", dirname, filename);

    free(dirname);

    return SUCCESS;
}


// AUXILIARY FUNCTIONS


// Returns the day of the week in ISO format (Sunday = 0, Monday = 1, ...).
// Based on Zeller's Congruence.
//
int dayofweek(int year, int month, int day)
{
    int wday;

    if (month < 3)
    {
        year--;

        month += 12;
    }

    wday = (day
            + (13 * month + 8) / 5
            + year + year / 4 - year / 100 + year / 400) % 7;

    return wday;
}


// Create a string with the day of the month, spaces and a separator to place
// in the calendar.
// The array pointed to by 'destination' must start with '\0'.
// Return zero if successful or an error code otherwise.
//
Status_t daytostring(char* destination, int day)
{
    int nspaces;
    int status;
    char strday[DAY_LEN];

    nspaces = (day < 10) ? CAL_PADDING + 1 : CAL_PADDING;

    while (nspaces--)
        strcat(destination, " ");           // Spaces

    status = snprintf(strday, DAY_LEN, "%d", day);

    if (status < 0)
    {
        printf("\nsnprintf: encoding error\n");

        return ENCODING_ERROR;
    }

    strcat(destination, strday);            // Day

    strcat(destination, CAL_R_MARGIN);      // Right separator

    return SUCCESS;
}


// Create a file name with the given year and month and save it to a static
// string.
// Return zero if successful or an error code otherwise.
//
Status_t getfilename(int year, int month)
{
    char stryear[YEAR_LEN];
    Status_t status;

    // Get month name
    status = strtolower(filename, months[month], FNAME_LEN);

    if (status < 0)
    {
        printf("\nerror: string processing failed\n");

        return status;      // NULL_POINTER_ERROR or INCOMPSIZE_ERROR
    }

    // Get year
    status = snprintf(stryear, YEAR_LEN, "%d", year);

    if (status < 0)
    {
        printf("\nsnprintf: encoding error\n");

        return ENCODING_ERROR;
    }

    // Concatenate the year and file extension
    strcat(filename, "_");

    strcat(filename, stryear);

    strcat(filename, F_EXTENSION);

    return SUCCESS;
}


// Write the calendar header according to the given year and month.
// Return zero if successful or an error code otherwise.
//
Status_t getheader(char* destination, int year, int month)
{
    int nspaces;
    int status;
    char stryear[YEAR_LEN];

    status = snprintf(stryear, YEAR_LEN, "%d", year);

    if (status < 0)
    {
        printf("\nsnprintf: encoding error\n");

        return ENCODING_ERROR;
    }

    // Blank spaces between month and year
    nspaces = strlen(CAL_LINE)
              - 2 * strlen(CAL_H_L_MARGIN)
              - strlen(months[month]) - strlen(stryear);

    strcat(destination, CAL_H_L_MARGIN);     // Left margin

    strcat(destination, months[month]);      // Month

    while (nspaces--)
        strcat(destination, " ");            // Spaces

    strcat(destination, stryear);            // Year

    strcat(destination, CAL_H_R_MARGIN);     // Right margin

    return SUCCESS;
}


// Read a number provided by the user and convert it to an integer value.
// Return zero if successful or an error code otherwise.
//
Status_t intfromstdin(int *intvar)
{
    int length;
    long number;
    char* string;
    char* strptr;

    // Twice the length of an int
    length = 2 * (int)ceil( log10(INT_MAX) );

    string = (char*)calloc( length, sizeof(char) );

    if (string == NULL)
    {
        perror("\ncalloc");

        return MEMORY_ERROR;
    }

    // Get a number
    if (fgets(string, length, stdin) == NULL)
    {
        perror("\nfgets");

        free(string);

        return READ_ERROR;
    }

    strptr = string;

    // Jump blanks
    while ( isblank(*strptr) )
        strptr++;

    // If there is a valid decimal number
    if ( isdigit(*strptr)                           
         || *strptr == '-' && isdigit( *(strptr + 1) )
         || *strptr == '+' && isdigit( *(strptr + 1) ) )
    {
        number = strtol(string, NULL, BASE);

        free(string);

        if (number >= INT_MAX || number <= INT_MIN)
        {
            printf("\nerror: number out of range\n");

            return RANGE_ERROR;
        }
    }
    else
    {
        printf("\nerror: format error\n");

        free(string);

        return FORMAT_ERROR;
    }

    *intvar = (int)number;

    return SUCCESS;
}


// Copies the C string pointed to by 'source' to the array pointed to by
// 'destination' with all letters converted to lowercase.
// The value of 'nlim' must be equivalent to the size of 'destination'.
// Return an error code if there is a problem with the given strings.
// If the length of 'source' is greater than that of 'destination' there may
// be undefined behavior.
//
Status_t strtolower(char* destination, const char* source, int nlim)
{
    if (!destination || !source)
    {
        printf("\nerror: unexpected null pointer\n");

        return NULL_POINTER_ERROR;
    }

    if (strlen(source) > nlim - 1)
    {
        printf("\nerror: incompatible string sizes\n");

        return INCOMPSIZE_ERROR;
    }

    while (*source)
        *destination++ = (char)tolower(*source++);

    *destination = '\0';

    return SUCCESS;
}
