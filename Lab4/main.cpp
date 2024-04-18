#include <iostream>
#include "Sort.h"
using namespace std;

int main()
{
    int v[3] = {1, 2, 3};
    Sort s1(10, 3, 100); ///constructorul 1
    s1.Print();
    s1.BubbleSort(true);
    s1.Print();
  
    Sort s2(10, 'A'); ///c 2 (char ul este pt a evita ambiguitatea)
    s2.Print();
    s2.QuickSort(false);
    s2.Print();

    Sort s3(v,3);///c 3
    s3.Print();
    s3.InsertSort(false);
    s3.Print();

    Sort s4(4, 5, 6, 7, 8); ///c 4
    s4.Print(); 
    std::cout << s4.GetElementsCount() << "\n";

    char* s = new char[101] {"10,4,100,70"};
    Sort s5(s); ///c 5
    s5.Print();
    std::cout << s5.GetElementFromIndex(0);
}