#include <iostream>
#include <fstream>
#include <string>
#include <vector>

using namespace std;

class Node
{
public:
    vector<Node*> children;
    Node* parent;
    uint64_t size;
    string name;
    bool isFile;

    Node(Node* children, size_t childCount, Node* parent, uint64_t size, bool isFile, string name);
    Node(vector<Node*> children, Node* parent, uint64_t size, bool isFile, string name);
    Node(Node* parent, uint64_t size, string name);
    Node(Node* parent, bool isFile, string name);
    Node(bool isFile, string name);
    Node();
    bool contains(string name);
    Node* getChild(string name);
    void newFolder(string name);
    void newFile(string name, uint64_t size);
    uint64_t calcSize();
    bool containsFolder();
    uint64_t getBigFolders(uint64_t thresh);
    uint64_t getSmallFolders(uint64_t thresh);
    static Node* generateTree(vector<string> input);
};

class Solver
{
public:
    void part01(Node* root);
    void part02(Node* root);
};

vector<Node*> AllNodes = vector<Node*>();


/* -----------------------------------------------------------------------
 * Node Implementation
 * -----------------------------------------------------------------------
*/

Node::Node(Node* children, size_t childCount, Node* parent, uint64_t size, bool isFile, string name):
size(size),                     parent(parent), name(name), isFile(isFile)
{
    this->children = vector<Node*>();
    for (int i = 0; i < childCount; i++)
    {
        this->children.push_back(&children[i]);
    }
}
Node::Node(vector<Node*> children, Node* parent, uint64_t size, bool isFile, string name):
size(size), children(children), parent(parent), name(name), isFile(isFile)
{}
Node::Node(Node* parent, uint64_t size, string name):
size(size),                     parent(parent), name(name), isFile(true)
{}
Node::Node(Node* parent, bool isFile, string name):
size(100),                        parent(parent), name(name), isFile(isFile)
{}
Node::Node(bool isFile, string name):
size(0),                                        name(name), isFile(isFile)
{}
Node::Node(){}
bool Node::contains(string name)
{
    for (Node* n : children)
    {
        if (n->name == name)
        {
            return true;
        }
    }
    return false;
}
Node* Node::getChild(string name)
{
    for (Node* n : children)
    {
        if (n->name == name)
        {
            return n;
        }
    }
    return nullptr;
}
void Node::newFolder(string name)
{
    Node* child = new Node(this, false, name);
    children.push_back(child);

    AllNodes.push_back(child);
}
void Node::newFile(string name, uint64_t size)
{
    Node* child = new Node(this, size, name);
    children.push_back(child);

    AllNodes.push_back(child);
}
uint64_t Node::calcSize()
{
    if (isFile)
    {
        return size;
    }
    size = 0;
    for (Node* n : children)
    {
        size += n->calcSize();
    }
    return size;
}
bool Node::containsFolder()
{
    for (long i = 0; i < children.size(); i++)
    {
        if (!(children[i]->isFile))
        {
            return true;
        }
    }
    return false;
}
uint64_t Node::getBigFolders(uint64_t thresh)
{
    if (!containsFolder())
        if (size >= thresh)
            return size;
        else
            return 0;

    uint64_t totalSize = 0;
    for (Node* n : children)
    {
        if (n->isFile)
            continue;
        totalSize += n->getBigFolders(thresh);
    }
    return totalSize;
}
uint64_t Node::getSmallFolders(uint64_t thresh)
{
    if (!containsFolder())
        if (size <= thresh)
            return size;
        else
            return 0;

    uint64_t totalSize = 0;
    for (Node* n : children)
    {
        if (n->isFile)
            continue;
        totalSize += n->getSmallFolders(thresh);
    }
    return totalSize;
}
Node* Node::generateTree(vector<string> input)
{
    Node* tree = new Node(false, "/");
    AllNodes.push_back(tree);

    Node* curNode;
    string s;
    for (int i = 0; i < input.size(); i++)
    {
        s = input[i];

        if (s.size() == 0)
        {
            continue;
        }
        if (s.find("cd") == 2) // cd
        {
            if (s.find('/') != string::npos) // root
            {
                curNode = tree;
            }
            else if (s.find("..") == 5)  // back
            {
                if (curNode->parent != nullptr)
                {
                    curNode = curNode->parent;
                }
            }
            else // go to dir
            {
                s.erase(0, 5);
                if (!curNode->contains(s))
                {
                    curNode->newFolder(s);
                }
                curNode = curNode->getChild(s);
            }
        }
        else if (s.find("ls") == 2) // ls
        {
            i++;
            while (i < input.size())
            {
                s = input[i];
                if (s.length() > 0 && s.at(0) == '$')
                {
                    i--;
                    break;
                }
                
                bool isFolder = s.find("dir") == 0;
                if (isFolder)
                {
                    s.erase(0, 4);
                    curNode->newFolder(s);
                }
                else
                {
                    int split = s.find(' ');
                    uint64_t fileSize = stoi(s.substr(0, split));
                    s.erase(0, split + 1);
                    curNode->newFile(s, fileSize);
                }
                i++;
            }
        }
    }

    tree->calcSize();

    return tree;
}

int main()
{
    cout << "Starting" << endl;

    ifstream file("input.txt");

    vector<string> input;

    if (file.is_open())
    {
        string line;
        while (getline(file, line))
        {
            input.push_back(line);
        }
        Solver s;

        Node* root = Node::generateTree(input);

        s.part01(root);
        s.part02(root);

        while (AllNodes.size() > 0)
        {
            delete AllNodes[0];
            AllNodes.erase(AllNodes.begin());
        }
    }
    else
    {
        cout << "error with file" << endl;
    }
}

void Solver::part01(Node* root)
{
    uint64_t totalSize = 0;
    for (Node* n : AllNodes)
    {
        if (!n->isFile && n->size < 100000)
        {
            totalSize += n->size;
        }
    }

    cout << "total size of small folders: " << totalSize << endl;
}

void Solver::part02(Node* root)
{
    uint64_t maxSpace = 70000000;
    uint64_t neededSpace = 30000000;
    uint64_t occupiedSpace = root->size;
    uint64_t spaceToFree = neededSpace - (maxSpace - occupiedSpace);
    cout << "root size: " << occupiedSpace << endl;
    cout << "needed space: " << spaceToFree << endl;


    uint64_t minSize = UINT64_MAX;
    Node* minNode;
    for (Node* n : AllNodes)
    {
        if (!n->isFile)
        {
            if (n->size > spaceToFree && n->size < minSize)
            {
                minNode = n;
                minSize = n->size;
            }
        }
    }
    cout << "min space foler: " << minSize << endl;
}
