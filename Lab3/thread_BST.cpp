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


int BST_threaded::get_counter()
{
    return counter;
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
    //hitta nod och parent till denna.
    bool is_right = false;
    Node *node_parent;

    if (root->left->value.first == key)
        root->left->remove(key, root, is_right);

    else
    {
        node_parent = root->left->find_parent(key, is_right);
        if (node_parent) //om den hittas
        {
            if(is_right)
                counter -= node_parent->right->remove(key, node_parent, is_right);

            else
                counter -= node_parent->left->remove(key, node_parent, is_right);
        }
        else
            cout << "hittade inte noden!" << endl;
    }
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
    return *it;
}


//Find the node in the BST storing key
//Return a BiIterator referring to the node storing the key, if the key is found.
//Otherwise, return this->end().

//Stega ökande: lägsta till största
BiIterator BST_threaded::find(string key) const
{
    Node *tmp;
    if(!root->l_thread)
    {
        tmp = root->left->find(key);
        if(tmp != nullptr)
            return BiIterator(tmp);

        else
            return end();
    }
    else
        return end();
}


//Return an iterator referring to the first node in the inorder traversal(genomkorsande) of the BST
BiIterator BST_threaded::begin() const
{
    Node *node = root->findMin();
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
