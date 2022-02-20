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

using ArgumentsCheckCallback = function<void(int argc, string SearchingString)>;

optional<Args> ParseArgs(
	int argc, 
	char* argv[], 
	const ArgumentsCheckCallback& errorsCallback)
{
	if (argc != 3 || argv[2] == "")
	{
		errorsCallback(argc, argv[2]);
		return nullopt;
	}

	Args args;
	args.inputFileName = argv[1];
	args.searchingText = argv[2];
	return args;
}

void ArgumentsErrors(int argc, string searchingString)
{
	if (argc != 3)
	{
		cout << "Invalid arguments count\n";
		cout << "Usage: CopiFile.exe <input file name> <text to search>" << endl;
	}

	if (searchingString == "") 
	{
		cout << "Invalid arguments\n";
		cout << "Searching string can't be empty string" << endl;
	}
};

using InputFileErrorsCallback = function<void(ifstream& input, const string inputFileName)>;

bool InputFileErrorsCheck(
	ifstream& input, 
	const string inputFileName,
	const InputFileErrorsCallback& errorsCallback)
{
	bool errors = false;
	if (!input.is_open() || input.bad())
	{
		errorsCallback(input, inputFileName);
		errors = true;
	}

	return errors;
}

void PrintInputFileErrors(ifstream& input, const string inputFileName)
{
	if (!input.is_open())
	{
		cout << "Failed to open '" << inputFileName << "' for reading" << endl;
	}

	if (input.bad())
	{
		cout << "Failed to read data from input file" << endl;
	}
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
	auto args = ParseArgs(argc, argv, ArgumentsErrors);

	// Открываем входной файл
	ifstream input;
	input.open(args->inputFileName);

	// Проверяем, не возникают ли ошибки при открытии файла 
	// или считывании из него информации
	if (InputFileErrorsCheck(input, args->inputFileName, PrintInputFileErrors))
	{
		return 1;
	}
	
	// Выводим результат поиска строки в файле
	FindStingInStream(input, args->searchingText, PrintFoundLineIndex, PrintMassageIfNoStringFound);

	return 0;
}

