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
    void part01();
    void part02();
};

struct Grid
{
public:
    vector<vector<uint8_t>> height;
    vec2 size;

    Grid(): height(), size(vec2()) {}
    Grid(vector<vector<uint8_t>> data): height(data)
    {
        size = vec2(data.size(), data.size() > 0 ? data[0].size() : 0);
    }
    Grid(vector<string> input)
    {
        size.y = input.size();

        for (string line : input)
        {
            height.push_back(vector<uint8_t>());
            for (char c : line)
            {
                (*height.rbegin()).push_back(c - '0');
            }
        }
        size.x = height[0].size();
    }

    const uint8_t operator [] (vec2 pos)
    {
        return height[pos.x][pos.y];
    }
} grid;

void day8()
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
        grid = Grid(input);

        /*
        vec2 pos;
        for (pos.x = 0; pos.x < grid.size.x; pos.x++)
        {
            for (pos.y = 0; pos.y < grid.size.y; pos.y++)
            {
                cout << (int) grid[pos];
            }
            cout << endl;
        }
        */

        Solver s;
        s.part01();
        s.part02();
    }
    else
    {
        cout << "error with file" << endl;
    }
}

vec2 directions[] = { vec2(-1, 0), vec2(1, 0), vec2(0, -1), vec2(0, 1) };

bool isVisible(vec2 pos)
{
    vec2 cur;
    uint8_t startHeight = grid[pos];
    vector<bool> visible;

    bool v;
    for (vec2 dir : directions)
    {
        cur = pos + dir;
        v = true;
        while (cur.x >= 0 && cur.x < grid.size.x && 
               cur.y >= 0 && cur.y < grid.size.y)
        {
            if (grid[cur] >= startHeight)
            {
                v = false;
                break;
            }

            cur += dir;
        }
        visible.push_back(v);
    }

    for (int i = 0; i < visible.size(); i++)
    {
        if (visible[i])
        {
            return true;
        }
    }
    return false;
}

uint viewScore(vec2 pos)
{
    vec2 cur;
    uint8_t startHeight = grid[pos];
    uint score = 1;

    uint curDist;
    for (vec2 dir : directions)
    {
        cur = pos + dir;
        curDist = 1;
        while (true)
        {
            if (cur.x < 0 || cur.x >= grid.size.x ||
                cur.y < 0 || cur.y >= grid.size.y)
            {
                curDist--;
                break;
            }
            if (grid[cur] >= startHeight)
            {
                break;
            }

            curDist++;
            cur += dir;
        }
        score *= curDist;
    }

    return score;
}

void Solver::part01()
{
    uint visibleCount = 0;
    vec2 pos;
    for (pos.x = 0; pos.x < grid.size.x; pos.x++)
    {
        for (pos.y = 0; pos.y < grid.size.y; pos.y++)
        {
            if (isVisible(pos))
            {
                visibleCount++;
            }
        }
    }

    cout << visibleCount << endl;
}

void Solver::part02()
{
    uint highestScore = 0, score;
    vec2 pos;
    for (pos.x = 0; pos.x < grid.size.x; pos.x++)
    {
        for (pos.y = 0; pos.y < grid.size.y; pos.y++)
        {
            score = viewScore(pos);
            if (score > highestScore)
                highestScore = score;
        }
    }

    cout << highestScore << endl;
}
