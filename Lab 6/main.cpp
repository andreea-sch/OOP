#include <iostream>
#include <cstdlib> 
#include <cstring>
#include "PowerPuffGirl.h"
#include "Profesor.h"
#include "MojoJojo.h"
using namespace std;

void Battle(Profesor& profesor, MojoJojo mojojojo)
{
    profesor.AddGirls();
    int fetite_initial = profesor.GetNr();
    int nr_ture = 0;
    while (mojojojo.GetHealth() > 0 && profesor.GetNr() > 0) 
    {
        nr_ture++;
        int putere = profesor.Damage_total();
        mojojojo.Atac(putere);
        int nr = rand() % profesor.GetNr(); 
        int x = profesor.GetGirlHealth(nr) - mojojojo.GetDamage();
        if (x < 0) x = 0;
        profesor.Mod_health(nr, x);
        if (x == 0) 
        {
            profesor.Mod_vector(nr);
        }
    }
    cout << "Castigatorul este ";
    if (mojojojo.GetHealth() == 0) cout << "Profesorul" << "\n";
    else cout << "MojoJojo" << "\n";
    cout << "Lupta a durat " << nr_ture << " ture" << "\n";
    cout << "Au murit " << fetite_initial - profesor.GetNr() << " fetite" << "\n";
}

void Statistica(Profesor profesor, MojoJojo mojojojo)
{
    cout << "Au supravietuit " << profesor.GetNr() << " fetite:" << "\n";
    if (profesor.GetNr() != 0)
    {
        for (int i = 0; i < profesor.GetNr(); ++i)
            if (profesor.GetGirlHealth(i) != 0)
                cout << "Fetita " << i << " cu health " << profesor.GetGirlHealth(i) << "\n";
    }
}

int main()
{
    char ingredients[50][50] = { "sugar", "spice", "spice", "everything_nice", "sugar", "everything_nice" };
    Profesor profesor(6, ingredients);
    MojoJojo mojojojo(5);
    Battle(profesor, mojojojo);
    Statistica(profesor, mojojojo);
    return 0;
}