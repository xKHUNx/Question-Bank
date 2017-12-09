/**********************************************************

                     Name: GOH KUN SHUN

                       ID: 1151101980

                    Email: kunshun225@gmail.com

                    Phone: 017-285 9398

***********************************************************/

#include "Colour.h"
#include <iostream>
#include <vector>
#include <algorithm>
#include "windows.h"
#include "Utility.h"

Colour::Colour( COLOUR foreground, COLOUR background ) : foreground( foreground ), background( background )
{
    if ( foreground == DEFAULT || background == DEFAULT )
    {
        this->foreground = INTENSE_WHITE;
        this->background = BLACK;
    }
}

Colour::Colour( COLOUR foreground ) : foreground( foreground )
{
    if ( foreground == DEFAULT )
    {
        this->foreground = INTENSE_WHITE;
        this->background = BLACK;
    }
}

COLOUR Colour::getForeground()
{
    return foreground;
}

COLOUR Colour::getBackground()
{
    return background;
}

void setColour( COLOUR fg, COLOUR bg )
{
    SetConsoleTextAttribute( GetStdHandle( STD_OUTPUT_HANDLE ), ( fg + bg * 16 ) );
}

void setColour( COLOUR C )
{
    if ( C == DEFAULT )
    {
        SetConsoleTextAttribute( GetStdHandle( STD_OUTPUT_HANDLE ), 15 );
    }
    else
    {
        SetConsoleTextAttribute( GetStdHandle( STD_OUTPUT_HANDLE ), C );
    }
}

void setColour( Colour c )
{
    SetConsoleTextAttribute( GetStdHandle( STD_OUTPUT_HANDLE ), c.getForeground() + c.getBackground() * 16 );
}

std::ostream& operator<<( std::ostream& os, Colour c )
{
    setColour( c.getForeground(), c.getBackground() );
    return os;
}

std::ostream& operator<<( std::ostream& os, COLOUR C )
{
    setColour( C );
    return os;
}

void highlightString( std::string const &str, std::string const &sub, COLOUR C )
{
    std::vector<size_t> v; // holds all the positions that sub occurs within str

    // Lowered string and substring
    std::string lowStr = toLower( str );
    std::string lowSub = toLower( sub );

    // Detect all substring's position
    size_t pos = lowStr.find( lowSub, 0 );
    while( pos != std::string::npos )
    {
        v.push_back( pos );
        pos = lowStr.find( lowSub, pos + 1 );
    }

    // Print out the original string with highlights
    for ( int i = 0; i < str.size(); i++ )
    {
        if ( std::find( v.begin(), v.end(), i ) != v.end() )
        {
            std::cout << C << sub << DEFAULT;
            i += sub.size() - 1;
        }
        else
        {
            std::cout << DEFAULT << str[ i ];
        }
    }
}
