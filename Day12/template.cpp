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
    void part01(vector<string>);
    void part02(vector<string>);
};

vector<vector<uint8_t>> elevation;
vec2 startPos;
vec2 finalPos;

int main()
{
    cout << "Starting" << endl;

    /*
    ifstream file("input.txt");

    vector<string> input;

    if (file.is_open())
    {
        cerr << "File error" << endl;
        return -1;
    }
    string line;
    while (getline(file, line))
    {
        cout << line << endl;
        input.push_back(line);
    }
    */
    vector<string> input;
    string line;
    while (cin)
    {
        getline(cin, line);
        if (line == "stop")
            break;
        //cout << line << endl;
        input.push_back(line);
    }

    vec2 pos = vec2(0, 0);
    for (string s : input)
    {
        pos.x = 0;

        elevation.push_back(vector<uint8_t>());
        for (int i = 0; i < s.length(); i++)
        {
            if (s.at(i) == 'S')
            {
                startPos = pos;
                s.at(i) = 'a';
            }
            if (s.at(i) == 'E')
            {
                finalPos = pos;
                s.at(i) = 'z';
            }

            elevation[elevation.size() - 1].push_back(s.at(i));
            pos.x++;
        }

        pos.y++;
    }

    Solver s;
    s.part01(input);
    s.part02(input);
}

vector<vec2> directions = { vec2(0, 1), vec2(0, -1), vec2(1, 0), vec2(-1, 0) };

void printMap(vec2 cur)
{
    vec2 pos = vec2(0, 0);
    for (pos.y = 0; pos.y < elevation.size(); pos.y++)
    {
        for (pos.x = 0; pos.x < elevation[pos.y].size(); pos.x++)
        {
            if (elevation[pos.y][pos.x] == UINT8_MAX)
            {
                cout << '#';
                continue;
            }
            if (pos == cur)
            {
                cout << '.';
                continue;
            }
            cout << elevation[pos.y][pos.x];
        }
        cout << endl;
    }
    cout << endl;
}

/*
uint findPath(vec2 current, uint steps)
{
    //printMap();
    if (current == finalPos)
        return steps;
    
    cout << current.x << " " << current.y << " " << steps << endl;

    vec2 nextPos;
    uint8_t height = elevation[current.y][current.x];
    elevation[current.y][current.x] = UINT8_MAX;
    int path;

    for (vec2 dir : directions)
    {
        nextPos = current + dir;
        if (elevation[nextPos.y][nextPos.x] <= height + 1)
        {
            path = findPath(nextPos, steps + 1);
        }
    }

    return path;
}
*/

void Solver::part01(vector<string> input)
{
    cout << startPos.x << " " << startPos.y << endl;
    cout << finalPos.x << " " << finalPos.y << endl;
    
    // vector<vec2> positions = vector<vec2>();
    // vector<uint> paths = vector<uint>();

    uint steps = 0;
    // positions.push_back(startPos);
    // paths.push_back(0);

    vec2* positions = new vec2[10000];
    uint* paths = new uint[10000];

    positions[0] = startPos;
    paths[0] = 0;

    uint posIndex = 0;

    vec2 pos, newPos;
    uint path;
    uint index = 0;
    // while (index < positions.size() && index < paths.size())
    while (index <= posIndex)
    {
        pos = positions[index];
        path = paths[index];

        cout << pos.x << " " << pos.y << " " << path << " " << index << endl;

        printMap(pos);

        index++;
        if (elevation[pos.y][pos.x] == UINT8_MAX)
            continue;

        if (pos == finalPos)
        {
            steps = path;
            cout << "Path found" << endl;
            break;
        }
        elevation[pos.y][pos.x] = UINT8_MAX;

        for (vec2 d : directions)
        {
            // positions.push_back(pos + d);
            // paths.push_back(path + 1);
            newPos = pos + d;
            if (newPos.y < 0 || newPos.y >= elevation.size() ||
                newPos.x < 0 || newPos.x >= elevation[0].size() ||
                elevation[pos.y][pos.x] < elevation[newPos.y][newPos.x] - 1)
                continue;

            positions[posIndex] = pos + d;
            paths[posIndex] = path + 1;
            posIndex++;
        }
        // cout << index << " " << positions.size() << " " << paths.size() << endl;
    }

    cout << "Steps: " << steps << endl;
}

void Solver::part02(vector<string> input)
{
    
}
