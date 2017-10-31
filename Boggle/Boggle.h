#include "Dictionary.h"

struct Results
{
    const char* const* Words;    // pointers to unique found words, each terminated by a non-alpha char
    unsigned           Count;    // number of words found
    unsigned           Score;    // total score
    void*              UserData; // ignored
};

class Boggle
{
    int *visited;
    char str[50];
    int k;
    Dictionary d;
    int score_list[8];
public:
    Boggle();
    void FindWordsUtil(const char*boggle, int i, int j, int width, int height, char ** word_ptr,int* word_count,int* score);
    Results FindWords(const char* board, unsigned width, unsigned height); 
    void PrintOutput(Results r);
    int GetWordsCount(Results r);
    int GetBoggleScore(Results r);
    bool IsBoggleWord(Results r,char * word);
    void FreeWords(Results r);
};



