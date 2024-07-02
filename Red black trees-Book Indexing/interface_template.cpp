#include <bits/stdc++.h>
using namespace std;
vector<pair<string, string>> words_chapters;
vector<string> common_words;
class HybridNode
{
public:
    string key;              // Word
    string element;          // Chapter
    HybridNode *parent;      // Parent node
    HybridNode *left_child;  // Left child node
    HybridNode *right_child; // Right child node
    HybridNode *next_node;   // Next node in the linked list
    string color = "black";  // Color of the node

    HybridNode(string key_val, string element_val) : key(key_val), element(element_val), parent(nullptr), left_child(nullptr), right_child(nullptr), next_node(nullptr) {}
};

class IndexEntry
{
private:
    string word;
    vector<pair<string, int>> chapter_word_counts; // List of (chapter, word_count) tuples

public:
    IndexEntry(string word_val) : word(word_val) {}

    void setWord(string word_val)
    { // Set the word
        word = word_val;
    }

    string getWord()
    { // Get the word
        return word;
    }

    void setChapterWordCounts(vector<pair<string, int>> chapter_word_counts_val)
    { // Set the list of (chapter, word_count) tuples
        chapter_word_counts = chapter_word_counts_val;
    }

    vector<pair<string, int>> getChapterWordCounts()
    { // Get the list of (chapter, word_count) tuples
        return chapter_word_counts;
    }
};
vector<IndexEntry> index;
vector<string> chapter12;
class RedBlackTree
{
private:
    HybridNode *root; // Root node

public:
    RedBlackTree() : root(nullptr) {}
    int getTotalNodes(HybridNode *node)
    {
        if (node == nullptr)
        {
            return 0;
        }
        return 1 + getTotalNodes(node->left_child) + getTotalNodes(node->right_child);
    }
    HybridNode *getRoot()
    {
        return root; // Return the root node
    }

    void setRoot(HybridNode *node)
    {
        root = node; // Set the root node
    }
    int stringcompare(string s1, string s2)
    {
        char *c1 = new char[s1.length() + 1];
        strcpy(c1, s1.c_str());

        char *c2 = new char[s2.length() + 1];
        strcpy(c2, s2.c_str());
        int result = strcmp(c1, c2);
        return result;
    }
    HybridNode *insert(string key, string element)
    {
        // Implement Red-Black Tree insertion

        HybridNode *temp = getRoot();
        HybridNode *parent = nullptr;
        HybridNode *new_node = new HybridNode(key, element);
        HybridNode *check;
        new_node->color = "red";
        string c_word_name;
        int count;
        if (root == nullptr)
        {
            IndexEntry a (key);
            vector<pair<string, int>> t;
            for (int i = 0; i < chapter12.size(); i++)
            {
                pair<string, int> p(chapter12[i].substr(0,8), 0);
                if (element == chapter12[i].substr(0,8))
                {
                    p.second++;
                }
                t.push_back(p);
            }
            a.setChapterWordCounts(t);
            index.push_back(a);
            root = new_node;
            root->color = "black";
            return root;
        }
        else
        {
            while (temp != nullptr)
            {
                parent = temp;
                if (stringcompare(key, temp->key) < 0)
                {
                    temp = temp->left_child;
                }
                else if (stringcompare(key, temp->key) > 0)
                {
                    temp = temp->right_child;
                }
                else
                {

                    for (int k=0;k<index.size();k++)
                    {
                        if (index[k].getWord() == key)
                        {
                            for (int z=0;z<index[k].getChapterWordCounts().size();z++)
                            {
                                if (index[k].getChapterWordCounts()[z].first == element)
                                {vector<pair<string,int>> v=index[k].getChapterWordCounts();
                                    v[z].second++; 
                                    index[k].setChapterWordCounts(v);
                                }
                            }
                        }
                    }
                    return nullptr;
                }
            }
            new_node->parent = parent;
            if (stringcompare(new_node->key, parent->key) < 0)
            {
              IndexEntry a(key);
                vector<pair<string, int>> t;
                for (int i = 0; i < chapter12.size(); i++)
                {
                    pair<string, int> p(chapter12[i].substr(0,8), 0);
                    if (element == chapter12[i].substr(0,8))
                    {
                        p.second++;
                    }
                    t.push_back(p);
                }
                a.setChapterWordCounts(t);
                index.push_back(a);
                parent->left_child = new_node;
            }
            else
            {
               IndexEntry a(key);
                vector<pair<string, int>> t;
                for (int i = 0; i < chapter12.size(); i++)
                {
                    pair<string, int> p(chapter12[i].substr(0,8), 0);
                    if (element == chapter12[i].substr(0,8))
                    {
                        p.second++;
                    }
               
                    t.push_back(p);
                }
             
                a.setChapterWordCounts(t);
                index.push_back(a);
                parent->right_child = new_node;
            }
        }
        while (new_node->parent != nullptr && new_node->parent->color == "red")
        {
            HybridNode *grandparent = new_node->parent->parent;
            HybridNode *sibling;
            if (grandparent->right_child == new_node->parent)
            {
                sibling = grandparent->left_child;
                if (sibling != nullptr && sibling->color == "red")
                {
                    sibling->color = "black";
                    new_node->parent->color = "black";
                    grandparent->color = "red";
                    new_node = grandparent;
                }
                else
                {
                    if (new_node->parent->right_child == new_node)
                    {
                        grandparent->color = "red";
                        new_node->parent->color = "black";
                        rotateleft(grandparent);
                        return root;
                    }
                    else
                    {
                        new_node->color = "black";
                        grandparent->color = "red";
                        rotateright(new_node->parent);
                        rotateleft(grandparent);
                        return root;
                    }
                }
            }
            else
            {
                sibling = grandparent->right_child;
                if (sibling != nullptr && sibling->color == "red")
                {
                    new_node->parent->color = "black";
                    sibling->color = "black";
                    grandparent->color = "red";
                    new_node = grandparent;
                }
                else
                {
                    if (new_node->parent->left_child == new_node)
                    {
                        new_node->parent->color = "black";
                        grandparent->color = "red";
                        rotateright(grandparent);
                        return root;
                    }
                    else
                    {
                        grandparent->color = "red";
                        new_node->color = "black";
                        rotateleft(new_node->parent);
                        rotateright(grandparent);
                        return root;
                    }
                }
            }
        }
        if (new_node->parent == nullptr)
        {
            root = new_node;
            root->color = "black";
        }

        return root;
    }
    void rotateright(HybridNode *node)
    {
        HybridNode *x, *y, *T2;
        y = node;
        x = y->left_child;
        T2 = x->right_child;
        x->right_child = y;
        y->left_child = T2;
        if (y->parent == nullptr)
        {
            x->parent = nullptr;
            y->parent = x;
        }
        else
        {
            if (y->parent->left_child == y)
            {
                y->parent->left_child = x;
                x->parent = y->parent;
                y->parent = x;
            }
            else
            {
                y->parent->right_child = x;
                x->parent = y->parent;
                y->parent = x;
            }
        }
        if (T2 != nullptr)
        {
            T2->parent = y;
        }
    }
    void rotateleft(HybridNode *node)
    {
        HybridNode *x, *y, *T2;
        x = node;
        y = x->right_child;
        T2 = y->left_child;
        y->left_child = x;
        x->right_child = T2;
        if (x->parent == nullptr)
        {
            y->parent = nullptr;
            x->parent = y;
        }
        else
        {
            if (x->parent->left_child == x)
            {
                x->parent->left_child = y;
                y->parent = x->parent;
                x->parent = y;
            }
            else
            {
                x->parent->right_child = y;
                y->parent = x->parent;
                x->parent = y;
            }
        }
        if (T2 != nullptr)
        {
            T2->parent = x;
        }
    }
    HybridNode *successor(HybridNode *node)
    {
        HybridNode *temp = root;
        if (node->right_child != nullptr)
        {
            node = node->right_child;
            while (node != nullptr && node->left_child != nullptr)
            {
                node = node->left_child;
            }
            return node;
        }
        else
        {
            HybridNode *new_node = node->parent;
            while (new_node != nullptr && node == new_node->right_child)
            {
                node = new_node;
                new_node = new_node->parent;
            }
            return new_node;
        }
        return nullptr;
    }
    HybridNode *swap_node(HybridNode *u, HybridNode *v)
    {
        if (u->parent == nullptr)
        {
            root = v;
        }
        else if (u->parent->left_child == u)
        {
            u->parent->left_child = v;
        }
        else
        {
            u->parent->right_child = v;
        }
        v->parent = u->parent;
    }
    HybridNode *BSTdel(HybridNode *temp)
    {
        if (temp->left_child == nullptr && temp->right_child == nullptr)
        {
            return nullptr;
        }
        if (temp->left_child == nullptr)
        {
            return temp->right_child;
        }
        else if (temp->right_child == nullptr)
        {
            return temp->left_child;
        }
        else
        {
            return successor(temp);
        }
    }
    void doubleblack(HybridNode *u)
    {
        
        HybridNode *sibling;
        while (u->parent != nullptr && u->color == "black")
        {
            if (u->parent->left_child == u)
            {
                sibling = u->parent->right_child;
              
                if (sibling != nullptr && sibling->color == "red")
                {
                    sibling->color = "black";
                    u->parent->color = "red";
                    rotateleft(u->parent);
                    sibling = u->parent->right_child;
                }
                else
                {
                    if ((sibling->left_child != nullptr && sibling->right_child != nullptr && sibling->left_child->color == "black" && sibling->right_child->color == "black") || (sibling->left_child == nullptr && sibling->right_child != nullptr && sibling->right_child->color == "black") || (sibling->left_child != nullptr && sibling->left_child->color == "black" && sibling->right_child == nullptr) || (sibling->left_child == nullptr && sibling->right_child == nullptr))
                    {
                        sibling->color = "red";
                        if (sibling->parent->color == "red")
                        {
                            sibling->parent->color = "black";
                            return;
                        }
                        u = u->parent;
                    }
                    else
                    {
                        if (sibling->left_child != nullptr && sibling->left_child->color == "red")
                        {
                            sibling->left_child->color = "black";
                            sibling->color = "red";
                            rotateright(sibling);
                            sibling = u->parent->right_child;
                        }
                        sibling->color = u->parent->color;
                        u->parent->color = "black";
                        sibling->right_child->color = "black";
                        rotateleft(u->parent);
                        u = root;
                    }
                }
            }
            else
            {
                sibling = u->parent->left_child;
                if (sibling != nullptr && sibling->color == "red")
                {
                    sibling->color = "black";
                    u->parent->color = "red";
                    rotateright(u->parent);
                    sibling = u->parent->left_child;
                }
                else
                {
                    if ((sibling->left_child != nullptr && sibling->right_child != nullptr && sibling->left_child->color == "black" && sibling->right_child->color == "black") || (sibling->left_child == nullptr && sibling->right_child != nullptr && sibling->right_child->color == "black") || (sibling->left_child != nullptr && sibling->left_child->color == "black" && sibling->right_child == nullptr) || (sibling->left_child == nullptr && sibling->right_child == nullptr))
                    {
                        sibling->color = "red";
                        if (sibling->parent->color == "red")
                        {
                            sibling->parent->color = "black";
                            return;
                        }
                        u = u->parent;
                    }
                    else
                    {
                        if (sibling->right_child != nullptr && sibling->right_child->color == "red")
                        {
                            sibling->color = "red";
                            sibling->right_child->color = "black";
                            rotateleft(sibling);
                            sibling = u->parent->left_child;
                        }
                        sibling->color = u->parent->color;
                        u->parent->color = "black";
                        sibling->left_child->color = "black";
                        rotateright(u->parent);
                        u = root;
                    }
                }
            }
        }
        if (u->parent == nullptr)
        {
            root = u;
            root->color = "black";
        }
    }
    void bstdelete(HybridNode *temp)
    {
      
        HybridNode *u = BSTdel(temp);
      
        string vclr = temp->color;
      
        string vkey = temp->key;
        string uclr;
        if (u != nullptr)
        {
           
            uclr = u->color;
        }
        if (u == nullptr)
        {
            if (temp == root)
            {
              
                root == nullptr;
            }
            else
            {
                if (vclr == "black")
                {
                    doubleblack(temp);
                }
                if (temp->parent->left_child == temp)
                {
                    temp->parent->left_child = nullptr;
                }
                else
                {
                    temp->parent->right_child = nullptr;
                }
                delete temp;
                return;
            }
        }
        else
        {
            if (temp->left_child == nullptr || temp->right_child == nullptr)
            {
                if (temp == root)
                {
                    swap_node(temp, u);
                    delete temp;
                }
                else
                {
                    if (temp->parent->left_child == temp)
                    {
                        temp->parent->left_child = u;
                        u->parent = temp->parent;
                    }
                    else
                    {
                        temp->parent->right_child = u;
                        u->parent = temp->parent;
                    }
                    delete temp;
                    if (vclr == "black" && uclr == "black")
                    {
                        doubleblack(u);
                    }
                    else
                    {
                        u->color = "black";
                    }
                }
                return;
            }
            else
            {
                string value;
                value = u->key;
                u->key = temp->key;
                temp->key = value;
                bstdelete(u);
            }
        }
    }
    bool deleteNode(string key)
    {
        // Implement Red-Black Tree deletion
        HybridNode *temp = search(key);
        bstdelete(temp);
    }

    vector<HybridNode *> traverseUp(HybridNode *node)
    {
        // Traverse up the tree from the given node to the root
        // Return the vector of nodes in the path
    }

    vector<HybridNode *> traverseDown(HybridNode *node, string bit_sequence)
    {
        // Traverse down the tree based on the bit sequence
        // Return the vector of nodes in the path
    }

    vector<HybridNode *> preOrderTraversal(HybridNode *node, int depth)
    {
        // Perform pre-order traversal staying within specified depth
    }
    HybridNode *search(string key)
    {
     
        // Implement Red-Black Tree search
        HybridNode *temp = root;
        while (temp != NULL && temp->key != key)
        {
            if (key < temp->key)
            {
                temp = temp->left_child;
            }
            else
            {
                temp = temp->right_child;
            }
        }
        
        return temp;
    }

    int blackheight(HybridNode *node)
    {
        // Implement blackheight
        int count = 0;
        HybridNode *temp = node;
        while (temp != nullptr)
        {
            if (temp->color == "black")
            {
                count++;
            }
            temp = temp->right_child;
        }
        return count;
    }
    void inOrderTraversal(HybridNode *node)
    {
        if (node == nullptr)
        {
            return;
        }
        inOrderTraversal(node->left_child);
        cout << node->key << " " << node->color << endl;
        inOrderTraversal(node->right_child);
    }
    bool isBlackHeightBalanced(HybridNode *root)
    {
        int blackHeight = -1; // Initialize with an invalid value
        return checkBlackHeight(root, blackHeight);
    }

    bool checkBlackHeight(HybridNode *node, int &blackHeight)
    {
        if (node == nullptr)
        {
            if (blackHeight == -1)
            {
                blackHeight = 0; // Set initial black height
                return true;
            }
            return blackHeight == 0; // All paths should have the same black height
        }

        int leftBlackHeight = 0, rightBlackHeight = 0;

        bool leftBalanced = checkBlackHeight(node->left_child, leftBlackHeight);
        bool rightBalanced = checkBlackHeight(node->right_child, rightBlackHeight);

        // Check if left and right subtrees are balanced and have the same black height
        if (leftBalanced && rightBalanced && leftBlackHeight == rightBlackHeight)
        {
            // Update the black height for the current node
            blackHeight = leftBlackHeight + (node->color == "black" ? 1 : 0);
            return true;
        }
    }
};

class Lexicon
{
private:
    RedBlackTree red_black_tree; // Red-Black Tree

public:
    Lexicon() {}

    void setRedBlackTree(RedBlackTree tree)
    { // Set the Red-Black Tree
        red_black_tree = tree;
    }

    RedBlackTree getRedBlackTree()
    { // Get the Red-Black Tree
        return red_black_tree;
    }

    void readChapters(vector<string> chapter_names)
    {
        chapter12 = chapter_names;
        // Process words from a chapter and update the Red-Black Tree
        // chapter_names is a vector of chapter names
        string ch_name;
        string txt_name;
        string line;
        vector<string> chapters;
        for (int i = 0; i < chapter_names.size(); i++)
        {
            chapters.clear();
            ch_name.clear();
            ifstream file(chapter_names[i]);
            txt_name = chapter_names[i];
            int j = 0;
            while (txt_name[j] != '.')
            {
                ch_name += txt_name[j];
                j++;
            }
            if (file.is_open())
            {
                stringstream buffer;
                buffer << file.rdbuf();
                file.close();
                string element = buffer.str();
                istringstream stream(element);
                while (getline(stream, line, '\n'))
                {
                    chapters.push_back(line);
                }
            }
            for (int k = 0; k < chapters.size(); k++)
            {
                string word;
                istringstream stream(chapters[k]);
                while (getline(stream, word, ' '))
                {

                    for (int m = 0; m < word.size(); m++)
                    {
                        if (word[m] >= 65 && word[m] <= 90)
                        {
                            word[m] = word[m] + 32;
                        }
                    }
                    words_chapters.emplace_back(word, ch_name);
                    red_black_tree.insert(word, ch_name);
                }
            }
        }
        for (auto i : index)
        {
           
            int h = 0;
            for (auto l : i.getChapterWordCounts())
            {
                
                if (l.second == 0)
                {
                 
                    h = 1;
                }
            }
            if (h == 0)
            {
               
                red_black_tree.deleteNode(i.getWord());
                  
            }
        }
    }
    vector<IndexEntry> buildIndex()
    {
        
        return index;
    }
};
// int main()
// {
//     vector<string> chapter_names;
//     string a = "Chapter1.txt";
//     chapter_names.push_back(a);
//     string b = "Chapter2.txt";
//     chapter_names.push_back(b);
//     string c = "Chapter3.txt";
//     chapter_names.push_back(c);
//     Lexicon lex;
//     lex.readChapters(chapter_names);
//     cout << common_words.size() << endl;
//     for (int i = 0; i < common_words.size(); i++)
//     {
//         cout << common_words[i] << endl;
//     }
//     cout << lex.getRedBlackTree().deleteNode("his") << endl;
   
//     cout << lex.getRedBlackTree().getRoot()->key << " " << lex.getRedBlackTree().getRoot()->color << endl;
//     // RedBlackTree rd;
//     // rd.inOrderTraversal(lex.getRedBlackTree().getRoot());
// }
