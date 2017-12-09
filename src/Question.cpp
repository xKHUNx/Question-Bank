/**********************************************************

                     Name: GOH KUN SHUN

                       ID: 1151101980

                    Email: kunshun225@gmail.com

                    Phone: 017-285 9398

***********************************************************/

#include "Question.h"
#include <iostream>

Question::Question( std::string ques, std::string ans, int points ): question( ques ), answer( ans ), points( points )
{

}

int Question::getPoints() const
{
    return points;
}

std::string Question::getQuestion() const
{
    return question;
}

std::string Question::getAnswer() const
{
    return answer;
}


int Question::getOptionCount() const
{
    return 0;
}

std::string Question::getOption( int index ) const
{
    return "error";
}
