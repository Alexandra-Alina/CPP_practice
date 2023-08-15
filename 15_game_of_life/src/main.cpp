#include <iostream>
#include <vector>
#include <chrono>
#include<windows.h>

using namespace std::chrono; // nu am gasit alternativa, sorry:(, o sa mai ma doctumentez

//vectori de directie (offset-uri pentru toti cei 8 vecini)
int dx[] = { -1, -1, -1, 0, 1, 1, 1, 0 };
int dy[] = { -1, 0, 1, 1, 1, 0, -1, -1 };

enum Shapes
{
	BLOCK,
	BOAT,
	BLINKER,
	BEACON,
	PULSAR,
	PENTADECATHLON,
	SPACESHIP

};

class Matrix
{
private:

	int height, width;
	std::vector < std::vector < bool > > matrice; // avem doua valori - alb ->0/ negru ->1
	void setCell(int x, int y, int valoare)
	{
		// verificam daca X si Y sunt in limite
		if (x < 0 || x >= width)
		{
			return;
		}
		if (y < 0 || y >= height)
		{
			return;
		}


		//0 -> F <=> dead
		//alt numar -> T <=> alive

		//convertim din int in bool
		matrice[y][x] = valoare ? true : false;
	}

	int getCell(int x, int y)
	{
		// verificam daca x si y sunt in limite
		if (x < 0 || x >= width)
		{
			return 0; // pentru cand avem vecini in afara matricei
		}
		if (y < 0 || y >= height)
		{
			return 0;
		}

		//convertim din bool in int
		return matrice[y][x] ? 1 : 0;
	}



public:
	Matrix(int height, int width)
	{
		this->height = height;
		this->width = width;
		// alocam spatiu pentru o matrice de tipul matrice[height][width]
		matrice.assign(height, std::vector<bool>(width));
	}

	void nextFrame()
	{
		std::vector < std::vector <bool> > matrice_noua(height, std::vector <bool>(width));

		for (int y = 0; y < height; y++)
			for (int x = 0; x < width; x++)
			{
				int counter = 0; // numaram cati vecini sunt in viata

				// verificam cei 8 vecini
				for (int k = 0; k < 8; k++)
				{
					int nx = x + dx[k];
					int ny = y + dy[k];

					// getCell == 1 - vecinul e in viata
					counter += getCell(nx, ny);
				}
				if (matrice[y][x] == true)
				{
					if (counter == 2 || counter == 3)
					{
						matrice_noua[y][x] = true;
					}
					else
					{
						matrice_noua[y][x] = false;
					}
				}
				else // matrice == false
					if (counter == 3)
					{
						matrice_noua[y][x] = true;
					}
					else
					{
						matrice_noua[y][x] = false;
					}
			}
		matrice.clear();
		matrice = matrice_noua;
	}

	void DrawShape(Shapes shape, int start_x, int start_y)
	{
		int size_x, size_y;
		std::vector < std::vector <int> > shape_matrice;

		switch (shape)
		{
		case BLOCK:
			size_x = 2, size_y = 2;
			shape_matrice = { {1, 1},
							  {1, 1} };
			break;

		case BOAT:
			size_x = 3, size_y = 3;
			shape_matrice = { {1, 1, 0},
							  {1, 0, 1},
							  {0, 1, 0} };
			break;

		case BLINKER:
			size_x = 3, size_y = 1;
			shape_matrice = { {1, 1, 1} };

			break;

		case BEACON:
				size_x = 4, size_y = 4;
				shape_matrice = { {1, 1, 0, 0},
								  {1, 0, 0, 0},
								  {0, 0, 0, 1},
								  {0, 0, 1, 1} };
				break;

			case PULSAR:
				size_x = 15, size_y = 15;
				shape_matrice = { {0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0},
								  {0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0},
								  {0, 0, 0, 0, 1, 1, 0, 0, 0, 1, 1, 0, 0, 0, 0},
								  {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
								  {1, 1, 1, 0, 0, 1, 1, 0, 1, 1, 0, 0, 1, 1, 1},
								  {0, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 0},
								  {0, 0, 0, 0, 1, 1, 0, 0, 0, 1, 1, 0, 0, 0, 0},
								  {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
								  {0, 0, 0, 0, 1, 1, 0, 0, 0, 1, 1, 0, 0, 0, 0},
								  {0, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 0},
								  {1, 1, 1, 0, 0, 1, 1, 0, 1, 1, 0, 0, 1, 1, 1},
								  {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
								  {0, 0, 0, 0, 1, 1, 0, 0, 0, 1, 1, 0, 0, 0, 0},
								  {0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0},
								  {0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0}, };
				break;

			case PENTADECATHLON:
					size_x = 10; size_y = 3;
					shape_matrice = { {0, 0, 1, 0, 0, 0, 0, 1, 0, 0},
									  {1, 1, 0, 1, 1, 1, 1, 0, 1, 1},
									  {0, 0, 1, 0, 0, 0, 0, 1, 0, 0} };
					break;

				case SPACESHIP:

					size_x = 3, size_y = 3;
					shape_matrice = { {0, 1, 0},
									  {0, 0, 1},
									  {1, 1, 1} };
					break;
		};

		for (int y = 0; y < size_y; y++)
		{
			for (int x = 0; x < size_x; x++)
			{
				setCell(start_x + x, start_y + y, shape_matrice[y][x]);
			}
		}
	}

	void print()
	{
		for (int y = 0; y < height; y++)
			for (int x = 0; x < width; x++)
			{
				std::cout << (matrice[y][x] ? 'X' : '-') << " \n"[x == width - 1]; // Printeaza ' ' if x != width-1 else  '\n'
			}
		std::cout << std::endl;
	}

};



int main()
{
	int n = 20, m = 20;
	int frame_count = 15; // cea mai mare perioada

	Matrix matrice = Matrix(n, m);
	// test pt static si oscilator de perioada 2
	/*
	matrice.DrawShape(BLOCK, 2, 2);
	matrice.DrawShape(BOAT, 2, m-5);
	matrice.DrawShape(BLINKER, n-5, 3);
	matrice.DrawShape(BEACON, n-6, m-6);
	*/

	// test pt pulsar
	matrice.DrawShape(PULSAR, n / 2 - 15 / 2, m / 2 - 15 / 2); //urcam cu jumatate din toata forma ca sa o centram in mijloc

	// test pt pentadecathlon
	// matrice.DrawShape(PENTADECATHLON, n/2 - 10/2, m/2 - 3/2);

	// test pt spaceship
	/*
	matrice.DrawShape(SPACESHIP, 2, 2);
	matrice.DrawShape(SPACESHIP, 8, 2);
	*/
	std::cout << "Matricea initiala:" << std::endl;
	matrice.print();

	for (int i = 0; i < frame_count; ++i)
	{
		matrice.nextFrame();
		Sleep(1500);
		system("cls");
		if( i == 0)
            std::cout << "Matricea dupa " << i + 1 << " frame:" << std::endl;
        else
            std::cout << "Matricea dupa " << i + 1 << " frame-uri:" << std::endl;
		matrice.print();

	}

	return 0;
}

