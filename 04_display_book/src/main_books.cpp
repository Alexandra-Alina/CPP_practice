#include <string.h>
#include <iostream>

// Define the maximum length for the name to use.
// Specify the length of characters in the content (Excluding the terminator).
#define MAX_NAME_LEN 10
#define MAX_TITLE_LEN 50

struct Author
{
	//char name[MAX_NAME_LEN + 1];
    char* name = nullptr;

	void setName(char* nameToSet)
	{
		int len = strlen(nameToSet) +1;
		name = (char*)malloc(len);
		strncpy(name, nameToSet, len);
	}

	void print()
	{
		std::cout << name << std::endl;
	}
};

struct Book
{
	int id;
	char title[MAX_TITLE_LEN + 1]; // 50 chr + NULL

	int numAuthors;
	Author authors[5];

	void addAuthor(Author author)
	{
		authors[numAuthors] = author;
		numAuthors++;
	}

	void print()
	{
		std::cout << "Book #" << id << std::endl;
		std::cout << "------" << std::endl;
		std::cout << this->title << std::endl; // nu mai mult de 50 caractere

		// TODO: add all authors
        int i;
		for (i = 0; i < numAuthors; i++)
		{
			std::cout << authors[i].name << std::endl;
		}
		std::cout << std::endl;
	}
};

void setBookName(Book& book, std::string name)
{
    book.title[MAX_TITLE_LEN] = NULL;
	strncpy(book.title, name.c_str(), MAX_TITLE_LEN);
}

void eliberareMem(Book book)
{
    for( int a = 0; a < book.numAuthors; a++)
    {
        free(book.authors[a].name);
    }
}

int main()
{
	Book book1;
	Book book2;
	Book book3;
	Author author;

	// Load the data into books
	book1.id = 1;
	book1.numAuthors = 0;
	setBookName(book1, "The origin of truth");
	author.setName("Gusti");
	book1.addAuthor(author);

	book2.id = 2;
	book2.numAuthors = 0;
	setBookName(book2, "Arhanghelul Raul");
	author.setName("Ovidiu Eftimie");
	book2.addAuthor(author);

	book3.id = 3;
	book3.numAuthors = 0;
	setBookName(book3, "Factfulness");
	author.setName("Hans Rosling");
	book3.addAuthor(author);

	author.setName("Ola Rosling");
	book3.addAuthor(author);

	author.setName("Anna Rosling Ronnlund");
	book3.addAuthor(author);

	// Display the books
	book1.print();
	book2.print();
	book3.print();

	eliberareMem(book1);
	eliberareMem(book2);
	eliberareMem(book3);
	return 0;
}
