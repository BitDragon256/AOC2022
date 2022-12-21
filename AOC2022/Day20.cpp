#include <iostream>
#include <algorithm>

#include "Day20.h"

using namespace std;

void Day20::resetNodes(vector<int> values, int64_t key)
{
	nodeCount = values.size();

	/*
	if (nodes != nullptr)
		delete[] nodes;
	*/
		
	nodes = new Node[nodeCount];
	int i = 0;
	for (Node* it = nodes; it < nodes + nodeCount; it++)
	{
		it->set(static_cast<int64_t>(values.at(i)) * key, it + 1, it - 1);
		// it->encryptedValue = values.at(i) * key;
		// cout << it << endl;
		i++;

		if (it->value == 0)
			zero = it;
	}

	nodes->prev = nodes + nodeCount - 1;
	(nodes + nodeCount - 1)->next = nodes;
}

void Day20::move(int index)
{
	long value = nodes[index].value % (nodeCount - 1);

	Node* moveNode = nodes + index;
	Node* node = nodes + index;

	if (value > 0)
	{
		for (long i = 0; i < value; i++)
			node = node->next;

		if (value == 1)
		{
			node->prev = moveNode->prev;
			moveNode->prev->next = node;
		}
		else
		{
			moveNode->prev->next = moveNode->next;
			moveNode->next->prev = moveNode->prev;
		}

		node->next->prev = moveNode;
		moveNode->next = node->next;

		node->next = moveNode;
		moveNode->prev = node;
	}
	else if (value < 0)
	{
		for (long i = 0; i > value; i--)
			node = node->prev;

		if (value == -1)
		{
			node->next = moveNode->next;
			moveNode->next->prev = node;
		}
		else
		{
			moveNode->next->prev = moveNode->prev;
			moveNode->prev->next = moveNode->next;
		}

		node->prev->next = moveNode;
		moveNode->prev = node->prev;

		node->prev = moveNode;
		moveNode->next = node;
	}
}

void Day20::mix()
{
	if (debug)
	{
		cout << "Initial" << endl;
		Node* it = zero;
		for (long i = 0; i < nodeCount; i++)
		{
			cout << it->value << " ";
			it = it->next;
		}
		cout << endl << endl;
	}

	for (int i = 0; i < nodeCount; i++)
	{
		move(i);

		if (debug)
		{
			cout << "Iteration " << i + 1 << endl;
			Node* it = zero;
			for (long i = 0; i < nodeCount; i++)
			{
				cout << it->value << " ";
				it = it->next;
			}
			cout << endl;
		}
	}
	if (debug)
		cout << endl;
}

int Day20::solvePart1(vector<int> values)
{
	resetNodes(values, 1);

	mix();

	int sum = 0;
	Node* it = zero;
	for (int i = 1; i <= 3000; i++)
	{
		it = it->next;
		if (i % 1000 == 0)
		{
			cout << "Adding " << it->value << endl;
			sum += it->value;
		}
	}

	return sum;
}

int64_t Day20::solvePart2(vector<int> values)
{
	resetNodes(values, 811589153);

	for (long i = 0; i < 10; i++)
		mix();

	int64_t sum = 0;
	Node* it = zero;
	for (int i = 1; i <= 3000; i++)
	{
		it = it->next;
		if (i % 1000 == 0)
		{
			cout << "Adding " << it->value << endl;
			sum += it->value;
		}
	}

	return sum;
}