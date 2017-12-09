/**********************************************************

                     Name: GOH KUN SHUN

                       ID: 1151101980

                    Email: kunshun225@gmail.com

                    Phone: 017-285 9398

***********************************************************/

#include <iostream>
#include <stdlib.h>
#include <vector>
#include <ctype.h>
#include <fstream>
#include <iomanip>
#include "Colour.h"
#include "QuestionBank.h"
#include "LList.h"
#include "Player.h"
#include "HighScore.h"
#include "Utility.h"

// This function will list all the QuestionBanks available and return a QuestionBank a user chose from the list
QuestionBank* chooseQuestionBank( std::string action = "perform action on" );

// This function will prompt the user to login and return true if login success
bool login();

// This function prints out a banner
void printBanner( std::string text = "" );

int main()
{
    // Initialize variables
    bool quit = false;
    char choice;


    // Program loop
    while ( !quit )
    {
        // Clear screen
        system( "cls" );

        // Print menu
        printBanner( "QUIZ BANK" );
        std::cout << "    1" << DEFAULT << ". Take quiz.\n" << YELLOW;
        std::cout << "    2" << DEFAULT << ". Admin login.\n" <<  YELLOW;
        std::cout << "    Q" << DEFAULT << ". Quit.\n\n" << YELLOW;
        std::cout << " =>  " << DEFAULT;

        std::cin >> choice;
        flush( std::cin );    // Flush the standard input stream

        switch( choice )
        {
            case '1':
                {
                    // Declare variables
                    std::string firstName, lastName, quesCount;
                    unsigned int nQuesCount;
                    int totalMark = 0;
                    bool isValid = false;

                    system( "cls" );

                    // Get player info
                    printBanner( "INFO" );
                    std::cout << INTENSE_CYAN << "                              First name: ";
                    setColour( DEFAULT );
                    getline( std::cin, firstName );
                    std::cout << INTENSE_CYAN << "                               Last name: ";
                    setColour( DEFAULT );
                    getline( std::cin, lastName );
                    flush( std::cin );

                    // Generate objects
                    Player *p = new Player( firstName, lastName );

                    // Choose and load quiz file
                    QuestionBank* qb = chooseQuestionBank( "to try" );

                    // Shuffle loaded questions
                    if ( qb->getQuesCount() > 0 )
                    {
                        qb->shuffle();

                        // Quiz session settings
                        while ( !isValid )
                        {
                            system( "cls" );
                            printBanner( "SETTINGS" );
                            std::cout << YELLOW << "How many questions would you like ( out of " << qb->getQuesCount() << " )?\n";
                            setColour( DEFAULT );
                            getline( std::cin, quesCount );
                            if ( isdigit( quesCount[ 0 ]) )
                            {
                                nQuesCount = atoi( quesCount.c_str() );
                                if ( nQuesCount <= qb->getQuesCount() && nQuesCount > 0 )
                                {
                                    isValid = true;
                                }
                                else
                                {
                                    std::cout << INTENSE_RED << "Sorry, that is too many or too few.\n";
                                    pause();
                                }
                            }
                            else
                            {
                                std::cout << INTENSE_RED << "Sorry, that is not valid.\n";
                                pause();
                            }
                        }

                        // Answering session
                        for ( unsigned int i = 1; i <= nQuesCount; i++ )
                        {
                            system( "cls" );
                            totalMark += qb->getQuestion( i )->getPoints();
                            std::cout << YELLOW << "============================ " << DEFAULT << "Question " << i
                                      << YELLOW << " ============================\n";
                            p->answerQuestion( qb->getQuestion( i ) );
                            std::cout << DEFAULT << "You now have " << INTENSE_MAGENTA << p->getPoints() << DEFAULT << " points!\n";
                            std::cout << YELLOW << "================================================================================\n";
                            pause();
                        }
                        system( "cls" );
                        std::cout << YELLOW << "================================================================================\n";
                        std::cout << INTENSE_CYAN << "      " << firstName << " " << lastName << DEFAULT << ", your game is over!\n";
                        std::cout << YELLOW << "================================================================================\n";
                        std::cout << DEFAULT << "      You final score is " << INTENSE_MAGENTA << p->getPoints()
                                  << DEFAULT << " points out of " << totalMark << ".\n\n";
                        std::cout << YELLOW << "--------------------------------------------------------------------------------\n";
                        std::cout << DEFAULT << "                           Thanks for playing!" << std::endl;
                        std::cout << YELLOW << "--------------------------------------------------------------------------------\n" << DEFAULT;

                        // Save quiz session result
                        std::ofstream fout;
                        fout.open( "data/Records/records.txt", std::ofstream::app );
                        fout << p->getFirstName() << "\n" << p->getLastName() << "\n" << p->getPoints() << "\n" << totalMark << "\n";
                        fout.close();
                    }
                    else
                    {
                        std::cout << INTENSE_RED << "This question bank is empty!\n" << DEFAULT;
                    }

                    // Clean up everything
                    delete p;
                    delete qb;

                }
                pause();
                break;

            case '2':
                if ( login() )
                {
                    pause();

                    // Initialize variables
                    bool quit = false;
                    char choice;

                    // Menu loop
                    while ( !quit )
                    {
                        // Clear screen
                        system( "cls" );

                        // Print menu
                        printBanner( "ADMIN" );
                        std::cout << "    1" << DEFAULT << ". Add new questions to the database.\n" << YELLOW;
                        std::cout << "    2" << DEFAULT << ". Remove questions from the database.\n" << YELLOW;
                        std::cout << "    3" << DEFAULT << ". Search and edit questions.\n" << YELLOW;
                        std::cout << "    4" << DEFAULT << ". Display top 10 high scores.\n" << YELLOW;
                        std::cout << "    5" << DEFAULT << ". Display all records.\n" << YELLOW;
                        std::cout << "    6" << DEFAULT << ". Add new category.\n" << YELLOW;
                        std::cout << "    Q" << DEFAULT << ". Quit.\n\n" << YELLOW;
                        std::cout << " =>  " << DEFAULT;

                        std::cin >> choice;
                        flush( std::cin );    // Flush the standard input stream

                        switch ( choice )
                        {
                            case '1':
                            {
                                // Initialize variables
                                char choice2;
                                bool quit2 = false;
                                bool isValid2 = false;
                                std::string type;
                                std::string question;
                                std::string answer;
                                std::string optionCount;
                                std::string opt;
                                std::string* options = new std::string;
                                char ans = 'g';
                                unsigned int nOptionCount;
                                int nPoints;

                                // Choose and load quiz file
                                QuestionBank* qb = chooseQuestionBank( "add a question into" );

                                // Add question
                                while ( !quit2 )
                                {
                                    system( "cls" );

                                    // Reset isValid2 flag
                                    isValid2 = false;

                                    // Question maker menu
                                    printBanner( "CHOOSE" );
                                    std::cout << YELLOW << "Which type of question are you adding?\n";
                                    std::cout << "    1" << DEFAULT << ". Simple Answer    ( SA )\n" << YELLOW;
                                    std::cout << "    2" << DEFAULT << ". True or False    ( TF )\n" << YELLOW;
                                    std::cout << "    3" << DEFAULT << ". Multiple Choicen ( MC )\n" << YELLOW;
                                    std::cout << "    Q" << DEFAULT << ". Quit\n" << YELLOW;
                                    std::cout << " =>  " << DEFAULT;

                                    std::cin >> choice2;
                                    flush( std::cin );    // Flush the standard input stream

                                    switch ( choice2 )
                                    {
                                        case '1':
                                            {
                                                // Get question
                                                std::cout << INTENSE_MAGENTA << "Question:\n";
                                                setColour( DEFAULT );
                                                getline( std::cin, question );

                                                // Get points
                                                std::cout << INTENSE_CYAN << "Points:\n";
                                                setColour( DEFAULT );
                                                while ( !( std::cin >> nPoints ) )
                                                {
                                                    flush( std::cin );
                                                    std::cout << INTENSE_CYAN << "Points:\n";
                                                    setColour( DEFAULT );
                                                }
                                                std::cin.clear();
                                                std::cin.ignore( 1000, '\n' );

                                                // Get answer
                                                std::cout << INTENSE_CYAN << "Answer:\n";
                                                setColour( DEFAULT );
                                                getline( std::cin, answer );

                                                // Add SA question
                                                std::cout << INTENSE_GREEN << "SA question added!\n" << DEFAULT;
                                                qb->addQuestion( question, answer, nPoints, "SA" );
                                            }
                                            pause();
                                            break;

                                        case '2':
                                            {
                                                // Get question
                                                std::cout << INTENSE_MAGENTA << "Question:\n";
                                                setColour( DEFAULT );
                                                getline( std::cin, question );

                                                // Get points
                                                std::cout << INTENSE_CYAN << "Points:\n";
                                                setColour( DEFAULT );
                                                while ( !( std::cin >> nPoints ) )
                                                {
                                                    flush( std::cin );
                                                    std::cout << INTENSE_CYAN << "Points:\n";
                                                    setColour( DEFAULT );
                                                }
                                                flush( std::cin );

                                                //  Check if answer is true or false
                                                while ( !isValid2 )
                                                {
                                                    // Get answer
                                                    std::cout << INTENSE_CYAN << "Answer:\n";
                                                    setColour( DEFAULT );
                                                    getline( std::cin, answer );

                                                    if ( toLower( answer ) == "true" || toLower( answer ) == "false" )
                                                    {
                                                        isValid2 = true;
                                                        std::cout << INTENSE_GREEN << "TF question added!\n" << DEFAULT;
                                                        qb->addQuestion( question, answer, nPoints, "TF" );
                                                    }
                                                    else
                                                    {
                                                        std::cout << INTENSE_RED << "Answer must be true or false!\n" << DEFAULT;
                                                    }
                                                }
                                            }
                                            pause();
                                            break;

                                        case '3':
                                            {
                                                // Get question
                                                std::cout << INTENSE_MAGENTA << "Question:\n" << DEFAULT;
                                                getline( std::cin, question );

                                                // Get points
                                                std::cout << INTENSE_CYAN << "Points:\n" << DEFAULT;
                                                while ( !( std::cin >> nPoints ) )
                                                {
                                                    flush( std::cin );
                                                    std::cout << INTENSE_CYAN << "Points:\n" << DEFAULT;
                                                }
                                                flush( std::cin );

                                                // Get options
                                                while ( !isValid2 )
                                                {
                                                    std::cout << YELLOW << "How many options would you like? ( 2 - 6 ) \n" << DEFAULT;
                                                    getline( std::cin, optionCount );
                                                    if ( isdigit( optionCount[ 0 ] ) )
                                                    {
                                                        nOptionCount = atoi( optionCount.c_str() );
                                                        if ( nOptionCount >= 2 && nOptionCount <= 6 )
                                                        {
                                                            isValid2 = true;
                                                            options = new std::string[ nOptionCount ];
                                                            for ( unsigned int i = 0; i < nOptionCount; i++ )
                                                            {
                                                                std::cout << YELLOW << "Enter option " << i + 1 << ": \n";
                                                                setColour( DEFAULT );
                                                                std::getline( std::cin, opt );
                                                                options[ i ] = opt;
                                                            }
                                                            isValid2 = true;
                                                        }
                                                        else
                                                        {
                                                            std::cout << INTENSE_RED << "Sorry, the number choice must be from 2 - 6.\n" << DEFAULT;
                                                        }
                                                    }
                                                    else
                                                    {
                                                        std::cout << INTENSE_RED << "Sorry, that is not a valid number.\n" << DEFAULT;
                                                    }
                                                }

                                                // Get answer
                                                std::cout << INTENSE_CYAN << "Answer ( A - " << static_cast<char>( 'B' + nOptionCount - 2 ) << " ):\n" << DEFAULT;
                                                std::cin >> ans;
                                                while ( tolower( ans ) <  'a' || tolower( ans ) >  ( 'b' + nOptionCount - 2 ) )
                                                {
                                                    flush( std::cin );
                                                    std::cout << INTENSE_CYAN << "Answer ( A - " << static_cast<char>( 'B' + nOptionCount - 2 ) << " ):\n" << DEFAULT;
                                                    std::cin >> ans;
                                                }
                                                std::cout << INTENSE_GREEN << "MC question added!\n" << DEFAULT;
                                                qb->addQuestion( question, toupper( ans ), nPoints, nOptionCount, options );
                                                std::cin.clear();
                                                std::cin.ignore( 1000, '\n' );
                                                delete [] options;
                                            }
                                            pause();
                                            break;

                                        case 'Q':
                                        case 'q':
                                            quit2 = true;
                                            break;

                                        default:
                                            std::cout << "Invalid Input!\n";
                                            pause();
                                    }
                                }

                                // Clean up everything
                                delete qb;
                            }
                            pause();
                            break;

                            case '2':
                            {
                                // Initializing variables
                                char input;

                                // Choose and load quiz file
                                QuestionBank* qb = chooseQuestionBank( "to delete a question from" );

                                // Loop through the questions in the question bank
                                for ( int i = 1; i <= qb->getQuesCount(); i++ )
                                {
                                    // Display original question
                                    std::cout << "Question " << i << ":\n";
                                    std::cout << "       Type: " << qb->getQuestion( i )->getType() << std::endl;
                                    std::cout << "     Points: " << qb->getQuestion( i )->getPoints() << std::endl;
                                    std::cout << "   Question: " << qb->getQuestion( i )->getQuestion() << std::endl;
                                    if ( qb->getQuestion( i )->getType() == "MC" )
                                    {
                                        std::cout << "    Options:\n";
                                        for ( unsigned int j = 0; j < qb->getQuestion( i )->getOptionCount(); j++ )
                                        {
                                            std::cout << "       " << static_cast<char>( 65 + j ) << ". " << qb->getQuestion( i )->getOption( j ) << std::endl;
                                        }
                                    }
                                    std::cout << "     Answer: " << qb->getQuestion( i )->getAnswer() << std::endl;

                                    // Let user choose which question to delete
                                    std::cout << INTENSE_CYAN << "Delete this question? ( Enter 'Y' to edit )\n" << DEFAULT;
                                    std::cout << YELLOW << " =>  " << DEFAULT;
                                    std::cin.get( input );
                                    flush( std::cin );    // Flush instream

                                    // Ask if the user to edit the questions
                                    if ( input == 'Y' || input == 'y' )
                                    {
                                        // Delete the question from the question bank
                                        std::cout << INTENSE_GREEN << "Question " << i << " deleted! \n" << DEFAULT;
                                        qb->removeQuestion( i );
                                        i--;
                                    }
                                }

                                // Clean up everything
                                delete qb;
                            }
                            pause();
                            break;

                            case '3':
                            {
                                // Initializing variables
                                bool isValid4 = false;
                                std::string keyword;
                                std::string lowKeyword;
                                std::string newType;
                                std::string newQuestion;
                                std::string newAnswer;
                                std::string newOption;
                                std::string optionCount;
                                std::string* newOptions = new std::string;
                                char newAns;
                                unsigned int newOptionCount;
                                int newPoints;
                                char input;

                                // Choose and load quiz file
                                QuestionBank* qb = chooseQuestionBank( "to search from" );

                                // Get keyword to be search
                                std::cout << INTENSE_CYAN << "Enter word to search for:\n" << INTENSE_GREEN;
                                getline( std::cin, keyword );
                                lowKeyword = toLower( keyword );
                                setColour( DEFAULT );

                                // Search keyword from question
                                bool found;
                                std::string::size_type foundInQues;   // foundInQues and foundInAns is a size_type,
                                std::string::size_type foundInAns;    // which is a static member of string class

                                // Loop through the questions in the question bank
                                for ( int i = 1; i <= qb->getQuesCount(); i++ )
                                {
                                    // Reset found
                                    found = false;

                                    // Search in question
                                    foundInQues = toLower( qb->getQuestion( i )->getQuestion() ).find( lowKeyword );
                                    if ( foundInQues != std::string::npos )  // std::string::npos is maximum value
                                    {                                        // representable by the type size_type
                                        found = true;
                                    }

                                    /// Search in answer
                                    if ( qb->getQuestion( i )->getType() == "MC" ) // Extra steps for multiple choice
                                    {
                                        // Search through options in QuestionMC
                                        for ( unsigned int j = 0; j <  qb->getQuestion( i )->getOptionCount(); j++ )
                                        {
                                            foundInAns = toLower( qb->getQuestion( i )->getOption( j ) ).find( lowKeyword );
                                            if ( foundInAns != std::string::npos )
                                            {
                                                found = true;
                                            }
                                        }
                                    }
                                    else    // Steps for QuestionTF and QuestionSA
                                    {
                                        // Search in answer
                                        foundInAns = toLower( qb->getQuestion( i )->getAnswer() ).find( lowKeyword );
                                        if ( foundInAns != std::string::npos )
                                        {
                                            found = true;
                                        }
                                    }

                                    // Display and ask if the want to edit the question if the keyword is found
                                    if ( found )
                                    {
                                        // Display original question
                                        std::cout << "Question " << i << ":\n";
                                        std::cout << "       Type: " << qb->getQuestion( i )->getType() << std::endl;
                                        std::cout << "     Points: " << qb->getQuestion( i )->getPoints() << std::endl;
                                        std::cout << "   Question: ";
                                        highlightString( qb->getQuestion( i )->getQuestion(), keyword, INTENSE_GREEN );
                                        std::cout << "\n";
                                        if ( qb->getQuestion( i )->getType() == "MC" )
                                        {
                                            std::cout << "    Options:\n";
                                            for ( unsigned int j = 0; j < qb->getQuestion( i )->getOptionCount(); j++ )
                                            {
                                                std::cout << "       " << static_cast<char>( 65 + j ) << ". ";
                                                highlightString( qb->getQuestion( i )->getOption( j ), keyword, INTENSE_GREEN );
                                                std::cout << "\n";
                                            }
                                        }
                                        std::cout << "     Answer: ";
                                        highlightString( qb->getQuestion( i )->getAnswer(), keyword, INTENSE_GREEN );
                                        std::cout << "\n";

                                        // Ask if user want to edit the question
                                        std::cout << YELLOW << "Do you want to edit this question? ( Enter 'Y' to edit ) \n";
                                        std::cout << "  =>  " << DEFAULT;
                                        std::cin.get( input );
                                        flush( std::cin );    // Flush instream
                                        // Ask if the user to edit the questions
                                        if ( input == 'Y' || input == 'y' )
                                        {
                                            do
                                            {
                                                std::cout << "Select new question type ( TF, SA, MC ): ";
                                                getline( std::cin, newType );
                                                newType = toUpper( newType );
                                            }
                                            while ( newType != "TF" && newType != "SA" && newType != "MC" );

                                            if ( newType == "SA" )  // Edit QuestionSA
                                            {
                                                // Get question
                                                std::cout << INTENSE_MAGENTA << "Question:\n";
                                                setColour( DEFAULT );
                                                newQuestion = editString( qb->getQuestion( i )->getQuestion() );

                                                // Get points
                                                std::cout << INTENSE_CYAN << "Points:\n";
                                                setColour( DEFAULT );
                                                while ( !( std::cin >> newPoints ) )
                                                {
                                                    flush( std::cin );
                                                    std::cout << INTENSE_CYAN << "Points:\n";
                                                    setColour( DEFAULT );
                                                }
                                                std::cin.clear();
                                                std::cin.ignore( 1000, '\n' );

                                                // Get answer
                                                std::cout << INTENSE_CYAN << "Answer:\n";
                                                setColour( DEFAULT );
                                                getline( std::cin, newAnswer );

                                                // Update SA question
                                                qb->removeQuestion( i );
                                                i--;
                                                std::cout << INTENSE_GREEN << "SA question updated!\n" << DEFAULT;
                                                qb->addQuestion( newQuestion, newAnswer, newPoints, "SA" );
                                            }
                                            else if ( newType == "TF" ) // Edit QuestionTF
                                            {
                                                // Get question
                                                std::cout << INTENSE_MAGENTA << "Question:\n";
                                                setColour( DEFAULT );
                                                newQuestion = editString( qb->getQuestion( i )->getQuestion() );

                                                // Get points
                                                std::cout << INTENSE_CYAN << "Points:\n";
                                                setColour( DEFAULT );
                                                while ( !( std::cin >> newPoints ) )
                                                {
                                                    std::cin.clear();
                                                    std::cin.ignore( 1000, '\n' );
                                                    std::cout << INTENSE_CYAN << "Points:\n";
                                                    setColour( DEFAULT );
                                                }
                                                std::cin.clear();
                                                std::cin.ignore( 1000, '\n' );

                                                //  Check if answer is true or false
                                                while ( !isValid4 )
                                                {
                                                    // Get answer
                                                    std::cout << INTENSE_CYAN << "Answer:\n";
                                                    setColour( DEFAULT );
                                                    getline( std::cin, newAnswer );

                                                    if ( toLower( newAnswer ) == "true" || toLower( newAnswer ) == "false" )
                                                    {
                                                        isValid4 = true;
                                                        qb->removeQuestion( i );
                                                        i--;
                                                        std::cout << INTENSE_GREEN << "TF question updated!\n" << DEFAULT;
                                                        qb->addQuestion( newQuestion, newAnswer, newPoints, "TF" );
                                                    }
                                                    else
                                                    {
                                                        std::cout << INTENSE_RED << "Answer must be true or false!\n" << DEFAULT;
                                                    }
                                                }
                                            }
                                            else    // Edit QuestionMC
                                            {
                                                // Get question
                                                std::cout << INTENSE_MAGENTA << "Question:\n" << DEFAULT;
                                                newQuestion = editString( qb->getQuestion( i )->getQuestion() );

                                                // Get points
                                                std::cout << INTENSE_CYAN << "Points:\n" << DEFAULT;
                                                while ( !( std::cin >> newPoints ) )
                                                {
                                                    std::cin.clear();
                                                    std::cin.ignore( 1000, '\n' );
                                                    std::cout << INTENSE_CYAN << "Points:\n" << DEFAULT;
                                                }
                                                std::cin.clear();
                                                std::cin.ignore( 1000, '\n' );

                                                // Get options
                                                while ( !isValid4 )
                                                {
                                                    std::cout << YELLOW << "How many options would you like? ( 2 - 6 ) \n" << DEFAULT;
                                                    getline( std::cin, optionCount );
                                                    if ( isdigit( optionCount[ 0 ] ) )
                                                    {
                                                        newOptionCount = atoi( optionCount.c_str() );
                                                        if ( newOptionCount >= 2 && newOptionCount <= 6 )
                                                        {
                                                            isValid4 = true;
                                                            newOptions = new std::string[ newOptionCount ];
                                                            for ( unsigned int j = 0; j < newOptionCount; j++ )
                                                            {
                                                                std::cout << YELLOW << "Enter option " << j + 1 << ": \n";
                                                                setColour( DEFAULT );
                                                                std::getline( std::cin, newOption );
                                                                newOptions[ j ] = newOption;
                                                            }
                                                            isValid4 = true;
                                                        }
                                                        else
                                                        {
                                                            std::cout << INTENSE_RED << "Sorry, the number choice must be from 2 - 6.\n" << DEFAULT;
                                                            pause();
                                                        }
                                                    }
                                                    else
                                                    {
                                                        std::cout << INTENSE_RED << "Sorry, that is not a valid number.\n" << DEFAULT;
                                                        pause();
                                                    }
                                                }

                                                // Get answer
                                                std::cout << INTENSE_CYAN << "Answer ( A - " << static_cast<char>( 'B' + newOptionCount - 2 ) << " ):\n" << DEFAULT;
                                                std::cin >> newAns;
                                                while ( tolower( newAns ) <  'a' || tolower( newAns ) >  ( 'b' + newOptionCount - 2 ) )
                                                {
                                                    flush( std::cin );
                                                    std::cout << INTENSE_CYAN << "Answer ( A - " << static_cast<char>( 'B' + newOptionCount - 2 ) << " ):\n" << DEFAULT;
                                                    std::cin >> newAns;
                                                    setColour( DEFAULT );
                                                }
                                                qb->removeQuestion( i );
                                                std::cout << INTENSE_GREEN << "MC question updated!\n" << DEFAULT;
                                                qb->addQuestion( newQuestion, toupper( newAns ), newPoints, newOptionCount, newOptions );
                                                i--;
                                                std::cin.clear();
                                                std::cin.ignore( 1000, '\n' );
                                                delete [] newOptions;
                                            }
                                        }
                                    }
                                }
                                // Clean up everything
                                delete qb;
                            }
                            pause();
                            break;

                            case '4':
                            {
                                // LList to store the records in descending order
                                LList<HighScore> highscores;
                                int nPoints;
                                int nTotal;

                                // Read player's record
                                std::ifstream fin;
                                fin.open( "data/Records/records.txt" );
                                system( "cls" );
                                printBanner( "HIGH SCORE" );
                                std::string firstN, lastN, p, t;
                                std::cout << YELLOW  << "--------------------------------------------------------------------------------\n" << DEFAULT;
                                while ( !fin.eof() )
                                {
                                    getline( fin, firstN );
                                    getline( fin, lastN );
                                    getline( fin, p );
                                    if ( !fin.eof() )
                                    {
                                        getline( fin, t );
                                        nTotal = atoi( t.c_str() );
                                        nPoints = atoi( p.c_str() );
                                        highscores.sortedInsertDesc( HighScore( Player( firstN, lastN, nPoints ) , nTotal ) );
                                    }
                                }
                                fin.close();

                                int max = 10;
                                if ( highscores.getLength() < max )
                                {
                                    max = highscores.getLength();
                                }

                                for ( int i = 1; i <= max; i++ )
                                {
                                    std::cout << YELLOW << "    #" << i << "\n" << DEFAULT;
                                    std::cout << "    Player Name: " << INTENSE_MAGENTA << highscores[ i ].getPlayer().getFirstName()
                                              << " " << highscores[ i ].getPlayer().getLastName() << std::endl << DEFAULT;
                                    std::cout << "     Percentage: " << INTENSE_CYAN << highscores[ i ].getPercentage() << "%\n" << DEFAULT;
                                    std::cout << "         Points: " << INTENSE_GREEN << highscores[ i ].getTotalPoints() << std::endl << DEFAULT;
                                }

                                std::cout << YELLOW  << "--------------------------------------------------------------------------------\n" << DEFAULT;
                            }
                            pause();
                            break;

                            case '5':
                            {
                                // Read player's record
                                std::ifstream fin;
                                fin.open( "data/Records/records.txt" );
                                system( "cls" );
                                int nPoints;
                                int nTotal;
                                printBanner( "RECORDS" );
                                std::string fname, lname, points, total;
                                std::cout << YELLOW  << "--------------------------------------------------------------------------------\n" << DEFAULT;
                                while ( !fin.eof() )
                                {
                                    getline( fin, fname );
                                    getline( fin, lname );
                                    getline( fin, points );
                                    if ( !fin.eof() )
                                    {
                                        getline( fin, total );
                                        nTotal = atoi( total.c_str() );
                                        nPoints = atoi( points.c_str() );
                                        std::cout << "    Player Name: " << INTENSE_MAGENTA << fname << " " << lname << std::endl << DEFAULT;
                                        std::cout << "     Percentage: " << INTENSE_CYAN << 100 * ( static_cast<double>( nPoints ) / nTotal ) << "%\n" << DEFAULT;
                                        std::cout << "         Points: " << INTENSE_GREEN << points << std::endl << DEFAULT;
                                        std::cout << YELLOW  << "--------------------------------------------------------------------------------\n" << DEFAULT;
                                    }
                                }
                                fin.close();
                            }
                            pause();
                            break;

                            case '6':
                            {
                                system( "cls" );

                                // Initialize variables
                                std::string fileName;
                                std::ofstream fout;
                                printBanner( "CATEGORY" );

                                // Get question bank's name
                                std::cout << YELLOW << "Enter the name of new category:\n\n =>  " << DEFAULT;
                                do
                                {
                                    getline( std::cin, fileName );
                                    // flush( std::cin );
                                }
                                while ( fileName == "" );

                                // Create question bank
                                fout.open( "data/QuestionBanks/" + fileName + ".txt" );
                                std::cout << INTENSE_GREEN << fileName << " created!\n" << DEFAULT;

                                // Initialize the empty file
                                fout << "0\n";

                                // Close the file
                                fout.close();

                            }
                            pause();
                            break;

                            case 'Q':
                            case 'q':
                                quit = true;
                                break;

                            default:
                                std::cout << "Invalid Input!\n";
                                pause();
                        }
                    }
                }
                break;

            case 'Q':
            case 'q':
                quit = true;
                break;

            default:
                std::cout << "Invalid Input!\n";
                pause();
        }
    }

    return 0;
}

// This function will list all the QuestionBanks available and return a QuestionBank a user chose from the list
QuestionBank* chooseQuestionBank( std::string action )
{
    system( "cls" );
    printBanner( "CHOOSE" );
    std::vector<QuestionBank*> qb;
    int choice;
    int count = 0;
    int fileCount = 0;
    std::string line;
    std::ifstream fin;

    // Update Metadata.txt that will locate all QuestionBank stores in the QuestionBanks folder
    system( "dir data\\QuestionBanks /b > data\\Metadata.txt" );

    // Get how many lines from metadata and display choices
    std::cout << YELLOW << "Choose a question bank " << action << ".\n";

    // Load the Metadata.txt
    fin.open( "data/Metadata.txt" );

    while( !fin.eof() )
    {
        // Read and list all QuestionBanks
        getline( fin, line );
        if ( !fin.eof() )
        {
            count++;
            // Remove ".txt"
            for ( int i = 0; i < 4; i++ )
                line.pop_back();
            std::cout << YELLOW << "    " << count << DEFAULT << ". " << line << "\n";
        }
    }
    fin.close();

    // Load all QuestionBanks to qb
    fin.open( "data/Metadata.txt" );

    while( !fin.eof() )
    {
        getline( fin, line );
        if ( !fin.eof() )
        {
            qb.push_back( new QuestionBank );
            qb[ fileCount ]->loadQuestions( "data/QuestionBanks/" + line );
            fileCount++;
        }
    }
    fin.close();

    // Let user choose the question bank
    do
    {
        std::cout << YELLOW << " =>  " << DEFAULT;
        getline( std::cin, line );
        choice = atoi( line.c_str() );
    }
    while ( choice < 1 || choice > count );

        // Flush the standard input stream
    return qb[ choice - 1 ];

}

// This function will prompt the user to login and return true if login success
bool login()
{
    std::string name;

    system( "cls" );
    printBanner( "LOGIN" );
    std::cout << INTENSE_CYAN << "                              Name: " << DEFAULT;

    getline( std::cin, name );

    std::cout << INTENSE_CYAN
              << "                          Password: " << DEFAULT;

    if ( getPassword() == "admin" && name == "admin" )
    {
        std::cout << INTENSE_GREEN << "\n                             Login success!\n" << DEFAULT;
        return true;
    }

    std::cout << INTENSE_RED << "\n                             Access denied!\n" << DEFAULT;
    pause();
    return false;
}

// This function prints out a banner
void printBanner( std::string text )
{
    std::cout << YELLOW
              << "================================================================================\n";
    std::cout << DEFAULT << std::setw( 45 ) << text << "\n" << YELLOW
              << "================================================================================\n";
}
