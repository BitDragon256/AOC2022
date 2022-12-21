#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

class Solver
{
public:
    void part01(vector<string>);
    void part02(vector<string>);
};

void day3()
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

void Solver::part01(vector<string> input)
{
    int prioritySum = 0, counter = 0;
    for (string r : input)
    {
        /*
        custom, highly complicated random number generator

        const size_t compSize = r.size() / 2;
        const char* rP = r.c_str();
        char* firstComp = new char[compSize];
        for (int i = 0; i < compSize; i++)
        {
            firstComp[i] = (rP[i] < 'a') ? rP[i] - 'A' + 27 : rP[i] - 'a' + 1;
        }
        const char* secondComp = firstComp + compSize;

        for (int i = 0; i < compSize / 2; i++)
        {
            for (int j = 0; j < compSize / 2; j++)
            {
                //cout << (int) firstComp[i] << " " << (int) secondComp[j] << " " << prioritySum << endl;
                if (firstComp[i] == secondComp[j])
                {
                    prioritySum += firstComp[i];
                    i = compSize;
                    j = compSize;
                }
            }
        }

        delete[] firstComp;
        */

       size_t compSize = r.size() / 2;

        for (size_t i = 0; i < compSize; i++)
            for (size_t j = compSize; j < r.size(); j++)
            {
                if (r.at(i) == r.at(j))
                {
                    prioritySum += r.at(i) < 'a' ? r.at(i) - 'A' + 27 : r.at(i) - 'a' + 1;
                    i = compSize, j = r.size();
                }
            }
            // cout << counter << endl;
            counter++;
    }
    cout << prioritySum << endl;
}

void Solver::part02(vector<string> input)
{
    vector<vector<uint8_t>> prios;
    vector<uint8_t> backpack;
    for (string r : input)
    {
       size_t compSize = r.size() / 2;
       prios.push_back(vector<uint8_t>());

        for (size_t i = 0; i < compSize; i++)
            for (size_t j = compSize; j < r.size(); j++)
                if (r.at(i) == r.at(j))
                {
                    backpack.push_back(r.at(i) < 'a' ? r.at(i) - 'A' + 27 : r.at(i) - 'a' + 1);
                    i = compSize, j = r.size();
                }
        
        sort(backpack.begin(), backpack.end());
        prios.push_back(backpack);
    }

    uint16_t sumPrios = 0;
    for (uint16_t i = 0; i < prios.size(); i += 3)
    {
        for (uint16_t j = i + 1; j < i + 3; j++)
        {
            for (uint16_t k = 0; k < prios[0].size(); k++)
            {
                for (uint16_t l = 0; l < prios[j].size(); l++)
                {
                    if (prios[i][k] > prios[j][l])
                        break;
                    if (prios[i][k] == prios[j][l])
                    {
                        sumPrios += prios[i][k];
                        k = prios[0].size();
                        break;
                    }
                }
            }
        }
    }
    
    cout << sumPrios << endl;
}
