//  Created by Frank M. Carrano and Tim Henry.
//  Copyright (c) 2013 __Pearson Education__. All rights reserved.
//  Slight modification by GOH KUN SHUN

/** @file Node.cpp
    Listing 4-2 */

#include "LList.h"
#include "Node.h"
#include <stdlib.h>
#include <iostream>
#include <ctime>

template <class ObjectType>
LList<ObjectType>::LList()
    :  headPtr( nullptr ), objCount( 0 )
{

}


template <class ObjectType>
LList<ObjectType>::LList( const LList<ObjectType> &linkedList )
    : objCount( linkedList.objCount ), sortDsc( linkedList.sortDsc )
{
    Node<ObjectType>* origListPtr = linkedList.headPtr;  // Points to nodes in original chain

    // Check if original chain it empty
    if ( origListPtr == nullptr )
        headPtr = nullptr;
    else
    {
        // Copy first node
        headPtr = new Node<ObjectType>();
        headPtr->setObject( origListPtr->getObject() );

        // Copy remaining nodes
        Node<ObjectType>* newListPtr = headPtr;     // Points to last node in new chain
        origListPtr = origListPtr->getNext();       // Advance original-chain pointer
        while ( origListPtr != nullptr )
        {
            // Get next object from original chain
            ObjectType nextObject = origListPtr->getObject();

            // Create a new node containing the next object
            Node<ObjectType>* newNodePtr = new Node<ObjectType>( nextObject );

            // Link new node to end of new chain
            newListPtr->setNext( newNodePtr );

            // Advance pointer to new last node
            newListPtr = newListPtr->getNext();

            // Advance original-chain pointer
            origListPtr = origListPtr->getNext();
        }

        newListPtr->setNext( nullptr );
    }
}

template <class ObjectType>
LList<ObjectType>::~LList()
{
    clear();
}

template <class ObjectType>
bool LList<ObjectType>::isEmpty()
{
    return objCount == 0;
}

template <class ObjectType>
int LList<ObjectType>::getLength()
{
    return objCount;
}

template <class ObjectType>
bool LList<ObjectType>::insert( ObjectType obj )
{
    return insertAt( obj, objCount + 1 );
}

template <class ObjectType>
bool LList<ObjectType>::sortedInsertDesc( ObjectType obj )
{
    // Sort the nodes
    if ( !sortDsc )
        sortDesc();

    // Create new node to be insert
    Node<ObjectType>* newNodePtr = new Node<ObjectType>( obj );

    // If the objCount is 0 or it's smaller than the first node, insert the new item at the beginning
    if ( objCount == 0 || obj > headPtr->getObject() )
    {
        // Point newNodePtr's nest to headPtr
        newNodePtr->setNext( headPtr );
        // set newNodePtr as the new headPtr
        headPtr = newNodePtr;
        // Update objCount
        objCount++;
        return true;
    }
    else
    {
        // Declare 2 pointers to allow new entry to be inserted in the middle
        Node<ObjectType>* prevPtr = headPtr;
        Node<ObjectType>* currentPtr;
        // A counter to keep track of current item position
        int i = 1;
        // Check if there is only one item, if yes, put it at the end, otherwise loop until
        //   you find the suitable position to be inserted or objCount is reach
        while ( i < objCount )
        {
            // Point current pointer to prevPtr's next
            currentPtr = prevPtr->getNext();
            if ( obj <= prevPtr->getObject() && obj >= currentPtr->getObject() )
            {
                // Connect prevPtr's next to newNodePtr
                prevPtr->setNext( newNodePtr );
                // Connect newNodePtr's next to currentPtr
                newNodePtr->setNext( currentPtr );
                // Update objCount
                objCount++;
                return true;
            }
            // Update counter
            i++;
            // Update prevPtr to it's next
            prevPtr = prevPtr->getNext();
        }

        // Insert the new node at the end
        // Set newnOdePtr's next to nullptr
        newNodePtr->setNext( nullptr );
        // Connect the previous last node's next ( prevPtr ) to new node
        prevPtr->setNext( newNodePtr );
        // Update objCount
        objCount++;
        return true;
    }

}

template <class ObjectType>
bool LList<ObjectType>::erase( int pos )
{
    bool ableToRemove = ( pos >= 1 ) && ( pos <= objCount );
    if ( ableToRemove )
    {
        Node<ObjectType>* curPtr = nullptr;
        if ( pos == 1 )
        {
            // Remove the first node in the chain
            curPtr = headPtr;   // Save pointer to node
            headPtr = headPtr->getNext();
        }
        else
        {
            // Find node that is before the one to delete
            Node<ObjectType>* prevPtr = getNodeAt( pos - 1 );

            // Point to node to delete
            curPtr = prevPtr->getNext();

            // Disconnect indicated node from chain by connecting the
            // prior node with the one after
            prevPtr->setNext( curPtr->getNext() );
        }

        // Return node to system
        curPtr->setNext( nullptr );
        delete curPtr;
        curPtr = nullptr;

        objCount--;  // Decrease count of entries
    }

    return ableToRemove;
}

template <class ObjectType>
ObjectType LList<ObjectType>::retrieve( int pos )
{
    // Enforce precondition
   bool ableToGet = ( pos >= 1 ) && ( pos <= objCount );

   if ( ableToGet )
      return getNodeAt( pos )->getObject();
   else
   {
      std::string message = "getEntry() called with an empty list or ";
      message  = message + "invalid position.";
      throw( PrecondViolatedExcep( message ) );
   }

}

template <class ObjectType>
void LList<ObjectType>::randomize()
{
    // Seed random generator
    srand( time( NULL ) );
    int n = 0;
    // Swap questions with from random generated number n
    for ( unsigned int i = 1; i <= objCount; i++ )
    {
        n = rand() % objCount;
        swapNodes( i, n );
    }
    sortDsc = false;
}

template  <class ObjectType>
bool LList<ObjectType>::insertAt( ObjectType obj, int pos )
{
    bool ableToInsert = ( pos >= 1 ) && ( pos <= objCount + 1 );
    if ( ableToInsert )
    {
        // Create a new node containing the new entry
        Node<ObjectType>* newNodePtr = new Node<ObjectType>( obj );

        // Attach new node to chain
        if ( pos == 1 )
        {
            // Insert new node at beginning of chain
            newNodePtr->setNext( headPtr );
            headPtr = newNodePtr;
        }
        else
        {
            // Find node that will be before new node
            Node<ObjectType>* prevPtr = getNodeAt( pos - 1 );

            // Insert new node after node to which prevPtr points
            newNodePtr->setNext( prevPtr->getNext() );
            prevPtr->setNext( newNodePtr );
        }
        objCount++;  // Increase count of entries
        sortDsc = false;
    }

    return ableToInsert;
}

template  <class ObjectType>
Node<ObjectType>* LList<ObjectType>::getNodeAt( int pos ) const
{
    // Debugging check of precondition
    bool validPosition = ( ( pos >= 1 ) && ( pos <= objCount ) );

    if ( validPosition )
    {
        // Count from the beginning of the chain
        Node<ObjectType>* curPtr = headPtr;
        for ( int skip = 1; skip < pos; skip++ )
            curPtr = curPtr->getNext();
        return curPtr;
    }
    else
        return nullptr;
}

template  <class ObjectType>
bool LList<ObjectType>::swapNodes( int pos1, int pos2 )
{
    bool validSwap = ( ( pos1 >= 1 ) && ( pos1 <= objCount ) && ( pos2 >= 1 ) && ( pos2 <= objCount ) );

    if ( validSwap )
    {
        // Create pointers that points to node to be swapped
        Node<ObjectType>* node1 = getNodeAt( pos1 );
        Node<ObjectType>* node2 = getNodeAt( pos2 );

        // Swap the objects in the nodes
        ObjectType temp = node1->getObject();
        node1->setObject( node2->getObject() );
        node2->setObject( temp );
    }
    return validSwap;
}

template <class ObjectType>
void LList<ObjectType>::clear()
{
   while ( !isEmpty() )
      erase( 1 );
}

template  <class ObjectType>
ObjectType LList<ObjectType>::operator[]( int i )
{
    return retrieve( i );
}

template <class ObjectType>
void LList<ObjectType>::sortDesc()
{
    int max_index;
    for ( int i = 1; i <= objCount; i++ )
    {
        max_index = i;
        for ( int j = i; j <= objCount; j++ )
        {
            if ( getNodeAt( j )->getObject() > getNodeAt( max_index )->getObject() )
            {
                max_index = j;
            }
        }
        swapNodes( i, max_index );
    }
    sortDsc = true;
}
