/**********************************************************

                     Name: GOH KUN SHUN

                       ID: 1151101980

                    Email: kunshun225@gmail.com

                    Phone: 017-285 9398

***********************************************************/

#pragma once
#include <string>
#include "Question.h"
#include "LList.h"

class QuestionBank
{
    public:
        QuestionBank();
        ~QuestionBank();
        bool loadQuestions( std::string fileName );
        void printAllQuestions();
        void shuffle();
        void addQuestion( std::string q, std::string a, int p, std::string type );
        void addQuestion( std::string q, char a, int p, int oc, std::string* op );
        void removeQuestion( int n );
        unsigned int getQuesCount();
        Question* getQuestion( int n );

    protected:

    private:
        // Private member
        LList<Question*> questions;
        std::string database;

        // Private function
        void saveQuestionBanks();
};
