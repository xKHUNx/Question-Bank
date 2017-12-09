/**********************************************************

                     Name: GOH KUN SHUN

                       ID: 1151101980

                    Email: kunshun225@gmail.com

                    Phone: 017-285 9398

***********************************************************/

#include "QuestionTF.h"
#include <string>
#include <iostream>
#include "Utility.h"
#include "Colour.h"

QuestionTF::QuestionTF( std::string ques, std::string ans, int points )
    : Question( ques, ans, points )
{

}

bool QuestionTF::checkAnswer( std::string ans ) const
{
    // Convert user's answer and true answer to lowercase for comparing
    ans = toLower( ans );
    if ( ans == toLower( answer ) )
    {
        std::cout << INTENSE_GREEN << "Correct! You get " << INTENSE_MAGENTA << points << INTENSE_GREEN << " points!\n\n";
        return true;
    }
    else
    {
        std::cout << INTENSE_RED << "Incorrect, the answer was " << DEFAULT << answer << INTENSE_RED
                  << ". You lose " << INTENSE_MAGENTA << points << INTENSE_RED << " points!\n\n";
        return false;
    }
}

std::string QuestionTF::getType() const
{
    return "TF";
}
