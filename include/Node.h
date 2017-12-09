//  Created by Frank M. Carrano and Tim Henry.
//  Copyright (c) 2013 __Pearson Education__. All rights reserved.
//  Slight modification by GOH KUN SHUN

/** @file Node.h
    Listing 4-1 */

#pragma once

template <class ObjectType>
class Node
{
    public:
        Node();
        Node( const ObjectType& obj ) ;
        Node( const ObjectType& obj, Node<ObjectType>* nextNodePtr );
        void setObject( const ObjectType& obj );
        void setNext( Node<ObjectType>* nextNodePtr ) ;
        ObjectType getObject() const;
        Node<ObjectType>* getNext() const;

    private:
        ObjectType object;
        Node<ObjectType>* next;
};

#include "Node.cpp"
