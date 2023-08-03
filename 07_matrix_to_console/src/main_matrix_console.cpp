#include <iostream>
#include <string>
#include <vector>

using namespace std;

class Matrix
{
private:
	size_t column_count;
	size_t line_count;

    vector < vector < char > > matrice;

public:
	Matrix(size_t numColumnsX, size_t numLinesY)
	{
		column_count = numColumnsX;
		line_count = numLinesY;

		// matrix[line_count][column_count]
		matrice.assign(line_count, vector<char>(column_count));
	}

	// Set an entire line
	void setLine(size_t line_number, const std::string& data)
	{
	    // primim data ca argument, eliberam linia si o repopulam
		matrice[line_number].clear();
		for (int i = 0; data.c_str()[i]; i++)
			matrice[line_number].push_back(data.c_str()[i]);
	}

	void setCellXY(size_t x, size_t y, char cell_content)
	{
	    if (x < 0 || x >= column_count) return;
		if (y < 0 || y >= line_count) return;
		matrice[y][x] = cell_content;
	}

	void print()
	{
	    for (auto row : matrice) {
			for (auto it : row)
				cout << it;
			cout << endl;
		}

		cout << endl;
	}
};

int main()
{
	// Create a matrix with the width of 20 and height of 10.
	Matrix matrix(20, 10);

	matrix.setLine(0, "X-----X----X-----XX-");
	matrix.setLine(1, "--X-----------------");
	matrix.setLine(2, "-----X--------------");
	matrix.setLine(3, "--------X-----------");
	matrix.setLine(4, "-----------X--------");
	matrix.setLine(5, "--------------X-----");
	matrix.setLine(6, "-----------------X--");
	matrix.setLine(7, "-------------------X");
	matrix.setLine(8, "------------------X-");
	matrix.setLine(9, "-----------------X--");

	matrix.print();
	// Would print
/*
X-----X----X-----XX-
--X-----------------
-----X--------------
--------X-----------
-----------X--------
--------------X-----
-----------------X--
-------------------X
------------------X-
-----------------X--
*/
	matrix.setCellXY(2, 1, '-');
	matrix.print();
	// Would print
/*
X-----X----X-----XX-
--------------------
-----X--------------
--------X-----------
-----------X--------
--------------X-----
-----------------X--
-------------------X
------------------X-
-----------------X--
*/

	matrix.setCellXY(3, 7, 'O');
	matrix.print();
/*
X-----X----X-----XX-
--------------------
-----X--------------
--------X-----------
-----------X--------
--------------X-----
-----------------X--
---O---------------X
------------------X-
-----------------X--
*/

	// This should silently fail (not trigger an error): cell Y=11 invalid due to limited height.
	matrix.setCellXY(3, 11, 'O');
	return 0;
}
