#include <assert.h>
#include <iomanip>

#include "hashTable.h"

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
}


//destructor
// IMPLEMENT
HashTable::~HashTable()
{
    Item* temp;

    for(int i = 0; i < size; i++)
    {
        temp = hTable[i];
        delete temp;
    }
    delete[] hTable;
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
        if(!hTable[slot])
            break;

        if(hTable[slot]->key == key)
            return hTable[slot]->value;

        counter++;
        slot++;

        if(slot == (size-1))
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
    int slot = h(key, size)+1;
    int counter = 0;
    //Rehash
    cout << endl << "loadFactor: " << loadFactor() << endl;
    if((loadFactor()) >= MAX_LOAD_FACTOR)
        reHash();

    //testa om key redan finns
    do {
        //key == key -> KLÄRT
        if (!hTable[slot])
            break;

        else if(hTable[slot]->key == key)
        {
            hTable[slot]->value = v;
            test = true;
        }
        slot++;
        counter++;

        //börja om från början i arrayen
        if(slot == (size))
            slot = 1;

    } while (!test && ( counter < size ));

    //Fall 1: om key redan finns
    //Fall 2: Om slot för key = null
    slot = h(key, size)+1;
    while (!test)
    {
        //om key == null
        if (!hTable[slot])
        {
            hTable[slot] = new Item(key, v);
            nItems++;
            break;
        }
        //om deleted key = ""
        else if(hTable[slot]->key == "" && hTable[slot]->value == -1 )
        {
            hTable[slot] = new Item(key, v);
            nItems++;
            break;
            //måste man ta bort Item("", -1) ?
        }
        else
            slot++;
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
        if (hTable[slot]->key == key) {
            hTable[slot] =  Deleted_Item::get_Item();
            return true;
        }
        counter++;
        slot++;

        //börja om från början i arrayen
        if(slot == (size-1))
            slot = 0;

    }while(counter < size);

    return false; //to be deleted
}


void HashTable::display(ostream& os)
{
    if (!hTable) return;

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


//Display the table to stream os
// IMPLEMENT
ostream& operator<<(ostream& os, const HashTable& T)
{
    for(int i = 0; i < T.size; i++)
    {
        if(!T.hTable[i])
            continue;

        else if(T.hTable[i]->key == "" && T.hTable[i]->value == -1)
            continue;

        else
            os << "Key: " << T.hTable[i]->key << " Value: " << T.hTable[i]->value << endl;
    }
    return os;
}

//Private member functions

//Rehashing function
// IMPLEMENT
void HashTable::reHash()
{
    cout << "REHASH" << endl;
    int newCap = nextPrime((size*2));
    Item** newHashTable = new Item*[newCap];

    for(int i = 0; i < size; ++i)
    {
        cout << "KUL MED REHASH" << endl;
        newHashTable[i] = hTable[i];
    }

    delete[] hTable;

    hTable = newHashTable;
}
