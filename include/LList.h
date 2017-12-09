//  Created by Frank M. Carrano and Tim Henry.
//  Copyright (c) 2013 __Pearson Education__. All rights reserved.
//  Slight modification by GOH KUN SHUN

/** ADT list: Link-based implementation.
    Listing 9-2.
    @file LList.h */

#pragma once
#include "Node.h"
#include "PrecondViolatedExcep.h"

template <class ObjectType>
class LList
{
    public:
        // Constructors
        LList();
        LList( const LList<ObjectType> &linkedList );

        // Destructor
        ~LList();

        // Public member functions
        bool isEmpty();
        int getLength();
        bool insert( ObjectType obj );
        bool sortedInsertDesc( ObjectType obj );
        bool erase( int pos );
        ObjectType retrieve( int pos );
        void randomize();

        // Operator overloading
        ObjectType operator[]( int i );

    private:
        // Private data members
        Node<ObjectType>* headPtr;
        int objCount = 0;
        bool sortDsc = false;

        // Private function
        bool insertAt( ObjectType obj, int pos );
        Node<ObjectType>* getNodeAt( int pos ) const;
        void clear();
        void sortDesc();
        bool swapNodes( int pos1, int pos2 );



};

#include "LList.cpp"
