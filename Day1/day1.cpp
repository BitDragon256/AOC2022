#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

int main()
{
    cout << "start" << endl;

    ifstream file("./input.txt");

    if (file.is_open())
    {
        vector<int> calories;
        bool newElf = false;
        string line;
        while (getline(file, line))
        {
            if (line == "")
            {
                newElf = true;
                continue;
            }

            if (newElf)
                calories.push_back(stoi(line));
            else
            {
                calories[calories.size()] += stoi(line);
            }
        }
        int max = 0;
        for (int c : calories)
        {
            if (c > max)
                max = c;
        }

        cout << max << endl;
    }
    else
    {
        cout << "error with file" << endl;
    }
}