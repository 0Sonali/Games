const int alphabets = 26;

struct TrieNode
{
    TrieNode *children[alphabets];
    bool isLeaf;
};

class Dictionary
{
    TrieNode * root;

public: 
    Dictionary();
    struct TrieNode * GetNode();
    void SetRoot();
    void AddToDictionary(const char *word);
    int SearchInDictionary(const char *word);
    void LoadDictionary(const char* filepath);
    bool IsDictionaryLoaded();
    void FreeDictionary();
    void FreeDictionaryNodes(TrieNode * rootRef);
};



