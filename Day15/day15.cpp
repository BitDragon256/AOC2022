#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <math.h>

#include "../Util.h"

using namespace std;

class Solver
{
public:
    void part01(vector<string>);
    void part02(vector<string>);
};

int day15()
{
    cout << "Starting" << endl;

    ifstream file("input.txt");

    vector<string> input;

    if (!file.is_open())
        return -1;
    string line;
    while (getline(file, line))
    {
        input.push_back(line);
    }
    Solver s;
    s.part01(input);
    s.part02(input);
}

void Solver::part01(vector<string> input)
{
    uint beaconsAtY = 0;
    const long Y = 2000000;
    uint32_t noBeacons = 0;

    long d, scanX, scanY, beacX, beacY, b, delta;
    vector<string> split;
    for (string s : input)
    {
        split = Util::split(s, " ");

        scanX = stoi(split[3].substr(2, split[3].length() - 1 - 2));
        scanY = stoi(split[4].substr(2, split[4].length() - 1 - 2));

        beacX = stoi(split[8].substr(2, split[8].length() - 1 - 2));
        beacY = stoi(split[9].substr(2, split[9].length() - 1 - 2));

        if (beacY == Y)
            beaconsAtY++;

        d = abs(scanX - beacX) + abs(scanY - beacY);
        delta = abs(Y - scanY);
        b = Util::min(1 + 2 * (d - delta), 0);

        noBeacons += b;
    }

    cout << (noBeacons - beaconsAtY);

}

void Solver::part02(vector<string> input)
{
    
}
