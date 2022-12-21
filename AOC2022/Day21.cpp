#include "Day21.h"
#include "Util.h"

/*
* -------------------------------------------------------------------------------------------------------------------------
*													Monkey Constructors
* -------------------------------------------------------------------------------------------------------------------------
 */

Day21::Monkey::Monkey() : hasValue(true), value(0), left(""), right(""), operation(' '), humnDependent(false) {}
Day21::Monkey::Monkey(int value) : hasValue(true), value(value), left(""), right(""), operation(' '), humnDependent(false) {}
Day21::Monkey::Monkey(char op, string left, string right) : hasValue(false), value(0), left(left), right(right), operation(op), humnDependent(false) {}


/*
* -------------------------------------------------------------------------------------------------------------------------
*													Recursive Evaluations
* -------------------------------------------------------------------------------------------------------------------------
 */


/*
* For each theoretical monkey, check if he is the human in reality or if he is dependent on his value
*/
bool Day21::humn(string monkey)
{
	Monkey* m = &monkeys[monkey];
	if (monkey == "humn")
	{
		m->humnDependent = true;
		return true;
	}
	if (m->hasValue)
		return false;

	m->humnDependent = humn(m->left) || humn(m->right);
	return m->humnDependent;
}

/*
* Evaluate through each monkey's operations and values
*/
int64_t Day21::eval(string monkey)
{
	Monkey m = monkeys[monkey];
	if (m.hasValue)
		return m.value;

	int64_t lvalue = eval(m.left);
	int64_t rvalue = eval(m.right);
	if (m.operation == '+')
		return lvalue + rvalue;
	if (m.operation == '-')
		return lvalue - rvalue;
	if (m.operation == '*')
		return lvalue * rvalue;
	if (m.operation == '/')
		return lvalue / rvalue;
	cerr << "monkey not real" << endl;
	return 0;
}

/*
* Evaluate through all monkey's operations and values, who are not dependent on the human, if they are, calculate the current number the human has to say and pass it on
*/
int64_t Day21::revEval(string monkey, int64_t other)
{
	if (monkey == "humn")
	{
		return other;
	}

	Monkey m = monkeys[monkey];

	if (monkeys[m.left].humnDependent)
	{
		if (other == INT64_MAX)
			return revEval(m.left, eval(m.right));

		if (m.operation == '+')
			return revEval(m.left, other - eval(m.right));
		if (m.operation == '-')
			return revEval(m.left, other + eval(m.right));
		if (m.operation == '*')
			return revEval(m.left, other / eval(m.right));
		if (m.operation == '/')
			return revEval(m.left, other * eval(m.right));
		cerr << "monkey not real in rev eval (left): " << monkey << endl;
		return 0;
	}

	if (other == INT64_MAX)
		return revEval(m.right, eval(m.left));

	if (m.operation == '+')
		return revEval(m.right, other - eval(m.left));
	if (m.operation == '-')
		return revEval(m.right, eval(m.left) - other);
	if (m.operation == '*')
		return revEval(m.right, other / eval(m.left));
	if (m.operation == '/')
		return revEval(m.right, eval(m.left) / other);
	cerr << "monkey not real in rev eval (right): " << monkey << endl;
	return 0;
}


/*
* -------------------------------------------------------------------------------------------------------------------------
*													Solver Methods
* -------------------------------------------------------------------------------------------------------------------------
 */

int64_t Day21::solvePart1(vector<string> input)
{
	createMonkeys(input);

	return eval("root");
}

int64_t Day21::solvePart2(vector<string> input)
{
	createMonkeys(input);

	return revEval("root", INT64_MAX);
}


/*
* -------------------------------------------------------------------------------------------------------------------------
*													Monkey Creation
* -------------------------------------------------------------------------------------------------------------------------
 */

void Day21::createMonkeys(vector<string> input)
{
	vector<string> split;
	for (string line : input)
	{
		split = Util::split(line, " ");
		if (split.size() == 2)
		{
			monkeys[Util::split(split[0], ":")[0]] = Monkey(stoi(split[1]));
		}
		else
		{
			monkeys[Util::split(split[0], ":")[0]] = Monkey(split[2].at(0), split[1], split[3]);
		}
	}

	humn("root");
}