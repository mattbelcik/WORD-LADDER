#include <iostream>
#include <fstream>
#include <string>
#include "linearlist.h"
#include "queue.h"

// create an array of linked list
// make struct that stores to next word

// in algor its a queue of structs

using namespace std;

struct Rung
{
    string word;
    int ptr = -1;        // set during gen ladder
    LinearList<int> adj; // store indexes
};

// Rung wordArray[5757];

// word to int where rung is
int search(string w, Rung list[])
{
    for (int i = 0; i < 5757; i++)
    {
        if (list[i].word == w)
        {
            return i;
        }
    }
    return -1;
}

int hamming(string w1, string w2)
{
    int count = 0;
    for (int i = 0; i < 5; i++)
    {
        if (w1[i] != w2[i])
        {
            count++;
        }
        // return count;
    }
    return count;
}

// 2 for loops one if statements and use structs

void CloseWords(Rung wordArray[])
{

    for (int i = 0; i < 5756; i++)
    {
        for (int j = i + 1; j < 5757; j++)
        {
            if (hamming(wordArray[i].word, wordArray[j].word) == 1)
            {

                wordArray[i].adj.insert(wordArray[i].adj.size(), j);
                wordArray[j].adj.insert(wordArray[j].adj.size(), i);
            }
        }
    }
}
void genLadder(string w1, string w2, Rung wordArray[])
{
    Queue<int> Q;
    int w2Index = search(w2, wordArray); // sesrch is an interger. may need to flip w2 and wordArray
    int w1Index = search(w1, wordArray);
    if (w2Index == -1 || w1Index == -1)
    {
        cout << "word is not on list" << endl;
        return;
    }

    Q.enqueue(w2Index);

    while (!Q.isEmpty())
    {
        int w = Q.dequeue(); // index of rung w
        // wordArray[w].adj;
        for (int v = 0; v < wordArray[w].adj.size(); v++)
        {
            if (wordArray[wordArray[w].adj[v]].ptr == -1 && wordArray[w].adj[v] != w2Index)
            {
                wordArray[wordArray[w].adj[v]].ptr = w;
                Q.enqueue(wordArray[w].adj[v]);
            }
        }
    }
    if (wordArray[w1Index].ptr != -1)
    {

        cout << wordArray[w1Index].word << endl;
        int w = wordArray[w1Index].ptr;
        while (w != -1)
        {
            cout << wordArray[w].word << endl;
            w = wordArray[w].ptr;
        }
    }
    else
    {
        cout << "there is no ladder" << endl;
    }
}

int main()
{
    Rung words[5757];
    ifstream inFile;
    inFile.open("sgb-words.txt");

    if (inFile)
    {

        for (int i = 0; !inFile.eof(); i++)
        {
            inFile >> words[i].word;
        }
        for (int i = 0; i < 5757; i++)
        {
            cout << words[i].word << endl;
        }
        CloseWords(words);

        string wo1;
        string wo2;

        cout << "pick two items from list" << endl;
        cin >> wo1 >> wo2;

        genLadder(wo1, wo2, words);
    }
    else
    {

        cout << "failed to open" << endl;
    }
    inFile.close();

    return 0;
}
