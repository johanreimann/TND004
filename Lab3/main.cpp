/**********************************************
* File: main.cpp                              *
* Author: Aida Nordman                        *
* Course: TND004, Lab 3                       *
* Date: VT2, 2015                             *
* Description: frequency table                *
* DO NOT MODIFY                               *
***********************************************/

#include "threaded_BST.h"
#include "BiIterator.h"

#include <iostream>
#include <iomanip>
#include <algorithm>
#include <string>
#include <fstream>
#include <vector>
#include <iterator>

#include <map>
#include <sstream>
#include <cctype>


using namespace std;

/*******************************
* Functions                    *
********************************/
void display(MAP &table, int count)
{
    cout << "Number of words in the file = " << count << endl;
    cout << "Number unique words in the file = " << table.get_counter() << endl << endl << endl;
    cout << "Frequency table sorted alphabetically..." << endl << endl;
    cout << "KEY	           COUNTER" << endl;
    cout << "==================================" << endl;

    BiIterator it = table.begin();
    for(it; it != table.end(); it++)
        cout << setw(22) << left << it->first << it->second << endl;
}



/*******************************
* 2. Main function             *
********************************/


int main()
{
    MAP table;

    string name, s;
    int count = 0;

    /******************************************************
    * PHASE 0: Load the words in the text file            *
    *          into a the table                           *
    *******************************************************/

    cout << "File name? ";
    getline(cin, name);

    ifstream textFile(name);

    if (!textFile)
    {
        cerr << "Text file could not be opened!!" << endl;
        exit(1);
    }

    cout << "Loading the words from " << name << " ...\n";

    //Read words and load them in the table
    while (textFile >> s)
    {
        //remove non-alphanumeric chars: rensa bort allt utom siffra och bokstav
        s.erase(remove_if(s.begin(), s.end(), ::ispunct), s.end());

        //convert to lower-case letters
        transform(s.begin(), s.end(), s.begin(), ::tolower);

        if (!s.size()) continue; //skip numbers and punctuation signs

        table[s].second++;  //if s is not in the table then it is inserted
        count++;
    }


    /******************************************************
    * PHASE 1: Display                                    *
    * - number of words in the text                       *
    * - number of unique words (occurring only once)      *
    * - frequency table                                   *
    *******************************************************/

    display(table, count);




    /******************************************************
    * PHASE 3: remove all words with counter 1            *
    *          and display table again                    *
    *******************************************************/

    string wait;
    string words[count];
    getline(cin, wait);
    int counter = 0;

    BiIterator it = table.begin();

    for(it; it !=table.end(); it++)
    {
        if(it->second == 1)
        {
            words[counter] = it->first;
            counter++;
        }
    }

    for (int i = 0; i < counter; i++)
    {
        cout << "ta bort: " << words[i] << endl;
        table.remove(words[i]);
    }


//    for(it; it !=table.end(); it++)
//    while(it != table.end())
//    {
//        cout << it->first << endl;
//        if(it->second == 1)
//        {
//            cout << "1" << endl;
//            cout << it->first << endl;
//            table.remove(it->first);
//            count--;
//            it--;
//        }
//        else
//            it++;
//    }
    count -= counter;

    display(table, count);

    /***********************************************************
    * PHASE 4: request two words to the user w1 and w2         *
    *          then display all words in the interval [w1,w2]  *
    ************************************************************/

    //ADD CODE



    return 0;
}
