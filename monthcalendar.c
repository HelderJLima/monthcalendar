// Program: monthcalendar
//
// Summary:
//   This program is a simple command-line application that displays a monthly
//   calendar for a given year and month of the Gregorian calendar.
//
// Usage:
//   The program prompts the user to enter a year and a month in numeric
//   format.
//   Based on this input, it generates and displays the corresponding monthly
//   calendar.
//
// Features:
//   - Displays the calendar for the specified month and year.
//   - Provides an option to save the generated calendar to a .txt file.
//
// Output:
//   - Calendar displayed on the standard output.
//   - Optional text file containing the same calendar representation.
//
// by HelderJLima 


#include <stdio.h>
#include "mcfunctions.h"

int main()
{
    int year, month;
    int executing = 1;
    Status_t status;
    char option = 0;
    char calendar[CAL_ROWS][CAL_COLUMNS] = { 0 };
    
    printf("\n\n\t\t*** MONTH CALENDAR ***\n\n");

    do
    {
        // Presentation of options
        do
        {
            printf("\nType an option:\n");

            printf("\nC - Find a Gregorian calendar for a month\n");

            printf("\nQ - Quit\n\n");

            option = getoption();

            if (option == EOF)
            {
                printf("\nError reading character\n");

                return -1;
            }
        }
        while (option != 'c' && option != 'q');

        // Calendar option chosen
        if (option == 'c')
        {
            printf("\nEnter a year: ");

            year = getyear();

            printf("\nEnter a month: ");

            month = getmonth();

            makecalendar(year, month, calendar);

            printcalendar(calendar);

            // Give option to save the calendar
            do
            {
                printf("\nDo you want to save the calendar? (Y/N): ");

                option = getoption();

                if (option == EOF)
                {
                    printf("\nError reading character\n");

                    return -2;
                }
            }
            while (option != 'y' && option != 'n');

            // Save option chosen
            if (option == 'y')
            {
                status = savecalendar(calendar, year, month);

                if (status >= 0)
                {
                    printf("\nThe calendar has been "
                           "successfully saved in the directory:\n\n");

                    status = showpath();

                    if (status < 0)
                        printf("\nUnable to show the path.\n");
                }
                else
                    printf("\nUnable to save calendar\n");
            }

            // Reset the array to a new calendar
            resetcalendar(calendar);
        }
        else
            executing = 0;      // End the program
    }
    while (executing);

    return 0;
}
