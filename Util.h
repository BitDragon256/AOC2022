#include <fstream>
#include <iostream>
#include <string>
#include <vector>
#include <stack>
#include <algorithm>
#include <math.h>

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

    vector<string> splitMulti(string s, vector<string> dels)
    {
        vector<string> res;
        res.push_back(s);
        size_t pos;
        size_t size;
        for (string del : dels)
        {
            size = res.size();
            for (int i = 0; i < size; i++)
            {
                while ((pos = res[i].find(del)) != string::npos)
                {
                    res.push_back(res[i].substr(0, pos));
                    res[i].erase(0, pos + del.length());
                }
                if (res[i] != "")
                    res.push_back(res[i]);
            }
            res.erase(res.begin(), res.begin() + size);
        }
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
        long x, y;
        vec2(long x, long y): x(x), y(y) {}
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

        vec2 operator-(vec2 other)
        {
            return vec2(this->x - other.x, this->y - other.y);
        }

        float operator/(vec2 other)
        {
            vec2 delta = other - *this;
            return sqrt(delta.x * delta.x + delta.y * delta.y);
        }

        bool operator==(vec2 other)
        {
            return this->x == other.x && this->y == other.y;
        }

        bool operator!=(vec2 other)
        {
            return !(*this == other);
        }

        static vec2 min(vec2 a, vec2 b)
        {
            return vec2(std::min(a.x, b.x), std::min(a.y, b.y));
        }

        static vec2 max(vec2 a, vec2 b)
        {
            return vec2(std::max(a.x, b.x), std::max(a.y, b.y));
        }

        long sqrMagnitude()
        {
            return x * y;
        }
    };

    long clamp(long a, long min, long max)
    {
        if (a < min)
            return min;
        if (a > max)
            return max;
        return a;
    }

    long min(long a, long b)
    {
        if (a > b)
            return b;
        return a;
    }

    long max(long a, long b)
    {
        if (a < b)
            return b;
        return a;
    }

    ostream& operator<< (ostream& os, vec2& v)
    {
        os << "x: " << v.x << " y: " << v.y;
        return os;
    }
};
