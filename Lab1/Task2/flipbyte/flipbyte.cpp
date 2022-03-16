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

//Посмотри, есть ли в сpp унаследоваться от базового исключения
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
	}
	else if (!*argv[1])
	{
		throw ParseArgsException("Invalid arguments\nNumber can't be empty");
	}

	Args args;
	size_t pos{};

	int number = stoi(argv[1], &pos);

	if (argv[1][pos] != '\0')
	{
		throw ParseArgsException("Number must be in decimal notation");
	}
	
	if (number < 0 || number > 255)
	{
		throw ParseArgsException("Number must be in the range from 0 to 255");
	}

	args.inputNumber = number;

	return args;		
};

//задать через тип uint8_t
uint8_t ReverseNumber(uint8_t number)
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
		cout << static_cast<int>(ReverseNumber(args->inputNumber)) << endl;
		
	}
	catch (ParseArgsException& error)
	{
		cout << error.message << endl;
		return 1;
	}
 
	return 0;
}