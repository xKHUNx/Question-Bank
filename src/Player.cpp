/**********************************************************

                     Name: GOH KUN SHUN

                       ID: 1151101980

                    Email: kunshun225@gmail.com

                    Phone: 017-285 9398

***********************************************************/

#include "Player.h"
#include <iostream>
#include <string>
#include "Colour.h"

Player::Player( std::string firstName, std::string lastName ) : firstName( firstName ), lastName( lastName )
{

}

Player::Player( std::string firstName, std::string lastName, int points )
    : firstName( firstName ), lastName( lastName ), points( points )
{

}

std::string Player::getFirstName()
{
    return firstName;
}

std::string Player::getLastName()
{
    return lastName;
}

int Player::getPoints()
{
    return points;
}

void Player::answerQuestion( const Question *q )
{
    std::string answer;

    std::cout << DEFAULT << q->getQuestion() << INTENSE_MAGENTA << " ( " << q->getPoints() << " points )\n" << DEFAULT;

    // Display options if is MC question
    if ( q->getType() == "MC" )
    {
        for ( int i = 0; i < q->getOptionCount(); i++ )
        {
            std::cout << YELLOW << static_cast<char>( 65 + i ) << DEFAULT << ") " << q->getOption( i ) << std::endl;
        }
    }

    std::cout << YELLOW << "\nAnswer:\n" << DEFAULT;
    std::getline( std::cin, answer );
    std::cout << YELLOW << "\n------------------------------------------------------------\n";

    // Check answer and gain/lose point
    if ( q->checkAnswer( answer ) )
    {
        gainPoints( q->getPoints() );
    }
    else
    {
        losePoints( q->getPoints() );
    }
}

void Player::gainPoints( int points )
{
    this->points += points;
}

void Player::losePoints( int points )
{
    this->points -= points;
}

bool Player::operator==( Player p )
{
    return points == p.getPoints();
}

bool Player::operator>( Player p )
{
    return points > p.getPoints();
}

bool Player::operator<( Player p )
{
    return points < p.getPoints();
}

bool Player::operator<=( Player p )
{
    return points <= p.getPoints();
}

bool Player::operator>=( Player p )
{
    return points >= p.getPoints();
}
