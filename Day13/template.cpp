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
    void part01(vector<string>);
    void part02(vector<string>);
};

int main()
{
    cout << "Starting" << endl;

    ifstream file("input.txt");

    vector<string> input;

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
        
        input.push_back(line);
    }

    Solver s;
    s.part01(input);
    s.part02(input);
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
    
    cout << "Comparing " << left << " (" << (left.is_number() ? "number" : "list") << ") and "
                         << right << " (" << (right.is_number() ? "number" : "list") << ")" << endl;
    

    if (left.is_number() && right.is_number())
    {
        return dirComp(left, right);
    }
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
    {
        // if (right.size() > 1)
        //     return 1;
        // if (right.size() == 0)
        //     return -1;
        // return dirComp(left, right.at(0));

        return compare(json::array( { left } ), right);
    }

    // if (left.size() > 1)
    //     return -1;
    // if (left.size() == 0)
    //         return 1;
    // return dirComp(left.at(0), right);

    return compare(left, json::array( { right } ));
}

void Solver::part01(vector<string> input)
{
    uint sum = 0;

    string line, nextLine;
    for (int i = 1; i < input.size(); i += 2)
    {
        line = input[i - 1], nextLine = input[i];
        //cout << i << endl << line << endl << nextLine << endl;

        json right, left;
        left = json::parse(line);
        right = json::parse(nextLine);

        cout << ((i + 1) / 2) << ": ";
        if (compare(left, right) == -1)
        {
            cout << "Wrong Order | " << sum << endl;
            continue;
        }
        sum += (i + 1) / 2;
        cout << "Right Order | " << sum << endl;
    }

    cout << "Part 1: " << sum << endl;
}

void Solver::part02(vector<string> input)
{
    
}
