#pragma once
#include <vector>
#include <string>
#include <map>
#include <cstdint>

using namespace std;

class Day21
{
public:
	struct Monkey
	{
		int value;
		bool hasValue;
		bool humnDependent;
		string left;
		string right;
		char operation;

		Monkey();
		Monkey(int);
		Monkey(char, string, string);

	};
	bool humn(string);
	int64_t eval(string);
	int64_t revEval(string, int64_t);

	bool debug;
	map<string, Monkey> monkeys;
	int64_t solvePart1(vector<string>);
	int64_t solvePart2(vector<string>);
	void createMonkeys(vector<string>);
};

