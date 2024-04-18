#include <iostream>
#include "Canvas.h"
using namespace std;

int main()
{
	Canvas canvas(30, 30);
	canvas.DrawLine(10, 10, 20, 20, '*');
	canvas.Print();
	canvas.Clear();
	canvas.DrawCircle(15, 15, 5, '*');
	canvas.Print();
	canvas.Clear();
	canvas.FillCircle(15, 15, 5, '*');
	canvas.Print();
	canvas.Clear();
	canvas.DrawRect(10, 10, 20, 20, '@');
	canvas.Print();
	canvas.Clear();
	canvas.FillRect(10, 10, 20, 20, '&');
	canvas.Print();
}