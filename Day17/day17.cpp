#include <iostream>
#include <iomanip>

#include <fstream>
#include <sstream>

#include <string>
#include <vector>

#include <windows.h>

#include <utility>

#include "../Util.h"

using namespace std;
using namespace Util;

class Solver
{
private:
    stringstream sol1, sol2;
public:
    void part01();
    void part02();

    void printResult();
};

string gasStreams;

bool debug = false;

// visualizing vars
bool visualize = false;

int delta;
int delay;

HANDLE  hConsole;
CONSOLE_CURSOR_INFO cursorInfo;

int day17(int argc, char** argv)
{
    cout << "Starting with input from " << argv[1] << " with debugging " << ((argc > 1) ? "enabled" : "disabled") << endl;
    //debug = true;
    if (argc >= 3)
        if (argv[2] == "debug")
            debug = true;
        else
        {
            if (argc <= 3)
            {
                cerr << "For visualization please insert [lines to draw] [delay between drawings]" << endl;
                return 0;
            }
            visualize = true;
            delta = stoi(argv[3]);
            delay = stoi(argv[4]);
            hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
        }

    ifstream file(argv[1]);

    if (!file.is_open())
        return -1;
    getline(file, gasStreams);
    Solver s;

    s.part01();
    //s.part02();

    s.printResult();
}

const int caveWidth = 7;
const int caveMaxHeight = 2022 * 4;
//const int caveMaxHeight = 60546 * 2;
const vec2 spawnPos(2, 3);

bool cave[caveWidth][caveMaxHeight];

const int rockCount = 5;
const int rockSize = 4;
const int rockWidth[rockCount] = { 4, 3, 3, 1, 2 };
const int rockHeight[rockCount] = { 1, 3, 3, 4, 2 };
bool rockShapes[rockCount][rockSize][rockSize] =
{
    {
        { 0, 0, 0, 0 },
        { 0, 0, 0, 0 },
        { 0, 0, 0, 0 },
        { 1, 1, 1, 1 },
    },
    {
        { 0, 0, 0, 0 },
        { 0, 1, 0, 0 },
        { 1, 1, 1, 0 },
        { 0, 1, 0, 0 },
    },
    {
        { 0, 0, 0, 0 },
        { 0, 0, 1, 0 },
        { 0, 0, 1, 0 },
        { 1, 1, 1, 0 },
    },
    {
        { 1, 0, 0, 0 },
        { 1, 0, 0, 0 },
        { 1, 0, 0, 0 },
        { 1, 0, 0, 0 },
    },
    {
        { 0, 0, 0, 0 },
        { 0, 0, 0, 0 },
        { 1, 1, 0, 0 },
        { 1, 1, 0, 0 },
    },
};

bool getRock(int rock, int x, int y)
{
    return rockShapes[rock][rockSize - y - 1][x];
}

int gasIndex;
int sideMovement()
{
    gasIndex++;
    if (gasIndex >= gasStreams.length())
        gasIndex = 0;
    return gasStreams.at(gasIndex) - 61;
}

bool intersect(vec2 rockPos, int rock)
{
    if (rockPos.y < 0)
        return true;
    for (int x = 0; x < rockSize; x++)
    {
        for (int y = 0; y < rockSize; y++)
        {
            if (getRock(rock, x, y) && cave[x + rockPos.x][y + rockPos.y])
            {
                return true;
            }
        }
    }
    return false;
}

void restRock(vec2 rockPos, int rock)
{
    for (int x = 0; x < rockWidth[rock]; x++)
    {
        for (int y = 0; y < rockHeight[rock] ; y++)
        {
            if (rockPos.x + x > caveWidth || rockPos.x + x < 0 ||
                rockPos.y + y < 0)
            {
                cerr << "rock out of bounds for " << rockPos.x + x << " in " << caveWidth << " and " << rockPos.y + y << " in " << 0 << endl;
                continue;
            }
            cave[rockPos.x + x][rockPos.y + y] = cave[rockPos.x + x][rockPos.y + y] || getRock(rock, x, y);
        }
    }
}

void initCave()
{
    for (int y = delta; y >= 0; y--)
    {
        cout << "|";
        for (int x = 0; x < caveWidth; x++)
        {
            cout << ".";
        }
        cout << "|" << endl;
    }
}

void printCave(int height, vec2 rockPos, int rock)
{
    GetConsoleCursorInfo(hConsole, &cursorInfo);
    cursorInfo.bVisible = FALSE;
    cursorInfo.dwSize = 100;
    SetConsoleCursorInfo(hConsole, &cursorInfo);

    for (int i = 0; i < delta + 1; i++)
        cout << "\033[A";

    cout << '\r';
    for (int i = 0; i < gasStreams.length(); i++)
    {
        if (i == gasIndex)
            SetConsoleTextAttribute(hConsole, 4);
        else
            SetConsoleTextAttribute(hConsole, 2);
        
        cout << gasStreams.at(i);
    }
    cout << endl;


    int start = max(0, height - 10);
    SetConsoleTextAttribute(hConsole, 7);
    for (int y = start + delta - 1; y >= start; y--)
    {
        cout << '\r' << "|";
        for (int x = 0; x < caveWidth; x++)
        {
            if (cave[x][y])
            {
                SetConsoleTextAttribute(hConsole, 0);
                cout << "#";
                continue;
            }
            if (x - rockPos.x >= 0 && x - rockPos.x < rockWidth[rock] && y - rockPos.y >= 0 && y - rockPos.y < rockHeight[rock] && getRock(rock, x - rockPos.x, y - rockPos.y))
            {
                SetConsoleTextAttribute(hConsole, 3);
                cout << "@";
                continue;
            }
            cout << " ";
        }
        SetConsoleTextAttribute(hConsole, 7);
        cout << "|" << endl;
    }
    cout << '\r';
    SetConsoleTextAttribute(hConsole, 15);
    cout << "Height: ";
    SetConsoleTextAttribute(hConsole, 14);
    cout << height;

    Sleep(delay);
}

void Solver::part01()
{
    gasIndex = -1;
    int rock = 0;
    int height = 0;

    vec2 rockPos;

    cout << endl;
    cout << "Rocks: " << endl;
    for (int i = 0; i < rockCount; i++)
    {
        cout << "Rock " << i << " with width " << rockWidth[i] << " and height " << rockHeight[i] << ":" << endl;
        for (int y = rockSize - 1; y >= 0; y--)
        {
            for (int x = 0; x < rockSize; x++)
            {
                if (getRock(i, x, y))
                    cout << "#";
                else
                    cout << ".";
            }
            cout << endl;
        }
    }
    cout << endl << endl;

    // temp
    int sideMove;

    if (visualize)
        initCave();

    for (int i = 0; i < 2022; i++)
    {
        rockPos = vec2(0, height) + spawnPos;
        if (debug)
            cout << "rock " << i + 1 << " starts falling at " << rockPos << endl;
        while (true)
        {
            if (visualize)
                printCave(height, rockPos, rock);

            //cout << rockPos << " ";

            sideMove = sideMovement();
            if (rockPos.x + sideMove >= 0 &&
                rockPos.x + sideMove + rockWidth[rock] <= caveWidth &&
                !intersect(rockPos + vec2(sideMove, 0), rock))
                rockPos.x += sideMove;
                
            //cout << sideMove << " " << rockPos << endl;
            
            if (visualize)
                printCave(height, rockPos, rock);

            if (intersect(rockPos.oneDown(), rock))
                break;

            rockPos.y--;
        }
        
        if (debug)
            cout << rockPos << " | " << sideMove << " | " << rockPos.x - sideMove << " | " << rockPos.x - sideMove + rockWidth[rock] << " | " << rockPos.x + rockWidth[rock] << endl;
        
        restRock(rockPos, rock);

        if (debug)
            cout << "rock rests at " << rockPos << endl;

        height = 0;
        for (int y = 0; y < caveMaxHeight; y++)
        {
            for (int x = 0; x < caveWidth; x++)
            {
                if (cave[x][y])
                    height = y + 1;
            }
        }

        if (debug)
            for (int y = height + 5; y >= max(0, height - 10); y--)
            {
                cout << setw(3);
                cout << y;
                cout << setw(7);
                for (int x = 0; x < caveWidth; x++)
                {
                    if (cave[x][y])
                    {
                        cout << "#";
                        continue;
                    }
                    cout << ".";
                }
                cout << endl;
            }

        rock++;
        if (rock >= rockCount)
            rock = 0;
    }

    sol1 << height;
}

void Solver::part02()
{
    // TODO solving part 2

    gasIndex = -1;
    int rock = 0;
    long height = 0;

    vec2 rockPos;

    for (int x = 0; x < caveWidth; x++)
    {
        for (int y = 0; y < caveMaxHeight; y++)
        {
            cave[x][y] = 0;
        }
    }

    // temp
    int sideMove;
    long tempHeight;
    long lastHeight;
    bool found;

    if (visualize)
        initCave();

    for (long i = 0; i < caveMaxHeight; i++)
    {
        if (i == 60546)
        {
            tempHeight = height;
        }
 
        rockPos = vec2(0, height) + spawnPos;
        while (true)
        {
            sideMove = sideMovement();
            if (rockPos.x + sideMove >= 0 &&
                rockPos.x + sideMove + rockWidth[rock] <= caveWidth &&
                !intersect(rockPos + vec2(sideMove, 0), rock))
                rockPos.x += sideMove;
            
            if (visualize)
                printCave(height, rockPos, rock);

            if (intersect(rockPos.oneDown(), rock))
                break;

            rockPos.y--;
        }
        restRock(rockPos, rock);

        lastHeight = height;
        height = 0;
        for (long y = max((long) 0, lastHeight - 40); y < lastHeight + 40; y++)
        {
            found = false;
            for (int x = 0; x < caveWidth; x++)
            {
                if (cave[x][y])
                {
                    height = y + 1;
                    found = true;
                }
            }
            if (!found)
                break;
        }
        if (i % 1000 == 0)
            cout << height << " | " << i << endl;

        rock++;
        if (rock >= rockCount)
            rock = 0;
    }

    long solution = tempHeight + (height - tempHeight) * 16516367.7204109272288838;
    sol2 << solution;
}

void Solver::printResult()
{
    cout << "Part 1: " << sol1.str() << endl << "Part 2: " << sol2.str() << endl;
}
