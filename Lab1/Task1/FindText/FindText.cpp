#include <cassert>
#include <functional> 
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

using Callback = function<void(const string& outMessage)>;

optional<Args> ParseArgs(
	int argc, 
	char* argv[],
	const Callback& printCountArgsErrors = Callback())
{
	//1. �������� ��� ��������� ��������� callback | �������
	if (argc != 3)
	{
		printCountArgsErrors(
			"Invalid arguments count\nUsage: CopiFile.exe <input file name> <text to search>\n");
		return nullopt;
	}
 
	Args args;
	args.inputFileName = argv[1];
	args.searchingText = argv[2];
	return args;
}

// ����� empty | �������
bool CheckArgumentsErrors(
	const optional<Args>& args,
	const Callback& printMessage = Callback())
{
	bool isErrors = false;

	if (!args)
	{
		return true;
	}

	if (args->searchingText.empty())
	{
		printMessage("Invalid arguments\nSearching string can't be empty string\n");
		isErrors = true;
	}

	return isErrors;
};

//3. � ��������� ������� ����� ������������ ������ 
// (���������� ��������(��������: ���������..���-��)) | �������
bool CheckFileErrors(
	ifstream& input, 
	const Callback& printMessage = Callback())
{
	bool isErrors = false;
	if (!input.is_open() || input.bad())
	{
		if (!input.is_open())
		{
			printMessage("Failed to open input file for reading\n");
		}

		if (input.bad())
		{
			printMessage("Failed to read data from input file\n");
		}

		isErrors = true;
	}

	return isErrors;
}

using FindStringCallback = function<void(int& lineIndex)>;

void FindStingInStream(
	istream& input,
	const string& searchingString,
	const Callback& printMessage = Callback(),
	const FindStringCallback& printLineIndex = FindStringCallback())
{
	string line;

	// ������ ����� �������� ������� � ������-�� ������� (is, can � �.�) | �������
	bool isFound = false;
	for (int lineIndex = 1; getline(input, line); ++lineIndex)
	{
		auto pos = line.find(searchingString);
		if (pos != string::npos)
		{
			isFound = true;

			//4. ����� ���������� �� ������ ��������
			// ���������� ����� | �������
			printLineIndex(lineIndex);
		}
	}
	
	if (!isFound)
	{
		printMessage("No string found\n");
	}
}

//2. �������� ��� ����� ������� ��� ����� ��� �������� ������� �����������
// �� �������� ������ ��������� � ���������� ������ | �������
void PrintMessage(const string& outMessage)
{
	cout << outMessage;
};

void PrintLineIndex(const int& lineIndex)
{
	cout << lineIndex << "\n";
};

int main(int argc, char* argv[])
{
	auto args = ParseArgs(argc, argv, PrintMessage);

	if (CheckArgumentsErrors(args, PrintMessage))
	{
		return 1;
	}

	ifstream input;
	input.open(args->inputFileName);

	if (CheckFileErrors(input, PrintMessage))
	{
		return 1;
	}
	
	FindStingInStream(input, args->searchingText, PrintMessage, PrintLineIndex);

	return 0;
}