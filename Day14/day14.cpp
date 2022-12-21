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

bool* grid;
vec2 gridSize;
vec2 sandStart;

void printGrid(vec2);

int day14()
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
            coords[coords.size() - 1].push_back( vec2(stoi(split[0]), stoi(split[1])) ); // X: 460 - 521 | Y: 166
        }
    }

    vec2 min = vec2(10000, 10000); vec2 max = vec2(-1, -1);
    for (vector<vec2> rockLine : coords)
    {
        for (vec2 v : rockLine)
        {
            if (v.x > max.x)
                max.x = v.x;
            if (v.y > max.y)
                max.y = v.y;
            if (v.x < min.x)
                min.x = v.x;
            if (v.y < min.y)
                min.y = v.y;
        }
    }
    vec2 span = max - min;
    gridSize = vec2(max.y * 2 + 1, max.y + 1 + 2);
    uint delta = (gridSize.x - span.x) / 2;
    sandStart = vec2(500 - min.x + delta, 0);

    //cout << "Span: " << span.x << " " << span.y << endl;
    cout << "Span: " << span << endl;
    cout << "Gridsize: " << gridSize << endl;
    cout << "Delta: " << delta << endl;
    cout << "Sandstart: " << sandStart << endl;

    grid = new bool[gridSize.sqrMagnitude()];
    for (int i = 0; i < gridSize.sqrMagnitude(); i++)
    {
        grid[i] = false;
    }

    vec2 minPos, maxPos;
    for (vector<vec2> rock : coords)
    {
        for (int i = 1; i < rock.size(); i++)
        {
            maxPos = vec2::max(rock[i - 1], rock[i]);
            minPos = vec2::min(rock[i - 1], rock[i]);
            for (int x = minPos.x + delta - min.x; x <= maxPos.x + delta - min.x; x++)
            {
                for (int y = minPos.y; y <= maxPos.y; y++)
                {
                    grid[x + y * gridSize.x] = true;
                }
            }
        }
    }

    Solver s;
    s.part01();
    s.part02();

    delete[] grid;
}

void printGrid(vec2 sand)
{
    cout << endl << endl;

    for (int i = 0; i < gridSize.sqrMagnitude(); i++)
    {
        if (i % gridSize.x == 0)
            cout << endl;

        if (i == sand.x + sand.y * gridSize.x)
        {
            cout << "o";
            continue;
        }

        cout << (grid[i] ? "#" : ".");
    }
}

void Solver::part01()
{
    vec2 sand = sandStart;
    uint sandCount = 0;
    uint8_t state = 0;

    while (true)
    {
        switch (state)
        {
            case 0:
                sand.y += 1;
                break;
            case 1:
                sand.x--;
                break;
            case 2:
                sand.x += 2;
                break;
            case 3:
                sand.y--;
                sand.x--;

                grid[sand.x + sand.y * gridSize.x] = true;
                sand = sandStart;
                sandCount++;
                state = 0;
                break;
        }
        
        if (sand.y >= gridSize.y - 2) // ignore floor of part 2
        {
            break;
        }
        if (grid[sand.x + sand.y * gridSize.x])
        {
            state++;
            continue;
        }
        state = 0;
    }
    cout << sandCount << endl;
}

void Solver::part02()
{
    // add the floor
    for (int x = 0; x < gridSize.x; x++)
    {
        int y = gridSize.y - 1;
        grid[x + y * gridSize.x] = true;
    }

    vec2 sand = sandStart;
    uint sandCount = 0;
    uint8_t state = 0;

    while (true)
    {
        switch (state)
        {
            case 0:
                sand.y += 1;
                break;
            case 1:
                sand.x--;
                break;
            case 2:
                sand.x += 2;
                break;
            case 3:
                sand.y--;
                sand.x--;
                
                grid[sand.x + sand.y * gridSize.x] = true;
                sand = sandStart;
                sandCount++;
                state = 0;
                break;
        }

        
        if (grid[sandStart.x + sandStart.y * gridSize.x])
        {
            break;
        }
        if (grid[sand.x + sand.y * gridSize.x])
        {
            //cout << sand.x << " " << sand.y << " " << (sand.x + sand.y * gridSize.x) << endl;
            state++;
            continue;
        }
        state = 0;
    }
    cout << sandCount << endl;
}
