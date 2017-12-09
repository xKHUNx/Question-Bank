/**********************************************************

                     Name: GOH KUN SHUN

                       ID: 1151101980

                    Email: kunshun225@gmail.com

                    Phone: 017-285 9398

***********************************************************/

#pragma once
#include <Question.h>
#include <string>

class QuestionMC : virtual public Question
{
    public:
        QuestionMC( std::string ques, std::string ans, int points, int option_count, std::string* options );
        ~QuestionMC();
        int getOptionCount() const;
        std::string getOption( int index ) const;
        std::string getType() const;
        bool checkAnswer( std::string ans ) const;

    protected:

    private:
        int option_count;
        std::string* options = new std::string[ option_count ];
};
