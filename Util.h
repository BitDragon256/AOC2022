#include <fstream>
#include <iostream>

#include <string>
#include <vector>
#include <algorithm>

#define uint unsigned int

using namespace std;

class Util
{
public:
    static vector<string> split(string s, string del)
    {
        vector<string> res;
        size_t pos;
        while ((pos = s.find(del)) != string::npos)
        {
            res.push_back(s.substr(0, pos));
            s.erase(0, pos + del.length());
        }
        res.push_back(s);
        return res;
    }

    static void printStacks(vector<stack<char>*> stacks)
    {
        for (auto stack : stacks)
        {
            while (stack->size() > 0)
            {
                cout << stack->top();
                stack->pop();
            }
            cout << "]" << endl;
        }
    }
};
