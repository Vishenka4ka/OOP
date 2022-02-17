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

optional<Args> ParseArgs(int argc, char* argv[])
{
	if (argc != 3)
	{
		cout << "Invalid arguments count\n";
		cout << "Usage: CopiFile.exe <input file name> <text to search>\n";
		return nullopt;
	}
	Args args;
	args.inputFileName = argv[1];
	args.searchingText = argv[2];
	return args;
}

using FindStringCallback = function<void(int lineIndex)>;

bool FindStingInStream(
	istream& haystack,
	const string& needle,
	const FindStringCallback& callback)
{
	string line;
	bool found = false;
	for (int lineIndex = 1; getline(haystack, line); ++lineIndex)
	{
		auto pos = line.find(needle);
		if (pos != string::npos)
		{
			found = true;
			// Передаем в функцию обратного вызова информацию о
			// первом найденном вхождении подстроки
			if (callback)
			{
				callback(lineIndex);
			}
		}
	}
	return found;
}

void PrintFoundLineIndex(int lineIndex)
{
	cout << lineIndex << endl;
}

int main(int argc, char* argv[])
{
	auto args = ParseArgs(argc, argv);
	// Провекра корректности аргументов командной строки
	if (!args)
	{
		return 1;
	}

	// Открываем входной файл
	ifstream input;
	input.open(args->inputFileName);
	if (!input.is_open())
	{
		cout << "Failed to open '" << args->inputFileName << "' for reading\n";
		return 1;
	}

	if (input.bad())
	{
		std::cout << "Failed to read data from input file\n";
		return 1;
	}

	if (!FindStingInStream(input, args->searchingText, PrintFoundLineIndex))
	{
		cout << "No string found" << endl;
	}

	return 0;
}

