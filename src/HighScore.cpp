#include "HighScore.h"

HighScore::HighScore( Player player, int totalPoints ) : player( player ), totalPoints( totalPoints )
{
    percentage = static_cast<double>( player.getPoints() ) / totalPoints * 100;
}

Player HighScore::getPlayer()
{
    return player;
}

int HighScore::getTotalPoints()
{
    return totalPoints;
}

double HighScore::getPercentage()
{
    return percentage;
}

bool HighScore::operator==( HighScore hs )
{
    return percentage == hs.getPercentage();
}

bool HighScore::operator>( HighScore hs )
{
    return percentage > hs.getPercentage();
}

bool HighScore::operator<( HighScore hs )
{
    return percentage < hs.getPercentage();
}

bool HighScore::operator<=( HighScore hs )
{
    return percentage <= hs.getPercentage();
}

bool HighScore::operator>=( HighScore hs )
{
    return percentage >= hs.getPercentage();
}
