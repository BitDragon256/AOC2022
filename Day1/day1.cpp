#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

void day1()
{
    cout << "start" << endl;

    ifstream file("input.txt");

    if (file.is_open())
    {
        vector<int> calories;
        bool newElf = true;
        string line;
        while (getline(file, line))
        {
            if (line.size() == 0)
            {
                newElf = true;
                continue;
            }
            
            if (newElf)
            {
                calories.push_back(stoi(line));
                newElf = false;
            }
            else
            {
                calories[calories.size() - 1] += stoi(line, nullptr, 10);
            }
        }

        // Part 1
        int max = 0;
        for (int c : calories)
        {
            if (c > max)
                max = c;
        }

        cout << max << endl;

        // Part 2
        int top3[3] = { 0,0,0 };
        for (int c : calories)
        {
            cout << c;
            for (int i = 0; i < 3; i++)
            {
                cout << " | " << top3[i];
                if (c > top3[i])
                {
                    for (int j = 2; j >= i + 1; j--)
                    {
                        top3[j] = top3[j - 1];
                    }
                    top3[i] = c;
                    break;
                }
            }
            cout << endl;
        }

        int topSum = 0;
        for (int v : top3)
        {
            topSum += v;
        }
        cout << topSum << endl;
    }
    else
    {
        cout << "error with file" << endl;
    }
}