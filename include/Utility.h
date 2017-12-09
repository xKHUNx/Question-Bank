/**********************************************************

                     Name: GOH KUN SHUN

                       ID: 1151101980

                    Email: kunshun225@gmail.com

                    Phone: 017-285 9398

***********************************************************/

#pragma once
#include <string>
#include <vector>

// Return a string to lowercase
std::string toLower( std::string s );

// Return a string to uppercase
std::string toUpper( std::string s );

// Prompt user to enter password with password masking
std::string getPassword();

// Allow string to be edited like in a text file
std::string editString( std::string s );

// Flush an istream
void flush( std::istream& is );

// Pause screen without using the infamous system( "pause );
void pause();
