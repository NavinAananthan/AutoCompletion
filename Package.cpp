#include <iostream>
#include <vector>
using namespace std;


//creating a node using struct
struct Node
{
    char data;
    int char_end;
    struct Node* left;
    struct Node* eq;
    struct Node* right;
};


// Function to creating a new node
Node* createNode(char newData)
{
    struct Node* newNode = new Node();
    newNode->data = newData;
    newNode->char_end = 0;
    newNode->left = NULL;
    newNode->eq = NULL;
    newNode->right = NULL;

    return newNode;
}


//function to insert a new word into the tree
void insert(Node** root,string word,int pos = 0)
{

    //creating a node root
    if (!(*root))
    {
        *root = createNode(word[pos]);
    }

    //creating a node for left pointer when the character is lesser than the root
    if ((*root)->data > word[pos])
    {
        insert(&((*root)->left), word, pos);
    }

    //creating a node for right pointer when the character is greater than the root
    else if ((*root)->data < word[pos])
    {
        insert(&((*root)->right), word, pos);
    }

    //creating a node when character is equal to the root
    else
    {
        //if it is the end of the string we update with position of the string whether it is end or not
        if (pos + 1 == word.size())
        {
            (*root)->char_end = 1;
        }

        else
        {
            //if it is not the last character then we insert the present character into the tree
            insert(&((*root)->eq), word, pos + 1);
        }
    }
}


// Function to traverse the ternary search tree
void traverse(Node* root, vector<string>& ret, char* buff, int depth = 0)
{
    if (!root)
    {
        return;
    }

    //traversing the left subtree
    traverse(root->left, ret,buff, depth);
    buff[depth] = root->data;


    //if it is the end of the string store it in the final answer
    if (root->char_end)
    {
        buff[depth + 1] = '\0';
        ret.push_back(string(buff));
    }

    //traversing the equal pointer subtree
    traverse(root->eq, ret, buff, depth + 1);

    //traversing the right subtree
    traverse(root->right, ret, buff, depth);
}


// Function to find all the words
vector<string> find_all(Node* root, string pattern)
{
    //it stores the words of auto suggestion
    char buffer[2000];

    vector<string> ret;

    traverse(root, ret, buffer);

    if (root->char_end == 1)
    {
        ret.push_back(pattern);
    }
    return ret;
}

//Function for the auto completion and complete the words with the given prefixes
vector<string> autocomplete(Node* root, string pattern)
{
    vector<string> words;
    int pos = 0;

    //if patterns is empty it returns an empty list
    if (pattern.empty())
    {
        return words;
    }

    //iterating over the tree and find the pattern using the given prefix
    while (root && pos < pattern.length())
    {

        if (root->data > pattern[pos])
        {
            root = root->left;
        }

        else if (root->data < pattern[pos])
        {
            root = root->right;
        }

        else if (root->data == pattern[pos])
        {
            root = root->eq;
            pos++;
        }

        else
        {
            return words;
        }
    }

    //it searches for all the words in the current node
    words = find_all(root, pattern);

    return words;
}


//Function to print the autosuggested words
void print(vector<string> sugg, string pat)
{
    for (int i = 0; i < sugg.size(); i++)
    {
        cout << pat << sugg[i].c_str()<<endl;
    }
}

// Driver Code
int main()
{
    //storing the words for implementing int the tree
    vector<string> word= {"what","when","where","wallstreet","which","wallmart"};
    vector<string> numbers= {"1234567890","1234098765","5467890123"};

    Node* tree = NULL;

    //inserting into the strings into the tree
    for (string str : numbers)
    {
        insert(&tree, str);
    }


    string pat;

    //getting input from the user for a pattern
    cout<<"Enter the letters you want according to your match: ";
    cin>>pat;
    cout<<endl;

    vector<string> sugg = autocomplete(tree, pat);

    if (sugg.size() == 0)
    {
        cout << "No words according to your match";
    }

    else
    {
        print(sugg, pat);
    }
    return 0;
}
