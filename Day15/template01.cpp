#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <math.h>
#include <unordered_set>
#include <set>

#include "../Util.h"

using namespace std;

class Solver
{
public:
    void part01(vector<string>);
    void part02(vector<string>);
};

int main()
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
    //s.part01(input);
    s.part02(input);
}

void Solver::part01(vector<string> input)
{
    set<long> noBeacons = set<long>();
    const long Y = 2000001;
    //const long Y = 11;
    uint beaconsAtY = 0;

    long d, scanX, scanY, beacX, beacY, b, delta;
    vector<string> split;
    for (string s : input)
    {
        //cout << s << endl;
        split = Util::split(s, " ");

        //cout << split[2] << " " << split[3] << " " << split[8] << " " << split[9] << endl;

        scanX = stoi(split[2].substr(2, split[2].length() - 1));
        scanY = stoi(split[3].substr(2, split[3].length() - 1));

        beacX = stoi(split[8].substr(2, split[8].length() - 1));
        beacY = stoi(split[9].substr(2, split[9].length() - 1));

        if (beacY == Y)
            beaconsAtY++;

        d = abs(scanX - beacX) + abs(scanY - beacY);
        delta = Util::max(d - abs(Y - scanY), 0);
        cout << scanX << " " << scanY << " "
             << beacX << " " << beacY << " "
             << d << " " << delta << endl;

        for (int x = scanX - delta; x < scanX + delta; x++)
        {
            noBeacons.insert(x);
        }
    }

    cout << (noBeacons.size() - beaconsAtY);

}

using namespace Util;

void Solver::part02(vector<string> input)
{
    // unordered_set<long> beacons = unordered_set<long>();
    const long Y = 2000001;
    //const long Y = 11;
    uint beaconsAtY = 0;

    uint64_t count = 0;

    vector<vec2> scanners;
    vector<vec2> beacons;
    vector<long> widths;
    vector<string> split;
    // int count
    for (string s : input)
    {
        //cout << s << endl;
        split = Util::split(s, " ");

        //cout << split[2] << " " << split[3] << " " << split[8] << " " << split[9] << endl;

        scanners.push_back( vec2 (
            stoi(split[2].substr(2, split[2].length() - 1)),
            stoi(split[3].substr(2, split[3].length() - 1))
        ));

        beacons.push_back( vec2 (
            stoi(split[8].substr(2, split[8].length() - 1)),
            stoi(split[9].substr(2, split[9].length() - 1))
        ));
    }

    for (int i = 0; i < scanners.size(); i++)
    {
        widths.push_back(   abs(scanners[i].x - beacons[i].x) +
                            abs(scanners[i].y - beacons[i].y)   );
    }

    vector<long> beaconPartitions;
    long d;
    for (int y = 0; y < 4000000; y++) 
    {
        if (y % 100 == 0)
            cout << y / 4000000.0 << "%" << endl;

        beaconPartitions.clear();
        for (int i = 0; i < scanners.size(); i++)
        {
            d = abs(y - scanners[i].y);
            if (d < widths[i])
            {
                
            }
        }
    }
}
