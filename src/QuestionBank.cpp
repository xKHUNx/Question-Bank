/**********************************************************

                     Name: GOH KUN SHUN

                       ID: 1151101980

                    Email: kunshun225@gmail.com

                    Phone: 017-285 9398

***********************************************************/

#include "QuestionBank.h"
#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <stdlib.h>
#include <algorithm>
#include "Utility.h"
#include "Colour.h"
#include "QuestionMC.h"
#include "QuestionTF.h"
#include "QuestionSA.h"

QuestionBank::QuestionBank()
{

}

QuestionBank::~QuestionBank()
{
    while( !questions.isEmpty() )
        questions.erase( 1 );
}

bool QuestionBank::loadQuestions( std::string fileName )
{
    // Initialize variables
    std::ifstream fin;
    std::string line, type, points, question, options_count, answer;
    unsigned int nOptions_count, nPoints, qCount;

    // Open quiz file
    fin.open( fileName.c_str() );

    // Return error if opening fail
    if ( fin.fail() )
    {
        std::cout << INTENSE_RED << "File not found!\n" << DEFAULT;
        pause();
        return false;
    }

    // Set the opened file as database
    database = fileName;

    // Load question count
    getline( fin, line );
    qCount = atoi( line.c_str() );

    // Loop through question file
    while ( !fin.eof() && qCount > 0 )
    {
        // Load string to stringstream
        getline( fin, line );
        std::istringstream sin( line );
        // Get question type and points from from stringstream
        sin >> type >> points;
        // Convert points from string to integer
        nPoints = atoi( points.c_str() );
        // Generate questions based on question type
        switch ( type[ 0 ] )
        {
            case 'T':
                {
                    getline( fin, question );
                    getline( fin, answer );
                    questions.insert( new QuestionTF( question, answer, nPoints ) );
                    qCount--;
                }
                break;

            case 'M':
                {
                    getline( fin, question );
                    getline( fin, options_count );
                    nOptions_count = atoi( options_count.c_str() );
                    std::string* options = new std::string[ nOptions_count ];
                    for ( unsigned int i = 0; i < nOptions_count; i++ )
                    {
                        getline( fin, line );
                        options[ i ] = line;
                    }
                    getline( fin, answer );
                    questions.insert( new QuestionMC( question, answer, nPoints, nOptions_count, options ) );
                    qCount--;
                    delete [] options;
                }
                break;

            case 'S':
                {
                    getline( fin, question );
                    getline( fin, answer );
                    questions.insert( new QuestionSA( question, answer, nPoints ) );
                    qCount--;
                }
                break;
        }
    }
    // Clean up
    fin.close();

}

void QuestionBank::printAllQuestions()
{
    for ( unsigned int i = 1; i <= questions.getLength(); i++ )
    {
        std::cout << "Question " << i << ":\n";
        std::cout << "       Type: " << questions[ i ]->getType() << std::endl;
        std::cout << "     Points: " << questions[ i ]->getPoints() << std::endl;
        std::cout << "   Question: " << questions[ i ]->getQuestion() << std::endl;
        if ( questions.retrieve( i )->getType() == "MC" )
        {
            std::cout << "    Options:\n";
            for ( int j = 0; j < questions[ i ]->getOptionCount(); j++ )
            {
                std::cout << "       " << static_cast<char>( 65 + j ) << ". " << questions[ i ]->getOption( j ) << std::endl;
            }
        }
        std::cout << "     Answer: " << questions[ i ]->getAnswer() << std::endl;
        std::cout << std::endl;
    }
}

void QuestionBank::shuffle()
{
    questions.randomize();
}

void QuestionBank::addQuestion( std::string q, std::string a, int p, std::string type )
{
    if ( type == "TF" )
    {
        questions.insert( new QuestionTF( q, a, p ) );
    }
    else if ( type == "SA" )
    {
        questions.insert( new QuestionSA( q, a, p ) );
    }
    saveQuestionBanks();
}

void QuestionBank::addQuestion( std::string q, char a, int p, int oc, std::string* op )
{
    std::string ans;
    ans.push_back( a );
    questions.insert( new QuestionMC( q, ans, p, oc, op ) );
    saveQuestionBanks();
}

void QuestionBank::removeQuestion( int n )
{
    questions.erase( n );
    saveQuestionBanks();
}

void QuestionBank::saveQuestionBanks()
{
    // Open the database to be updated
    std::ofstream fout;
    fout.open( database );

    // Overwrite the data inside the database file
    fout << questions.getLength() << "\n";              // Write in the number of questions

    for( int i = 1; i <= questions.getLength(); i++ )    // Write in the questions
    {
        fout << questions[ i ]->getType() << " " << questions[ i ]->getPoints() << "\n";
        fout << questions[ i ]->getQuestion() << "\n";

        // Check if question is MC type
        if( questions[ i ]->getType() == "MC" )
        {
            fout << questions[ i ]->getOptionCount() << "\n";
            for ( int j = 0; j < questions[ i ]->getOptionCount(); j++ )
            {
                fout << questions[ i ]->getOption( j ) << "\n";
            }
        }

        fout << questions[ i ]->getAnswer() << "\n";
    }

    fout.close();
}

unsigned int QuestionBank::getQuesCount()
{
    return questions.getLength();
}

Question* QuestionBank::getQuestion( int n )
{
    return questions.retrieve( n );
}
