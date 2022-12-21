#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include "../Util.h"

using namespace std;

class Solver
{
public:
    void part01(vector<string>);
    void part02(vector<string>);
};

void day10()
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
        //s.part01(input);
        s.part02(input);
    }
    else
    {
        cout << "error with file" << endl;
    }
}

void Solver::part01(vector<string> input)
{
    int registry = 1;
    int vToAdd = 0;
    int cycle = 0;
    int index = -1;
    int signal = 0;
    vector<string> split;
    for (int i = 0; i < input.size() || i <= cycle; i++)
    {
        if ((i + 20) % 40 == 0)
        {
            signal += registry * i;
        }

        cout << i << ": " << registry << " | ";

        if (cycle > i)
        {
            cout << "wait" << endl;
            continue;
        }

        if (vToAdd != 0)
            cout << "add " << vToAdd << endl;

        registry += vToAdd;
        vToAdd = 0;
        index++;

        if (index >= input.size())
            break;

        split = Util::split(input[index], " ");

        cout << input[index] << endl;

        if (split[0] == "noop")
        {
            cycle++;
            continue;
        }

        vToAdd = stoi(split[1]);
        cycle += 2;
    }

    cout << signal << endl;
}

void Solver::part02(vector<string> input)
{
    int registry = 1;
    int vToAdd = 0;
    int cycle = 0;
    int index = -1;
    int x, y;
    vector<string> split;

    const int HEIGHT = 6, WIDTH = 40;
    bool** display = new bool*[HEIGHT];
    for (int i = 0; i < HEIGHT; i++)
    {
        display[i] = new bool[WIDTH];
    }

    //for (int i = 0; i < input.size() || i <= cycle; i++)
    for (int i = 0; i < 40 * 6; i++)
    {
        x = i % 40;
        y = (int) (i / 40);

        cout << i << ": " << registry << " | ";

        if (cycle > i)
        {
            display[y][x] = Util::clamp(registry - x, -1, 1) == (registry - x);
            cout << "wait" << endl;
            continue;
        }

        if (vToAdd != 0)
            cout << "add " << vToAdd << endl;

        registry += vToAdd;
        vToAdd = 0;
        index++;
        display[y][x] = Util::clamp(registry - x, -1, 1) == (registry - x);

        if (index >= input.size())
            break;

        split = Util::split(input[index], " ");

        cout << input[index] << endl;

        if (split[0] == "noop")
        {
            cycle++;
            continue;
        }

        vToAdd = stoi(split[1]);
        cycle += 2;
    }

    cout << endl;
    for (int y = 0; y < HEIGHT; y++)
    {
        for (int x = 0; x < WIDTH; x++)
        {
            cout << (display[y][x] ? '#' : '.');
        }
        cout << endl;
    }

    delete[] display;
}
