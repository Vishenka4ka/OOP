#include <cassert>
#include <functional>
#include <iostream>
#include <fstream>
#include <optional>
#include <string>

using namespace std;

struct Args 
{
	char *inputNumber;
};

using Callback = function<void()>;

optional<Args> ParseArgs(
	int argc,
	char* argv[],
	const Callback& argsCountCallback = Callback(),
	const Callback& numberIsEmptyCallback = Callback())
{
	if (argc != 2)
	{
		argsCountCallback();

		return nullopt;
	}

	if (!*argv[1])
	{
		numberIsEmptyCallback();

		return nullopt;
	}

	Args args;
	args.inputNumber = argv[1];

	return args;
};

bool CheckArguments(
	optional<Args> args)
{
	if (!args)
	{
		return 0;
	}
};

bool CheckNumber(
	char *end,
	long Number,
	const Callback& wrongNotationCallback = Callback(),
	const Callback& wrongRangeCallback = Callback())
{
	if (*end)
	{
		wrongNotationCallback();
	
		return 0;
	}
	
	if (Number > 255 || Number < 0)
	{
		wrongRangeCallback();

		return 0;
	}
}

void ReverseByte(long& Number)
{
	long changedNumber = 0;
	for (int i = 0; i < 4; i++)
	{
		changedNumber +=
			(((Number >> i) & 1) << (7 - i)) + 
			(((Number >> (7 - i)) & 1) << i);
	}
	cout << changedNumber << "\n";
};

void PrintArgumentsCountErrors()
{
	cout << "Invalid arguments count\n";
	cout << "Usage: flipbyte.exe <number>" << endl;
};

void PrintNumberIsEmptyError()
{
	cout << "Invalid arguments\n";
	cout << "Number can't be empty" << endl;
};

void PrintWrongNotationError()
{
	cout << "Number must be in decimal notation" << endl;
};

void PrintWrongRangeError()
{
	cout << "Number must be in the range from 0 to 255" << endl;
};


int main(int argc, char* argv[])
{
	auto args = ParseArgs(
		argc, 
		argv, 
		PrintArgumentsCountErrors, 
		PrintNumberIsEmptyError);

	if (!CheckArguments(args))
	{
		return 1;
	}

	char* end;
	long Number = strtol(args->inputNumber, &end, 10);

	if (!CheckNumber(
		end, 
		Number, 
		PrintWrongNotationError, 
		PrintWrongRangeError))
	{
		return 1;
	}

	ReverseByte(Number);
 
	return 0;
}