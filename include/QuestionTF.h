/**********************************************************

                     Name: GOH KUN SHUN

                       ID: 1151101980

                    Email: kunshun225@gmail.com

                    Phone: 017-285 9398

***********************************************************/

#pragma once
#include <Question.h>

class QuestionTF : virtual public Question
{
    public:
        QuestionTF( std::string ques, std::string ans, int points );
        std::string getType() const;
        bool checkAnswer( std::string ans ) const;

    protected:

    private:
};
