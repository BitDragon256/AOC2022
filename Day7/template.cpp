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
    vector<Node> children;
    Node* parent;
    unsigned int size;
    Node(Node* children, size_t childCount, Node* parent, unsigned int size):
    size(size), parent(parent)
    {
        this->children = vector<Node>();
        for (int i = 0; i < childCount; i++)
        {
            this->children.push_back(children[i]);
        }
    }
    Node(vector<Node> children, Node* parent, unsigned int size):
    size(size), children(children), parent(parent)
    {}
    Node(){}
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
    Node tree, curNode;
    string s;
    for (int i = 0; i < input.size(); i++)
    {
        s = input[i];
        if (s.size() == 0)
        {
            continue;
        }
        if (s.at(2) == 'c') // cd
        {
            if (s.find('/') == string::npos)
            {
                
            }
        }
        if (s.at(2) == 'l') // cd
        {

        }
    }
}

void Solver::part02(vector<string> input)
{
    
}
