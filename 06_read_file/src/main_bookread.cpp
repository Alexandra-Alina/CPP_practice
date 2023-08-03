﻿#include <iostream>
#include <string>
#include <vector>
#include <fstream>


using namespace std;

class Book
{
public:
	std::string name;
	std::string authors;

	Book(string name, string authors)
	{
	    this->name = name;
	    this->authors = authors;
	}



        void print()
	    {
	       	std::cout << this->name << std::endl;
            std::cout << "\t(by " << this->authors << ")" << std::endl;

	    }
};

/**
	Reads a vector of books from a text file.
	Note: the text file shall contain lines of text in pairs for the book name and authors
	E.g.
		BOOK 1
		AUTHOR 1
		BOOK 2
		AUTHOR 2
		BOOK 3
		AUTHOR 1, AUTHOR 2, AUTHOR 3
	@param file_name The name of the file to read from (must include path).
	@return Vector of books.
*/
std::vector<Book> readBooksFromTextFile(const std::string& file_name)
{
	vector<Book> results;
	ifstream myFile(file_name);
    string carte;
	string autor;

	while(getline(myFile, carte))
    {
        getline(myFile, autor);


		Book myBook = Book(carte, autor);
		results.emplace_back(myBook); // pune cartea la finalul vectorului
    }

	myFile.close();

	return results;
}

int main()
{
	// Read a collection of books from a file.
	// Simple examples can be found everywhere.
	// E.g. https://stackoverflow.com/questions/7868936/read-file-line-by-line-using-ifstream-in-c

	// Read the data
	std::string input_data("../../data/ermahgerd_berks.txt");
	std::cout << "Reading the data from " << input_data << std::endl;
	std::vector<Book> books_from_file = readBooksFromTextFile(input_data);

	// Print the data
	std::cout << "Here are all the books found in the data file..." << std::endl;
	for (auto book : books_from_file)
	{
		book.print();
	}

	return 0;
}
