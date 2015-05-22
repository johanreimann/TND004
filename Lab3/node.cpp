/**********************************************
* File: node.cpp                              *
* Author: Aida Nordman                        *
* Course: TND004, Lab 3                       *
* Date: VT2, 2014                             *
* Description: class Node                     *
***********************************************/

#include "node.h"

#ifndef DOXYGEN_SHOULD_SKIP_THIS


Node::Node(ELEMENT v, Node *l, Node *r)
 : value(v), left(l), right(r)
{
    l_thread = r_thread = true; //ledig = true, pekar isch på root
}


//Destructor
//recursively deletes the nodes in the left_subtree and right-subtree
Node::~Node()
{
    if(!l_thread)
        delete left;

    if(!r_thread)
        delete right;
}


//Insert v in the tree having as root this node
//Return true, if v was inserted
//Otherwise, return false --v already exists in the tree
bool Node::insert(ELEMENT v)
{
    Node *tmp = this;

    if(tmp->value.first == v.first)
    {
        tmp->value.second++;
        return false;
    }

    //Lägg till åt höger
    else if(v.first > value.first && tmp->r_thread)
    {
        Node *newNode = new Node(v, tmp, tmp->right);
        tmp->right = newNode;
        tmp->r_thread = false;
        return true;
    }
    //lägg till åt vänster
    else if(v.first < value.first && tmp->l_thread)
    {
        Node *newNode = new Node(v, tmp->left, tmp);
        tmp->left = newNode;
        tmp->l_thread = false;
        return true;
    }

    //Stega vidare i trädet åt höger
    else if(v.first > value.first && !tmp->r_thread)
    {
        tmp = tmp->right;
        return tree_insert(this, tmp, v);
    }

    //Stega vidare i trädet åt vänster
    else if(v.first < value.first && !tmp->l_thread)
    {
        tmp = tmp->left;
        return tree_insert(this, tmp, v);
    }
    return false;
}


// tryck in i trädet!
bool Node::tree_insert(Node* n, Node* tmp, ELEMENT v)
{
    bool ins = false;

    do
    {
        if(tmp->value.first == v.first)
        {
            tmp->value.second++;
            return false;
        }
        //om större och höger är ledig->lägg in till höger
        else if(v.first > tmp->value.first && tmp->r_thread)
        {
            Node *newNode;

            newNode = new Node(v, tmp, tmp->right);

            tmp->right = newNode;
            tmp->r_thread = false;
            return true;
        }

        //gå åt höger
        else if( v.first > tmp->value.first&& !tmp->r_thread)
            tmp = tmp->right;

        //gå åt vänster
        else if( v.first < tmp->value.first&& !tmp->l_thread)
            tmp = tmp->left;

        //lägg in till höger
        else if(v.first > tmp->value.first && tmp->r_thread)
        {
            Node *newNode;

            //Om parent pekar på root
            newNode = new Node(v, tmp, tmp->right);

            tmp->right = newNode;
            tmp->r_thread = false;
            return true;
        }

        //Lägg till vänster
        else if(v.first < tmp->value.first && tmp->l_thread)
        {
            Node* newNode;
            //Om parent pekar på root
            newNode = new Node(v, tmp->left, tmp);

            tmp->left = newNode;
            tmp->l_thread = false;
            return true;
        }
    } while(!ins);
}


//Remove the key from the tree having as root this node
//Return true, if a node storing key was found and deleted
//Otherwise, return false -- there is no node storing key
//isRight==false: this node is left child of parent
//isRight==true: this node is right child of parent
bool Node::remove(string key, Node* parent, bool isRight)
{
    //fall 1: vänster nod med både vänster och höger child
    if (!isRight && !l_thread && !r_thread)
    {
        Node* tmp = this;
        value = tmp->right->findMin()->value;
        if(!tmp->right->l_thread)
        {
            tmp = tmp->right;
            while(!tmp->left->l_thread)
                tmp = tmp->left;

            tmp->left->removeMe(tmp, false);
        }
        else
            tmp->right->removeMe(tmp, true);
    }

    //fall 2: höger nod med både vänter och höger child
    else if (isRight && !l_thread && !r_thread)
    {
        Node* tmp = this;
        tmp->value = tmp->left->findMin()->value;
        tmp = tmp->left;
        if(!tmp->l_thread)
        {
            while(!tmp->left->l_thread)
                tmp = tmp->left;
        }
        tmp->left->removeMe(tmp, false);
    }

    else
        removeMe(parent, isRight);

    return false;
}



//Remove this node -- this node has at most one child
//isRight==false: this node is left child of parent
//isRight==true: this node is right child of parent
//Remove has 6 cases
//1a: a left child with only a right child
//1b: a left child with only a left child
//1c: a left child with no children
//2a: a right child with only a right child
//2b: a right child with only a left child
//2c: a right child with no children
void Node::removeMe(Node* parent, bool isRight)
{
    //1a; left child with only a right child
    if (!isRight && l_thread && !r_thread)
    {
        parent->left = right;
        right->left = left;
    }

    //1b: a left child with only a left child
    else if (!isRight && !l_thread && r_thread)
    {
        parent->left = left;
        left->right = right;
    }

    //1c: a left child with no children
    else if (!isRight && l_thread && r_thread)
    {
        parent->left = parent->left->left;
        parent->l_thread = true;
    }

    //2a: a right child with only a right child
    else if (isRight && l_thread && !r_thread)
    {
        parent->right = right;
        right->left = left;
    }

    //2b: a right child with only a left child
    else if (isRight && !l_thread && r_thread)
    {
        parent->right = left;
        left->right = right;
    }

    //2c: a right child with no children
    else
    {
        parent->right = right;
        parent->r_thread = true;
    }
}



//Return a pointer to the Node storing key
//key is possibly stored in one of the sub-trees of this node
//If there is no node storing key then return nullptr
Node* Node::find(string key)
{
    if(value.first == key)
        return this;

    else if(key < value.first && !l_thread)
        return left->find(key);

    else if(key > value.first && !r_thread)
        return right->find(key);

    return nullptr;
}

//return parent(node) of found key
Node* Node::find_parent(string key, bool &is_right)
{
    if (key < value.first && !l_thread)
    {
        if (left->value.first == key)
        {
            is_right = false;
            return this; //return parent
        }
        else
            return left->find_parent(key, is_right);
    }

    else if (key > value.first && !r_thread )
    {
        if (right->value.first == key)
        {
            is_right = true;
            return this;
        }
        else
            return right->find_parent(key, is_right);
    }
    return nullptr; //hittar ej
}


//Return a pointer to the node storing the smallest value
//of the tree whose root is this node
Node* Node::findMin()
{
    //ADD CODE
    if(l_thread)
        return this;

    return left->findMin();
}


//Return a pointer to the node storing the largest value
//of the tree whose root is this node
Node* Node::findMax()
{
    //ADD CODE
    if(r_thread)
        return this;

    return right->findMax();
}


//Display in inorder all keys
//stored in the tree whose root is this node
//recursive function
//Used for debugging -- ONLY
void Node::display() const
{
    if ( !l_thread ) //display left sub-tree
        left->display();

    cout << value.first << " "; //display key stored in the node

    if ( !r_thread ) //display right sub-tree
        right->display();
}


#endif /* DOXYGEN_SHOULD_SKIP_THIS */
