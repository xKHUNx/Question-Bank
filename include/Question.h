/**********************************************************

                     Name: GOH KUN SHUN

                       ID: 1151101980

                    Email: kunshun225@gmail.com

                    Phone: 017-285 9398

***********************************************************/

#pragma once
#include <string>

class Question
{
    public:
        Question( std::string ques, std::string ans, int points );
        int getPoints() const;
        std::string getQuestion() const;
        std::string getAnswer() const;
        virtual int getOptionCount() const;
        virtual std::string getOption( int index ) const;
        virtual bool checkAnswer( std::string ans ) const = 0;
        virtual std::string getType() const = 0;


    protected:
        std::string question;
        std::string answer;
        int points;

    private:

};
