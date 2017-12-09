//  Created by Frank M. Carrano and Tim Henry.
//  Copyright (c) 2013 __Pearson Education__. All rights reserved.
//  Slight modification by GOH KUN SHUN

/** @file Node.cpp
    Listing 4-2 */

#include "Node.h"

template <class ObjectType>
Node<ObjectType>::Node() : next( nullptr )
{

}

template <class ObjectType>
Node<ObjectType>::Node( const ObjectType& obj )
    : object( obj ), next( nullptr )
{

}

template <class ObjectType>
Node<ObjectType>::Node( const ObjectType& obj, Node<ObjectType>* nextNodePtr )
    : object( obj ), next( nextNodePtr )
{

}

template <class ObjectType>
void Node<ObjectType>::setObject( const ObjectType& obj )
{
    object = obj;
}

template <class ObjectType>
void Node<ObjectType>::setNext( Node<ObjectType>* nextNodePtr )
{
    next = nextNodePtr;
}

template <class ObjectType>
ObjectType Node<ObjectType>::getObject() const
{
    return object;
}

template <class ObjectType>
Node<ObjectType>* Node<ObjectType>::getNext() const
{
    return next;
}
