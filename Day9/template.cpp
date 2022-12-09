#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <map>

#include "../Util.h"

using namespace std;
using namespace Util;

class Solver
{
public:
    void part01(vector<string>);
    void part02(vector<string>);
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

map<char, vec2> directions = { 
    { 'R', vec2(1, 0) },
    { 'L', vec2(-1, 0) },
    { 'U', vec2(0, 1) },
    { 'D', vec2(0, -1) }
 };

void Solver::part01(vector<string> input)
{
    vec2 head, tail;

    char move;
    uint len;
    for (string s : input)
    {
        move = s.at(0);
        len = stoi(split(s, " ")[1]);

        head += directions[move];

    }
}

void Solver::part02(vector<string> input)
{
    
}
