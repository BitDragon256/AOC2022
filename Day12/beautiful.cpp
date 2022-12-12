#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>
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
vector<vector<uint8_t>> originalElevation;
vector<vec2> startPositions;
vec2 startPos;
vec2 finalPos;

int main()
{
    cout << "Starting" << endl;

    vector<string> input;
    string line;
    while (cin)
    {
        getline(cin, line);
        if (line == "stop")
            break;
        input.push_back(line);
    }

    vec2 pos = vec2(0, 0);
    startPositions = vector<vec2>();
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
            if (s.at(i) == 'a')
                startPositions.push_back(pos);

            elevation[elevation.size() - 1].push_back(s.at(i));
            pos.x++;
        }

        pos.y++;
    }

    originalElevation = elevation;

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

template <typename T>
struct Grid
{
public:
    T** data;
    vec2 size;
    Grid(vec2 size): size(size)
    {
        data = new T*[size.x];
        for (int i = 0; i < size.x; i++)
        {
            data[i] = new T[size.y];
        }
    }

    ~Grid()
    {
        for (long i = 0; i < size.x; i++)
        {
            delete[] data[i];
        }
        delete[] data;
    }

    operator[](vec2 pos)
    {
        return data[pos.x][pos.y];
    }

    void set(vec2 pos, T data)
    {
        data[pos.x][pos.y] = data;
    }

    
};

void Solver::part01(vector<string> input)
{
    vec2* positions = new vec2[100000];
    uint* paths = new uint[100000];

    positions[0] = startPos;
    paths[0] = 0;

    uint posIndex = 0;

    vec2 pos, newPos;
    uint path;
    uint index = 0;
    while (index <= posIndex)
    {
        pos = positions[index];
        path = paths[index];

        cout << pos.x << " " << pos.y << " " << path << " " << index << endl;

        index++;

        if (pos == finalPos)
        {
            cout << "Path found: " << path << endl;
            break;
        }

        bool b = false;
        for (vec2 d : directions)
        {
            newPos = pos + d;
            if (newPos.y < 0 || newPos.y >= elevation.size() ||
                newPos.x < 0 || newPos.x >= elevation[0].size() ||
                pos.y < 0 || pos.y >= elevation.size() ||
                pos.x < 0 || pos.x >= elevation[0].size())
                continue;
        
            if (elevation[pos.y][pos.x] == UINT8_MAX ||
                elevation[newPos.y][newPos.x] == UINT8_MAX)
                continue;

            if (elevation[pos.y][pos.x] < elevation[newPos.y][newPos.x] - 1)
                continue;

            positions[posIndex] = pos + d;
            paths[posIndex] = path + 1;
            posIndex++;
            b = true;
        }

        elevation[pos.y][pos.x] = UINT8_MAX;
    }
    delete[] positions;
    delete[] paths;
}

void Solver::part02(vector<string> input)
{
    vector<uint> steps = vector<uint>();

    vec2* positions = new vec2[100000];
    uint* paths = new uint[100000];

    positions[0] = startPos;
    paths[0] = 0;

    uint posIndex = 0;

    vec2 pos, newPos;
    uint path;
    uint index = 0;
    for (int i = 0; i < startPositions.size(); i++)
    {
        index = 0;
        positions[0] = startPositions[i];
        paths[0] = 0;
        elevation = originalElevation;
        posIndex = 0;

        while (index <= posIndex)
        {
            pos = positions[index];
            path = paths[index];
            index++;

            if (pos == finalPos)
            {
                steps.push_back(path);
                break;
            }

            bool b = false;
            for (vec2 d : directions)
            {
                newPos = pos + d;
                if (newPos.y < 0 || newPos.y >= elevation.size() ||
                    newPos.x < 0 || newPos.x >= elevation[0].size() ||
                    pos.y < 0 || pos.y >= elevation.size() ||
                    pos.x < 0 || pos.x >= elevation[0].size())
                    continue;
            
                if (elevation[pos.y][pos.x] == UINT8_MAX ||
                    elevation[newPos.y][newPos.x] == UINT8_MAX)
                    continue;

                if (elevation[pos.y][pos.x] < elevation[newPos.y][newPos.x] - 1)
                    continue;

                positions[posIndex] = pos + d;
                paths[posIndex] = path + 1;
                posIndex++;
                b = true;
            }
            elevation[pos.y][pos.x] = UINT8_MAX;
        }
    }

    sort(steps.begin(), steps.end());
    cout << "Steps:";
    for (uint i : steps)
    {
        cout << " " << i;
    }
    cout << endl;
    
    delete[] positions;
    delete[] paths;
}
