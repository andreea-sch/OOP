#include "Canvas.h"
#include <iostream>

using namespace std;

Canvas::Canvas(int width, int height) ///constructor
{
	this->width = width; 
	this->height = height;
	this->matrix = new char* [height];///alocam dinamic memorie 
	///Creeaza o matrice în care fiecare element este un pointer catre un tablou de caractere alocat dinamic.
	for (int i = 0; i < height; ++i) ///parcurgem fiecare rand al matricei
	{
		this->matrix[i] = new char[width]; 
		for (int j = 0; j < width; ++j) 
			matrix[i][j] = ' '; 
	}
}

void Canvas::DrawCircle(int x, int y, int ray, char ch) ///(x,y) coordonatele centului, raza, caracterul pt contur
{
	for(int i=0;i<this->height;++i) ///parcurgem toata matricea
		for (int j = 0; j < this->width; ++j)
		{
			///pentru fiecare lunct calulam distanta dintre el si centrul cercului cu formula distantei
			double distanta = sqrt((i - x) * (i - x) + (j - y) * (j - y));
			if (abs(distanta - ray) < 0.5) ///daca se afla pe conturul cercului (distanta este aproximativ egala cu raza)
				this->matrix[i][j] = ch;///il coloram
		}
}

void Canvas::FillCircle(int x, int y, int ray, char ch)
{
	for (int i = 0; i < this->height; ++i) ///parcurgem toata matricea
		for (int j = 0; j < this->width; ++j)
		{
			///pentru fiecare punct calculam distanta dintre el si centrul cercului cu formula distantei
			double distanta = sqrt((i - x) * (i - x) + (j - y) * (j - y));
			if (abs(distanta - ray) <= ray) ///daca se afla in interiorul cercului
				this->matrix[i][j] = ch;///il coloram
		}
}

void Canvas::DrawRect(int left, int top, int right, int bottom, char ch) ///st sus - dr jos, desenam cu car ch marginile dreptunghiului
{
	for (int i = left; i <= right; ++i) ///coloram marginile orizontale
	{
		this->SetPoint(top, i, ch); ///sus
		this->SetPoint(bottom, i, ch);///jos
	}
	for (int i = top; i <= bottom; ++i) ///coloram marginile verticale
	{
		this->SetPoint(i, left, ch);///stg
		this->SetPoint(i, right, ch);///drp
	}
}

void Canvas::FillRect(int left, int top, int right, int bottom, char ch) ///umplem dreptunghiul
{
	for (int i = top; i <= bottom; ++i) ///liniile de sus in jos
		for (int j = left; j <= right; ++j) ///coloanele de la stg la drp
			this->SetPoint(i, j, ch);
}

void Canvas::SetPoint(int x, int y, char ch)
{
	if (x >= 0 && x < this->width && y >= 0 && y < this->height) ///daca nu iese din matrice
		this->matrix[x][y] = ch; ///il coloram
}

void Canvas::DrawLine(int x1, int y1, int x2, int y2, char ch) ///desenam liniile cu algoritmul Bresenham
{
	int dx = abs(x2 - x1);
	int dy = abs(y2 - y1);
	int sx = (x1 < x2) ? 1 : -1;
	int sy = (y1 < y2) ? 1 : -1;
	int err = dx - dy;
	while (x1 != x2 || y1 != y2) 
	{
		this->matrix[x1][y1] = ch;
		int e2 = 2 * err;
		if (e2 > -dy) 
		{
			err -= dy; x1 += sx;
		}
		if (e2 < dx) 
		{
			err += dx; y1 += sy;
		}
	}
}

void Canvas::Print() // afisam matricea
{
	for (int i = 0; i < this->height; ++i)
	{
		for (int j = 0; j < this->width; ++j) cout << matrix[i][j] << " ";
		cout << "\n";
	}
}

void Canvas::Clear() // refacem matricea initiala
{
	for (int i = 0; i < this->height; ++i)
		for (int j = 0; j < this->width; ++j)
			matrix[i][j] = ' ';
}