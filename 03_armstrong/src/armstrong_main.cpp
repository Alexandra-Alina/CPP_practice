#include <iostream>
#include<math.h>
#include<string>

using namespace std;

//vedem cate cifre are - determinam puterea cifrelor din suma
int putere(int number)
{
	int putere_numar = 0;
	while (number > 0)
	{
		number /= 10;
		putere_numar++;
	}
	return putere_numar;
}


// calculam suma de puteri
int sumaCifre(int number)
{
	int putere_numar = putere(number);
	int sum = 0;
	while (number > 0)
	{
		int cifra = number % 10;
		sum = sum + pow(cifra, putere_numar);
		number /= 10;
	}
	return sum;
}

bool isArmstrongNumber(int number)
{
	int suma_cifre = sumaCifre(number);

	return number == suma_cifre;

}

void printIsArmstrong(int number)
{
	if (isArmstrongNumber(number))
	{
		std::cout << "Armstrong" << std::endl;
	}
	else
	{
		std::cout << "NOT Armstrong" << std::endl;
	}
}

int main(int argc, char *argv[])
{
	// Make sure there are some program arguments available.
	if (argc <= 1)
	{
		cout << "No program arguments found." << std::endl;
		return 1;
	}

	// Get the first argument
	string argumentAsString = argv[1];

	// TODO: read number / cast to integer

	int number;

	try
	{
		string::size_type sz;
		number = stoi(argumentAsString, &sz);

		if (!argumentAsString.substr(sz).empty())
		{
			throw invalid_argument("Undefined output");
		}
	}
	catch (const invalid_argument ia)
	{
		cout << ia.what() << endl;
		return 1;
	}

	printIsArmstrong(number);
	return 0;
}
