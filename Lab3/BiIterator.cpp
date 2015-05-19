/**********************************************
* File: BiIterator.cpp                        *
* Author: Aida Nordman                        *
* Course: TND004, Lab 2                       *
* Date: VT2, 2014                             *
* Description: class biIterator               *
* Represents bidirectional iterators          *
***********************************************/


#include "BiIterator.h"


#ifndef DOXYGEN_SHOULD_SKIP_THIS


// Constructor
BiIterator::BiIterator(Node *ptr)
 : current(ptr)
 { }


//Dereferencing operator
ELEMENT& BiIterator::operator*() const
{
    //static ELEMENT e("", 0); //MUST remove this code
    //FUNGERAR DENNA?

    return current->value;
}


//Member access operator
ELEMENT* BiIterator::operator->() const
{
    //FUNGERAR?

    return &(current->value);
}


//Equality comparison operator
//param it reference to the rhs iterator of the comparison.
//return true, if this iterator and it point to the same node. Otherwise, return false.
bool BiIterator::operator==(const BiIterator &it) const
{
    //FUNGERAR DENNA?
    //pekar iterator och it på samma sak? == true
    if(current == it.current) //kollar adressen
        return true;

    return false;
}


//Inequality comparison operator
bool BiIterator::operator!=(const BiIterator &it) const
{
    if(current != it.current)
        return true;

    return false;
}


//Pre increment operator
//Advance the iterator to point to the next node in the inorder traversal.
//return This iterator, after advancing the internal pointer.
BiIterator& BiIterator::operator++()
{
    //FUNGERAR? VI FATTAR  INTE RIKTIGT........
    //Node* tmp = current;
    if (!current->r_thread) //is there right sub-tree
        current = current->right->findMin();

    else
        current = current->left->findMax(); //follow right thread

    return *this;
}


//Pos increment operator: see page 277 and 278 of C++ direkt
//Advance the iterator to point to the next node in the inorder traversal.
//return (A copy of) this iterator, before advancing the internal pointer.
BiIterator BiIterator::operator++(int)
{
    cout << "kiss!";
    BiIterator it(current);

    if (!current->r_thread) //is there right sub-tree
        current = current->right->findMin();
    else
        current = current->right->right->findMin();

    return it;

//        while(!current->left->l_thread)
//        {
//            current = current->left; //find the smallest node of the right subtree
//        }
//        Node* tmp = current;
//        current = current->left;
//        return tmp;
//
//
//    else
//    {
//        Node* tmp = current;
//        current = current->right; //follow right thread
//        return tmp;
//    }
}

//Pre decrement operator
//Make the iterator to point to the previous node in the inorder traversal.
//return This iterator, after updating the internal pointer.
BiIterator& BiIterator::operator--()
{
    //WAHHHOOOOO!
    if (!current->l_thread) //is there left sub-tree?
        current = current->left->findMax();

    else
        current = current->right->findMin();

    return *this;

//    {
//        do
//        {
//            current = current->right; //find the biggest node of the left subtree
//        } while (!current->r_thread);
//    }
//
//    else
//        current = current->left; //follow left thread
//
//    return *this;
}

//Pos decrement operator
BiIterator BiIterator::operator--(int)
{
    BiIterator it(current);

	if (!current->l_thread)
		current = current->left->findMax();
	else
		current = current->right->findMin();

	return it;



//    if (!current->l_thread) //is there left sub-tree?
//    {
//        while(!current->right->r_thread)
//        {
//            current = current->right; //find the smallest node of the right subtree
//        }
//        Node* tmp = current;
//        current = current->right;
//        return tmp;
//    }
//
//    else
//    {
//        Node* tmp = current;
//        current = current->left; //follow right thread
//        return tmp;
//    }
}

#endif /* DOXYGEN_SHOULD_SKIP_THIS */
