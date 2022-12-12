#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <functional>
// #include <bits/stdc++.h> 

#include "../Util.h"

#define SOLVING

using namespace std;

class Solver
{
public:
    void part01();
    void part02();
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
    // s.part01();
    s.part02();
}

#ifdef SOLVING

vector<vector<uint64_t>> monkeys = {
    {53, 89, 62, 57, 74, 51, 83, 97},
    {85, 94, 97, 92, 56},
    {86, 82, 82},
    {94, 68},
    {83, 62, 74, 58, 96, 68, 85},
    {50, 68, 95, 82},
    {75},
    {92, 52, 85, 89, 68, 82}
};

vector<function<uint64_t(uint64_t)>> ops = {
    [](uint64_t item) { return item * 3   ; },
    [](uint64_t item) { return item + 2   ; },
    [](uint64_t item) { return item + 1   ; },
    [](uint64_t item) { return item + 5   ; },
    [](uint64_t item) { return item + 4   ; },
    [](uint64_t item) { return item + 8   ; },
    [](uint64_t item) { return item * 7   ; },
    [](uint64_t item) { return item * item; }
};

vector<function<bool(uint64_t)>> tests = {
    [](uint64_t item){ return item % 13 == 0; },
    [](uint64_t item){ return item % 19 == 0; },
    [](uint64_t item){ return item % 11 == 0; },
    [](uint64_t item){ return item % 17 == 0; },
    [](uint64_t item){ return item % 3  == 0; },
    [](uint64_t item){ return item % 7  == 0; },
    [](uint64_t item){ return item % 5  == 0; },
    [](uint64_t item){ return item % 2  == 0; }
};

vector<int> monTrues = {
    1, 5, 3, 7, 3, 2, 7, 0
};

vector<int> monFalses = {
    5, 2, 4, 6, 6, 4, 0, 1
};

uint64_t mod = 9699690;

#endif

#ifdef TESTING

vector<vector<uint64_t>> monkeys = {
    {79, 98},
    {54, 65, 75, 74},
    {79, 60, 97},
    {74}
};

vector<function<uint64_t(uint64_t)>> ops = {
    [](uint64_t item) { return item * 19  ; },
    [](uint64_t item) { return item + 6   ; },
    [](uint64_t item) { return item * item; },
    [](uint64_t item) { return item + 3   ; }
};

vector<function<bool(uint64_t)>> tests = {
    [](uint64_t item){ return item % 23 == 0; },
    [](uint64_t item){ return item % 19 == 0; },
    [](uint64_t item){ return item % 13 == 0; },
    [](uint64_t item){ return item % 17 == 0; }
};

vector<int> monTrues = {
    2, 2, 1, 0
};

vector<int> monFalses = {
    3, 0, 3, 1
};

uint64_t mod = 23 * 19 * 13 * 17;

#endif

void monkey(int index)
{
    int item;
    while (monkeys[index].size() > 0)
    {
        item = monkeys[index][0];
        monkeys[index].erase(monkeys[index].begin());

        item = ops[index](item);
        item /= 3;

        if (tests[index](item))
            monkeys[monTrues[index]].push_back(item);
        else
            monkeys[monFalses[index]].push_back(item);
    }
}

void monkeyWorried(int index)
{
    uint64_t item;
    while (monkeys[index].size() > 0)
    {
        item = monkeys[index][0];
        monkeys[index].erase(monkeys[index].begin());

        item = ops[index](item);
        item = item % mod;

        if (tests[index](item))
            monkeys[monTrues[index]].push_back(item);
        else
            monkeys[monFalses[index]].push_back(item);
    }
}

void Solver::part01()
{
    int* monkeyActivity = new int[monkeys.size()];
    for (int i = 0; i < monkeys.size(); i++)
    {
        monkeyActivity[i] = 0;
    }

    for (int i = 0; i < 20; i++)
    {
        for (int j = 0; j < monkeys.size(); j++)
        {
            monkeyActivity[j] += monkeys[j].size();

            monkey(j);
        }

        for (int j = 0; j < monkeys.size(); j++)
        {
            cout << "monkey " << j << ": ";
            for (int i : monkeys[j])
            {
                cout << i << ", ";
            }
            cout << endl;
        }
        cout << endl;
    }

    sort((monkeyActivity), monkeyActivity + monkeys.size());
    for (int i = 0; i < monkeys.size(); i++)
    {
        cout << monkeyActivity[i] << endl;
    }
    cout << monkeyActivity[monkeys.size() - 1] * monkeyActivity[monkeys.size() - 2] << endl;

    delete[] monkeyActivity;
}

void Solver::part02()
{
    uint64_t* monkeyActivity = new uint64_t[monkeys.size()];
    for (int i = 0; i < monkeys.size(); i++)
    {
        monkeyActivity[i] = 0;
    }

    for (int i = 0; i < 10000; i++)
    {
        for (int j = 0; j < monkeys.size(); j++)
        {
            monkeyActivity[j] += monkeys[j].size();

            monkeyWorried(j);
        }

        if (i != 0 && i != 19 && (i + 1) % 1000 != 0)
            continue;
        for (int j = 0; j < monkeys.size(); j++)
        {
            cout << "monkey " << j << " inspected " << monkeyActivity[j] << " items : ";
            for (uint64_t i : monkeys[j])
            {
                cout << i << ", ";
            }
            cout << endl;
        }
        cout << endl;
    }

    sort((monkeyActivity), monkeyActivity + monkeys.size());
    for (int i = 0; i < monkeys.size(); i++)
    {
        cout << monkeyActivity[i] << endl;
    }
    cout << monkeyActivity[monkeys.size() - 1] * monkeyActivity[monkeys.size() - 2] << endl;

    delete[] monkeyActivity;
}
