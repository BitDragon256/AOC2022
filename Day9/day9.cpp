#include <iostream>
#include <fstream>
#include <string>

#include <vector>
#include <map>
#include <set>

#include <math.h>

#include "../Util.h"

using namespace std;
using namespace Util;

class Solver
{
public:
    void part01(vector<string>);
    void part02(vector<string>);
};

void day9()
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

 vector<vec2> visited;

void printRope(vec2 head, vec2 tail, vec2 size)
{
    cout << head.x << ", " << head.y << " | " << tail.x << ", " << tail.y << endl;

    vec2 pos;
    for (pos.y = size.y; pos.y >= -size.y; pos.y--)
    {
        for (pos.x = -size.x; pos.x <= size.x; pos.x++)
        {
            if (head == pos)
            {
                cout << "H ";
                continue;
            }
            else if (tail == pos)
            {
                cout << "T ";
            }
            else
            {
                cout << ". ";
            }
        }
        cout << endl;
    }
    cout << endl << endl;
}

void Solver::part01(vector<string> input)
{
    vec2 head = vec2(), tail = vec2();

    char move;
    uint len;

    float dist;
    vec2 delta;

    visited = vector<vec2>();

    // printRope(head, tail, vec2(10, 10));

    for (string s : input)
    {
        move = s.at(0);
        len = stoi(split(s, " ")[1]);

        for (int i = 0; i < len; i++)
        {
            head += directions[move];

            // move tail accordingly
            dist = head / tail;
            if (dist > 1.42f)
            {
                // cout << "move" << endl;
                delta = head - tail;
                tail = tail + vec2(clamp(delta.x, -1, 1), clamp(delta.y, -1, 1));
            }
            visited.push_back(tail);

            // printRope(head, tail, vec2(10, 10));
        }
    }

    for (int i = 0; i < visited.size(); i++)
    {
        for (int j = i + 1; j < visited.size(); j++)
        {
            if (visited[i] == visited[j])
            {
                visited.erase(visited.begin() + j);
                j--;
            }
        }
    }

    cout << visited.size() << endl;
}

void Solver::part02(vector<string> input)
{
    vector<vec2> elems = vector<vec2>(10, vec2());

    char move;
    uint len;

    float dist;
    vec2 delta;

    visited = vector<vec2>();

    for (string s : input)
    {
        move = s.at(0);
        len = stoi(split(s, " ")[1]);

        for (int i = 0; i < len; i++)
        {
            elems[0] += directions[move];

            // move tail accordingly
            for (int j = 1; j < tails.size(); j++)
            {
                dist = elems[0] / tails[j];
                if (dist > 1.42f)
                {
                    delta = elems[0] - tails[j];
                    tails[j] = tails[j] + vec2(clamp(delta.x, -1, 1), clamp(delta.y, -1, 1));
                }
                visited.push_back(tails[j]);
            }
        }
    }

    for (int i = 0; i < visited.size(); i++)
    {
        for (int j = i + 1; j < visited.size(); j++)
        {
            if (visited[i] == visited[j])
            {
                visited.erase(visited.begin() + j);
                j--;
            }
        }
    }

    cout << visited.size() << endl;
}
