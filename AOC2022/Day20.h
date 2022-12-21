#pragma once

#include <vector>
#include <cstdint>

using namespace std;

struct Node
{
	Node* next;
	Node* prev;
	int64_t value;
	// long encryptedValue;

	Node() : value(0), next(nullptr), prev(nullptr) {}
	void set(int64_t v, Node* n, Node* p) { value = v; next = n; prev = p; }
};

class Day20
{
private:
	Node* nodes;
	Node* zero;
	long nodeCount;
public:
	bool debug;

	void resetNodes(vector<int>, int64_t);
	void move(int);
	void mix();

	int solvePart1(vector<int>);
	int64_t solvePart2(vector<int>);
};