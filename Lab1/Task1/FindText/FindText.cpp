#include <cassert>
#include <functional> // Необходим для std::function
#include <iostream>
#include <fstream>
#include <optional>
#include <string>

using namespace std;

struct Args
{
	string inputFileName;
	string searchingText;
};

using ArgumentsCheckCallback = function<void()>;

optional<Args> ParseArgs(
	int argc, 
	char* argv[],
	const ArgumentsCheckCallback& callback)
{
	if (argc != 3)
	{
		callback();
		return nullopt;
	}
 
	Args args;
	args.inputFileName = argv[1];
	args.searchingText = argv[2];
	return args;
}

bool InputFileErrorsCheck(ifstream& input, const string inputFileName)
{
	bool errors = false;
	if (!input.is_open() || input.bad())
	{
		errors = true;
	}

	return errors;
}

using FindStringCallback = function<void(int lineIndex)>;
using DontFindStringCallback = function<void()>;

void FindStingInStream(
	istream& input,
	const string& SearchingString,
	const FindStringCallback& foundCallback, 
	const DontFindStringCallback& didntFoundCallback)
{
	string line;
	bool found = false;
	for (int lineIndex = 1; getline(input, line); ++lineIndex)
	{
		auto pos = line.find(SearchingString);
		if (pos != string::npos)
		{
			found = true;
			// Передаем в функцию обратного вызова информацию о
			// первом найденном вхождении подстроки
			if (foundCallback)
			{
				foundCallback(lineIndex);
			}
		}
	}

	if (!found)
	{
		didntFoundCallback();
	}
}

void PrintInputFileErrors(ifstream& input, const string inputFileName)
{
	if (!input.is_open())
	{
		cout << "Failed to open input file for reading" << endl;
	}

	if (input.bad())
	{
		cout << "Failed to read data from input file" << endl;
	}
}

void PrintArgumentsErrors()
{
	cout << "Invalid arguments count\n";
	cout << "Usage: CopiFile.exe <input file name> <text to search>" << endl;
};
void PrintStringIsEmptyError()
{
	cout << "Invalid arguments\n";
	cout << "Searching string can't be empty string" << endl;
};

void PrintFoundLineIndex(int lineIndex)
{
	cout << lineIndex << endl;
}

void PrintMassageIfNoStringFound()
{
	cout << "No string found" << endl;
}

int main(int argc, char* argv[])
{
	auto args = ParseArgs(argc, argv, PrintArgumentsErrors);

	if (!args)
	{
		return 1;
	}

	if (args->searchingText == "")
	{
		PrintStringIsEmptyError();
		return 1;
	}

	ifstream input;
	input.open(args->inputFileName);

	if (InputFileErrorsCheck(input, args->inputFileName))
	{
		PrintInputFileErrors(input, args->inputFileName);
		return 1;
	}
	
	FindStingInStream(
		input, args->searchingText, 
		PrintFoundLineIndex, 
		PrintMassageIfNoStringFound);

	return 0;
}