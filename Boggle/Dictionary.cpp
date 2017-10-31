#include <iostream>
#include "Dictionary.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <fstream>

using namespace std;

void Dictionary :: FreeDictionaryNodes(TrieNode * rootRef)
{
    for (int i=0; i < 26; ++i)
    {
        if (rootRef->children[i])
        {
             FreeDictionaryNodes(rootRef->children[i]);
        }
    }

    free (rootRef);
}

void Dictionary :: FreeDictionary()
{
    FreeDictionaryNodes(root);
}
 
// Returns new trie node (initialized to NULLs)
struct TrieNode * Dictionary :: GetNode()
{
    TrieNode *pNode = (TrieNode *)malloc(sizeof(TrieNode));
 
    if (pNode)
    { 
        pNode->isLeaf = false;
 
        for (int i = 0; i < alphabets; i++)
            pNode->children[i] = NULL;
    }
 
    return pNode;
}
 
// If not present, inserts key into trie
// If the key is prefix of trie node, just marks leaf node
void Dictionary :: AddToDictionary(const char *key)
{
    int length = strlen(key);
    int index = 0;
 
    TrieNode *pCrawl = root;
 
    for (int level = 0; level < length; level++)
    {
        //index = int(key[level])-int('a'); 
        index = int(tolower(key[level])) - int('a');
        if (!pCrawl->children[index])
             pCrawl->children[index] = GetNode();
 
        pCrawl = pCrawl->children[index];
    }
 
    pCrawl->isLeaf = true; // mark last node as leaf
}
 
// Returns 1 if key is present in trie and node is a leaf node
//         2 if key is present in trie and node is not a leaf node
//         0 if key is not present in the trie
int Dictionary :: SearchInDictionary(const char *key)
{
    int length = strlen(key);
    int index = 0;
    TrieNode *pCrawl = root;
 
    for (int level = 0; level < length; level++)
    {
        //index = int(key[level])-int('a'); 
        index = int(tolower(key[level])) - int('a');

 
        if (!pCrawl->children[index])
            return 0;
 
        pCrawl = pCrawl->children[index];
    }
 
    if (pCrawl != NULL && pCrawl->isLeaf)
    {
        return 1;
    }
    else if (pCrawl != NULL)
    {
        return 2;
    }
    return 0;   
}

bool Dictionary :: IsDictionaryLoaded()
{
    if (root == NULL)
        return false;
    else 
        return true;
}

void Dictionary :: SetRoot()
{
    root = GetNode();
}

//Loads dictionary from given path
void Dictionary :: LoadDictionary(const char* path)
{
    char * word = (char*)malloc(256);
    //ifstream in(path);
    //ifstream ifs (path, std::ifstream::in);
    ifstream ifs;

    ifs.open (path, ifstream::in);

    if(!ifs) 
    {
        cout << "Error:Cannot open dictionary.";
        exit(-1);
    }

    SetRoot();
    while(ifs) 
    {
        ifs.getline(word, 255);
        if(ifs) 
           AddToDictionary(word);
    }
    ifs.close();
   /* string line;
    ifstream myfile (path);
    if (myfile.is_open())
    {
        while ( getline (myfile,line) )
        {
            cout << line << '\n';
        }
        myfile.close();
    }

    else cout << "Unable to open file";*/ 
    free(word);
}

Dictionary::Dictionary()
{
    root = NULL;
}
