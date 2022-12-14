#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include "../Util.h"

using namespace std;
using namespace Util;

class Solver
{
public:
    void part01(vector<uint8_t>);
    void part02(vector<uint8_t>);
};

vector<vector<uint8_t>> grid;

int main()
{
    cout << "Starting" << endl;

    ifstream file("input.txt");

    vector<vector<string>> input;

    if (!file.is_open())
        return -1;
    
    string line;
    vector<string> split;
    while (getline(file, line))
    {
        split = Util::split(line, " -> ");
        input.push_back(split);
    }

    vector<vector<vec2>> coords;
    for (vector<string> rockLine : input)
    {
        coords.push_back(vector<vec2>());
        for (string coord : rockLine)
        {
            split = Util::split(coord, ",");
            coords[coords.size() - 1].push_back( vec2(stoi(split[0]) - 460, stoi(split[1]) - 13) ); // X: 460 - 521 | Y: 13 - 166
        }
    }

    // uint minX = 10000; uint maxX = 0; uint minY = 10000; uint maxY = 0;
    // for (vec2 v : coords)
    // {
    //     cout << v.x << " " << v.y << endl;
    //     if (v.x > maxX)
    //         maxX = v.x;
    //     if (v.y > maxY)
    //         maxY = v.y;
    //     if (v.x < minX)
    //         minX = v.x;
    //     if (v.y < minY)
    //         minY = v.y;
    // }

    // cout << minX << " " << maxX << endl << minY << " " << maxY << endl;

    Solver s;
    // s.part01(input);
    // s.part02(input);
}

void Solver::part01(vector<uint8_t> input)
{
    
}

void Solver::part02(vector<uint8_t> input)
{
    
}
