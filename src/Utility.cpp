/**********************************************************

                     Name: GOH KUN SHUN

                       ID: 1151101980

                    Email: kunshun225@gmail.com

                    Phone: 017-285 9398

***********************************************************/

#include "Utility.h"
#include <string>
#include <vector>
#include <iostream>
#include <conio.h>
#include <stdlib.h>
#include <cstdio>
#include <cctype>
#include <cstdarg>
#include <limits>

std::string toLower( std::string s )
{
    // Look through the characters in the string
    for ( int unsigned i = 0; i < s.size(); i++ )
    {
        // Search if any uppercase character
        if ( s[ i ] >= 65 && s[ i ] <= 90 )
        {
            // Convert from uppercase to lowercase character
            s[ i ] += 32;
        }
    }
    return s;
}

std::string toUpper( std::string s )
{
    // Look through the characters in the string
    for ( int unsigned i = 0; i < s.size(); i++ )
    {
        // Search if any uppercase character
        if ( s[ i ] >= 87 && s[ i ] <= 122 )
        {
            // Convert from uppercase to lowercase character
            s[ i ] -= 32;
        }
    }
    return s;
}

std::string getPassword()
{
    // Initialize variables
    char ch;
    std::string password;
    bool stop = false;


    do
    {
        // Get characters from keyboard
        ch = getch();
        switch( ch )
        {
            // Enter
            case '\r': // Detected as return
                // Stop and exit loop
                stop = true;
                break;

            // Backspace
            case '\b':
                if ( password.size() != 0 )
                {
                    std::cout << "\b \b"; // Moves the cursor back one space, then writes a space to erase the character
                    password.pop_back();
                }
                break;

            // Any other characters
            default:
                {
                    // Add char to char vector (string)
                    password.push_back( ch );
                    // Display '*' to 'mask' the password
                    std::cout << '*';
                }
        }
    }
    while ( !stop );

    // Clear cin buffer
    flush( std::cin );

    // Return password for checking
    return password;
}

std::string editString( std::string s )
{
    // Initialize variables
    char ch;
    bool stop = false;

    // Display text to give the illusion of editing
    std::cout << s;

    do
    {
        // Get input from user's keyboard
        ch = getch();

        switch( ch )
        {
            // Enter
            case '\r': // Detected as return
                // Stop and exit loop
                stop = true;
                break;

            // Backspace
            case '\b':
                if ( s.size() != 0 ) // Won't pop back if string is empty already
                {
                    // Moves the cursor back one space, then writes a space to erase the character
                    std::cout << "\b \b";
                    s.pop_back();
                }
                break;

            // Any other characters
            default:
                s.push_back( ch );
                std::cout << ch;
        }
    }
    while ( !stop );

    // Flush cin stream
    flush( std::cin );

    return s;
}

void flush( std::istream& is )
{

    if ( is.peek() == '\n' ) // Remove '\n' in the stream if it is the next in the stream
    {
        is.ignore( std::numeric_limits<std::streamsize>::max(), '\n' );
    }
    is.clear();
}

void pause()
{
    getch();
}
