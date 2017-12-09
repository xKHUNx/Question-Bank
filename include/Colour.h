/**********************************************************

                     Name: GOH KUN SHUN

                       ID: 1151101980

                    Email: kunshun225@gmail.com

                    Phone: 017-285 9398

***********************************************************/

#pragma once
#include "windows.h"
#include <iostream>

enum COLOUR
{
    BLACK,
    BLUE,
    GREEN,
    CYAN,
    RED,
    MAGENTA,
    BROWN,
    WHITE,
    GRAY,
    INTENSE_BLUE,
    INTENSE_GREEN,
    INTENSE_CYAN,
    INTENSE_RED,
    INTENSE_MAGENTA,
    YELLOW,
    INTENSE_WHITE,
    DEFAULT
};

class Colour
{
    public:
        Colour( COLOUR foreground );                    // Create colour with black background and selected colour
        Colour( COLOUR foreground, COLOUR backgroud );  // Create colour with selected colours
        COLOUR getForeground();
        COLOUR getBackground();

    protected:

    private:
        COLOUR foreground = BLACK;
        COLOUR background = BLACK;
};

// Set console for both foreground and background colour with COLOUR enums
void setColour( COLOUR fg, COLOUR bg );

// Set console for foreground colour with COLOUR enums
void setColour( COLOUR C );

// Set console for foreground and background colour with Colour object
void setColour( Colour c );

// Overloaded << operator with COLOUR enmus
std::ostream& operator<<( std::ostream& os, Colour c );

// Overloaded << operator with Colour object
std::ostream& operator<<( std::ostream& os, COLOUR C );

// Highlight substring from a string
void highlightString( std::string const &str, std::string const &sub, COLOUR C );
