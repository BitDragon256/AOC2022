#include <fstream>
#include <iostream>

#include <string>
#include <vector>
#include <algorithm>

#define uint unsigned int

using namespace std;

namespace Util
{
    vector<string> split(string s, string del)
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

    void printStacks(vector<stack<char>*> stacks)
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

    struct vec2
    {
    public:
        uint x, y;
        vec2(uint x, uint y): x(x), y(y) {}
        vec2(): x(0), y(0) {}

        vec2 operator+ (vec2 other)
        {
            return vec2(this->x + other.x, this->y + other.y);
        }

        vec2& operator+=(vec2& other)
        {
            this->x += other.x;
            this->y += other.y;
            return *this;
        }
    };
};
