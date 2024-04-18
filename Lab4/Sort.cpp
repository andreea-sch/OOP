#define _CRT_SECURE_NO_WARNINGS
#include "Sort.h"
#include <iostream>
#include <cstdarg>
#include <cstring>

using namespace std;

Sort::Sort(int nrElemente, int min, int max) ///constructor 1
{
    this->nrElemente = nrElemente;
    elemente = new int[nrElemente];
    for (int i = 0; i < nrElemente; i++)
        ///elemente[i] = (((int)&elemente) % max) + min; /// pseudo-random
        elemente[i] = min + rand() % (max - min + 1);
}

Sort::Sort(int nrElemente, char s) : elemente(new int[nrElemente] {68, 29, 39, 23, 71, 22, 26, 11, 79, 70}) ///constructor 2
{
    this->nrElemente = nrElemente;
} 

Sort::Sort(int v[100], int nrElemente) ///constructor 3
{
    this->nrElemente = nrElemente;
    this->elemente = new int[nrElemente];
    for (int i = 0; i < nrElemente; i++)
        this->elemente[i] = v[i];
}

Sort::Sort(int nrElemente, ...) ///constructor 4
{
    this->nrElemente = nrElemente;
    this->elemente = new int[nrElemente];
    va_list args;
    va_start(args, nrElemente);
    for (int i = 0; i < nrElemente; i++)
        this->elemente[i] = va_arg(args, int);
    va_end(args);
}

Sort::Sort(char s[]) ///constructor 5
{
    char sep[] = ",", *p,cuv[100];
    int n = 0; ///pt a parcurge 
    int v[100]; ///numerele
    p = strtok(s, sep);
    while (p)
    {
        strcpy_s(cuv, p);
        int nr = 0;
        for (int i = 0; i < strlen(cuv); ++i)
        {
            int c = cuv[i] - '0';
            nr = nr * 10 + c;
        }
        v[n] = nr;
        n++;
        p = strtok(0, sep);
    }
    this->nrElemente = n;
    this->elemente = new int[n];
    for (int i = 0; i < n; ++i)
        this->elemente[i] = v[i];
}

Sort::~Sort()
{
    delete[] this->elemente;
}

void Sort::InsertSort(bool ascendent)
{
    int nr;
    if (ascendent == false) nr = 1;
    else nr = -1;
    for (int i = 0; i < this->nrElemente; i++)
    {
        int aux = this->elemente[i];
        int j = i - 1;
        while (j >= 0 && nr * this->elemente[j] < nr * aux)
            this->elemente[j + 1] = this->elemente[j], j--;
        elemente[j + 1] = aux;
    }

}

int Pivotare(int* elemente, int st, int dr, bool ascendent)
{
    int nr, aux1, aux2;
    if (ascendent == false) nr = 1;
    else nr = -1;

    int i, j, pasi, pasj;
    i = st; j = dr;
    pasi = 0; pasj = 1;
    while (i < j)
    {
        if (nr * elemente[i] < nr * elemente[j])
        {
            aux1 = elemente[i];
            elemente[i] = elemente[j];
            elemente[j] = aux1;

            aux2 = pasi;
            pasi = pasj;
            pasj = aux2;
        }
        i = i + pasi;
        j = j - pasj;
    }
    return i;
}

void QS(int* elemente, int st, int dr, bool ascendent)
{
    if (st < dr)
    {
        int p = Pivotare(elemente, st, dr, ascendent);
        QS(elemente, st, p - 1, ascendent);
        QS(elemente, p + 1, dr, ascendent);
    }
}

void Sort::QuickSort(bool ascendent)
{
    QS(this->elemente, 0, this->nrElemente - 1, ascendent);
}

void Sort::BubbleSort(bool ascendent)
{
    int nr;
    if (ascendent == false) nr = 1;
    else nr = -1;
    bool OK = 0;
    int aux;
    while (OK == 0)
    {
        OK = 1;
        for (int i = 0; i < this->nrElemente - 1; i++)
            if (nr * elemente[i] < nr * elemente[i + 1])
            {
                aux = elemente[i];
                elemente[i] = elemente[i + 1];
                elemente[i + 1] = aux;
                OK = 0;
            }
    }
}


void Sort::Print()
{
    for (int i = 0; i < this->nrElemente; ++i)
        cout << elemente[i] << " ";
    cout << "\n";
}

int  Sort::GetElementsCount()
{
    return this->nrElemente;
}

int  Sort::GetElementFromIndex(int index)
{
    if (index >= 0 && index < this->nrElemente)
        return elemente[index];
    else return -1;
}