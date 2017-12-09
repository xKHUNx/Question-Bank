/**********************************************************

                     Name: GOH KUN SHUN

                       ID: 1151101980

                    Email: kunshun225@gmail.com

                    Phone: 017-285 9398

***********************************************************/

#pragma once
#include <string>
#include "Question.h"

class Player
{
    public:
        Player( std::string firstName, std::string lastName );
        Player( std::string firstName, std::string lastName, int points );
        std::string getFirstName();
        std::string getLastName();
        int getPoints();
        void answerQuestion( const Question *q ); // Call by reference a pointer
        // Operator overloading
        bool operator==( Player p );
        bool operator>( Player p );
        bool operator<( Player p );
        bool operator<=( Player p );
        bool operator>=( Player p );

    private:
        std::string firstName;
        std::string lastName;
        int points = 0;
        void gainPoints( int points );
        void losePoints( int points );
};
