#include <cassert>
#include <functional>
#include <iostream>
#include <fstream>
#include <optional>
#include <string>

using namespace std;

struct Args 
{
	//сохранить сразу число в нужном типе
		uint8_t inputNumber;
};

struct ParseArgsException
{
	string message;

	ParseArgsException(const string& message) :
		message(message)
	{}
};

optional<Args> ParseArgs(int argc, char* argv[])
{
	if (argc != 2)
	{
		throw ParseArgsException("Invalid arguments count\nUsage: flipbyte.exe <number>");
		return nullopt;
	}
	else if (!*argv[1])
	{
		throw ParseArgsException("Invalid arguments\nNumber can't be empty");
		return nullopt;
	}

	Args args;
	size_t pos{};

	args.inputNumber = stoi(argv[1], &pos, 10);

	if (argv[1][pos] != '\0')
	{
		throw ParseArgsException("Number must be in decimal notation");
	}
	
	if ((args.inputNumber < 0) || (args.inputNumber > 255))
	{
		throw ParseArgsException("Number must be in the range from 0 to 255");
	}

	return args;		
};

//задать через тип uint8_t
int ReverseNumber(uint8_t number)
{
	uint8_t changedNumber = 0;
	for (int i = 0; i < 4; i++)
	{
		changedNumber +=
			(((number >> i) & 1) << (7 - i)) + 
			(((number >> (7 - i)) & 1) << i);
	}

	return changedNumber;
};

int main(int argc, char* argv[])
{
	try
	{
		auto args = ParseArgs(argc, argv);
		cout << ReverseNumber(args->inputNumber) << "\n";
	}
	catch (ParseArgsException& e)
	{
		cout << e.message << endl;
	}
 
	return 0;
}