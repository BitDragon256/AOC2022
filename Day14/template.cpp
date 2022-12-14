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
const vec2 gridSize = vec2(400, 166 + 1 + 2);
const int delta = gridSize.x / 2 - 61;
//const vec2 gridSize = vec2(10, 10);

void printGrid(vec2);

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
            coords[coords.size() - 1].push_back( vec2(stoi(split[0]) - 460 + delta, stoi(split[1])) ); // X: 460 - 521 | Y: 166
        }
    }

    grid = new bool[gridSize.x * gridSize.y];
    for (int i = 0; i < gridSize.x * gridSize.y; i++)
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
            for (int x = minPos.x; x <= maxPos.x; x++)
            {
                for (int y = minPos.y; y <= maxPos.y; y++)
                {
                    grid[x + y * gridSize.x] = true;
                }
            }
        }
    }
    for (int x = 0; x < gridSize.x; x++)
    {
        int y = gridSize.y - 1;
        grid[x + y * gridSize.x] = true;
    }

    printGrid(vec2(0, 0));

    // delete[] grid;
    // return 0;

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
    s.part01();
    //s.part02();

    delete[] grid;
}

void printGrid(vec2 sand)
{
    string s;
    cin >> s;
    cout << endl << endl;

    for (int i = 0; i < gridSize.x * gridSize.y; i++)
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
    vec2 sandStart = vec2(500 - 460 + delta, 0);
    //vec2 sandStart = vec2(500 - 494, 0);
    vec2 sand = sandStart;
    uint sandCount = 0;
    uint8_t state = 0;

    while (true)
    {
        //printGrid(sand);
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

                //printGrid(sand);

                grid[sand.x + sand.y * gridSize.x] = true;
                sand = sandStart;
                sandCount++;
                state = 0;
                break;
        }
        
        // if (sand.y >= gridSize.y)
        if (grid[sandStart.x + sandStart.y * gridSize.x])
        {
            printGrid(vec2(0, 0));
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
    
}
