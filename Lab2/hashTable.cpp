#include <assert.h>
#include <iomanip>


#include "hashTable.h"

/*
Kraschar vid dump table: Konstruktorn skapar en hashtable med skräpvärde i plats 1, varför?
Funkar om man sätter hTable[0] till nullptr.
*/

const double MAX_LOAD_FACTOR = 0.5;

//Test if a number is prime
bool isPrime( int n )
{
    if( n == 2 || n == 3 )
        return true;

    if( n == 1 || n % 2 == 0 )
        return false;

    for( int i = 3; i * i <= n; i += 2 )
        if( n % i == 0 )
            return false;

    return true;
}

//Return a prime number at least as large as n
int nextPrime( int n )
{
    if( n % 2 == 0 )
        n++;

    for(; !isPrime( n ); n += 2 );

    return n;
}

// Constructor
// IMPLEMENT
HashTable::HashTable(int table_size, HASH f)
    : size(nextPrime(table_size)), h(f), nItems(0)
{
    hTable = new Item*[size];

    for(int i = 0; i < size; i++)
        hTable[i] = nullptr;
}


//destructor
// IMPLEMENT
HashTable::~HashTable()
{
//    Item* temp;
//
//    for(int i = 0; i < size; i++)
//    {
//        temp = hTable[i];
//        delete temp;
//    }
    delete hTable;
}


//Return the load factor of the table
double HashTable::loadFactor() const
{
    return (double) nItems / size;
}


//Return the value associated with key
//If key does not exist in the table then NOT_FOUND is returned
// IMPLEMENT
int HashTable::find(string key) const
{
    int slot = h(key, size);
    int counter = 0;

    do {
        if(hTable[slot] == nullptr || hTable[slot] == Deleted_Item::get_Item())
        {
            counter++;
            slot++;
        }

        else if(hTable[slot]->key == key)
            return hTable[slot]->value;

        else
        {
            counter++;
            slot++;
        }

        if(slot == (size))
            slot = 0;

    } while(counter < size);

    return NOT_FOUND; //to be deleted
}


//Insert the Item (key, v) in the table
//If key already exists in the table then change the associated value to v
//Re-hash if the table becomes 50% full
// IMPLEMENT
void HashTable::insert(string key, int v)
{
    bool test = false;
    int slot = h(key, size);
    int counter = 0;
    //Rehash
    if((loadFactor()) >= MAX_LOAD_FACTOR)
        reHash();

    //testa om key redan finns
    do {
        if(hTable[slot] == nullptr || hTable[slot] == Deleted_Item::get_Item())
        {
            slot++;
            counter++;
        }

        else if(hTable[slot]->key == key)
        {
            hTable[slot]->value = v;
            test = true;
        }
        else
        {
            slot++;
            counter++;
        }
        //börja om från början i arrayen
        if(slot == (size))
            slot = 0;


    } while (!test && ( counter < size ));

    //Fall 1: om key redan finns
    //Fall 2: Om slot för key = null
    slot = h(key, size);

    while (!test)
    {
        //om key == null
        if (hTable[slot] == nullptr || hTable[slot] == Deleted_Item::get_Item())
        {
            hTable[slot] = new Item(key, v);
            nItems++;
            break;
        }

        else
        {
            slot++;
        }
    }
}

//Remove Item with key
//If an Item with key belongs to the table then return true,
//otherwise, return false
// IMPLEMENT
bool HashTable::remove(string key)
{
    int slot = h(key, size);
    int counter = 0;

    do {
        if(hTable[slot] == nullptr || hTable[slot] == Deleted_Item::get_Item())
        {
            counter++;
            slot++;
        }
        else if(hTable[slot]->key == key)
        {
            hTable[slot] =  Deleted_Item::get_Item();
            nItems--;
            return true;
        }
        else
        {
            counter++;
            slot++;
        }
        //börja om från början i arrayen
        if(slot == (size-1))
            slot = 0;

    }while(counter < size);

    return false;
}


void HashTable::display(ostream& os)
{
    if (!hTable)
        return;

    os << "-------------------------------\n";

    for (int i = 0; i < size; ++i)
    {
        os << setw(6) << i << ": ";

        if (!hTable[i])
        {
            os << "null" << endl;
        }
        else
        {
            string key = hTable[i]->key;
            os << "key = " << "\"" << key << "\""
               << setw(12) << "value = " << hTable[i]->value
               << "  (" << h(key,size) << ")" << endl;
        }
    }
    os << endl;
}


int HashTable::get_number_total_words() const
{
    int words = 0;
    for (int i = 0; i < size; i++)
    {
        if(hTable[i] == nullptr || hTable[i] == Deleted_Item::get_Item())
            continue;

        else
            words += hTable[i]->value;
    }
     return words;
}

//Display the table to stream os
// IMPLEMENT
ostream& operator<<(ostream& os, const HashTable& T)
{
    cout << endl << "Number of words in the file = " << T.get_number_total_words() << endl;
    cout << "Number unique  words in the file = " << T.get_number_OF_items() << endl << endl;;
    cout << "Frequency table ..." << endl << endl;
    for(int i = 0; i < T.size; i++)
    {
        if(T.hTable[i] == nullptr || T.hTable[i] == Deleted_Item::get_Item())
            continue;

        else
            os << "Key: " << setw(13) << left << T.hTable[i]->key << " Value: " << T.hTable[i]->value << endl;
    }
/*
    cout << endl << "Number of words in the file = " << T.get_number_total_words() << endl;
    cout << "Number unique  words in the file = " << T.get_number_OF_items() << endl << endl;
    cout << "Frequency table ..." << endl << endl; */

    return os;
}


void HashTable::operator[](const string w)
{
    string word = w;
    cleanUp(word);

    bool test = false;
    int slot = h(word, size);
    int counter = 0;

    //Rehash
    if((loadFactor()) >= MAX_LOAD_FACTOR)
        reHash();

    //testa om key redan finns
    do {
        if (hTable[slot] == nullptr || hTable[slot] == Deleted_Item::get_Item())
        {
            slot++;
            counter++;
        }
        else if(hTable[slot]->key == word)
        {
            hTable[slot]->value++;
            test = true;
        }
        else
        {
            slot++;
            counter++;
        }
        //börja om från början i arrayen

        if(slot == (size))
            slot = 0;

    } while (!test && ( counter < size ));

    //Fall 1: om key redan finns
    //Fall 2: Om slot för key = null
    slot = h(word, size);
    while (!test)
    {
        //om key == null
        if (!hTable[slot] || hTable[slot] == Deleted_Item::get_Item())
        {
            hTable[slot] = new Item(word, 1);
            nItems++;
            break;
        }
        else
            slot++;
    }
//    return hTable[slot]->value;
}


void HashTable::cleanUp(string& w)
{
	for(int i = 0; i < w.size(); i++)
    {
        if(ispunct(w[i]) && w[i] != '\'')
        {
            w.erase(i, 1);
            i--;
        }
        w[i] = tolower(w[i]);
    }
}

//Private member functions

//Rehashing function
// IMPLEMENT
void HashTable::reHash()
{
    int newCap = nextPrime(size*2);
    Item** newHashTable = new Item*[newCap];

    for(int i = 0; i < newCap; i++)
        newHashTable[i] = nullptr;

    for(int i = 0; i < size; ++i)
        newHashTable[i] = hTable[i];

    delete hTable;
    size = newCap;
    hTable = newHashTable;

/*
    cout << "Rehashing... " << endl;
    cout << "New Size: " << newCap << endl << endl;*/
}
