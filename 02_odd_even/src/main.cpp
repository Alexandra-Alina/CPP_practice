#include <stdio.h>
#include <iostream>
#include <string>

void printOddOrEven(int number)
{
	if (number % 2 == 0)
	{
		printf("EVEN\n");
	}
	else
	{
		printf("ODD\n");
	}
}

int main(int argc, char *argv[])
{
	int number = -13;

	// Make sure there are some program arguments available.
	if (argc <= 1)
	{
		printf("No program arguments found.\n");
	}

	// Get the first argument
	std::string argumentAsString = argv[1];
	const char* argumentAsCharArray = argumentAsString.c_str();


    try
    {
        int number = std::stoi(argumentAsString);
        printOddOrEven(number);
    }
    catch (const std::invalid_argument ia)
    {
        std::cout << "NAN";
    }

	return 0;
}
