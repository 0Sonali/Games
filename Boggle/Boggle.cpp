/* BoggleProj.cpp : Boggle game solver 
General Rules (From Wiki):

1.Board Size : N * N 
2.Time : 3 min // skipping this
3.Each player searches for words that can be constructed from the letters of sequentially adjacent cubes, where "adjacent" cubes are those horizontally, vertically, and diagonally neighboring. 
4.Words must be at least three letters long
5.Words may include singular and plural (or other derived forms) separately
6.May not use the same letter cube more than once per word
7. Score 

Word
length	Points
---------------
3, 4	1

5	    2

6	    3

7	    5

8+	    11

8. Not considering elimination of duplicates 
*/


#include "Boggle.h"
#include <iostream>
#include <fstream>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

using namespace std;
#include <ctype.h>

Boggle :: Boggle()
{
    visited = NULL;
    memset(str,'\0', sizeof(str));
    k=0;
    
    score_list[0] = 0;
    score_list[1] = 0;
    score_list[2] = 0;
    score_list[3] = 1;
    score_list[4] = 1;
    score_list[5] = 2;
    score_list[6] = 3;
    score_list[7] = 5;
}

void Boggle::FreeWords( Results r )
{
    for (int i =0; i < r.Count; i++)
    {
        free((char*)r.Words[i]);
    }
    free((char*)r.Words);
    r.Words = NULL;
}

int Boggle :: GetWordsCount(Results r)
{
    return r.Count;
}

int Boggle :: GetBoggleScore(Results r)
{
    return r.Score;
}

bool Boggle ::IsBoggleWord(Results r,char * word)
{
    for (int i =0; i < r.Count; i++)
    {
        if(strcmp(r.Words[i],word)==0)
        {
            return true;
        }
    }
    return false;
}

void Boggle::PrintOutput(Results r)
{
    ofstream myfile ("output.txt");
    if (myfile.is_open())
    {
        myfile << "Number of words found:"<<r.Count<<"\n";
        myfile << "Score:"<<r.Score<<"\n"<<"\n";
        myfile << "Words:\n"<<"------------------------------------"<<"\n";
        for (int i =0; i < r.Count; i++)
            myfile <<i+1<<"." << r.Words[i] <<"\n";
        myfile.close();
	
	cout << "Check output.txt for output";
    }
    else cout << "Unable to open file";
}

// A recursive function to print all words present on boggle
void Boggle :: FindWordsUtil(const char*boggle, int i, int j, int width, int height, char ** word_ptr,int *word_count,int *score)
{
    // Mark current cell as visited and append current character to str
    static int count = 0;
    int flag = 1;
    *(visited + i*height + j) = 1;
    const char * boggleptr = boggle + i*height + j;
    if ( *boggleptr == 'q' || *boggleptr == 'Q')//'q' represents 'qu' boggle cube
    {
        str[k] = 'q';
        k++;
        str[k] = 'u';
    }
    else
    {
        str[k] = *boggleptr;
    }
    k++;
    count++;
    //cout <<count<<"."<<str<<endl;
    
    flag = d.SearchInDictionary(str);
    if (flag == 1)
    {
        int str_length = strlen(str);
        if (str_length >=3 )
        {
            char* word = (char*)malloc(str_length+1);
            strcpy (word, str);
            word_ptr[*word_count] = word;
            word = NULL;
            (*word_count)++;
            if (str_length>=8)
            {
                *score = (*score) + 11;            }
            else
            {
                *score = (*score) + score_list[str_length];
            }
        }
    }
   
    // Traverse 8 adjacent cells of boggle[i][j]
    for (int row=i-1; row<=i+1 && row<width; row++)
    {
      for (int col=j-1; col<=j+1 && col<height; col++)
      {
        if (row>=0 && col>=0 && *(visited + row*height + col) == 0)
        {
          if (flag != 0)
          {
            FindWordsUtil(boggle, row, col, width, height, word_ptr, word_count, score);
          }
        }
      }
    }
    if (str[k-1] == 'u')
    {
        if (str[k-2] == 'q')
        {
            str[k-1] = '\0';
            k--;
        }
    }
    k--;
    *(visited + i*height + j) = 0;
    str[k] = '\0';
    flag = 0;
}
 
// Prints all words present in dictionary.
Results Boggle :: FindWords(const char* board, unsigned width, unsigned height)
{
    if (board == NULL)
    {
        cout << "Enter valid boggle board";
        exit(-1);
    }
    if (width <3 || height <3)
    {
        "Enter valid boggle board";
        exit(-1);
    }
    if (width != height)
    {
        "Enter valid boggle board";
        exit(-1);
    }
    int k = 0;
    if (!d.IsDictionaryLoaded())
    {
        char * filename = "dictionary.txt";
        d.LoadDictionary(filename);
    }
    Results r;
    int word_count = 0, score =0 ;
    visited = (int *)calloc(width * height, sizeof(int));
    char ** aPtr = (char**)malloc(sizeof(char*) * 500);
    // Consider every character and look for all words starting with this character
    for (int i=0; i<width; i++)
    {
       for (int j=0; j<height; j++)
       {
             FindWordsUtil(board, i, j, width, height, aPtr,&word_count,&score);
       }
    }
    r.Words = aPtr;
    r.Count = word_count;
    r.Score = score;
    aPtr = NULL;
    free(visited);
    d.FreeDictionary();
    return r;
}
 
int main()
{
    //Hardcoding boggle size and boggle board for time being
    const unsigned int width = 3, height = 3;
    //const unsigned int width = 4, height = 4;
    char boggleboard[width][height]={{'d','z','x'},
                                    {'e','a','i'},
                                    {'q','u','t'}};
    /*char boggleboard[width][height]={{'d','e','h','i'},
                                {'i','l','p','s'},
                                {'y','e','u','t'},
                                {'e','o','r','n'}};*/

    /*char boggleboard[width][height]={{'D','Z','X'},
                                    {'E','A','I'},
                                    {'Q','U','T'}};*/

    Boggle b;
    Results results = b.FindWords((char*)boggleboard,width,height);
    b.PrintOutput(results);
    b.FreeWords(results);  

    return 0;
}
