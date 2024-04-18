#pragma once

class Sort
{
    int* elemente;
    int nrElemente;
public:
    Sort(int nrElemente, int min, int max); //c1
    Sort(int nrElemnte, char s); //c2
    Sort(int v[100], int nrElemente);//c3
    Sort(int nrElemente, ...);//c4
    Sort(char s[]);//c5
    ~Sort();
    void InsertSort(bool ascendent = false);
    void QuickSort(bool ascendent = false);
    void BubbleSort(bool ascendent = false);
    void Print();
    int  GetElementsCount();
    int  GetElementFromIndex(int index);
};