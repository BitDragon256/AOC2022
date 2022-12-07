#include <fstream>
#include <iostream>

#include <string>
#include <vector>
#include <algorithm>

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
        return res;
    }
};
