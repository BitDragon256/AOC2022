#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include "../Util.h"

#include "json.hpp"

using json = nlohmann::json;

using namespace std;

class Solver
{
public:
    void part01(vector<json>);
    void part02(vector<json>);
};

int main()
{
    cout << "Starting" << endl;

    ifstream file("input.txt");

    vector<json> packages;

    if (!file.is_open())
    {
        cerr << "File Error" << endl;
        return -1;
    }
    string line;
    while (getline(file, line))
    {
        if (line == "")
        {
            continue;
        }
        
        packages.push_back(json::parse(line));
    }

    Solver s;
    s.part01(packages);
    s.part02(packages);
}

int8_t dirComp(json left, json right)
{
    if (left == right)
        return 0;
    if (left < right)
        return 1;
    return -1;
}

int8_t compare(json left, json right)
{
    
    // cout << "Comparing " << left << " (" << (left.is_number() ? "number" : "list") << ") and "
    //                      << right << " (" << (right.is_number() ? "number" : "list") << ")" << endl;
    

    if (left.is_number() && right.is_number())
        return dirComp(left, right);

    if (left.is_array() && right.is_array())
    {
        int8_t res;
        for (int i = 0; i < right.size(); i++)
        {
            if (i >= left.size())
                return 1;
            res = compare(left.at(i), right.at(i));
            if (res == 0)
                continue;
            return res;
        }
        if (left.size() == right.size())
            return 0;
        return -1;
    }
    if (left.is_number())
        return compare(json::array( { left } ), right);

    return compare(left, json::array( { right } ));
}

void Solver::part01(vector<json> packages)
{
    uint sum = 0;

    json right, left;
    for (int i = 1; i < packages.size(); i += 2)
    {
        left = packages[i - 1];
        right = packages[i];

        //cout << ((i + 1) / 2) << ": ";

        if (compare(left, right) == -1)
        {
            //cout << "Wrong Order | " << sum << endl;

            continue;
        }
        sum += (i + 1) / 2;

        //cout << "Right Order | " << sum << endl;
    }

    cout << "Part 1: " << sum << endl;
}

void Solver::part02(vector<json> packages)
{
    uint8_t key1 = 1, key2 = 2;
    int8_t res;
    json divPack1 = json::parse("[[2]]"), divPack2 = json::parse("[[6]]");
    for (json j : packages)
    {
        res = compare(j, divPack1);
        if (res == 1)
            key1++;
        
        res = compare(j, divPack2);
        if (res == 1)
            key2++;
    }

    cout << "Part 2: " << key1 * key2 << endl;
}
