/**********************************************************

                     Name: GOH KUN SHUN

                       ID: 1151101980

                    Email: kunshun225@gmail.com

                    Phone: 017-285 9398

***********************************************************/

#include "QuestionMC.h"
#include <iostream>
#include <string>
#include "Utility.h"
#include "Colour.h"

#define ALPHA_TO_INDEX 65

QuestionMC::QuestionMC( std::string ques, std::string ans, int points, int option_count, std::string* options )
    : Question( ques, ans, points ), option_count( option_count )
{
    // Load options
    this->options = new std::string[ option_count ];
    for ( int i =0; i < this->option_count; i++ )
    {
        this->options[ i ] = options[ i ];
    }
}

QuestionMC::~QuestionMC()
{
    std::cout << "Clean up!\n";
    // Clean up options
    delete [] options;
}

int QuestionMC::getOptionCount() const
{
    return option_count;
}

std::string QuestionMC::getOption( int index ) const
{
    if ( index < option_count )
    {
        return options[ index ];
    }
    else
    {
        return "error";
    }
}

std::string QuestionMC::getType() const
{
    return "MC";
}


bool QuestionMC::checkAnswer( std::string ans ) const
{
    // Convert user's answer and true answer to lowercase for comparing
    std::string temp_ans = toLower( ans );
    if ( temp_ans == toLower( answer ) || temp_ans == toLower( options[  answer[ 0 ] - ALPHA_TO_INDEX ] ) )
    {
        std::cout << INTENSE_GREEN << "Correct! You get " << INTENSE_MAGENTA << points << INTENSE_GREEN << " points!\n\n" << DEFAULT;
        return true;
    }
    else
    {
        std::cout << INTENSE_RED << "Incorrect, the answer was " << DEFAULT << options[  answer[ 0 ] - ALPHA_TO_INDEX ]
                  << INTENSE_RED << ". You lose " << INTENSE_MAGENTA << points << INTENSE_RED << " points!\n\n" << DEFAULT;
        return false;
    }
}
