#include <iostream>
#include <fstream>
#include <string>
#include <vector>

using namespace std;

class Solver
{
public:
    void part01(vector<string>);
    void part02(vector<string>);
};

class Node
{
public:
    vector<Node*> children;
    Node* parent;
    unsigned int size;
    string name;
    bool isFile;

    Node(Node* children, size_t childCount, Node* parent, unsigned int size, bool isFile, string name):
    size(size), parent(parent), name(name), isFile(isFile)
    {
        this->children = vector<Node*>();
        for (int i = 0; i < childCount; i++)
        {
            this->children.push_back(&children[i]);
        }
    }

    Node(vector<Node*> children, Node* parent, unsigned int size, bool isFile, string name):
    size(size), children(children), parent(parent), name(name), isFile(isFile)
    {}

    Node(Node* parent, unsigned int size, string name):
    parent(parent), name(name), isFile(true), size(size)
    {}

    Node(Node* parent, bool isFile, string name):
    parent(parent), name(name), isFile(isFile)
    {}

    Node(bool isFile, string name):
    name(name), isFile(isFile)
    {}

    Node(){}

    bool contains(string name)
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

    Node* getChild(string name)
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

    void newFolder(string name)
    {
        Node* child = new Node(this, false, name);
        children.push_back(child);
    }

    void newFile(string name, unsigned int size)
    {
        Node child(this, true, name);
        children.push_back(&child);
    }

    int calcSize()
    {
        if (isFile)
        {
            cout << size << endl;
            return size;
        }
        size = 0;
        for (Node* n : children)
        {
            size += n->calcSize();
        }
        cout << size << endl;
        return size;
    }

    bool containsFolder()
    {
        for (int i = 0; i < children.size(); i++)
        {
            if (!(children[i]->isFile))
            {
                return true;
            }
        }
        return false;
    }

    int getBigFolders(int thresh)
    {
        if (!containsFolder())
            return size;

        int totalSize = 0;
        for (Node* n : children)
        {
            if (n->isFile)
                continue;
            totalSize += n->getBigFolders(thresh);
        }
        return totalSize;
    }
};

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
        s.part01(input);
        s.part02(input);
    }
    else
    {
        cout << "error with file" << endl;
    }
}

void Solver::part01(vector<string> input)
{
    Node tree(false, "/");
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
            if (s.find('/') != string::npos)        // root
            {
                curNode = &tree;
            }
            else if (s.find("..") == 5)  // back
            {
                if (curNode->parent != nullptr)
                {
                    curNode = curNode->parent;
                }
            }
            else        // go to dir
            {
                s.erase(0, 3);
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

                cout << i << ": " << s << endl;
                
                bool isFolder = s.find("dir") == 0;
                if (isFolder)
                {
                    s.erase(0, 4);
                    curNode->newFolder(s);
                }
                else
                {
                    size_t split = s.find(' ');
                    unsigned int fileSize = stoi(s.substr(0, split));
                    s.erase(0, split);
                    curNode->newFile(s, fileSize);
                }
                i++;
            }
        }
    }

    int dirCount = 0;
    int sizeThresh = 100000;
    tree.calcSize();

    cout << tree.getBigFolders(sizeThresh) << endl;
}

void Solver::part02(vector<string> input)
{
    
}
