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
    for(int i = 0; i < size; i++)
    {
        if(hTable[i]->key == key)
            return hTable[i]->value;
    }
    return NOT_FOUND; //to be deleted
}


//Insert the Item (key, v) in the table
//If key already exists in the table then change the associated value to v
//Re-hash if the table becomes 50% full
// IMPLEMENT
void HashTable::insert(string key, int v)
{
    double load_factor;
    bool found = false;
    cout << "HEJ!" << endl;
    //om key redan finns
    for(int i = 0; i < size; i++)
    {
         cout << "1" << endl;
         cout << "Key: " << key << endl;
        if(hTable[i]->key == key)
        {
            cout << "2" << endl;
            hTable[i]->value = v;
            found = true;
            cout << "HITTA DEN! WOOP!" << endl;
        }
    }
    cout << "PÅ DIG!" << endl;

    load_factor = nItems/size;

    if(!found)
    {
        cout << "hitta inte... :(" << endl;
        //re-hash
        if((load_factor) >= 0.5)
        {
            //make a new hash table ???????????????
        }
        //new HashTable(size+1);

        //Lägg bara in värdet!!!!
        else
        {
            for (int i = 0; i < size; i++)
            {
                if (hTable[i]->key == "" && hTable[i]->value == -1)
                {
                    cout << "Det här ska inte visas" << endl;
                    Item* temp = hTable[i];
                    delete temp;
                    hTable[i] = new Item(key, v);
                    /*
                    hTable[i]->key = key;
                    hTable[i]->value = v;
                    break;*/
                }
                else if(!hTable[i])
                {
                    cout << "Hit ska jag komma!" << endl;
                    hTable[i] = new Item(key, v);
                    break;
                }
            }
        }
    }
}


//Remove Item with key
//If an Item with key belongs to the table then return true,
//otherwise, return false
// IMPLEMENT
bool HashTable::remove(string key)
{
    return true; //to be deleted
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
    return os;
}

//Private member functions

//Rehashing function
// IMPLEMENT
void HashTable::reHash()
{

}
