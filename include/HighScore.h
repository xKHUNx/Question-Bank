#pragma once
#include "Player.h"

class HighScore
{
    public:
        HighScore( Player player, int totalPoints = 0 );
        Player getPlayer();
        int getTotalPoints();
        double getPercentage();

        // Operator overloading
        bool operator==( HighScore hs );
        bool operator>( HighScore hs );
        bool operator<( HighScore hs );
        bool operator<=( HighScore hs );
        bool operator>=( HighScore hs );


    private:
        Player player;
        int totalPoints;
        double percentage = 0.0;
};
