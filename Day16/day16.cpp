#include <iostream>
#include <fstream>
#include <sstream>

#include <vector>
#include <map>

#include <utility>

#include "../Util.h"

using namespace std;

class Solver
{
private:
    stringstream sol1, sol2;
public:
    void part01();
    void part02();

    void printResult();
};

struct Valve
{
    int flow;
    vector<string> tunnels;
};

map<string, int> valveIds;
vector<Valve*> valves;

int day16()
{
    cout << "Starting" << endl;

    ifstream file("input.txt");

    if (!file.is_open())
        return -1;
    string line;
    vector<string> split;
    Valve* v;
    while (getline(file, line))
    {
        split = Util::splitMulti(line, { " ", "=", ";", "," });
        v = new Valve();
        v->flow = stoi(split[5]);
        for (auto it = split.begin() + 10; it != split.end(); it++)
        {
            v->tunnels.push_back(*it);
        }
        valveIds[split[1]] = valves.size() - 1;
        valves.push_back(v);
    }

    Solver s;

    s.part01();
    s.part02();

    s.printResult();
}

const int valveCount = 63; // hard-coded number of valves
int matrix[valveCount][valveCount] = { 0 };



void Solver::part01()
{
    // adjacency matrix

    for (int i = 0; i < valveCount; i++)
        for (int j = 0; j < valveCount; j++)
            matrix[i][j] = 100000;
    
    for (int i = 0; i < valveCount; i++)
        for (string tunnel : valves[i]->tunnels)
            matrix[i][valveIds[tunnel]] = 1;

    // Floyd-Warshall

    for (int k = 0; k < valveCount; k++)
    {
        for (int i = 0; i < valveCount; i++)
        {
            for (int j = 0; j < valveCount; j++)
            {
                matrix[i][j] = min(matrix[i][j], matrix[i][k] + matrix[k][j]);
            }
        }
    }

    vector<Valve*> importantValves;
    for (Valve* v : valves)
        if (v->flow > 0)
            importantValves.push_back(v);
    
    int maxPressure = 0;

    sol1 << maxPressure;
}

void Solver::part02()
{
    

    sol2 << "not finished";
}

void Solver::printResult()
{
    cout << "Part 1: " << sol1.str() << endl << "Part 2: " << sol2.str() << endl;
}
