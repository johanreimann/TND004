/********************************************************
* File: threaded_BST.cpp                                *
* Author: Aida Nordman                                  *
* Course: TND004, Lab 3                                 *
* Date: VT2, 2014                                       *
* Description: class BST_threaded representing          *
*              a threaded binary search tree            *
*********************************************************/

#include "threaded_BST.h"

#ifndef DOXYGEN_SHOULD_SKIP_THIS

using namespace std;


//Default Constructor: create an empty tree
//Empty tree has a dummy node as root
//The real tree is stored as left child of the dummy root
BST_threaded::BST_threaded()
 : counter(0)
{
    root = new Node(ELEMENT(), root, root);
}


//destructor
BST_threaded::~BST_threaded()
{
    delete root;
}


//Test if the tree is empty
bool BST_threaded::empty() const
{
    if(root->l_thread)
        return true;

    return false;
}

//Return number of keys (elements) stored in the tree
int BST_threaded::size() const
{
    return  counter;
}


//Insert v in the tree
void BST_threaded::insert(ELEMENT v)
{
    if (empty())
    {
        //Insert first node of the BST has a left child of the BST
        root->left = new Node(v, root, root);
        root->left->l_thread = root->left->r_thread = true;

        root->l_thread = false;
        counter = 1;
    }

    else
        counter += root->left->insert(v); //call NODE::insert()
}


//Remove node with key from the tree
void BST_threaded::remove(string key)
{
   //ADD CODE
}



//If key matches the key of an element in the container,
//then return a reference to the ELEMENT with the key
//If key does not match the key of any element in the container,
//then an ELEMENT (key,0) is inserted and a reference to it is returned
ELEMENT& BST_threaded::operator[](string key)
{
    BiIterator it = find(key);

    if(it == end())
    {
        insert(ELEMENT(key, 0));
        it = find(key);
    }

    //VARFÖR FUNKAR DET INTE UTAN ATT DEKLARERA DESSA?CP
//    string k = it->first;
//    int t = it->second;

//    ELEMENT f(it->first, it->second);

//    ELEMENT f(k, t);

    return *it; //MUST remove this code
}


//Find the node in the BST storing key
//Return a BiIterator referring to the node storing the key, if the key is found.
//Otherwise, return this->end().

//Stega ökande: lägsta till största
BiIterator BST_threaded::find(string key) const
{
    Node *tmp = root->left->find(key);

    if(tmp != nullptr)
        return BiIterator(tmp);

    else
        return end();

   /* Node *tmp = root->left;
    BiIterator it = begin(); //ELEMENTET
    bool ins = false;

    for (it; it != end(); it++)
    {
        if(it->first == key)
            return it;
    }*/

//    cout << "KEY " << key << endl;
/*
    while(!ins)
    {

//        cout << " IT: " << it->value.first << endl;
//        cout << "KEY:  " << key << endl;

        if(key == it->first)
        {
            cout << "2" << endl;
            ins = true;
            cout << "HÄR ÄR IT: " << it->first << endl;
            return it;
        }


        else if(key < it->first && !it->)
        {
//            cout << "3" << endl;
            it = it->left;
//             cout << "efter 3: " << it->value.first << endl;
        }


        else if(key > it->value.first && !it->r_thread)
        {
//            cout << "4" << endl;
            it = it->right;
        }


        else if((key < it->value.first && it->l_thread) || (key > it->value.first && it->r_thread))
        {
            ins = true;
            return end();
        }

    }*/


}


//Return an iterator referring to the first node in the inorder traversal(genomkorsande) of the BST
BiIterator BST_threaded::begin() const
{
    Node *node = root->findMin();
    cout << "MIN: " << node->value.first << endl;
    return BiIterator(node);
}


 //Return a BiIterator referring to the past-the-end element in the BST
BiIterator BST_threaded::end() const
{
    BiIterator it(root);

    return it;
}


//Display all keys increasingly
//To be used for debugging -- ONLY
void BST_threaded::display() const
{
    if (!empty())
        root->left->display();
     else
        cout << "The container is empty!!" << endl;

}


#endif /* DOXYGEN_SHOULD_SKIP_THIS */
