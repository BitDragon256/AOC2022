#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>
#include <thread>
#include "../Util.h"

using namespace std;
using namespace Util;

void ruuuuuuuuuuun(vector<string>);

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

    ruuuuuuuuuuun(input);
}

float done;
const int THREAD_COUNT = 256;
const int WALL_TILES = 256;

const int TILE_COUNT = WALL_TILES * WALL_TILES;
const int THREAD_ = TILE_COUNT / THREAD_COUNT;
void tile(int);


bool intersect(vec2 posA, vec2 posB, long widthA, long widthB)







void ruuuuuuuuuuun(vector<string> input)
{
    long scanX, scanY, beacX, beacY;
    vector<string> split;
    
    vector<vec2> scanners;
    vector<vec2> beacons;
    vector<long> widths;

    for (string s : input)
    {
        split = Util::split(s, " ");

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

    vec2 maxDistPos;
    long maxDist = 0;
    long mag;
    vec2 delta;
    vec2 pos;
    const long SIZE = 4000000;

    for (pos.x = 0; pos.x < SIZE; pos.x += 100000)
    {
        for (pos.y = 0; pos.y < SIZE; pos.y += 100)
        {
            int i = 0;
            for (vec2 scanner : scanners)
            {
                mag = (scanner - pos).sqrMagnitude();
                cout << mag << endl;
                if (mag > maxDist)// && mag > widths[i]*widths[i])
                {
                    maxDist = mag;
                    maxDistPos = pos;
                }
                i++;
            }
        }
    }

    cout << "Distance: " << sqrt(maxDist) << " " << maxDistPos << endl;

    /*
    done = 0;

    string s = ".";
    for (int x = 0; x < 100; x++)
    {
        for (int y = 0; y < 100; y++)
        {
            s = ".";
            for (int i = 0; i < scanners.size(); i++)
            {
                if (abs(scanners[i].x / 40000 - x - y) < widths[i] / 40000 &&
                    abs(scanners[i].y / 40000 - x - y) < widths[i] / 40000)
                {
                    s = "#";
                }
            }
            cout << s;
        }
        cout << endl;
    }

    return;

    vector<thread*> _threads;
    
    for (int i = 0; i < THREAD_COUNT; i++)
    {
        thread* t = new thread(tile, i);
        _threads.push_back(t);
    }

    for (int i = 0; i < THREAD_COUNT; i++)
    {
        _threads[i]->join();
    }

    for (int i = 0; i < THREAD_COUNT; i++)
    {
        delete _threads[i];
    }
    */
}



void tile(int index)
{
    stringstream ss;
    ss << index << " starting" << endl;

    

    done += 1.f / THREAD_COUNT;
    ss.clear();
    ss << index << " done | " << done << endl;
    cout << ss.str();
}
